#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>


class MusicPlayer{
public:
    void run();
private:
    enum Mode { NORMAL, INSERT};
    Mode currentMode = NORMAL;

    void drawBorder();
    void displayInputSection();
    void handleInsertmode();
    void userInput();
    void displayMode();

    int total_height;
    int total_width;
    int input_section_height;
    int display_section_height;

    std::vector<std::string> playlist = {"Song1.mp3", "Song2.mp3"};
    int currentSelection = 0;
};

#endif