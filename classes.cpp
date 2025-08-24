#include "classes.h"

Player::Player(int startX, int startY) {
    x = startX;
    y = startY;
}

Enemy::Enemy(int spawnX, int spawnY) {
    x = spawnX;
    y = spawnY;
}

 
// <@ == fireball /*has aoe, can destroy walls, longer time between "casts"*/

// =>> == Icelance /* can pierce enemies, doesnt disappear on contact*/

 // _^_
 // /_\ == player

 // [*z*] == birdEnemy

 // /[::]\ == spiderEnemy