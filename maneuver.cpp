#include <fstream>
#include "clib1.c"
SDL_Rect objects2[14];
void set_objects2()
{
objects2[0].x = 269; //spaceship
objects2[0].y = 127;
objects2[0].w = 51;
objects2[0].h = 77;

objects2[1].x = 467; //spaceship hurt
objects2[1].y = 114;
objects2[1].w = 54;
objects2[1].h = 76;

objects2[2].x = 136; //enemy right1
objects2[2].y = 148;
objects2[2].w = 48;
objects2[2].h = 46;

objects2[3].x = 203; //enemy right2
objects2[3].y = 150;
objects2[3].w = 47;
objects2[3].h = 45;

objects2[4].x = 343; //enemy down
objects2[4].y = 140;
objects2[4].w = 52;
objects2[4].h = 47;

objects2[5].x = 401; //enemy up
objects2[5].y = 138;
objects2[5].w = 50;
objects2[5].h = 50;

objects2[6].x = 133; //explo 1
objects2[6].y = 231;
objects2[6].w = 33;
objects2[6].h = 31;

objects2[7].x = 171; //explo 2
objects2[7].y = 229;
objects2[7].w = 43;
objects2[7].h = 42;

objects2[8].x = 226; //explo 3
objects2[8].y = 230;
objects2[8].w = 48;
objects2[8].h = 46;

objects2[9].x = 293; //explo 4
objects2[9].y = 222;
objects2[9].w = 65;
objects2[9].h = 62;

objects2[10].x = 374; //explo 5
objects2[10].y = 221;
objects2[10].w = 61;
objects2[10].h = 67;

objects2[11].x = 456; //explo 6
objects2[11].y = 217;
objects2[11].w = 86;
objects2[11].h = 83;

objects2[12].x = 355; //bullet blue
objects2[12].y = 31;
objects2[12].w = 6;
objects2[12].h = 25;

objects2[13].x = 395; //bullet red
objects2[13].y = 26;
objects2[13].w = 6;
objects2[13].h = 25;
}
SDL_Rect rocks[12];
void set_up_rocks()
{
rocks[0].x = 2;
rocks[0].y = 2;
rocks[0].w = 504;
rocks[0].h = 256;

rocks[1].x = 1;
rocks[1].y = 265;
rocks[1].w = 503;
rocks[1].h = 257;

rocks[2].x = 508;
rocks[2].y = 11;
rocks[2].w = 507;
rocks[2].h = 201;

rocks[3].x = 511;
rocks[3].y = 225;
rocks[3].w = 505;
rocks[3].h = 207;

rocks[4].x = 1015;
rocks[4].y = 7;
rocks[4].w = 509;
rocks[4].h = 162;

rocks[5].x = 1022;
rocks[5].y = 193;
rocks[5].w = 511;
rocks[5].h = 161;

rocks[6].x = 1528;
rocks[6].y = 10;
rocks[6].w = 514;
rocks[6].h = 258;

rocks[7].x = 1526;
rocks[7].y = 290;
rocks[7].w = 509;
rocks[7].h = 246;

rocks[8].x = 2040;
rocks[8].y = 15;
rocks[8].w = 515;
rocks[8].h = 200;

rocks[9].x = 2044;
rocks[9].y = 248;
rocks[9].w = 504;
rocks[9].h = 195;

rocks[10].x = 2558;
rocks[10].y = 12;
rocks[10].w = 494;
rocks[10].h = 171;

rocks[11].x = 2557;
rocks[11].y = 202;
rocks[11].w = 489;
rocks[11].h = 173;
}


class screen1
{
    public:
    SDL_Rect camera; //x,y,w,h for the screen taken from the hold surface to be put on screen
    SDL_Surface *clip, *hold; //screen of clipping file and the screen that 'holds' the level
    int set_up_level(std::string); //reads from the level files and renders the level onto surface *hold
    void move_and_show(); //responsible for keeping the screen on the ship and show
    void show_lives(); //just put the lives output in with the screen class...
    void start_setup();
    void clean_upscreen();
} class_screen;

SDL_Rect lvlstuff[35];
void screen1::start_setup()
{
    hold = SDL_CreateRGBSurface(SDL_SWSURFACE,16000,500,32,0,0,0,0);
}

int screen1::set_up_level(std::string lvlfile)
{
    char content[35];
    int count, place;
    char what;
    std::ifstream inputfile (lvlfile.c_str());
    if (inputfile.is_open())
    {
            clip = load_image("space1.png");
            count = 0;
            place = 0;
            while (count <= 6) //17
            {
                apply_surface(place,0,clip,hold);
                place += 3000;
                count += 1;
            } //outputs the space background on the hold surface b4 the rock clips
            clip = load_image("rock3.bmp");
            get_fileline(lvlfile.c_str(),&content[0],1);
            count = 0; place = 0;
            while (count != 33)
            {
                lvlstuff[count].x = char_2_num(content[count]); //inputs into the array used for coll_detect
                switch (content[count])
                {
                    case '0':
                    place += 500;
                    break;
                    case '1':
                    apply_clip(place,0,clip,hold,&rocks[4]); //150 pxls 2 top
                    place += 500;
                    break;
                    case '2':
                    apply_clip(place,0,clip,hold,&rocks[2]); //200 pxls @ top
                    place += 500;
                    break;
                    case '3':
                    apply_clip(place,0,clip,hold,&rocks[0]); // 250 pxls @ top
                    place += 500;
                    break;
                }
                count += 1;
            } //outputs the rock clips to the top of the level
            get_fileline(lvlfile.c_str(),&content[0],2); //gets the next line in the levelfile, for the bottom
            count = 0; place = 0; //reset
            while (count != 33)
            {
                lvlstuff[count].y = char_2_num(content[count]); //inputs into the array used for coll_detect
                switch (content[count])
                {
                    case '0':
                    place += 500;
                    break;
                    case '1':
                    apply_clip(place,350,clip,hold,&rocks[5]); //150 pxls @ bottom
                    place += 500;
                    break;
                    case '2':
                    apply_clip(place,300,clip,hold,&rocks[3]); //200 pxls @ bottom
                    place += 500;
                    break;
                    case '3':
                    apply_clip(place,250,clip,hold,&rocks[1]); //250 pxls @ bottom
                    place += 500;
                    break;
                }
                count += 1;
            } //outputs the rock clips to the bottom of the level
            //SHOOTSHIPS
            //SDL_Delay(5000);
            clip = load_image("objects.png");
            get_fileline(lvlfile.c_str(),&content[0],3); //gets the nxt line in the levelfile, for top shootships

            count = 0; place = 250; //reset, but shootships must be in middle of rock
            while (count != 33)
            {
                lvlstuff[count].w = char_2_num(content[count]); //inputs into the array used for coll_detect
                switch (content[count])
                {
                    case '0':
                    place += 500;
                    break;
                    case '1':
                    apply_clip(place,55,clip,hold,&objects2[4]); //clips for shootship looking down
                    place += 500;
                    break;
                }
                count += 1;
            } //outputs the stationary shootships clips to the top of the level
            get_fileline(lvlfile.c_str(),&content[0],4); //nxt line in the levelfile, for bottom shootships
            count = 0; place = 250; //reset, but shootships must be in middle of rock
            while (count != 33)
            {
                lvlstuff[count].h = char_2_num(content[count]); //inputs into the array used for coll_detect
                switch (content[count])
                {
                    case '0':
                    place += 500;
                    break;
                    case '1':
                    apply_clip(place,400,clip,hold,&objects2[5]); //clips for shootship looking up
                    place += 500;
                    break;
                }
                count += 1;
            } //outputs the stationary shootships clips to the bottom of the level

    } //end of if the level file is open
    else { return -1; }
    //delete content; //deletes the allocated mem
}

int sc_x = 0;
int sc_y = 0;
SDL_Rect screen_rect;
void screen1::move_and_show()
{
    apply_clip(0,0,hold,screen,&screen_rect);
    output_number(screen_rect.x,200,100,15,screen,1);
    SDL_Flip(screen);
    Uint8 *keystates = SDL_GetKeyState( NULL );
    if (keystates[SDLK_RIGHT]) screen_rect.x += 100;
    if (keystates[SDLK_LEFT]) screen_rect.x -= 100;
}

void screen1::clean_upscreen()
{
    SDL_FreeSurface(hold);
    SDL_FreeSurface(clip);
}
//void explosions()
//{

//}
int past = SDL_GetTicks();
int delay;
void frame(int rate)
{
    delay = rate - (SDL_GetTicks() - past); //calcs how long delay needs to be to keep @ frame rate
    if (delay > 0) SDL_Delay(delay); //cannot delay for negative seconds
    past = SDL_GetTicks(); //gets the time for when the function is called again
}
/*
class spaceship
{
    public:
    int x,y,w,h;
    bool hurt, dead;
    void set_up_ship(); //set position, state, speed
    void movement(int);
    int collision_detct();
    void show();
} spaceship;
void spaceship::movement(int inc)
{
    Uint8 *keystates = SDL_GetKeyState( NULL );
    if (keystates[SDLK_RIGHT]) x += inc;
    if (keystates[SDLK_LEFT]) x -= inc;
    if (keystates[SDLK_UP]) y -= inc;
    if (keystates[SDLK_DOWN]) y += inc;
    if (x > 916) x = 916;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (y > 445) y = 445;
}
void spaceship::show()
{
    if (hurt == true)
    {
        apply_clip(x,y,objects2,screen,&stuffclip[3]);
        hurt = false;
    }
    else apply_clip(x,y,objects2,screen,&stuffclip[0]);
}



class enemyship_2
{
    public:
    SDL_Rect ships[5];
    void movement(int);
    int collision();
    void set_up();
    int shipmax;
    int count;
    SDL_Rect shootline[13];
    void handle_fire();
} the_enemy;
void enemyship_2::movement(int level)
{

}
//handle fire put in with the movement function
void enemyship_2::handle_fire()
{

}
void enemyship_2::set_up()
{

}
int enemyship_2::collision()
{

}
*/
int the_maneuver()
{
    maneuver_gameloop = true;
    set_objects2();
    set_up_rocks();
    class_screen.start_setup();
    class_screen.set_up_level("level1.txt");

    screen_rect.x = 0;
    screen_rect.y = 0;
    screen_rect.w = 1000;
    screen_rect.h = 500;
    output = load_image("alphabet.bmp");
    past = SDL_GetTicks();
    //SDL_Surface *test = load_image("objects.png");
    //SDL_Surface *test2 = SDL_CreateRGBSurface(SDL_SWSURFACE,5000,500,32,0,0,0,0);
    //apply_surface(0,0,test,test2);
    //apply_surface(900,0,test,test2);
    //int clolp = 0;
    //int sx = 0;
    while (maneuver_gameloop == true)
    {
        class_screen.move_and_show();
        //apply_surface(sx,0,test2,screen);

        //apply_clip(500,250,test,scSreen,&objects2[clolp]);

        SDL_Flip(screen);
        Uint8 *keystates = SDL_GetKeyState( NULL );
        //if (keystates[SDLK_RIGHT]) sx += 1;
        //if (keystates[SDLK_LEFT]) sx -= 1;

        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                class_screen.clean_upscreen();
                maneuver_gameloop = false;
                return -1;
            }
        } //end of the if sdl_PollEvent
    frame(50);
    } //end of the maneuver_gameloop loop
    return 0;
} //end of the_maneuver function

//make sure to delete all allocated memory
