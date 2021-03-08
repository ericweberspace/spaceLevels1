
int main_level;
int inclevel;
void level_inc()
{
    if (main_points == 7*inclevel)
    {
        inclevel += 15;
        main_level += 1;
    }
}


SDL_Rect stuffclip[18];
bool the_game_on;
SDL_Rect levelback;
void set_stuffclip()
{
stuffclip[0].x = 12;
stuffclip[0].y = 9;
stuffclip[0].w = 84;
stuffclip[0].h = 55;

stuffclip[1].x = 11;
stuffclip[1].y = 69;
stuffclip[1].w = 86;
stuffclip[1].h = 62;

stuffclip[2].x = 8;
stuffclip[2].y = 136;
stuffclip[2].w = 98;
stuffclip[2].h = 58;

stuffclip[3].x = 8;
stuffclip[3].y = 196;
stuffclip[3].w = 94;
stuffclip[3].h = 59;

stuffclip[4].x = 106;
stuffclip[4].y = 7;
stuffclip[4].w = 71;
stuffclip[4].h = 62;

stuffclip[5].x = 103;
stuffclip[5].y = 72;
stuffclip[5].w = 60;
stuffclip[5].h = 58;

stuffclip[6].x = 183;
stuffclip[6].y = 12;
stuffclip[6].w = 52;
stuffclip[6].h = 50;

stuffclip[7].x = 180;
stuffclip[7].y = 78;
stuffclip[7].w = 54;
stuffclip[7].h = 61;

stuffclip[8].x = 246;
stuffclip[8].y = 15;
stuffclip[8].w = 48;
stuffclip[8].h = 43;

stuffclip[9].x = 298;
stuffclip[9].y = 24;
stuffclip[9].w = 34;
stuffclip[9].h = 30;

stuffclip[10].x = 134;
stuffclip[10].y = 228;
stuffclip[10].w = 34;
stuffclip[10].h = 40;

stuffclip[11].x = 170;
stuffclip[11].y = 229;
stuffclip[11].w = 40;
stuffclip[11].h = 43;

stuffclip[12].x = 220;
stuffclip[12].y = 228;
stuffclip[12].w = 57;
stuffclip[12].h = 50;

stuffclip[13].x = 291;
stuffclip[13].y = 220;
stuffclip[13].w = 63;
stuffclip[13].h = 63;

stuffclip[14].x = 370;
stuffclip[14].y = 212;
stuffclip[14].w = 72;
stuffclip[14].h = 83;

stuffclip[15].x = 453;
stuffclip[15].y = 212;
stuffclip[15].w = 92;
stuffclip[15].h = 89;

stuffclip[16].x = 355;
stuffclip[16].y = 31;
stuffclip[16].w = 6;
stuffclip[16].h = 25;

stuffclip[17].x = 395;
stuffclip[17].y = 26;
stuffclip[17].w = 6;
stuffclip[17].h = 25;

}

int lives;
void show_lives(int live)
{
    int count = live;
    int x = 10;
    while (count > 0)
    {
        apply_clip(x,35,objects,screen,&stuffclip[9]);
        x += 40;
        count -= 1;
    }
}
int DoC(int Bx,int By,int Bw,int Bh,int sx,int sy,int sw,int sh)
{
    if (((sy >= By) && (sy <= By+Bh)) || ((sy+sh >= By) && (sy+sh <= By+Bh)))
    {
        if (((sx >= Bx) && (sx <= Bx+Bw)) || ((sx+sw >= Bx) && (sx+sw <= Bx+Bw)))
        {
            return 1;
        }
        else return 0;
    }
    else return 0;
}

SDL_Rect explodeallot[15];
int explo_line = 0;
void eXplode()
{
    int count = 0;
    int Ex,Ey;
    while (count < 15)
    {
        if (explodeallot[count].w <= 6)
        {
            Ex = explodeallot[count].x + rand_num(10,30);
            Ey = explodeallot[count].y + rand_num(10,30);
            apply_clip(Ex,Ey,objects,screen,&stuffclip[explodeallot[count].w+9]);
            explodeallot[count].w += 1;
        }
        count += 1;
    }
}
void set_explode()
{
    int count = 0;
    while (count < 15)
    {
        explodeallot[count].w = 7;
        count += 1;
    }
}

class thescreen
{
    public:
    void scroll(int);
} thescreen;
void thescreen::scroll(int inc)
{
    levelback.y += inc;
    if (levelback.y >= 1990)
    {
        levelback.y = 0;
    }
    apply_clip(0,0,background,screen,&levelback);
}

class spaceship
{
    public:
    int x,y,w,h;
    bool hurt, dead;
    void set_up_ship();
    void movement(int);
    void shooting();
    SDL_Rect shootallot[13];
    void set_up_shoot_que();
    int shootque;
    int time1;
    int collision_detct();
    void show();
} spaceship1;
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
        apply_clip(x,y,objects,screen,&stuffclip[3]);
        hurt = false;
    }
    else apply_clip(x,y,objects,screen,&stuffclip[0]);
}
void spaceship::set_up_shoot_que()
{
    int count = 0;
    while (count < 12)
    {
        shootallot[count].x = 0;
        shootallot[count].y = 0;
        shootallot[count].w = 0;
        shootallot[count].h = 0;
        count += 1;
    }
}
void spaceship::shooting()
{
    if (SDL_GetTicks() - time1 > 220)
    {
        time1 = SDL_GetTicks();
        Uint8 *keystates = SDL_GetKeyState( NULL );
        if (keystates[SDLK_SPACE])
        {
            shootque += 1;
            if (shootque >= 12)
            {
                shootque = 0;
            }
            shootallot[shootque].x = x + 42;
            shootallot[shootque].y = y + 5;
            shootallot[shootque].w = 490;
        }
    }
        int count2 = 0;
        while (count2 < 12)
        {
            if (shootallot[count2].w > 0)
            {
                apply_clip(shootallot[count2].x,shootallot[count2].y,objects,screen,&stuffclip[16]);
                shootallot[count2].y -= 15;
                shootallot[count2].w -= 15;
            }
            count2 += 1;
        }
}
void spaceship::set_up_ship()
{
    x = 416;
    y = 420;
    w = stuffclip[0].w;
    h = stuffclip[0].h;
    hurt = false;
    dead = false;
    spaceship1.set_up_shoot_que();
    spaceship1.shootque = -1;
    time1 = SDL_GetTicks();
}
//first type of ship can't shoot, but it takes 3 shots to kill it- other can shoot but it only takes
//one shot

class enemyship_1
{
    public:
    SDL_Rect enemyship[12];
    bool new_wave;
    void movement_animation();
    //handles the movement of the wave and the animation and the showing of the ships
    void set_up();
    int coll_det();
    private:
    int wave_type;
    int shipnum;
    int clip;
    int inc;
    int withstand;
} the_enemy1;
void enemyship_1::movement_animation()
{
    //for the big ships, the width is 60, height is 58
    //in new_wave, specify the increase amount, shipnum total and set up the ships to run
    //in wave type fuction, put in pattern for the ships, and include when a new_wave should start
    if (main_level > 15) withstand = 3;
    else withstand = 2;
    if (clip == 4) clip = 5;
    else clip = 4;
    int count1;
    int count2;
    if (new_wave == true)
    {
        wave_type = rand_num(1,4);
        //add level customization to the pattern of the waves
        if (wave_type == 1)
        {
            inc = 2;
            count1 = 0;
            shipnum = 10;
            count2 = 30;
            while (count1 <= shipnum)
            {
                enemyship[count1].x = count2;
                enemyship[count1].y = 0;
                enemyship[count1].w = withstand;
                count2 += 80;
                count1 += 1;
            }
        }
        if (wave_type == 2)
        {
            inc = 3;
            shipnum = 9;
            count1 = 0;
            count2 = 0;
            while (count1 <= shipnum)
            {
                enemyship[count1].x = count2;
                enemyship[count1].w = withstand;
                count2 -= 70;
                count1 += 1;
            }
        }
        if (wave_type == 3)
        {
            inc = 5;
            shipnum = 11;
            count1 = 0;
            count2 = 0;
            while (count1 <= shipnum)
            {
                enemyship[count1].x = 0 - count2;
                enemyship[count1].w = withstand;
                enemyship[count1].y = 0 - count2;
                enemyship[count1 + 1].x = 950 + count2;
                enemyship[count1 + 1].w = withstand;
                enemyship[count1 + 1].y = 0 - count2;
                count2 += 70;
                count1 += 2;
            }
        }
        if (wave_type == 4)
        {
            inc = 5;
            shipnum = 7;
            count1 = 0;
            count2 = 0;
            while (count1 <= shipnum)
            {
                enemyship[count1].x = -60;
                enemyship[count1].y = count2;
                enemyship[count1].w = withstand;
                enemyship[count1+1].x = 1000;
                enemyship[count1+1].y = count2 + 75;
                enemyship[count1+1].w = 3;
                count1 += 2;
                count2 += 150;
            }
        }
        new_wave = false;
    }
    if (wave_type == 1)
    {
        count1 = 0;
        while (count1 <= shipnum)
        {
            enemyship[count1].y += inc;
            if (enemyship[count1].w > 0)
            {
                apply_clip(enemyship[count1].x,enemyship[count1].y,objects,screen,&stuffclip[clip]);
            }
            count1 += 1;
        }
        if (enemyship[shipnum].y > 500)
        {
            new_wave = true;
        }
    }
    if (wave_type == 2)
    {
        count1 = 0;
        while (count1 <= shipnum)
        {
            if (enemyship[count1].w > 0)
            {
                count2 = enemyship[count1].x;
                enemyship[count1].y = (150*sin(.01*count2))+250;
                apply_clip(enemyship[count1].x,enemyship[count1].y,objects,screen,&stuffclip[clip]);
            }
            enemyship[count1].x += inc;
            count1 += 1;
        }
        if (enemyship[shipnum].x > 950)
        {
            new_wave = true;
        }
    }
    if (wave_type == 3)
    {
        count1 = 0;
        while (count1 <= shipnum)
        {
            if (enemyship[count1].w > 0)
            {
                apply_clip(enemyship[count1].x,enemyship[count1].y,objects,screen,&stuffclip[clip]);
            }
            enemyship[count1].y += inc;
            enemyship[count1].x += inc;
            if (enemyship[count1 + 1].w > 0)
            {
                apply_clip(enemyship[count1+1].x,enemyship[count1+1].y,objects,screen,&stuffclip[clip]);
            }
            enemyship[count1+1].y += inc;
            enemyship[count1+1].x -= inc;
            count1 += 2;
        }
        if (enemyship[shipnum].y > 500)
        {
            new_wave = true;
        }
    }
    if (wave_type == 4)
    {
        count1 = 0;
        while (count1 <= shipnum)
        {
            enemyship[count1].x += inc;
            enemyship[count1+1].x -= inc;
            if (enemyship[count1].w > 0)
            {
                apply_clip(enemyship[count1].x,enemyship[count1].y,objects,screen,&stuffclip[clip]);
            }
            if (enemyship[count1+1].w > 0)
            {
                apply_clip(enemyship[count1+1].x,enemyship[count1+1].y,objects,screen,&stuffclip[clip]);
            }
            count1 += 2;
        }
        if (enemyship[shipnum].x < 0)
        {
            new_wave = true;
        }
    }

}
void enemyship_1::set_up()
{
    new_wave = true;
    clip = 4;
}
int enemyship_1::coll_det()
{
    int cnt = 0;
    int cnt2 = 0;
    while (cnt < 12) //while loop to check each individual ship in the ships array
    {
        if (enemyship[cnt].w > 0)
        {
            cnt2 = 0;
            while (cnt2 < 13) //while loop checks whether the ship collided with any spaceship bullets
            {
                if (spaceship1.shootallot[cnt2].w > 0)
                {
                    if (DoC(enemyship[cnt].x,enemyship[cnt].y,50,50,spaceship1.shootallot[cnt2].x,spaceship1.shootallot[cnt2].y,5,20) == 1)
                    {
                        enemyship[cnt].w -= 1;
                        spaceship1.shootallot[cnt2].w = 0;
                        if (enemyship[cnt].w == 0)
                        {
                            explo_line += 1;
                            if (explo_line > 14) explo_line = 0;
                            explodeallot[explo_line].x = enemyship[cnt].x;
                            explodeallot[explo_line].y = enemyship[cnt].y;
                            explodeallot[explo_line].w = 1;
                            main_points += 7;
                        }
                        return 1;
                    } //end of the collision if with the big enemyship and a bullet
                } //end of if the bullet is alive
            cnt2 += 1;
            } //end of loop searching bullets
        }
        cnt += 1;
    } //end of loop searching the individual ships
    return 0;
}

class enemyship_2
{
    public:
    SDL_Rect ships[14];
    void movement(int);
    int collision();
    void set_up();
    int shipmax;
    int count1;
    int shootque;
    SDL_Rect shootline[13];
    void handle_fire();
    int time1;
    int clip1;
} the_enemy2;
void enemyship_2::movement(int level)
{
    //functions will update the max number of ships, max number will increase wiith the levels
    //for these small ships, the width is 52, height is 50
    if (level >= 5) shipmax = 3;
    if (level >= 10) shipmax = 5;
    if (level >= 15) shipmax = 7;
    if (level >= 20) shipmax = 9;
    if (level >= 25) shipmax = 11;
    if (level > 30) shipmax = 13;
    //initializes ships if dead, provides random x-value,starting y-value,random y-destination in h
    count1 = 0;
    int count2 = 800/shipmax;
    while (count1 <= shipmax)
    {
        if (ships[count1].w <= 0)
        {
            ships[count1].x = rand_num(50,150)+(count2*count1);
            ships[count1].y = -50;
            ships[count1].w = 1;
            ships[count1].h = rand_num(10,26)*rand_num(count1+4,15);
        }
        count1 += 1;
    }
//add movement towards the y destination, movment based on var h ,when to shoot,
//and when to commit suicide bombing :D
    if (clip1 == 6) clip1 = 7;
    else clip1 = 6;
    count1 = 0;
    while (count1 <= shipmax)
    {
        if (ships[count1].w == 1)
        {
            if (ships[count1].y < ships[count1].h)
            {
                ships[count1].y += 5;
            }
            /*
            if (ships[count1].h*2 - ships[count1].x > 0)
            {
                ships[count1].x += 5;
            }
            else ships[count1].x -= 5;
            */
            if ((SDL_GetTicks() - time1 > 250) && (ships[count1].x + 50 > spaceship1.x) && (ships[count1].x - 50 < spaceship1.x) && (ships[count1].y < spaceship1.y))
            {
                time1 = SDL_GetTicks();
                shootque += 1;
                if (shootque > 12) shootque = 0;
                shootline[shootque].x = ships[count1].x + 26;
                shootline[shootque].y = ships[count1].y + 50;
                shootline[shootque].w = 450;
            }  //ends shooting if
            apply_clip(ships[count1].x,ships[count1].y,objects,screen,&stuffclip[clip1]);
        }  //ends the alive (.w = 1) if
        count1 += 1;
    } //ends the while loop for movement
    handle_fire();
}
//handle fire put in with the movement function
void enemyship_2::handle_fire()
{
    count1 = 0;
    while (count1 < 13)
    {
        if (shootline[count1].w > 0)
        {
            apply_clip(shootline[count1].x,shootline[count1].y,objects,screen,&stuffclip[17]);
            shootline[count1].y += 15;
            shootline[count1].w += 15;
        }
        count1 += 1;
    }
}
void enemyship_2::set_up()
{
    shootque = 0;
    time1 = SDL_GetTicks();
    int count = 0;
    while (count < 13)
    {
        shootline[count].x = 0;
        shootline[count].y = 0;
        shootline[count].w = 0;
        shootline[count].h = 0;
        count += 1;
    }
    count = 0;
    while (count < 14)
    {
        ships[count].w = 0;
        count += 1;
    }
}
int enemyship_2::collision()
{
    int cnt = 0;
    int cnt2 = 0;
    while (cnt <= shipmax) //while loop to check each individual ship in the ships array
    {
        cnt2 = 0;
        while (cnt2 < 13) //while loop checks whether the ship collided with any spaceship bullets
        {
            if (spaceship1.shootallot[cnt2].w > 0)
            {
                if (DoC(ships[cnt].x,ships[cnt].y,48,50,spaceship1.shootallot[cnt2].x,spaceship1.shootallot[cnt2].y,5,20) == 1)
                {
                    ships[cnt].w = 0;
                    spaceship1.shootallot[cnt2].w = 0;
                    explo_line += 1;
                    if (explo_line > 14) explo_line = 0;
                    explodeallot[explo_line].x = ships[cnt].x;
                    explodeallot[explo_line].y = ships[cnt].y;
                    explodeallot[explo_line].w = 1;
                    main_points += 7;
                    return 1;
                } //end of the collision if with the small enemyship and a bullet
            } //end of if the bullet is alive
        cnt2 += 1;
        } //end of loop searching bullets
        cnt += 1;
    } //end of loop searching the individual ships
    return 0;
}
int spaceship::collision_detct()
{
    //checks if the mainship collided with enemies or enemy fire
    int cnt = 0;
    while (cnt < 12)
    {
        if (the_enemy1.enemyship[cnt].w > 0)
        {
            if (DoC(x,y,w,h,the_enemy1.enemyship[cnt].x,the_enemy1.enemyship[cnt].y,50,45) == 1)
            {
                hurt = true;
                lives -= 1;
                the_enemy1.enemyship[cnt].w = 0;
                explo_line += 1;
                if (explo_line > 14) explo_line = 0;
                explodeallot[explo_line].x = the_enemy1.enemyship[cnt].x;
                explodeallot[explo_line].y = the_enemy1.enemyship[cnt].y;
                explodeallot[explo_line].w = 1;
                return 1;
            } //end of the collision if with the big enemyships
        }
        cnt += 1;
    } //end of the while for the big enemyships
    cnt = 0;
    while (cnt <= the_enemy2.shipmax)
    {
        if (the_enemy2.ships[cnt].w > 0)
        {
            if (DoC(x,y,w,h,the_enemy2.ships[cnt].x,the_enemy2.ships[cnt].y,45,45) == 1)
            {
                hurt = true;
                lives -= 1;
                the_enemy2.ships[cnt].w = 0;
                explo_line += 1;
                if (explo_line > 14) explo_line = 0;
                explodeallot[explo_line].x = the_enemy2.ships[cnt].x;
                explodeallot[explo_line].y = the_enemy2.ships[cnt].y;
                explodeallot[explo_line].w = 1;
                return 1;
            } //end of the collision if with the small ships
        }
        cnt += 1;
    } //end of the while for the smmall ships


    cnt = 0;
    while (cnt < 13)
    {
        if (the_enemy2.shootline[cnt].w > 0)
        {
            if (DoC(x,y,w,h,the_enemy2.shootline[cnt].x,the_enemy2.shootline[cnt].y,5,25) == 1)
            {
                hurt = true;
                lives -= 1;
                the_enemy2.shootline[cnt].w = 0;
                return 1;
            } //end of the collision if with the small ships bulletstststs
        }
        cnt += 1;
    } //end of the while for the smmall ships bulletstststs

return 0;
}

int pack_time = SDL_GetTicks();
int px,py;
void health_pack()
{
    if (SDL_GetTicks() - pack_time > (45000 - (main_level*1000)))
    {
        pack_time = SDL_GetTicks();
        px = rand_num(50,950);
        py = 0;
    }
    if (py < 500)
    {
        apply_clip(px,py,objects,screen,&stuffclip[9]);
        if (DoC(spaceship1.x,spaceship1.y,spaceship1.w,spaceship1.h,px,py,34,30) == 1)
        {
            py = 550;
            lives += 2;
        }
        py += 5;
    }
}

int handle_lose()
{
    char the_score[15];
    std::ifstream score_file ("scores.txt");
    score_file >> the_score;
    int fad = atoi (the_score);
    score_file.close();
    if (main_points > fad)
    {
        std::ofstream score_file ("scores.txt",std::ios::trunc);
        score_file << main_points;
        score_file.close();
    }
    background = load_image("lose.png");
    //'new game' button = buttonclip[1], 4, and 7
    //back to menu button = buttonclip[20], 21, and 22
    bool losescreen = true;
    b_1.set_up_button(300,200,buttonclip[1].w,buttonclip[1].h,1,4,7);
    b_2.set_up_button(300,300,buttonclip[20].w,buttonclip[20].h,20,21,22);
//write the code for the lose screen to turn back to the game or the menu
//write code for the buttons and set them up, display lose screen, make sure to quit the lose
//screen, quit the game loop, and set the true statement for the menu screen (or exit the game)
    while (losescreen == true)
    {
        apply_surface(0,0,background,screen);
        b_1.show_button();
        b_2.show_button();
        SDL_Flip(screen);
        if (SDL_PollEvent(&event))
        {
            if (b_1.check_button() == 3)
            {
                //new game, goto beggining of mainlevels
                losescreen = false;
                the_game_on = false;
                return 1;
            }
            if (b_2.check_button() == 3)
            {
                //menu, goto first menu
                losescreen = false;
                the_game_on = false;
                return 0;
            }
            if (event.type == SDL_QUIT)
            {
                losescreen == false;
                return -1;
            }
        }
        SDL_Delay(55);
    }

}


int the_game()
{
    main_level = 1;
    inclevel = 15;
    the_game_on = true;
    lives = 5;
    explo_line = 0;
    pack_time = SDL_GetTicks();

    background = load_image("space2.png");
    objects = load_image("objects.png");
    //set_up_mainlevel();
    set_stuffclip();
    levelback.x = 0;
    levelback.y = 0;
    levelback.w = 1000;
    levelback.h = 500;
    count = 0;
    py = 550;
    spaceship1.set_up_ship();
    the_enemy1.set_up();
    the_enemy2.set_up();
    set_explode();
    output = load_image("alphabet.bmp");

    while (the_game_on == true)
    {
        thescreen.scroll(3);
        if (main_level >= 5) the_enemy2.movement(main_level);
        spaceship1.movement(10);
        spaceship1.show();
        spaceship1.shooting();
        the_enemy1.movement_animation();
        spaceship1.collision_detct();
        if (main_level >= 5) the_enemy2.collision();
        the_enemy1.coll_det();
        eXplode();
        output_string("Points:",10,10,20,screen,1);
        output_number(main_points,160,10,20,screen,1);
        output_number(lives,10,32,20,screen,1);
        health_pack();
        SDL_Flip(screen);
        if (lives == 0)
        {
            int path1 = handle_lose();
            switch (path1)
            {
                case -1:
                return -1;
                case 0:
                return 0;
                case 1:
                return 1;
            } // -1 = end total game, 0 = goto start menu, 1 = loop again
        }
        level_inc();
        //Uint8 *keystates = SDL_GetKeyState( NULL );
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                the_game_on = false;
                return -1;
            }
        }
        SDL_Delay(50);
    } //end of the game loop

return 0;
} //end of the game function
