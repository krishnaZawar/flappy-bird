#include "raylib.h"

#include "pipe.cpp"

class Player
{
    Vector2 pos;
    Vector2 size;
    
    public:
        Player()
        {
            reset();
        }

        void reset()
        {
            pos = {75, 300};
            size = {30, 30};
        }

        Vector2 getPos()
        {
            return pos;
        }
        float getPosX()
        {
            return pos.x;
        }
        float getPosY()
        {
            return pos.y;
        }

        void setPos(Vector2 new_pos)
        {
            pos = new_pos;
        }

        Vector2 getSize()
        {
            return size;
        }

        bool isTouchingBorders()
        {
            return pos.y <= 0 || pos.y + size.y >= 600;
        }

        bool isCollidingWithPipe(Pipe &pipe)
        {
            Rectangle playerRect = Rectangle(pos.x, pos.y, size.x, size.y);
            return CheckCollisionRecs(pipe.getTop(), playerRect) || CheckCollisionRecs(pipe.getBottom(), playerRect);
        }
};