#include "raylib.h"
#include "player.cpp"
#include "score_counter.cpp"
#include<vector>
#include<time.h>
#include<cstdlib>

int main()
{
    srand(time(0));
     
    const int screenWidth = 900;
    const int screenHeight = 600;

    bool isGameStarted = false;
    bool hasDied = false;

    //score counter
    scoreCounter counter = scoreCounter();

    //player
    Player player = Player();
    float jumpSpeed = -5;
    float finalVel = 0;
    float gravity = 0.2;

    //pipes
    std::vector<Pipe> pipes;
    resetPipes(pipes);

    InitWindow(screenWidth, screenHeight, "flappy bird");

    SetTargetFPS(30);

    menu:
        while(!isGameStarted && !WindowShouldClose())
        {
            if(IsKeyDown(32))
            {
                isGameStarted = true;
                    
                player.reset();
                counter.resetScore();
                if(hasDied)
                {
                    resetPipes(pipes);
                }
                break;
            }
            BeginDrawing();
                ClearBackground(BLUE);
                for(Pipe& pipe : pipes)
                {
                    pipe.drawPipe();
                }
                DrawRectangleV(player.getPos(), player.getSize(), RED);
                counter.displayScore();
                if(hasDied)
                {   
                    DrawText("press space to restart", 200, 250, 50, BLACK);
                }
                else
                {
                    DrawText("press space to start", 200, 250, 50, BLACK);
                }
            EndDrawing();
        }

    while(!WindowShouldClose())
    { 
        //player movement
        if(IsKeyDown(32))   // keycode for space : 32
        {
            //on click set cur velocity to jump speed to initiate jump and reset gravity effect
            finalVel = jumpSpeed;
            gravity = 0.2;
        }
        //apply gravity and increment gravity by small amounts to make pulling effect
        finalVel += gravity;
        gravity += 0.075;
        player.setPos({player.getPosX(), player.getPosY() + finalVel});

        if(player.isTouchingBorders() || player.isCollidingWithPipe(pipes.at(0)))
        {
            isGameStarted = false;
            hasDied = true;
            goto menu;
        }

        for(Pipe& pipe : pipes)
        {
            pipe.updatePos();
        }

        if(pipes.at(0).getPosX() + pipes.at(0).getWidth() <= player.getPosX())
        {
            if(!pipes.at(0).isCounted())
            {
                counter.addScore();
            } 
        }

        if(pipes.at(0).getPosX() + pipes.at(0).getWidth() <= 0)
        {
            pipes.erase(pipes.begin());
        }
        if(pipes.at(pipes.size()-1).getPosX() < 700)
        {
            pipes.push_back(Pipe());
        }

        BeginDrawing();
            ClearBackground(BLUE);
            for(Pipe& pipe : pipes)
            {
                pipe.drawPipe();
            }
            DrawRectangleV(player.getPos(), player.getSize(), RED);
            counter.displayScore(); 
        EndDrawing();
    }
    CloseWindow();
}