#include <ncurses.h>
#include "player.h"

int main(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    MusicPlayer player;
    player.run();
    refresh();
    
    getch();
    endwin();
    
    return 0;
}
