#include "classes.h"

//sprites as strings
const char* wizardSprite = "_^_\n/_\\";
const char* birdEnemySprite = "[*z*]";
const char* spiderEnemySprite = "/[::]\\";
const char* fireball = "<@";
const char* icelance = "==>";

const int SIZE = 23;

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
        maze[0][i] = '_';
        maze[size-1][i] = '_';   // top/bottom
        maze[i][0] =  '|';
        maze[i][size-1] = '|';   // left/right
    }

    // TODO: Random walls
        //Ayyye theres a rand func         
        for (int x = 0; x < size; x+=3){
            for (int y = 0; y < size; y+=3){
                int rng = rand() % 2;
                if (maze[y][x] == ' ' && rng == 1 && y!=0 && x!=0 && y != size - 1 && (x+1) != size-1){
                    maze[y][x] = '_';
                    maze[y][x+1] = '_';
                }
        }
        
    }
    return maze;
}
    

    


//much like the maze I changed this to use vectors as well, research vector library later
//note about reasoning Note: I pass Player &player by reference, otherwise you’d only be 
// modifying a copy. That’s a subtle but crucial C++ difference from your draft.

// passing in spells by reference instead of directly, through doing so they persist outside the function and can be called/erased
void movement(char keystroke, Player &player, std::vector<std::vector<char>> &maze,
std::vector<Spell> &spells){
    int newX = player.x;
    int newY = player.y;

    if (keystroke == 'w') newY--;
    else if (keystroke == 's') newY++; 
    else if (keystroke == 'a') newX--;
    else if (keystroke == 'd') newX++;
    else if (keystroke == 'j') {
        spells.push_back(Spell(player.x, player.y, -1, 0)); //Casting left
    }
    else if (keystroke == 'k') {
        spells.push_back(Spell(player.x, player.y, 1, 0)); //Casting Right
    }

    if (maze[newY][newX] != '|' && maze[newY][newX] != '_'){
        player.x = newX;
        player.y = newY;
    }
}


int main() {
    srand(time(0));

    Player player(1, SIZE-2); //starting position
    std::vector<Enemy> enemies;
    std::vector<Spell> spells;

    // add enemies
    for (int i = 0; i < 3; i++) {
        enemies.push_back(Enemy(SIZE-3-i, SIZE -3));
    }

    std::cout << "\033[?25l" ; //hide cursor
    auto maze = createMaze(SIZE);
    setNonBlockingInput();

    bool gameOver = false;
    while (!gameOver){
        std::cout << "\033[H"; //Cursor moves to top left
//input, if the kb is hit get that character and pass it as input to the 
// movement function along with the rest of the req info
        if (kbhit()){
            char input = getch();
            movement(input, player, maze, spells);
        }    

        //Really rough enemy "tracking"
        for (auto &enemy : enemies) { // Is the logic I substituted here okay
            if (enemy.x < player.x && (maze[enemy.y][enemy.x+1]) != '_') enemy.x++;
            if (enemy.x > player.x && (maze[enemy.y][enemy.x-1]) != '_') enemy.x--;
            if (enemy.y < player.y && (maze[enemy.y+1][enemy.x]) != '_') enemy.y++;
            if (enemy.y > player.y && (maze[enemy.y-1][enemy.x]) != '_') enemy.y--;

        }

        for (auto &spell : spells){ //for each spell in spells we get a reference to then updates its place
            spell.x += spell.dx;
            spell.y += spell.dy;
        }

            // explain the logic of this for loop, what the auto references and what the et references.
        for (auto it = spells.begin(); it != spells.end();){ //iterate over spells list, erase them once they hit, compare each spell to each enemy
            bool erased = false;
            for (auto et = enemies.begin(); et != enemies.end();){ // iterating over enemies list until we hit the end
                if (it->x == et->x && it->y == et->y){
                    et = enemies.erase(et);
                    it = spells.erase(it);
                    player.score += 50;
                    erased = true;
                    break;
                }else{
                    ++et; //if its not equal to enemies coordinates continue the loop??
                }
            if (!erased) ++it;
        }
    }

        //draw maze
        // Buffer to fix logic with sprite movement and maze disjoint
        std::vector<std::string> screenBuffer(SIZE, std::string(SIZE, ' '));
        for (int y = 0; y < SIZE; y++){
            for (int x = 0; x < SIZE; x++){
                screenBuffer[y][x] = maze[y][x];
                }
            }

                    // Overlay sprite function
        auto overlaySprite = [&](const char* sprite, int posX, int posY) {
            int row = 0, col = 0;
            for (int i = 0; sprite[i] != '\0'; i++) {
                if (sprite[i] == '\n') { row++; col = 0; continue; }
                int y = posY + row;
                int x = posX + col;
                if (y >= 0 && y < SIZE && x >= 0 && x < SIZE)
                    screenBuffer[y][x] = sprite[i];
                col++;
            }
        };
        //overwrites maze tiles for position of player adn enemies
        overlaySprite(wizardSprite, player.x, player.y);
        for (auto &enemy : enemies){
            overlaySprite(spiderEnemySprite, enemy.x, enemy.y);
        }

        for (auto &spell : spells){
            if (spell.x >= 0 && spell.x < SIZE && spell.y >= 0 && spell.y < SIZE)
                screenBuffer[spell.y][spell.x] = '*';
        }

        std::cout << "Score: " << player.score << "  Health: " << player.health << "\n";

        for (auto &row : screenBuffer) {
            std::cout << row << "\n";
        }

        std::cout << std::flush;

       // =========================================================
        // Collisions: player vs enemies
        // =========================================================
        for (auto &enemy : enemies) {
            if (player.x == enemy.x && player.y == enemy.y) {
                player.health--;
                if (player.health <= 0) {
                    std::cout << "Game Over! Score: " << player.score << "\n";
                    gameOver = true;
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }

    std::cout << "\033[?25h"; // show cursor again
    return 0;
}


//I want to make sure walls are still | and _ but eveything else can be * or the like #, I want to keep my naming conventions as well