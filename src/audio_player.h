#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <pulse/simple.h>
#include <pulse/error.h>
#include <string>
#include <vector>

class AudioPlayer{
public:
    AudioPlayer();
    ~AudioPlayer();

    bool loadFile(const std::string& filename);
    void play();
    void pause();
    void stop();
    bool isPlaying() const { return m_isPlaying; };

private:
    bool m_isPlaying;
    pa_simple* m_paSimple; // send audio data to audio hardware
    std::vector<float> m_buffer; // for audio data
    pa_sample_spec m_sampleSpec; // data ( sample_rate, sample_format, number of channels )
    size_t m_position; // track for buffer
};

#endif