#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>   // for cout/cin
#include <vector>     // for storing your maze and entities
#include <cstdlib>    // for rand()
#include <ctime>      // for seeding rand()
#include <termios.h>    // (Windows only) for _kbhit() and _getch()
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <chrono>
#include <thread>
#include <sstream>


class Player {
public:
    int x, y;
    int health = 3;
    int score = 0;
    bool moving = false;
    bool touching = false;

    Player(int startX, int startY);
};

class Enemy {
public:
    int x, y;
    bool hit = false;
    int points = 50;

    Enemy(int spawnX, int spawnY);
};

class Spell {
public:
    // add x y coords for moving, and also add contact w/ enemy equaling enemy death
    // maybe also add hearts, and input for fireball
    // fix wizard moving only hat 
    int x, y;
    int dx, dy;

    Spell(int startX, int startY, int dirX, int dirY){
        x = startX;
        y = startY;
        dx = dirX;
        dy = dirY;
    }
};

#endif // CLASSES_H
