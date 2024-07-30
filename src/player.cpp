#include "player.h"
#include <ncurses.h>
#include <iostream>
#include <string>

void MusicPlayer::run(){
    displayMenu();
    handleInput();
}

void MusicPlayer::displayMenu(){
    clear();

    // Drawing borders
    border('|', '|', '-', '-', '-', '-', '-', '-');
    int height, width;
    getmaxyx(stdscr, height, width);
    int total_height = height;
    int total_width = width;
    // height -> 24 and width -> 80
    int input_section_height = total_height * 0.2;
    int display_section_height = total_height * 0.8;
    mvhline(display_section_height + 1, 0, '-', total_width);

    // Drawing widgets now
    // input box
    mvprintw(display_section_height + 2, 2, "Song name: ");
    mvprintw(display_section_height + 2, 13, "[                                                  ]");
    mvprintw(display_section_height + 2, 68, "[ Search ]");


    refresh();
}


void MusicPlayer::handleInput(){
    // std::cout << "hello from player!" << std::endl;
}