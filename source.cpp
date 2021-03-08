#include "SDL.h"
#include "SDL_image.h"
#include "SDL_getenv.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <math.h>
#include "SDL_Header.space.cpp"
#include "mainlevels.cpp"
#include "maneuver.cpp"

using namespace std;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;
const int SCREEN_BPP = 32;

bool quit1 = false;
bool quit2 = false;
bool levelquit = false;

bool start_sdl()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }
    //SDL_Surface* icon = load_image("spaceship.bmp");
    //Uint32 colorkey = SDL_MapRGB(icon->format, 0, 0xFF, 0xFF);
    //SDL_SetColorKey(icon, SDL_SRCCOLORKEY, colorkey);
    putenv("SDL_VIDEO_WINDOW_POS=20,50");
    SDL_WM_SetIcon(SDL_LoadBMP("spaceship.bmp"),NULL);
    screen = SDL_SetVideoMode( SCREEN_WIDTH,SCREEN_HEIGHT, SCREEN_BPP,SDL_SWSURFACE);
    if( screen == NULL )
    {
        return false;
    }
    SDL_WM_SetCaption( "Space Wars", NULL );
    return true;
}
void end_pgrm()
{
    SDL_FreeSurface(background);
    SDL_FreeSurface(buttons);
    SDL_FreeSurface(objects);
    SDL_Quit();
}

void opening_2()
{
    SDL_Rect back;
    back.x = 0;
    back.y = 0;
    back.w = 1200;
    back.h = 700;
    int buttonsx = -240;
    int blocky = -120;
    while (buttonsx < 250)
    {
        apply_clip(0,0,background,screen,&back);
        apply_clip(150,blocky,buttons,screen,&buttonclip[10]);
        apply_clip(buttonsx,100,buttons,screen,&buttonclip[11]);
        apply_clip(buttonsx,250,buttons,screen,&buttonclip[12]);
        apply_clip(buttonsx,400,buttons,screen,&buttonclip[13]);
        SDL_Flip(screen);
        SDL_Delay(75);
        if (blocky < 50)
        {
            blocky = blocky + 50;
        }
        if (blocky >= 50)
        {
            buttonsx = buttonsx + 50;
        }
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                buttonsx = 260;
                quit1 = true;
                quit2 = true;
            }
        }
    }
}


int main (int argc, char* args[])
{
start_sdl();

bool loadgame;
bool choosescreen = false;
bool total_game_loop = true;
bool high_scores = false;
mainlevelson = false;
maneuver_on = false;
int choice;
SDL_Rect back1;
set_smallfont();
set_largefont();
set_buttonclip();

//SDL_Surface *test = load_image("rock3.bmp");
//SDL_Surface *test2;
//SDL_Rect test3;
//test3.x = 0; test3.y = 0; test3.w = 100; test3.h = 100;
//apply_clip(0,0,test,test2,&test3);
//successful test for the maneuver algorithm

while (total_game_loop == true)
{
    if (quit1 == false)
    {
        back1.x = 0;
        back1.y = 0;
        back1.w = 1000;
        back1.h = 600;
        background = load_image("space1.png");
        buttons = load_image("buttonclips.png");
        b_1.set_up_button(300,250,buttonclip[1].w,buttonclip[1].h,1,4,7);
        //b_2.set_up_button(300,300,buttonclip[2].w,buttonclip[2].h,2,5,8);
        b_3.set_up_button(300,350,buttonclip[3].w,buttonclip[3].h,3,6,9);

        while (quit1 == false)
        {
            back1.x = back1.x + 8;
            if (back1.x + back1.w > 2990)
            {
                back1.x = 0;
            }
            apply_clip(0,0,background,screen,&back1);
            apply_clip(280,50,buttons,screen,&buttonclip[0]);
            b_1.show_button();
            //b_2.show_button();
            b_3.show_button();
            if (SDL_PollEvent(&event))
            {
                if (b_1.check_button() == 3)
                {
                    //next while() enviroment for new game
                    loadgame = false;
                    quit1 = true;
                }
                if (b_3.check_button() == 3)
                {
                    //quits the game
                    quit1 = true;
                    quit2 = true;
                    total_game_loop = false;
                }
                if (event.type == SDL_QUIT)
                {
                    quit1 = true;
                    quit2 = true;
                    total_game_loop = false;
                }
            }
            SDL_Flip(screen);
            SDL_Delay(90);
        }
        //end of firstscreen loop
    }
    //end of the quit1
    if (quit2 == false)
    {
        back1.x = 0;
        back1.y = 0;
        back1.w = 1000;
        back1.h = 600;
        background = load_image("space1.png");
        buttons = load_image("buttonclips.png");
        opening_2();
        b_1.set_up_button(260,100,buttonclip[11].w,buttonclip[11].h,11,14,17);
        b_2.set_up_button(260,250,buttonclip[12].w,buttonclip[12].h,12,15,18);
        b_3.set_up_button(260,400,buttonclip[13].w,buttonclip[13].h,13,16,19);

        while (quit2 == false)
        {
            back1.x = back1.x + 8;
            if (back1.x + back1.w > 2990)
            {
                back1.x = 0;
            }
            apply_clip(0,0,background,screen,&back1);
            apply_clip(150,60,buttons,screen,&buttonclip[10]);
            b_1.show_button();
            b_2.show_button();
            b_3.show_button();
            if (SDL_PollEvent(&event))
            {
                if (b_1.check_button() == 3)
                {
                    main_level = 1;
                    main_points = 0;
                    mainlevelson = true;
                    quit2 = true;
                    // then goto the while loop for the main levels
                }
                if (b_2.check_button() == 3)
                {
                    maneuver_level = 1;
                    maneuver_points = 0;
                    maneuver_on = true;
                    quit2 = true;
                }
                if (b_3.check_button() == 3)
                {
                    high_scores = true;
                    b_2.set_up_button(300,300,buttonclip[20].w,buttonclip[20].h,20,21,22);
                    char the_score[15];
                    std::ifstream score_file ("scores.txt");
                    score_file >> the_score;
                    score_file.close();
                    int fad = atoi (the_score);
                    output = load_image("alphabet.bmp");
                    while (high_scores == true)
                    {
                        apply_clip(0,0,background,screen,&back1);
                        output_string("Mainlevel High Score:", 100,100,20,screen,2);
                        output_number(fad,100,160,20,screen,2);
                        b_2.show_button();
                        SDL_Flip(screen);
                        if (SDL_PollEvent(&event))
                        {
                            if (b_2.check_button() == 3)
                            {
                                high_scores = false;
                                b_2.set_up_button(260,250,buttonclip[12].w,buttonclip[12].h,12,15,18);
                                b_3.set_up_button(260,400,buttonclip[13].w,buttonclip[13].h,13,16,19);
                            }
                            if (event.type == SDL_QUIT)
                            {
                                high_scores = false;
                                quit2 = true;
                                total_game_loop = false;
                            }
                        } //end of poll event
                        SDL_Delay(90);
                    } //end of high_scores loop

                } //end of the high score button
                if (event.type == SDL_QUIT)
                {
                    quit2 = true;
                    total_game_loop = false;
                }
            }
            SDL_Flip(screen);
            SDL_Delay(90);
        } //end of the choosescreen loop
    } //end of choose screen
    while (mainlevelson == true)
    {
        //the_game returns -1 for total quit, 0 for goto menu (quit mainlevels), 1 for loooop
        choice = the_game();
        switch (choice)
        {
            case -1:
            total_game_loop = false;
            mainlevelson = false;
            break;
            case 0:
            mainlevelson = false;
            quit1 = false;
            quit2 = false;
            break;
            case 1:
            break;
        } //end of switch case
    } //end of while loop
    while (maneuver_on == true)
    {
        choice = the_maneuver();
        switch (choice)
        {
            case 1: //restart from the beginning
            break;
            case 0: //quit to the main page
            maneuver_on = false;
            quit1 = false;
            break;
            case -1: //quit ALL the things!
            maneuver_on = false;
            total_game_loop = false;
            break;
        }
    } //end of the maneuver game loop


} //end of total game loopp
end_pgrm();
}
