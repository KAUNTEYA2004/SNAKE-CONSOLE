#include <iostream>
#include <conio.h>  
#include <windows.h>  
#include <vector>
#include <cstdlib>    
#include <ctime>      

using namespace std;


const int WIDTH = 20;
const int HEIGHT = 20;
const char SNAKE_HEAD = 'O';
const char SNAKE_BODY = 'o';
const char FOOD = '*';
const char EMPTY = ' ';
const char WALL = '#';


enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

struct Point {
    int x, y;
};

class SnakeGame {
public:
    SnakeGame();
    void Run();

private:
    void Setup();
    void Draw();
    void Input();
    void Logic();
    void GenerateFood();
    void GameOver();
    bool IsFoodOnSnake();

    bool gameOver;
    Direction dir;
    Point food;
    vector<Point> snake;
    int score;
};

SnakeGame::SnakeGame() {
    Setup();
}

void SnakeGame::Setup() {
    gameOver = false;
    dir = STOP;
    score = 0;

    
    snake.push_back({ WIDTH / 2, HEIGHT / 2 });

   
    GenerateFood();
}

void SnakeGame::Draw() {
    system("cls");  

  
    for (int i = 0; i < WIDTH + 2; ++i)
        cout << WALL;
    cout << endl;


    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (x == 0)
                cout << WALL;  
            if (x == food.x && y == food.y)
                cout << FOOD;
            else if (x == snake[0].x && y == snake[0].y)
                cout << SNAKE_HEAD;
            else {
                bool print = false;
                for (size_t i = 1; i < snake.size(); ++i) {
                    if (snake[i].x == x && snake[i].y == y) {
                        cout << SNAKE_BODY;
                        print = true;
                        break;
                    }
                }
                if (!print)
                    cout << EMPTY;
            }
            if (x == WIDTH - 1)
                cout << WALL;  
        }
        cout << endl;
    }

   
    for (int i = 0; i < WIDTH + 2; ++i)
        cout << WALL;
    cout << endl;

   
    cout << "Score: " << score << endl;
}

void SnakeGame::Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 224:  
                switch (_getch()) {
                    case 75: dir = LEFT; break;  
                    case 77: dir = RIGHT; break; 
                    case 72: dir = UP; break;    
                    case 80: dir = DOWN; break;  
                }
                break;
            case 'x': gameOver = true; break;
        }
    }
}

void SnakeGame::Logic() {
    Point prev = snake[0];
    Point prev2;
    Point next = prev;

    
    switch (dir) {
        case LEFT:  next.x--; break;
        case RIGHT: next.x++; break;
        case UP:    next.y--; break;
        case DOWN:  next.y++; break;
        default: break;
    }

 
    if (next.x >= WIDTH) next.x = 0;
    if (next.x < 0) next.x = WIDTH - 1;
    if (next.y >= HEIGHT) next.y = 0;
    if (next.y < 0) next.y = HEIGHT - 1;

    
    for (size_t i = 1; i < snake.size(); ++i) {
        if (snake[i].x == next.x && snake[i].y == next.y)
            gameOver = true;
    }

    
    snake.insert(snake.begin(), next);
    if (next.x == food.x && next.y == food.y) {
        score += 10;
        GenerateFood();
    } else {
        snake.pop_back();
    }
}

void SnakeGame::GenerateFood() {
    do {
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;
    } while (IsFoodOnSnake());  
}

bool SnakeGame::IsFoodOnSnake() {
    for (const auto& segment : snake) {
        if (segment.x == food.x && segment.y == food.y)
            return true;
    }
    return false;
}

void SnakeGame::GameOver() {
    system("cls");
    cout << "Game Over!" << endl;
    cout << "Final Score: " << score << endl;
    cout << "Press any key to exit...";
    _getch();
}

void SnakeGame::Run() {
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);  
    }
    GameOver();
}

int main() {
    srand(static_cast<unsigned>(time(0)));  
    SnakeGame game;
    game.Run();
    return 0;
}
