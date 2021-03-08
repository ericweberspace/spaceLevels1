
SDL_Event event;
//int main_level;
int main_points;
int maneuver_level;
int maneuver_points;
bool mainlevelson;
bool maneuver_on;
bool maneuver_gameloop;
int count;

SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *buttons = NULL;
SDL_Surface *objects = NULL;

SDL_Surface *load_image(std::string filename)
{

    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load(filename.c_str() );
    optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);

    Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
    SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
    return optimizedImage;

}

void apply_clip(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
    SDL_Rect offset1;

    offset1.x = x;
    offset1.y = y;
    SDL_BlitSurface(source,clip,destination,&offset1);

}

void apply_surface(int x,int y, SDL_Surface* source1, SDL_Surface* destination1)
{
    SDL_Rect offset2;
    offset2.x = x;
    offset2.y = y;
    SDL_BlitSurface(source1,NULL,destination1,&offset2);

}

int rand_num(int low, int high)
{

    int randnumber;
    /*
    time_t seconds;
    time(&seconds);
    */
    Uint32 the_time = SDL_GetTicks();
    srand((unsigned int) the_time);
    randnumber = rand() % (high - low + 1) + low;
    return randnumber;
}


//for the clips...
//the output alphabet is (0 to 73): A B C D E F G H I J K L M N O P Q R S T U V W X Y Z a b c d e f
//g h i j k l m n o p q r s t u v w x y z 0 1 2 3 4 5 6 7 8 9 ! ? . , $ ( ) + - = :
SDL_Rect smallfont[74];
SDL_Rect largefont[74];
void set_smallfont()
{
    int count = 0;
    int x = 23;
    int y = 5;
    int w = 20;
    int h = 25;
    while (count <= 73)
    {
        smallfont[count].x = x;
        smallfont[count].y = y;
        smallfont[count].w = w;
        smallfont[count].h = h;
        x = x + 64;
        count = count + 1;
    }
}
void set_largefont()
{
    int count = 0;
    int x = 20;
    int y = 40;
    int w = 27;
    int h = 40;
    while (count <= 73)
    {
        largefont[count].x = x;
        largefont[count].y = y;
        largefont[count].w = w;
        largefont[count].h = h;
        x = x + 64;
        count = count + 1;
    }

}

SDL_Surface *output = NULL;
void output_string(std::string text,int x, int y,int w,SDL_Surface *outdest,int font)
{
    int charnum = 0;
    int clipnumber = 0;
    int length = text.length() - 1;
    while (charnum <= length)
    {
        //(0 to 73)
        switch (text[charnum])
        {
            case 'A':
            clipnumber = 0;
            break;
            case 'B':
            clipnumber = 1;
            break;
            case 'C':
            clipnumber = 2;
            break;
            case 'D':
            clipnumber = 3;
            break;
            case 'E':
            clipnumber = 4;
            break;
            case 'F':
            clipnumber = 5;
            break;
            case 'G':
            clipnumber = 6;
            break;
            case 'H':
            clipnumber = 7;
            break;
            case 'I':
            clipnumber = 8;
            break;
            case 'J':
            clipnumber = 9;
            break;
            case 'K':
            clipnumber = 10;
            break;
            case 'L':
            clipnumber = 11;
            break;
            case 'M':
            clipnumber = 12;
            break;
            case 'N':
            clipnumber = 13;
            break;
            case 'O':
            clipnumber = 14;
            break;
            case 'P':
            clipnumber = 15;
            break;
            case 'Q':
            clipnumber = 16;
            break;
            case 'R':
            clipnumber = 17;
            break;
            case 'S':
            clipnumber = 18;
            break;
            case 'T':
            clipnumber = 19;
            break;
            case 'U':
            clipnumber = 20;
            break;
            case 'V':
            clipnumber = 21;
            break;
            case 'W':
            clipnumber = 22;
            break;
            case 'X':
            clipnumber = 23;
            break;
            case 'Y':
            clipnumber = 24;
            break;
            case 'Z':
            clipnumber = 25;
            break;

            case 'a':
            clipnumber = 26;
            break;
            case 'b':
            clipnumber = 27;
            break;
            case 'c':
            clipnumber = 28;
            break;
            case 'd':
            clipnumber = 29;
            break;
            case 'e':
            clipnumber = 30;
            break;
            case 'f':
            clipnumber = 31;
            break;
            case 'g':
            clipnumber = 32;
            break;
            case 'h':
            clipnumber = 33;
            break;
            case 'i':
            clipnumber = 34;
            break;
            case 'j':
            clipnumber = 35;
            break;
            case 'k':
            clipnumber = 36;
            break;
            case 'l':
            clipnumber = 37;
            break;
            case 'm':
            clipnumber = 38;
            break;
            case 'n':
            clipnumber = 39;
            break;
            case 'o':
            clipnumber = 40;
            break;
            case 'p':
            clipnumber = 41;
            break;
            case 'q':
            clipnumber = 42;
            break;
            case 'r':
            clipnumber = 43;
            break;
            case 's':
            clipnumber = 44;
            break;
            case 't':
            clipnumber = 45;
            break;
            case 'u':
            clipnumber = 46;
            break;
            case 'v':
            clipnumber = 47;
            break;
            case 'w':
            clipnumber = 48;
            break;
            case 'x':
            clipnumber = 49;
            break;
            case 'y':
            clipnumber = 50;
            break;
            case 'z':
            clipnumber = 51;
            break;

            case '0':
            clipnumber = 52;
            break;
            case '1':
            clipnumber = 53;
            break;
            case '2':
            clipnumber = 54;
            break;
            case '3':
            clipnumber = 55;
            break;
            case '4':
            clipnumber = 56;
            break;
            case '5':
            clipnumber = 57;
            break;
            case '6':
            clipnumber = 58;
            break;
            case '7':
            clipnumber = 59;
            break;
            case '8':
            clipnumber = 60;
            break;
            case '9':
            clipnumber = 61;

            case '!':
            clipnumber = 62;
            break;
            case '?':
            clipnumber = 63;
            break;
            case '.':
            clipnumber = 64;
            break;
            case ',':
            clipnumber = 65;
            break;
            case '$':
            clipnumber = 66;
            break;
            case '(':
            clipnumber = 67;
            break;
            case ')':
            clipnumber = 68;
            break;
            case '+':
            clipnumber = 69;
            break;
            case '-':
            clipnumber = 70;
            break;
            case '=':
            clipnumber = 71;
            break;
            case ':':
            clipnumber = 72;
            break;
            case ' ':
            clipnumber = 73;
        }
        if (font == 1)
        {
            apply_clip(x,y,output,outdest,&smallfont[clipnumber]);
        }
        if (font == 2)
        {
            apply_clip(x,y,output,outdest,&largefont[clipnumber]);
        }
        x = x + w;
        charnum = charnum + 1;
    }
}

//note to self... never load an image in function that has to run in a loop that repeats
//in less than a second... it will slow down the loop
void output_number(int number,int x, int y,int w,SDL_Surface *outdest,int font)
{
    char numberchar[10];
    itoa(number,numberchar,10);
    int length = strlen(numberchar);
    int clipnumber;
    int zeros = 1;
    int strnum = 0;
    while (strnum < length)
    {
        if ((numberchar[strnum] == '0') && (zeros == 1) && (length > 1)){zeros = 1;}else{zeros = 0;}
        if (zeros != 1)
        {
            switch (numberchar[strnum])
            {
                case '0':
                clipnumber = 52;
                break;
                case '1':
                clipnumber = 53;
                break;
                case '2':
                clipnumber = 54;
                break;
                case '3':
                clipnumber = 55;
                break;
                case '4':
                clipnumber = 56;
                break;
                case '5':
                clipnumber = 57;
                break;
                case '6':
                clipnumber = 58;
                break;
                case '7':
                clipnumber = 59;
                break;
                case '8':
                clipnumber = 60;
                break;
                case '9':
                clipnumber = 61;
            }
            if (font == 1)
            {
                apply_clip(x,y,output,outdest,&smallfont[clipnumber]);
            }
            if (font == 2)
            {
                apply_clip(x,y,output,outdest,&largefont[clipnumber]);
            }
            x = x + w;
        }
        strnum = strnum + 1;
    }
    //end of the looooop
}

/*
void char_to_num(char *arry1,int *arry2,int len)
{
        int cnt = 0;
        while (cnt <= len)
        {
            *(arry2+cnt) = atoi(*(arry1+cnt));
            cnt += 1;
        }
}
*/
int button1 = 0;
/*
switch (button1)
{
    //normal
    case 0:
    apply_clip(,,scource,screen,&);
    break;
    //mouse motion
    case 1:
    apply_clip(,,scource,screen,&);
    break;
    //click
    case 2:
    apply_clip(,,scource,screen,&);
    break;
}
*/
int place_button(int x, int y, int w, int h)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    int mouse_x;
    int mouse_y;
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        mouse_x = event.button.x;
        mouse_y = event.button.y;
        if ((mouse_x > x) && (mouse_y > y) && (mouse_x < x + w) && (mouse_y < y + h))
        {
            button1 = 2;
            return 2;
        }
        else
        {
            button1 = 0;
        }
    }
    if (event.type == SDL_MOUSEMOTION)
    {
        mouse_x = event.button.x;
        mouse_y = event.button.y;
        if ((mouse_x > x) && (mouse_y > y) && (mouse_x < x + w) && (mouse_y < y + h))
        {
            button1 = 1;
            return 1;
        }
        else
        {
            button1 = 0;
        }
    }
    if (event.type == SDL_MOUSEBUTTONUP)
    {
        mouse_x = event.button.x;
        mouse_y = event.button.y;
        if ((mouse_x > x) && (mouse_y > y) && (mouse_x < x + w) && (mouse_y < y + h))
        {
            return 3;
        }
    }
}



//=============================================================
//ORIGINALLY IN THE SOURCE.CPP FILE, NEEDS TO BE DECLARED FOR MAINLEVELS.CPP
//=============================================================

SDL_Rect buttonclip[23];


void set_buttonclip()
{
buttonclip[0].x = 5;
buttonclip[0].y = 3;
buttonclip[0].w = 420;
buttonclip[0].h = 108;

buttonclip[1].x = 7;
buttonclip[1].y = 115;
buttonclip[1].w = 228;
buttonclip[1].h = 55;

buttonclip[2].x = 5;
buttonclip[2].y = 170;
buttonclip[2].w = 241;
buttonclip[2].h = 54;

buttonclip[3].x = 10;
buttonclip[3].y = 225;
buttonclip[3].w = 86;
buttonclip[3].h = 54;

buttonclip[4].x = 267;
buttonclip[4].y = 117;
buttonclip[4].w = 230;
buttonclip[4].h = 60;

buttonclip[5].x = 265;
buttonclip[5].y = 177;
buttonclip[5].w = 236;
buttonclip[5].h = 53;

buttonclip[6].x = 271;
buttonclip[6].y = 236;
buttonclip[6].w = 83;
buttonclip[6].h = 49;

buttonclip[7].x = 530;
buttonclip[7].y = 127;
buttonclip[7].w = 223;
buttonclip[7].h = 50;

buttonclip[8].x = 531;
buttonclip[8].y = 177;
buttonclip[8].w = 230;
buttonclip[8].h = 53;

buttonclip[9].x = 528;
buttonclip[9].y = 232;
buttonclip[9].w = 93;
buttonclip[9].h = 58;

buttonclip[10].x = 791;
buttonclip[10].y = 11;
buttonclip[10].w = 113;
buttonclip[10].h = 433;

buttonclip[11].x = 6;
buttonclip[11].y = 301;
buttonclip[11].w = 244;
buttonclip[11].h = 54;

buttonclip[12].x = 9;
buttonclip[12].y = 352;
buttonclip[12].w = 210;
buttonclip[12].h = 46;

buttonclip[13].x = 10;
buttonclip[13].y = 394;
buttonclip[13].w = 241;
buttonclip[13].h = 54;

buttonclip[14].x = 263;
buttonclip[14].y = 301;
buttonclip[14].w = 243;
buttonclip[14].h = 55;

buttonclip[15].x = 262;
buttonclip[15].y = 351;
buttonclip[15].w = 204;
buttonclip[15].h = 46;

buttonclip[16].x = 262;
buttonclip[16].y = 395;
buttonclip[16].w = 243;
buttonclip[16].h = 50;

buttonclip[17].x = 510;
buttonclip[17].y = 307;
buttonclip[17].w = 237;
buttonclip[17].h = 49;

buttonclip[18].x = 509;
buttonclip[18].y = 355;
buttonclip[18].w = 212;
buttonclip[18].h = 42;

buttonclip[19].x = 509;
buttonclip[19].y = 396;
buttonclip[19].w = 241;
buttonclip[19].h = 49;

buttonclip[20].x = 8;
buttonclip[20].y = 442;
buttonclip[20].w = 114;
buttonclip[20].h = 50;

buttonclip[21].x = 145;
buttonclip[21].y = 445;
buttonclip[21].w = 118;
buttonclip[21].h = 49;

buttonclip[22].x = 285;
buttonclip[22].y = 452;
buttonclip[22].w = 117;
buttonclip[22].h = 43;


}
class button
{
    int state;
    int states[4];
    //0 - norm, 1 - motion, 2 - down, 3 - up
    public:
    int x,y,w,h;
    void set_up_button(int,int,int,int,int,int,int);
    int check_button();
    void show_button();
    void set_buttonclip();
} b_1,b_2,b_3;
void button::set_up_button(int bx,int by,int bw,int bh, int n, int o,int d)
{
    x = bx;
    y = by;
    w = bw;
    h = bh;
    states[0] = n;
    states[1] = o;
    states[2] = d;
    state = states[0];
}
int button::check_button()
{
    int m_x;
    int m_y;
    if (event.type == SDL_MOUSEBUTTONUP)
    {
        m_x = event.button.x;
        m_y = event.button.y;
        if ((m_x > x) && (m_y > y) && (m_x < x + w) && (m_y < y + h))
        {
            return 3;
        }
        else
        {
            state = states[0];
        }
    }
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        m_x = event.button.x;
        m_y = event.button.y;
        if ((m_x > x) && (m_y > y) && (m_x < x + w) && (m_y < y + h))
        {
            state = states[2];
            return 2;
        }
        else
        {
            state = states[0];
        }
    }
    if (event.type == SDL_MOUSEMOTION)
    {
        m_x = event.motion.x;
        m_y = event.motion.y;
        if ((m_x > x) && (m_y > y) && (m_x < x + w) && (m_y < y + h))
        {
            state = states[1];
            return 1;
        }
        else state = states[0];
    }
    state = states[0];
    return 0;
}
void button::show_button()
{
    if (state == states[0])
    {
        apply_clip(x,y,buttons,screen,&buttonclip[state]);
    }
    if (state == states[1])
    {
        apply_clip(x,y,buttons,screen,&buttonclip[state]);
    }
    if (state == states[2])
    {
        apply_clip(x,y,buttons,screen,&buttonclip[state]);
    }
}

void debugex()
{
    output = load_image("alphabet.bmp");
    output_string("this works",100,100,15,screen,2);
    SDL_Flip(screen);
}

int char_2_num(char what)
{
    switch (what)
    {
        case '0':
        return 0;
        case '1':
        return 1;
        case '2':
        return 2;
        case '3':
        return 3;
        case '4':
        return 4;
        case '5':
        return 5;
        case '6':
        return 6;
        case '7':
        return 7;
        case '8':
        return 8;
        case '9':
        return 9;
    }

}
//===================================================
//END OF CODE FROM SOURCE.CPP
//===================================================


