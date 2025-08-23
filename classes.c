class Player {
public:
    int x,y; /* Position */
    int health = 3;
    int score = 0;
    /*enter starting position here once array is formed, preferably bottom left/middle*/
    bool moving = false /* set to true if an input is pressed, if that input is equal to a cardinal direction move the player then set to false again*/
}

class Enemy {
public:
    int x,y; /*spawn*/
    bool hit = false
    int points = 50
    /* insert rng here for drops*/
    /*insert tracking here towards player*/
}

class Spell {
public: 
    bool touching = false

}
 
 _^_
 /_\ == player

 [*z*] == birdEnemy

 /[::]\ == spiderEnemy