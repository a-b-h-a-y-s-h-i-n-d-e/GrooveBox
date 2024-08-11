#include "player.h"
#include <ncurses.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <filesystem>
#include "audio_player.h"

MusicPlayer::MusicPlayer() : symbol('>'), currentMode(NORMAL){

}


void MusicPlayer::run(){

    system("printf '\\e[8;24;80t'");
    usleep(100000);

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    resize_term(24, 80);
    clear();
    refresh();
    
    drawBorder();
    displayInputSection();
    userInput();

    clear();
    endwin();
}

void MusicPlayer::drawBorder(){
    clear();
    // Drawing borders
    border('|', '|', '-', '-', '-', '-', '-', '-');
    int height, width;
    getmaxyx(stdscr, height, width);
    total_height = height;
    total_width = width;
    // height -> 24 and width -> 80
    input_section_height = total_height * 0.2;
    display_section_height = total_height * 0.8;
    mvhline(display_section_height + 1, 0, '-', total_width);
    refresh();

}

void MusicPlayer::displayInputSection(){

    // Drawing widgets now
    // input box
    mvprintw(display_section_height + 2, 2, "Song name: ");
    mvprintw(display_section_height + 2, 13, "[                                                  ]");
    mvprintw(display_section_height + 2, 68, "[ Search ]");

    refresh();
}

void MusicPlayer::userInput(){
    char ch;
    currentMode = NORMAL;
    displayMode();
    bool isPlaying = false;

    while(true){
        try{
            ch = getch();
            
            switch (ch){
                case 'i':
                    currentMode = INSERT;
                    displayMode();
                    handleInsertmode();
                    currentMode = NORMAL;
                    displayMode();
                    displaySongs();
                    createSymbol();
                    break;
                
                case 'q':
                    clear();
                    endwin();
                    exit(0);
                    break;

                case '\n':
                    if(!song_list.empty()){
                        if(isPlaying){
                            pauseSong();
                            isPlaying = false;
                            updateSymbol();
                        }else{
                            updateSymbol();
                            playSong(song_list[0]);
                            isPlaying = true;
                            
                        }
                    }   
                    break;
                
                default:
                    break;

            }
        }catch(const std::exception& e){
            // do nothing
            refresh();
        }
        refresh();
    }
}


void MusicPlayer::handleInsertmode(){
    std::string input;
    int ch;
    int cursor_pos = 0;
    const int max_input_length = 50;

    curs_set(1);

    mvhline(1, 3, ' ', 76);
    mvhline(display_section_height + 2, 14, ' ', max_input_length);
    move(display_section_height + 2, 14);
    refresh();

    while(true){

        ch = getch();
        if(ch == '\n')
            break;

        if(ch == KEY_BACKSPACE || ch == 127){
            if(!input.empty() && cursor_pos > 0){
                input.pop_back();
                cursor_pos--;
                mvaddch(display_section_height + 2, 14 + cursor_pos, ' ');
                move(display_section_height + 2, 14 + cursor_pos);
            }
        }
        else if(isprint(ch) && input.length() < max_input_length){
            input.push_back(ch);
            mvaddch(display_section_height + 2, 14 + cursor_pos, ch);
            cursor_pos++;
        }

        refresh();
    }
    curs_set(0);
    refresh();

    std::string command = "python scripts/download_song.py \"" + input + "\"";
    system(command.c_str());


    mvhline(display_section_height + 2, 14, ' ', max_input_length);
    refresh();

}

void MusicPlayer::createSymbol(){
    int y = 2;
    mvaddch(y, total_width - 5, symbol);
    refresh();
}
void MusicPlayer::updateSymbol(){
    if(symbol == '>'){
        symbol = '=';
        int y = 2;
        mvhline(y, total_width - 5, ' ', 1);
        mvaddch(y, total_width - 5, symbol);
        refresh();
    }
    else{
        symbol = '>';
        int y = 2;
        mvhline(y, total_width - 5, ' ', 1);
        mvaddch(y, total_width - 5, symbol);
        refresh();
    }

}


void MusicPlayer::displaySongs(){
    // song_list.clear();
    std::string path = "songs/";
    int y = 2; // starting position to display song name

    for(const auto &entry : std::filesystem::directory_iterator(path)){
        std::string song_name = entry.path().filename().string();
        song_list.push_back(song_name);
        mvhline(y, 2, ' ', total_width - 3);
        mvprintw(y++, 2, song_name.c_str());
    }
    refresh();

}

void MusicPlayer::displayMode(){
    mvhline(display_section_height + 3, 2, ' ', 20);
    if (currentMode == INSERT)
        mvprintw(display_section_height + 3, 2, "[ INSERT MODE ]");
    else
        mvprintw(display_section_height + 3, 2, "[ NORMAL MODE ]");
    refresh();
}   

void MusicPlayer::playSong(const std::string& songName){
    std::string songPath = "songs/" + songName;
    
    if(audioPlayer.loadFile(songPath)){
        audioPlayer.play();
    }
    else{
        std::cerr << "Failed to play song: " << songName << std::endl;
    }
    refresh();
}

void MusicPlayer::pauseSong(){
    if(audioPlayer.isPlaying()){
        audioPlayer.pause();
    }
    refresh();
}