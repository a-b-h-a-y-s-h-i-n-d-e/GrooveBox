#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>


class MusicPlayer{
public:
    void run();
private:
    void displayMenu();
    void handleInput();
    void drawBorder();

    std::vector<std::string> playlist = {"Song1.mp3", "Song2.mp3"};
    int currentSelection = 0;
};

#endif