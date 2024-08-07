#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>


class MusicPlayer{
public:
    MusicPlayer();
    void run();
    void drawBorder();
    void displayInputSection();
    void handleInsertmode();
    void userInput();
    void displayMode();
    void displaySongs();
    void createSymbol();
    void updateSymbol();

private:
    int total_height;
    int total_width;
    int input_section_height;
    int display_section_height;
    std::string currentSymbol;
    std::vector<std::string> song_list;
    std::vector<std::string> playlist = {"Song1.mp3", "Song2.mp3"};
    int currentSelection = 0;
    char symbol = '>';
    enum Mode { NORMAL, INSERT} currentMode;
};

#endif