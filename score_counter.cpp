#include "raylib.h"

#include<string>

class scoreCounter
{
    int score;
    public:
        scoreCounter()
        {
            score = 0;
        }
        
        void resetScore()
        {
            score = 0;
        }
        void addScore()
        {
            score++;
        }

        void displayScore()
        {
            DrawText(std::to_string(score).c_str(), 25, 25, 30, BLACK);
        }
};