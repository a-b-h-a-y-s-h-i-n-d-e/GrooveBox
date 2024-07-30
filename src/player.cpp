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
    total_height = height;
    total_width = width;
    // height -> 24 and width -> 80
    input_section_height = total_height * 0.2;
    display_section_height = total_height * 0.8;
    mvhline(display_section_height + 1, 0, '-', total_width);

    // Drawing widgets now
    // input box
    mvprintw(display_section_height + 2, 2, "Song name: ");
    mvprintw(display_section_height + 2, 13, "[                                                  ]");
    mvprintw(display_section_height + 2, 68, "[ Search ]");


    refresh();
}


void MusicPlayer::handleInput(){
    std::string input;
    int ch;
    int cursor_pos = 0;
    const int max_input_length = 50;

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

    mvhline(display_section_height + 2, 14, ' ', max_input_length);
    mvprintw(1, 3, "%s", input.c_str());
    refresh();

    getch();

}