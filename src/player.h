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

    int total_height;
    int total_width;
    int input_section_height;
    int display_section_height;

    std::vector<std::string> playlist = {"Song1.mp3", "Song2.mp3"};
    int currentSelection = 0;
};

#endif