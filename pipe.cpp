#include "raylib.h"
#include<vector>

#include<cstdlib>

struct Gap
{
    int pos;
    int height;
};

class Pipe
{
    Gap gap;
    int posX;
    int width;
    int speed;
    bool counted;

    Rectangle top, bottom;

    void defaultSetting()
    {
        counted = false;
        speed = 5;
        width = 75;
        gap.pos = (rand() % 350) + 50;
        gap.height = 150;
        top = Rectangle(posX, 0, width, gap.pos);
        bottom = Rectangle(posX, gap.pos + gap.height, width, 600 - gap.pos - gap.height);
    }

    public:
        Pipe()
        {
            posX = 950;
            defaultSetting();
        }
        Pipe(int posX)
        {
            this->posX = posX;
            defaultSetting();
        }

        void drawPipe()
        {
            //top
            top = Rectangle(posX, 0, width, gap.pos);
            DrawRectangleRec(top, GREEN);
            //bottom
            bottom = Rectangle(posX, gap.pos + gap.height, width, 600 - gap.pos - gap.height);
            DrawRectangleRec(bottom, GREEN);
        }

        Rectangle getTop()
        {
            return top;
        }
        Rectangle getBottom()
        {
            return bottom;
        }
        
        int getPosX()
        {
            return posX;
        }
        int getWidth()
        {
            return width;
        }
        void updatePos()
        {
            posX -= speed;
        }

        bool isCounted()
        {
            if(!counted)
            {
                counted = true;
                return false;
            }
            return true;
        }
};

void resetPipes(std::vector<Pipe>& pipes)
{
    pipes.clear();
    pipes.push_back(Pipe(250));
    pipes.push_back(Pipe(450));
    pipes.push_back(Pipe(650)); 
    pipes.push_back(Pipe(850)); 
}