#include <iostream>   // for cout/cin
#include <vector>     // for storing your maze and entities
#include <cstdlib>    // for rand()
#include <ctime>      // for seeding rand()
#include <termios.h>    // (Windows only) for _kbhit() and _getch()
#include <unistd.h>
#include <fcntl.h>
#include "classes.h"
#include <sys/ioctl.h>


//sprites as strings
const char* wizardSprite = "_^_\n /_\\";
const char* birdEnemySprite = "[*z*]";
const char* spiderEnemySprite = "/[::]\\";

const int SIZE = 20;

// Have to right functions previously used in with these libraries
// unistd, termios and fcntl, sys/ioctl

// Function to set terminal to raw mode (non-blocking)
void setNonBlockingInput() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO); // turn off canonical mode & echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // make input non-blocking
}

// Check if a key was pressed
bool kbhit() {
    int bytesWaiting;
    ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
    return bytesWaiting > 0;
}

// Get a single character without waiting for Enter
char getch() {
    char c = 0;
    read(STDIN_FILENO, &c, 1);
    return c;
}

// standard library maze logic, better than nested array I had prior
std::vector<std::vector<char>> createMaze(int size) {
    std::vector<std::vector<char>> maze(size, std::vector<char>(size, ' '));

    // Fill borders
    for (int i = 0; i < size; i++) {
        maze[0][i] = maze[size-1][i] = '_';   // top/bottom
        maze[i][0] = maze[i][size-1] = '|';   // left/right
    }

    // TODO: Random walls
    return maze;
}

//much like the maze I changed this to use vectors as well, research vector library later
//note about reasoning Note: I pass Player &player by reference, otherwise you’d only be 
// modifying a copy. That’s a subtle but crucial C++ difference from your draft.

void movement(char keystroke, Player &player, std::vector<std::vector<char>> &maze){
    int newX = player.x;
    int newY = player.y;

    if (keystroke == 'w') newY--;
    else if (keystroke == 's') newY++; 
    else if (keystroke == 'a') newX--;
    else if (keystroke == 'd') newX++;
    if (maze[newY][newX] != '|' && maze[newY][newX] != '_'){
        player.x = newX;
        player.y = newY;
    }
}


int main() {
    srand(time(0));

    Player player(1, SIZE-2); //starting position
    Enemy enemy(SIZE-3, SIZE-3) //enemy start for now

    auto maze = createMaze(SIZE);
    setNonBlockingInput();
    bool gameOver = false;
    while (!gameOver){
        system("clear"); //clear clutter in terminal
//input, if the kb is hit get that character and pass it as input to the 
// movement function along with the rest of the req info
        if (kbhit()){
            char input = getch();
            movement(input, player, maze);
        //draw maze
        for (int y = 0; y < SIZE; y++){
            for (int x = 0; x < SIZE; x++){
                if(x == player.x && y == player.y) std::cout << "P";
                else if (x == enemy.x && y == enemy.y) std::cout << "E";
                else std::cout << maze[y][x];
                }
            }
        std::cout << "\n";
        /* Continue the game */
        /* continue refreshing with state changes and input*/
        /*update with those*/
    }

    //input, if the kb is hit get that character and pass it as input to the 
    // movement function along with the rest of the req info

    if (player.x == enemy.x && player.y == enemy.y){
        player.health --;
        if (player.health <= 0){
            std::cout << "Game Over! Score: " << player.score << "\n";
            gameOver = true;
            printf("Press Enter to Continue");
            }
        }
    }

    return 0;
}

//I want to make sure walls are still | and _ but eveything else can be * or the like #, I want to keep my naming conventions as well