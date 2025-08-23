

static SIZE = 20;

int map (SIZE){
    int maze = [SIZE][SIZE];
    /* fill in maze with _ and | on bounds as well as randomly throughout the maze, _ and | cannot span the entire row/column, therefore making the maze solvable*/
}

int movement(char keystroke, Player player){
    int newX = player.x;
    int newY = player.y;
    if (keystroke == 'w') newY--;
    else if (keystroke == 's') newY++; 
    else if (keystroke == 'a') newX--;
    else if (keystroke == ' d') newX++;
    if (maze[newY][newX] != '|' && maze[newY][newX] != '_'){
        player.x = newX;
        player.y = newY;
    }
}


int main() {
    Player player();
    Map maze(SIZE)
    bool gameOver = false
    while (!gameOver){
        /* Continue the game */
        /* continue refreshing with state changes and input*/
        /*update with those*/
    }

    if (player.x == enemy.x && player.y == enemy.y){
        player.health --;
        if (player.health <= 0){
            gameOver = true;
            printf("Game Over\nYour Score: %d", player.score)
            printf("Press Enter to Continue");
        }
        if (keystroke == '\n')
            gameOver = false
    }
}