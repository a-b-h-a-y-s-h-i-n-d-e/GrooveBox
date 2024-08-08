#include "player.h"
#include <iostream>
#include <string>
using namespace std;

void printHelp(){
    cout << "Usage: groovebox [options]\n"
         << "\n"
         << "Modes:\n"
         << "  [NORMAL] Mode:\n"
         << "    - Use 'j' and 'k' to scroll through songs in the display section.\n"
         << "    - Type 'i' to enter INSERT mode.\n"
         << "\n"
         << "  [INSERT] Mode:\n"
         << "    - Type the name of the song you want and hit ENTER to search for that song.\n";
}

int main(int argc, char* argv[]){

    if(argc > 1){
        string  arg1 = argv[1];
        if(arg1 == "--help"){
            printHelp();
            return 0;
        }
    }

    MusicPlayer player;
    player.run();
    return 0;
}
