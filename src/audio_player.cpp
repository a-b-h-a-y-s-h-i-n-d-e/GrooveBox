#include "audio_player.h"
#include <iostream>
#include <sndfile.h>
#include <thread>
#include <chrono>

AudioPlayer::AudioPlayer()
    : m_paSimple(nullptr), m_isPlaying(false), m_position(0) {

}
AudioPlayer::~AudioPlayer(){
    stop(); 
}

bool AudioPlayer::loadFile(const std::string& filename){
    
    SF_INFO sfInfo;
    SNDFILE* sndFile = sf_open(filename.c_str(), SFM_READ, &sfInfo);
    if(!sndFile){
        std::cerr << "Error opening sound file : " << filename << std::endl;
        return false;
    }

    m_buffer.resize(sfInfo.frames * sfInfo.channels);
    sf_read_float(sndFile, m_buffer.data(), m_buffer.size());
    sf_close(sndFile);

    m_sampleSpec.format = PA_SAMPLE_FLOAT32;
    m_sampleSpec.channels = sfInfo.channels;
    m_sampleSpec.rate = sfInfo.samplerate;

    return true;

}

void AudioPlayer::play() {
    if (m_isPlaying) return;

    int error;
    m_paSimple = pa_simple_new(nullptr, "Groovebox", PA_STREAM_PLAYBACK, nullptr, "playback", &m_sampleSpec, nullptr, nullptr, &error);
    if (!m_paSimple) {
        std::cerr << "Failed to create PulseAudio stream: " << pa_strerror(error) << std::endl;
        return;
    }

    m_isPlaying = true;
    m_position = 0;

    std::thread playbackThread([this]() {
        const size_t BUFFER_SIZE = 1024;
        std::vector<float> chunk(BUFFER_SIZE);

        while (m_isPlaying && m_position < m_buffer.size()) {
            size_t remaining = m_buffer.size() - m_position;
            size_t toWrite = std::min(BUFFER_SIZE, remaining);

            std::copy(m_buffer.begin() + m_position, m_buffer.begin() + m_position + toWrite, chunk.begin());

            int error;
            if (pa_simple_write(m_paSimple, chunk.data(), toWrite * sizeof(float), &error) < 0) {
                std::cerr << "Failed to write to PulseAudio stream: " << pa_strerror(error) << std::endl;
                break;
            }

            m_position += toWrite;

            if (toWrite < BUFFER_SIZE) {
                break;
            }
        }

        if (m_isPlaying) {
            stop();
        }
    });

    playbackThread.detach(); // Detach the thread to allow it to run independently
}


void AudioPlayer::pause() {
    if (!m_isPlaying) return;

    m_isPlaying = false;

    int error;
    if (pa_simple_flush(m_paSimple, &error) < 0) {
        std::cerr << "Failed to flush PulseAudio stream: " << pa_strerror(error) << std::endl;
    }
}

void AudioPlayer::stop() {
    if (m_paSimple) {
        m_isPlaying = false;

        pa_simple_free(m_paSimple);
        m_paSimple = nullptr;
    }
}