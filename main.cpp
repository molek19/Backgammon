#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"conio2.h"
#include <cstdlib>
#include <ctime>
const int h = 21; //board height
const int w = 80; //board width
const int mh = 5; //move in height
const int mw = 10; //move in width
const int iX = 3; // x component of interface
const int iY = 28; // y component of interface
const int gsX = 15; //x component of game state
const int gsY = 2; // y component of game state
const int doX = 95; // x component of diece one
const int doY = 10;// y component of diece one
const int dtX = 95;//x component of diece two
const int dtY = 11;//y component of diece two
const int tX = 95;//x component of turn
const int tY = 5;//y component of turn
const int cX = 15;//x component of communicate
const int cY = 4;//y component of communicate
const int aihX = 25;//x component of all in home detector
const int aihY = 1;//y component of all in home dtector
const int sgX = 95;//x component of save 
const int sgY = 15;//y component of save
const int wsX = 95;//x component of white score
const int wsY = 13;//y component of white score
const int rsX = 95;//x component of red score
const int rsY = 14;//y component of red score

//struct for fields coordinates
struct fc {

    int x;
    int y;

};

//struct for bar coordinates
struct bc {

    int x;
    int y;
};

//struct for double linked list
struct Node {
    char** board;
    Node* next;
    Node* prev;
};

//save to double linked list actual state of the board
void collect_all_board_states(char board[h][w], Node*& head, Node*& tails) {
    Node* newNode = new Node;
    newNode->board = new char* [h];
    newNode->prev = nullptr;
    for (int i = 0; i < h; i++) {
        newNode->board[i] = new char[w];
        for (int j = 0; j < w; j++) {
            newNode->board[i][j] = board[i][j];
        }
    }
    newNode->next = nullptr;
    Node* curr = head;
    if (head == nullptr) {
        head = newNode;
    }
    if (curr != nullptr)
    {
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
        newNode->prev = curr;
        tails = newNode;
    }

}

//show on screen working functionalities
void interface()
{
    gotoxy(iX, iY);
    cputs("p - PLAY _ n - NEW GAME _ q - QUIT _ r - ROLL THE DICE _ i - CHOOSE STONE _ m - SKIP _ s - SAVE _ l - LOAD");
    gotoxy(iX, iY + 2);
    cputs("v - SAVE AND SHOW MOVES FROM PREVIOUS DUEL (WORK ONLY AFTER DUEL)");
}

//show on screen scores of each player
void players_scores(char txt[32], int rs, int sw)
{
    gotoxy(rsX, rsY);
    sprintf(txt, "RED SCORE: %d", rs);
    cputs(txt);
    gotoxy(wsX, wsY);
    sprintf(txt, "WHITE SCORE: %d", sw);
    cputs(txt);
}

//show on screen state of the game
void game_state(bool in_progress)
{
    if (in_progress)
    {
        gotoxy(gsX, gsY);
        cputs("GAME IN PROGRESS");
    }
    else
    {
        gotoxy(gsX, gsY);
        cputs("PRESS -p- TO START THE GAME");
    }
}

//show on screen actual important informations
void communicates(int v)
{
    gotoxy(cX, cY);
    cputs("");
    if (v == 1)
    {
        cputs("PRESS 't' TO START MOVE");
    }
    else if (v == 3)
    {
        cputs("NOT EVEN A STONE !");
    }
    else if (v == 4)
    {
        cputs("NOT YOUR STONE !");
    }
    else if (v == 5)
    {
        cputs("MOVE WITH DICE ONE");
    }
    else if (v == 6)
    {
        cputs("MOVE WITH DICE TWO");
    }
    else if (v == 8)
    {
        cputs("RED MUST MOVE FROM BAR");
    }
    else if (v == 9)
    {
        cputs("WHITE MUST MOVE FROM BAR");
    }
   
    else if (v == 10)
    {
        cputs("DOUBLE !");
    }
    else if (v == 11)
    {
        cputs("WRONG DESTINATION FIELD TRY AGAIN");
    }
    else if (v == 12)
    {
        cputs("RED WON PRESS 'n' TO START NEW DUEL");
    }
    else if (v == 13)
    {
        cputs("WHITE WON PRESS 'n' TO START NEW DUEL");
    }
}

//show on screen that all stones of each player are in home 
void all_in_home(int value)
{
    if (value == 1)
    {
        gotoxy(aihX, aihY);
        cputs("ALL RED STONES IN HOME");
    }
    else if (value == 2)
    {
        gotoxy(aihX, aihY);
        cputs("ALL WHITE STONES IN HOME");
    }
    else if (value == 3)
    {
        gotoxy(aihX, aihY);
        cputs("");
    }
    else if (value == 4)
    {
        gotoxy(aihX, aihY);
        cputs("BOTH WHITES AND REDS IN HOMES");
    }
}

//fill baord with all characters
void fill_b(char board[h][w]) //fucntion which filling the board
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if ((j == 0) || ((j == 1) && (i != 0) && (i != (h)-1)) || (j == w - 1) || ((j == w - 2) && i != 0 && (i != (h)-1)))
            {
                board[i][j] = ':';
            }
            else if ((i == 0 && j != 0 && j != w - 1) || (i == (h)-1 && j != 0 && j != w - 1))
            {
                board[i][j] = '=';
            }
            else if ((j == w / 2 - 1 || j == w / 2 - 2 || j == w / 2) && i != 0 && i != h - 1)
            {
                if (i == h / 2)
                {
                    if (j == w / 2 - 2)
                    {
                        board[i][j] = 'B';
                    }
                    else if (j == w / 2 - 1)
                    {
                        board[i][j] = 'A';
                    }
                    else if (j == w / 2)
                    {
                        board[i][j] = 'R';
                    }
                }
                else
                {
                    board[i][j] = '|';
                }

            }
            else if (board[i][j] == 'o')
            {
                board[i][j] = 'o';
            }
            else
            {
                board[i][j] = '~';
            }
        }
    }
}

//put default stone steup in board
void default_stones(char board[h][w])//function establish default setup of stones
{
    //down side
    //#-red stone %-white stone
    int pX = h - 2;
    int pY = 4;
    while (pX >= h - 6)
    {
        board[pX][pY] = '#';
        pX--;
    }
    pX = h - 2;
    pY = 28;
    while (pX >= h - 4)
    {
        board[pX][pY] = '%';
        pX--;
    }
    pX = h - 2;
    pY = 44;
    while (pX >= h - 6)
    {
        board[pX][pY] = '%';
        pX--;
    }
    pX = h - 2;
    pY = 74;
    while (pX >= h - 3)
    {
        board[pX][pY] = '#';
        pX--;
    }

    //upper side
    pX = 1;
    pY = 4;
    while (pX <= 5)
    {
        board[pX][pY] = '%';
        pX++;
    }
    pX = 1;
    pY = 28;
    while (pX <= 3)
    {
        board[pX][pY] = '#';
        pX++;
    }
    pX = 1;
    pY = 44;
    while (pX <= 5)
    {
        board[pX][pY] = '#';
        pX++;
    }
    pX = 1;
    pY = 74;
    while (pX <= 2)
    {
        board[pX][pY] = '%';
        pX++;
    }
}

//find proper coordinates for fields
void where_field(char board[h][w], int spw, int sph, bool red_or_black)//fucntion searching for proper field coordinates
{
    int gwh = sph;
    int gww = spw;
    bool gnf = false;
    do
    {
        if (gnf == false)
        {

            if (gwh <= sph + 4)
            {
                if (red_or_black)
                {
                    board[gwh][gww] = '|';
                }
                else
                {
                    board[gwh][gww] = '"';
                }
                gwh++;
            }
            else
            {
                gwh = sph;
                gww += 2;
                gnf = true;
            }
        }
        else
        {

            if (gwh <= sph + 4)
            {
                if (red_or_black)
                {
                    board[gwh][gww] = '|';
                }
                else
                {
                    board[gwh][gww] = '"';
                }
                gwh++;
            }
            else
            {
                gwh = sph;
                gww += 4;
                gnf = false;
                if (board[sph + 4][gww - 4] == '|')
                {
                    red_or_black = false;
                }
                else if (board[sph + 4][gww - 4] == '"')
                {
                    red_or_black = true;
                }
            }
        }
    } while (gww < spw + w / 2 - 5 && gwh <= sph + 6);
}

//fill board with fields
void fill_fields(char board[h][w])
{
    where_field(board, 3, 1, true);
    where_field(board, 3, (2 * h) / 3 + 1, false);
    where_field(board, w / 2 + 3, 1, true);
    where_field(board, w / 2 + 3, (2 * h) / 3 + 1, false);

}

//show board on screen
void print_board(char board[h][w])
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (board[i][j] == '"')
            {
                gotoxy(mw + j, mh + i);
                textcolor(RED);
                cputs("|");
            }
            else if (board[i][j] == '%')
            {
                gotoxy(mw + j, mh + i);
                textcolor(WHITE);
                cputs("o");
            }
            else if (board[i][j] == '#')
            {
                gotoxy(mw + j, mh + i);
                textcolor(RED);
                cputs("o");
            }
            else if (board[i][j] == '~')
            {
                gotoxy(mw + j, mh + i);
                textcolor(WHITE);
                cputs(" ");
            }
            else
            {
                gotoxy(mw + j, mh + i);
                textcolor(WHITE);
                putch(board[i][j]);
            }
        }
        cputs("\n");
    }
}

//randomize dice one result
int diece_one()
{
    int diece_one = 0;

    diece_one = rand() % 6 + 1;

    return diece_one;
}

//randomize dice two result
int diece_two()
{
    int diece_two = 0;

    diece_two = rand() % 6 + 1;

    return diece_two;
}

//show on screen result of dices
void dieces_result(char txt[32], bool rd, int dor, int dtr)
{
    if (rd)
    {
        gotoxy(doX, doY);
        sprintf(txt, "DIECE ONE (RED ONE): %02d", dor);
        cputs(txt);
        gotoxy(dtX, dtY);
        sprintf(txt, "DIECE TWO (WHITE ONE): %02d", dtr);
        cputs(txt);
    }
    else
    {
        gotoxy(doX, doY);
        cputs("DIECE ONE: --");
        gotoxy(dtX, dtY);
        cputs("DIECE TWO: --");
    }

}

//show on screen whose turn is now
void whos_moving(char t)
{
    if (t == 'R')
    {
        gotoxy(tX, tY);
        cputs("RED ONE TURN");
    }
    else if (t == 'W')
    {
        gotoxy(tX, tY);
        cputs("WHITE ONE TURN");
    }
}

//fill structures of bar and fields with proper coordinates
void fill(fc field[24], bc red_bar[9], bc white_bar[9])//fuction fill board with proper fields signs and bar structure with coordinates
{
    field[0].y = 74;
    for (int i = 1; i < 6; i++)
    {
        field[i].y = field[i - 1].y - 6;
    }
    field[6].y = 34;
    for (int i = 7; i < 12; i++)
    {
        field[i].y = field[i - 1].y - 6;
    }
    field[12].y = 4;
    for (int i = 13; i < 18; i++)
    {
        field[i].y = field[i - 1].y + 6;
    }
    field[18].y = 44;
    for (int i = 19; i < 24; i++)
    {
        field[i].y = field[i - 1].y + 6;
    }
    for (int i = 0; i < 12; i++)
    {
        field[i].x = h - 1;
    }
    for (int i = 12; i < 24; i++)
    {
        field[i].x = 1;
    }
    int iterator = 0;
    for (int i = h / 2 - 1; i >= 1; i--)
    {
        red_bar[iterator].x = i;
        red_bar[iterator].y = w / 2 - 1;
        iterator++;
    }
    iterator = 0;
    for (int i = h / 2 + 1; i <= h - 2; i++)
    {
        white_bar[iterator].x = i;
        white_bar[iterator].y = w / 2 - 1;
        iterator++;
    }

}

//return values of coordinates of picked stone
int where_am_I(char board[h][w], int pfX, int pfY, fc field[24])
{
    if (pfX < 10)
    {
        pfX = 1;
    }
    else
    {
        pfX = h - 1;
    }
    for (int i = 0; i < 24; i++)
    {

        if (field[i].y == pfY && field[i].x == pfX)
        {
            return i;
        }
    }
    return 0;
}

//check that destination field is proper in case of color of the stone
bool check_color(char board[h][w], fc field[24], int wg, char turn)// fucntion check that dest field is proper in case of stone color
{
    int wgY = field[wg].y;
    int wgX = 0;

    if (wg < 12)
    {
        wgX = h - 2;
    }
    else
    {
        wgX = 1;
    }
    if (turn == 'R')
    {
        if (board[wgX][wgY] == '#' || board[wgX][wgY] == '~')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (turn == 'W')
    {
        if (board[wgX][wgY] == '%' || board[wgX][wgY] == '~')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

//check that it is possible to put stone at given destination
int can_I_put_here(char board[h][w], fc field[24], int wg, char turn)// function check if dest field is proper in case of free space
{
    if (check_color(board, field, wg, turn))
    {
        int wgY = field[wg].y;
        int wgX = 0;
        bool good_stone_type = false;

        if (wg < 12)
        {
            wgX = h - 2;

            for (int i = 0; i < 5; i++)
            {
                if (board[wgX][wgY] == '~')
                {
                    return wgX;//return x coord of destination place
                }
                wgX--;
            }
            return -1;
        }
        else
        {
            wgX = 1;
            for (int i = 0; i < 5; i++)
            {
                if (board[wgX][wgY] == '~')
                {
                    return wgX;
                }
                wgX++;
            }
            return -1;
        }
        return -1;
    }
    return -1;
}

//back to default variables values after move
void back_to_default_after_t(bool& ms, bool& rd, int& wc, bool& fm, bool& tp, bool& wm)
{
    ms = false;
    rd = false;
    wc = 0;
    fm = true;
    tp = false;
    wm = false;
}

//count actual number of stones at homes
void count_stones_in_homes(char board[h][w], fc field[24], int& rc, int& cw)
{
    rc = 0;
    cw = 0;
    int x_coord = 1;
    int y_coord = 44;

    for (int i = 0; i < 30; i++)
    {
        if (board[x_coord][y_coord] == '#')
        {
            rc++;
        }
        if (x_coord == 5)
        {
            x_coord = 1;
            y_coord += 6;
            continue;
        }
        x_coord++;
    }
    x_coord = h - 2;
    y_coord = 44;
    for (int i = 0; i < 30; i++)
    {
        if (board[x_coord][y_coord] == '%')
        {
            cw++;
        }
        if (x_coord == h - 6)
        {
            x_coord = h - 2;
            y_coord += 6;
            continue;
        }
        x_coord--;
    }
}

//remove stone
void get_out_stone(char board[h][w], int pfX, int pfY)
{
    board[pfX][pfY] = '~';
}

//find and remove farest stone at home
void remove_farest(char board[h][w], char turn)//fucntion work only in last phase, searching for the farest stone and remove them
{
    //go in homes form left to right and check where first stone will appear
    int x = 0;
    int y = 0;
    if (turn == 'R')
    {
        x = 5;
        y = 44;
        for (int i = 0; i < 30; i++)
        {
            if (board[x][y] == '#')
            {
                board[x][y] = '~';
                break;
            }
            if (x == 1)
            {
                x = 5;
                y += 6;
                continue;
            }
            x--;
        }
    }
    else if (turn == 'W')
    {
        x = h - 6;
        y = 44;
        for (int i = 0; i < 30; i++)
        {
            if (board[x][y] == '%')
            {
                board[x][y] = '~';
                break;
            }
            if (x == h - 2)
            {
                x = h - 6;
                y += 6;
                continue;
            }
            x++;
        }
    }
}

//check that at your destination field capturing is possible
bool can_capture(char board[h][w], char t, int wg, fc field[24]) // function checks if at dest field player can capture oponent stone
{
    int wgY = field[wg].y;
    int wgX = 0;
    int sc = 0;
    if (t == 'R')
    {
        if (wg < 12)
        {
            wgX = h - 2;
            for (int i = 0; i < 5; i++)
            {
                if (board[wgX][wgY] == '%')
                {
                    sc++;
                }
                wgX--;
            }
            if (sc == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            wgX = 1;
            for (int i = 0; i < 5; i++)
            {
                if (board[wgX][wgY] == '%')
                {
                    sc++;
                }
                wgX++;
            }
            if (sc == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else if (t == 'W')
    {
        if (wg < 12)
        {
            wgX = h - 2;
            for (int i = 0; i < 5; i++)
            {
                if (board[wgX][wgY] == '#')
                {
                    sc++;
                }
                wgX--;
            }
            if (sc == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            wgX = 1;
            for (int i = 0; i < 5; i++)
            {
                if (board[wgX][wgY] == '#')
                {
                    sc++;
                }
                wgX++;
            }
            if (sc == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}

//putting captured stone at bar as red player
void capturing_R(char board[h][w], char turn, int wg, fc field[24], bc white_bar[9], bc red_bar[9], int wgX, int wgY)
{
    if (wg < 12)
    {
        wgX = h - 2;
        board[wgX][wgY] = '#';
        for (int i = 0; i < 9; i++)
        {
            if (board[white_bar[i].x][white_bar[i].y] == '|')
            {
                board[white_bar[i].x][white_bar[i].y] = '%';
                break;
            }
        }
    }
    else
    {
        wgX = 1;
        board[wgX][wgY] = '#';
        for (int i = 0; i < 9; i++)
        {
            if (board[white_bar[i].x][white_bar[i].y] == '|')
            {
                board[white_bar[i].x][white_bar[i].y] = '%';
                break;
            }
        }
    }
}

//putting captured stone at bar as white player
void capturing_W(char board[h][w], char turn, int wg, fc field[24], bc white_bar[9], bc red_bar[9], int wgX, int wgY)
{
    if (wg < 12)
    {
        wgX = h - 2;
        board[wgX][wgY] = '%';
        for (int i = 0; i < 9; i++)
        {
            if (board[red_bar[i].x][red_bar[i].y] == '|')
            {
                board[red_bar[i].x][red_bar[i].y] = '#';
                break;
            }
        }
    }
    else
    {
        wgX = 1;
        board[wgX][wgY] = '%';
        for (int i = 0; i < 9; i++)
        {
            if (board[red_bar[i].x][red_bar[i].y] == '|')
            {
                board[red_bar[i].x][red_bar[i].y] = '#';
                break;
            }
        }
    }
}

//execute process of capturing for each player
void capturing(char board[h][w], char turn, int wg, fc field[24], bc white_bar[9], bc red_bar[9])//skrocic
{
    int wgY = field[wg].y;
    int wgX = 0;
    if (turn == 'R')
    {
        capturing_R(board, turn, wg, field, white_bar, red_bar, wgX, wgY);
    }
    else if (turn == 'W')
    {
        capturing_W(board, turn, wg, field, white_bar, red_bar, wgX, wgY);
    }
}

//function counts stones in red bar
int check_red_bar(char board[h][w], bc red_bar[9])
{
    int stones_counter = 0;
    for (int i = 0; i < 9; i++)
    {
        if (board[red_bar[i].x][red_bar[i].y] == '#')
        {
            stones_counter++;
        }
    }
    return stones_counter;
}

//fucntion counts stones in white bar
int check_white_bar(char board[h][w], bc white_bar[9])
{
    int stones_counter = 0;
    for (int i = 0; i < 9; i++)
    {
        if (board[white_bar[i].x][white_bar[i].y] == '%')
        {
            stones_counter++;
        }
    }
    return stones_counter;
}

//red one putting stone from bar to field
void out_of_bar_R(char board[h][w], int pfX, int pfY, fc field[24], int wg, int dor, int dtr, char t, bc r_bar[9], bc w_bar[9], bool& wm, int& wc, bool& pd)
{
    int wg1 = dor - 1;
    int psX = can_I_put_here(board, field, wg1, t);
    int psY = field[wg1].y;
    if (can_capture(board, t, wg1, field))
    {
        board[pfX][pfY] = '|';
        capturing(board, t, wg1, field, w_bar, r_bar);
        pd = 1;
        wm = 0;
    }
    else if (psX != -1)
    {
        board[pfX][pfY] = '|';
        board[psX][psY] = '#';
        pd = 1;
        wm = 0;
    }
    else if (psX == -1)
    {
        wm = 1;
        wc = 11;

    }
    if (!pd)
    {
        int wg2 = dtr - 1;
        psX = can_I_put_here(board, field, wg2, t);
        psY = field[wg2].y;
        if (can_capture(board, t, wg2, field))
        {
            board[pfX][pfY] = '|';
            capturing(board, t, wg2, field, w_bar, r_bar);
            wm = 0;
        }
        else if (psX != -1)
        {
            board[pfX][pfY] = '|';
            board[psX][psY] = '#';
            wm = 0;
        }
        else if (psX == -1)
        {
            wm = 1;
            wc = 11;

        }
    }
}

//white one putting stone form bar to field
void out_of_bar_W(char board[h][w], int pfX, int pfY, fc field[24], int wg, int dor, int dtr, char t, bc r_bar[9], bc w_bar[9], bool& wm, int& wc, bool& pd)
{
    int wg1 = (dor - 24) * -1;
    int psX = can_I_put_here(board, field, wg1, t);
    int psY = field[wg1].y;
    if (can_capture(board, t, wg1, field))
    {
        board[pfX][pfY] = '|';
        capturing(board, t, wg1, field, w_bar, r_bar);
        pd = 1;
    }
    else if (psX != -1)
    {
        board[pfX][pfY] = '|';
        board[psX][psY] = '%';
        pd = 1;
    }
    else if (psX == -1)
    {
        wm = 1;
        wc = 11;

    }
    if (!pd)
    {
        int wg2 = (dtr - 24) * -1;
        psX = can_I_put_here(board, field, wg2, t);
        psY = field[wg2].y;
        if (can_capture(board, t, wg2, field))
        {
            board[pfX][pfY] = '|';
            capturing(board, t, wg2, field, w_bar, r_bar);
        }
        else if (psX != -1)
        {
            board[pfX][pfY] = '|';
            board[psX][psY] = '%';
        }
        else if (psX == -1)
        {
            wm = 1;
            wc = 11;

        }
    }
}

//executions of putting stoe form bar to field
void out_of_bar(char board[h][w], int pfX, int pfY, fc field[24], int wg, int dor, int dtr, char t, bc r_bar[9], bc w_bar[9], bool& wm, int& wc)//function get stone out of bar at field
{
    bool pd = false;
    if (t == 'R')
    {
        out_of_bar_R(board, pfX, pfY, field, wg, dor, dtr, t, r_bar, w_bar, wm, wc, pd);
    }
    else if (t == 'W')
    {
        out_of_bar_W(board, pfX, pfY, field, wg, dor, dtr, t, r_bar, w_bar, wm, wc, pd);
    }
}

//function put stone on board at proper field and checks conditions of move
void put_stone(char board[h][w], int pfX, int pfY, fc field[24], int wg, int dor, int dtr, char t, bc red_bar[9], bc white_bar[9], bool& wm, int& wc)
{

    if (check_red_bar(board, red_bar) > 0 && t == 'R' || check_white_bar(board, white_bar) > 0 && t == 'W')
    {
        out_of_bar(board, pfX, pfY, field, wg, dor, dtr, t, red_bar, white_bar, wm, wc);
    }
    else if (can_capture(board, t, wg, field))
    {
        board[pfX][pfY] = '~';
        capturing(board, t, wg, field, white_bar, red_bar);
    }
    else
    {
        int put_stoneX = can_I_put_here(board, field, wg, t);
        int put_stoneY = field[wg].y;
        if (put_stoneX != -1)
        {
            board[pfX][pfY] = '~';
            wm = false;
            if (t == 'R')
            {
                board[put_stoneX][put_stoneY] = '#';
            }
            else if (t == 'W')
            {
                board[put_stoneX][put_stoneY] = '%';
            }
        }
        else
        {
            wm = true;
            wc = 11;
        }
    }
}

//change int type into bool type
void ints_to_bools(int rdi, bool& rd, int msi, bool& ms, int fmi, bool& fm, int tpi, bool& tp, int wmi, bool& wm, int arhi, bool& arh, int awhi, bool& awh, int dbi, bool& db, int woni, bool& won)
{
    if (rdi == 1)
        rd = true;
    else
        rd = false;
    if (msi == 1)
        ms = true;
    else
        ms = false;
    if (fmi == 1)
        fm = true;
    else
        fm = false;
    if (tpi == 1)
        tp = true;
    else
        tp = false;
    if (wmi == 1)
        wm = true;
    else
        wm = false;
    if (arhi == 1)
        arh = true;
    else
        arh = false;
    if (awhi == 1)
        awh = true;
    else
        awh = false;
    if (dbi == 1)
        db = true;
    else
        db = false;
    if (woni == 1)
        won = true;
    else
        won = false;
}

//change bool type into int type
void bools_to_ints(bool rd, int& rdi, bool ms, int& msi, bool fm, int& fmi, bool tp, int& tpi, bool wm, int& wmi, bool arh, int& arhi, bool awh, int& awhi, bool db, int& dbi, bool won, int& woni)
{
    if (rd)
        rdi = 1;
    else
        rdi = 0;
    if (ms)
        msi = 1;
    else
        msi = 0;
    if (fm)
        fmi = 1;
    else
        fmi = 0;
    if (tp)
        tpi = 1;
    else
        tpi = 0;
    if (wm)
        wmi = 1;
    else
        wmi = 0;
    if (arh)
        arhi = 1;
    else
        arhi = 0;
    if (awh)
        awhi = 1;
    else
        awhi = 0;
    if (db)
        dbi = 1;
    else
        dbi = 0;
    if (won)
        woni = 1;
    else
        woni = 0;
}

//enter file name
void file_name(char name[50])
{
    char c;
    gotoxy(sgX, sgY);
    cputs("File:");
    for (int i = 0; i < 50; i++) {
        c = getche();
        if (c == 0x0d)
        {
            name[i] = '\0';
            break;
        }
        else name[i] = c;
    }
}

//save actual game state to file
void save(char board[h][w], bool rd, int dor, int dtr,
    char t, bool ms, int ws, int wg, int pfX, int pfY,
    int wc, bool fm, bool tp, bool wm,
    int rc, int cw, int ahc, bool arh, bool awh, bool db, int mc, bool won, int rs, int sw)
{

    char name_s[50];
    file_name(name_s);
    int rdi = 0, msi = 0, fmi = 0, tpi = 0, wmi = 0, arhi = 0, awhi = 0, dbi = 0, woni = 0;
    bools_to_ints(rd, rdi, ms, msi, fm, fmi, tp, tpi, wm, wmi, arh, arhi, awh, awhi, db, dbi, won, woni);
    FILE* file;
    file = fopen(name_s, "w");
    fprintf(file, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %c", rdi, msi, fmi, tpi, wmi
        , arhi, awhi, dbi, dor, dtr, ws, wg
        , pfX, pfY, wc, rc, cw, mc, ahc, woni, rs, sw, t);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fprintf(file, "%c", board[i][j]);
        }
    }
    fclose(file);
}

//load game state from file
void load(char board[h][w], bool& rd, int& dor, int& dtr,
    char& t, bool& ms, int& ws, int& wg, int& pfX, int& pfY,
    int& wc, bool& fm, bool& tp, bool& wm,
    int& rc, int& cw, int& ahc, bool& arh, bool& awh, bool& db, int& mc, bool& won, int& rs, int& sw)

{
    int rdi, msi, fmi, tpi, wmi, arhi, awhi, dbi, wi;
    char name_l[50];
    file_name(name_l);
    FILE* f;
    f = fopen(name_l, "r");
    if (f == NULL) {
        printf("Err.\n");
    }
    int row = 0;
    while (!feof(f)) {
        if (ferror(f)) {
            printf("Err.\n");
            break;
        }
        fscanf(f, " %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %c", &rdi, &msi, &fmi, &tpi,
            &wmi, &arhi, &awhi, &dbi, &dor, &dtr,
            &ws, &wg, &pfX, &pfY, &wc, &rc, &cw, &mc, &ahc, &wi, &rs, &sw, &t);

        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                fscanf(f, " %c", &board[i][j]);
            }
        }
        ints_to_bools(rdi, rd, msi, ms, fmi, fm, tpi, tp, wmi, wm, arhi, arh, awhi, awh, dbi, db, wi, won);
        fclose(f);
        break;
    }

}


//save all board states from previous duel to file
void save_moves(char board[h][w], Node*& head)
{
    FILE* file;
    Node* traverse = head;
    file = fopen("moves.txt", "w");
    do
    {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                fprintf(file, "%c", traverse->board[i][j]);
            }
        }
        traverse = traverse->next;
    } while (traverse != nullptr);

    fclose(file);
}

//function looking for proper field with dice one result
void move_stone_with_dice_one(char board[h][w], char& t, int wg, int ws,
    int dor, int dtr, bool arh, bool awh, int pfX,
    int pfY, fc field[24], bc red_bar[9], bc white_bar[9], bool& wm, int& wc, Node*& head, Node*& tails)
{
    if (t == 'R')
    {
        wg = ws + dor;
        if (wg == 24 && arh)
        {
            get_out_stone(board, pfX, pfY);
        }
        else if (wg > 24 && arh)
        {
            remove_farest(board, t);
        }
        else
        {
            put_stone(board, pfX, pfY, field, wg, dor, dtr, t, red_bar, white_bar, wm, wc);
        }
    }
    else if (t == 'W')
    {
        wg = ws - dor;
        if (wg == -1 && awh)
        {
            get_out_stone(board, pfX, pfY);
        }
        else if (wg < -1 && awh)
        {
            remove_farest(board, t);
        }
        else
        {
            put_stone(board, pfX, pfY, field, wg, dor, dtr, t, red_bar, white_bar, wm, wc);
        }
    }
    collect_all_board_states(board, head, tails);
}

//function looking for proper field with dice two result
void move_stone_with_dice_two(char board[h][w], char& t, int wg, int ws,
    int dor, int dtr, bool arh, bool awh, int pfX,
    int pfY, fc field[24], bc red_bar[9], bc white_bar[9], bool& wm, int& wc, Node*& head, Node*& tails)
{
    if (t == 'R')
    {
        wg = ws + dtr;
        if (wg == 24 && arh)
        {
            get_out_stone(board, pfX, pfY);
        }
        else if (wg > 24 && arh)
        {
            remove_farest(board, t);
        }
        else
        {
            put_stone(board, pfX, pfY, field, wg, dor, dtr, t, red_bar, white_bar, wm, wc);
        }
        if (wm == false)
            t = 'W';
    }
    else if (t == 'W')
    {
        wg = ws - dtr;
        if (wg == -1 && awh)
        {
            get_out_stone(board, pfX, pfY);
        }
        else if (wg < -1 && awh)
        {
            remove_farest(board, t);
        }
        else
        {
            put_stone(board, pfX, pfY, field, wg, dor, dtr, t, red_bar, white_bar, wm, wc);
        }
        if (wm == false)
            t = 'R';
    }
    collect_all_board_states(board, head, tails);
}

//process of rolling the dieces
void roll(char& t, bool& rd, int& dor, int& dtr, int& wc, bool& ms, char board[h][w], bc red_bar[9], bc white_bar[9], bool& db)
{
    if (t == 'N')//who will start first check
    {
        rd = true;
        dor = diece_one();
        dtr = diece_two();
        if (dor > dtr)
        {
            t = 'R';
            wc = 1;
            ms = true;
        }
        else if (dor < dtr)
        {
            t = 'W';
            wc = 1;
            ms = true;
        }
        else
        {
            t = 'N';
        }
        if (check_red_bar(board, red_bar) > 0 && t == 'R')
        {
            wc = 8;
        }
        if (check_white_bar(board, white_bar) > 0 && t == 'W')
        {
            wc = 9;
        }
    }
    else
    {
        rd = true;
        dor = diece_one();
        dtr = diece_two();
        wc = 1;
        ms = true;
        if (dor == dtr)//check if double
        {
            db = true;
            wc = 10;
        }
        else
            db = false;
        if (check_red_bar(board, red_bar) > 0 && t == 'R')
        {
            wc = 8;
        }
        if (check_white_bar(board, white_bar) > 0 && t == 'W')
        {
            wc = 9;
        }
    }
}

//function gets coordinates of chosen stone
void pick(char t, char board[h][w], int x, int y, bool& ms, int& pfX,
    int& pfY, int& ws, fc field[24], bool& wm, int& wc)
{
    if (t == 'R')
    {
        if (board[y - mh][x - mw] == '#')
        {
            ms = true;
            pfX = y - mh;
            pfY = x - mw;
            ws = where_am_I(board, pfX, pfY, field);
            wm = false;
        }
        else if (board[y - mh][x - mw] == '%')
        {
            wc = 4;
            wm = true;
        }
        else
        {
            wc = 3;
            wm = true;
        }

    }
    else if (t == 'W')
    {
        if (board[y - mh][x - mw] == '%')
        {
            ms = true;
            pfX = y - mh;
            pfY = x - mw;
            ws = where_am_I(board, pfX, pfY, field);
            wm = false;
        }
        else if (board[y - mh][x - mw] == '#')
        {
            wc = 4;
            wm = true;
        }
        else
        {
            wc = 3;
            wm = true;
        }
    }
}

//function checks state of red and white homes (counts number of stones and checks if one of the player won)
void check_home_state(int rc, bool& arh, int cw, bool& awh, int& ahc, int& rs, char board[h][w], bc white_bar[9], bool& won, int& wc, int& sw, bc red_bar[9])
{
    //if all stones(each player have 15 stones) are at home
    if (!won)
    {
        if (rc == 15)
        {
            arh = true;
        }
        if (cw == 15)
        {
            awh = true;
        }
        if (arh && awh)
        {
            ahc = 4;
        }
        else if (arh)
        {
            ahc = 1;
        }
        else if (awh)
        {
            ahc = 2;
        }
        if (arh && rc == 0)
        {
            if (cw == 15)//if red one won and white have 15 stones sill at his home
            {
                rs += 2;
            }
            else if (check_white_bar(board, white_bar) > 0)//if red one won and white have at least one stone at bar
            {
                rs += 3;
            }
            else
                rs += 1;
            won = true;
            wc = 12;
        }
        else if (awh && cw == 0)
        {
            if (rc == 15)//same logic as for red player
            {
                sw += 2;
            }
            else if (check_red_bar(board, red_bar) > 0)
            {
                sw += 3;
            }
            else
                sw += 1;
            won = true;
            wc = 13;
        }
    }

}

//execution of functions before every duel
void exe_1(bool& rd, bool& ms, char& t, bool& arh, bool& awh, bool& won, int& rs, int& sw, Node*& head, int& wc, bool& fm, bool& tp, bool& wm, char txt[32], int dor, int dtr, char board[h][w], int& ahc)
{
    clrscr();
    rd = 0;
    ms = 0;
    t = 'N';
    arh = 0;
    awh = 0;
    ahc = 0;
    if (!won)
    {
        rs = 0;
        sw = 0;
    }
    else
    {
        won = 0;
    }
    head = nullptr;

    back_to_default_after_t(ms, rd, wc, fm, tp, wm);
    game_state(false);
    dieces_result(txt, rd, dor, dtr);
    interface();
    communicates(0);
    fill_b(board);
    fill_fields(board);
    default_stones(board);
    print_board(board);
}

//execution of functions after every button pressed
void exe_2(char txt[32], bool rd, int dor, int dtr, char board[h][w], fc field[24], int& rc, int& cw, bool& arh, bool& awh, int& ahc, int& rs, bc white_bar[9], bool& won, int& wc, int& sw, bc red_bar[9], char t, int x, int y, int attr, int back, int& zero)
{
    _setcursortype(_NOCURSOR);
    textbackground(BLACK);
    clrscr();
    textcolor(7);
    game_state(true);
    interface();
    dieces_result(txt, rd, dor, dtr);
    print_board(board);
    count_stones_in_homes(board, field, rc, cw);
    check_home_state(rc, arh, cw, awh, ahc, rs, board, white_bar, won, wc, sw, red_bar);
    communicates(wc);
    players_scores(txt, rs, sw);
    all_in_home(ahc);
    whos_moving(t);
    gotoxy(x, y);
    textcolor(attr);
    textbackground(back);
    putch('*');
    zero = 0;
}

//operate moving of cursor
void cursor(int& zn, int& zero, int& y, int& x)
{
    zero = 1;
    zn = getch();
    if (zn == 0x48) y--;//up arrow
    else if (zn == 0x50) y++;//down arrow
    else if (zn == 0x4b) x--;//left arrow
    else if (zn == 0x4d) x++;//right arrow
}

//type of move when results from dieces are equal(double)
void dbl(char board[h][w], char& t, int wg, int ws, int dor, int dtr, bool arh, bool awh, int pfX, int pfY, fc field[24], bc red_bar[9], bc white_bar[9], bool& wm, int& wc, Node*& head, int& mc, bool& db, bool& ms, bool& rd, bool& fm, bool& tp, Node*& tails)
{
    move_stone_with_dice_one(board, t, wg, ws, dor, dtr, arh, awh, pfX, pfY, field, red_bar, white_bar, wm, wc, head, tails);
    if (wm == false)
        mc++;//count moves that have been done

    if (mc == 4)//in double move type you can move 4 times with result from dice(one or two does not matter)
    {
        //end double move
        db = false;
        mc = 0;
        if (t == 'R')
            t = 'W';
        else if (t == 'W')
            t = 'R';
        back_to_default_after_t(ms, rd, wc, fm, tp, wm);
    }
}

//whole process of moving the stones
void t_exe(char board[h][w], char& t, int wg, int ws, int dor, int dtr, bool arh, bool awh, int pfX, int pfY, fc field[24], bc red_bar[9], bc white_bar[9], bool& wm, int& wc, Node*& head, int& mc, bool& db, bool& ms, bool& rd, bool& fm, bool& tp, Node*& tails)
{
    if (fm)//check if it is first move (move from dice one)
    {
        move_stone_with_dice_one(board, t, wg, ws, dor, dtr, arh, awh, pfX, pfY, field, red_bar, white_bar, wm, wc, head, tails);
        if (wm == false)
        {
            wc = 6;
            fm = false;
        }
    }
    else//move from dice two
    {
        move_stone_with_dice_two(board, t, wg, ws, dor, dtr, arh, awh, pfX, pfY, field, red_bar, white_bar, wm, wc, head, tails);
        if (wm == false)
            back_to_default_after_t(ms, rd, wc, fm, tp, wm);
    }
}
//skip turn if you know that you can not make a proper move
void m_exe(bool& ms, bool& rd, int& wc, bool& fm, bool& tp, bool& wm, char& t)
{
    back_to_default_after_t(ms, rd, wc, fm, tp, wm); //afer skipped turn back to default variables values

    //change turn
    if (t == 'R')
    {
        t = 'W';
    }
    else if (t == 'W')
    {
        t = 'R';
    }
}

//printing the boards states from previous duel
void print_specific_board(int i, int j, Node* traverse)
{
    gotoxy(mw + j, mh + i);
    if (traverse->board[i][j] == '"')
    {
        textcolor(RED);
        cputs("|");
    }
    else if (traverse->board[i][j] == '%')
    {

        textcolor(WHITE);
        cputs("o");
    }
    else if (traverse->board[i][j] == '#')
    {

        textcolor(RED);
        cputs("o");
    }
    else if (traverse->board[i][j] == '~')
    {
        textcolor(WHITE);
        cputs(" ");
    }
    else
    {
        textcolor(WHITE);
        putch(traverse->board[i][j]);
    }
}

//saving and visualization of all of the moves from previous duel
void v_exe(char board[h][w], Node*& head, Node*& tails)
{
    save_moves(board, head); //save board states to file
    clrscr();
    char sign;
    gotoxy(2, 2);
    cputs("right_arrow - next move,left_arrow - previous move,up_arrow - first move,down_arrow - last_move");
    do//go trough whole list of board states, work until you press n
    {
        Node* traverse = head;
        do//work until you press b
        {
            for (int i = 0; i < h; i++)
            {
                for (int j = 0; j < w; j++)
                {
                    print_specific_board(i, j, traverse);//printing board state at which poitner currently is 
                }
            }
            sign = getch();
            if (sign == 0x4d)//right arrow (next baord state)
                traverse = traverse->next;
            else if (sign == 0x4b)//left arrow (previous board state)
                traverse = traverse->prev;
            else if (sign == 0x48)//up arrow (first board state)
                traverse = head;
            else if (sign == 0x50)//down arrow (last board state) 
                traverse = tails;
        } while (sign != 'b');
        clrscr();
        gotoxy(2, 2);
        cputs("PRESS 'n' TO START NEW DUEL");
        sign = getch();
    } while (sign != 'n');
}

//choosing stone and checking type of movement
void i_button(char b[h][w], char& t, int wg, int& ws, int dor, int dtr, bool arh, bool awh, int& pfX, int& pfY, fc f[24], bc rbar[9], bc wbar[9], bool& wm, int& wc, Node*& head, int& mc, bool& db, bool& ms, bool& rd, bool& fm, bool& tp, int& x, int& y, Node*& tails)
{
    pick(t, b, x, y, ms, pfX, pfY, ws, f, wm, wc); // pick stone
    if (db) // if there is double (same dieces result)
    {
        dbl(b, t, wg, ws, dor, dtr, arh, awh, pfX, pfY, f, rbar, wbar, wm, wc, head, mc, db, ms, rd, fm, tp, tails);
    }
    if (tp && !wm) // stone movement
    {
        t_exe(b, t, wg, ws, dor, dtr, arh, awh, pfX, pfY, f, rbar, wbar, wm, wc, head, mc, db, ms, rd, fm, tp, tails);
    }
}

//calling save and load fucntions
void save_load_exe(char b[h][w], bool& rd, int& ro, int& rt, char& t, bool& ms, int& ws, int& wg, int& pfX, int& pfY, int& wc, bool& fm, bool& tp, bool& wm, int& rc, int& cw, int& ah, bool& ar, bool& aw, bool& db, int& mc, bool& w, int& rs, int& sw, int zn)
{
    if (zn == 's')
        save(b, rd, ro, rt, t, ms, ws, wg, pfX, pfY, wc, fm, tp, wm, rc, cw, ah, ar, aw, db, mc, w, rs, sw);
    else if (zn == 'l')
        load(b, rd, ro, rt, t, ms, ws, wg, pfX, pfY, wc, fm, tp, wm, rc, cw, ah, ar, aw, db, mc, w, rs, sw);
}

//fuction that operate the whole process of the game
void game(char txt[32], bool& rd, int& ro, int& rt, char b[h][w], fc f[24], int& rc, int& cw, bool& ar,
    bool& aw, int& ah, int& rs, bc wb[9], bool& w, int& wc, int& sw, bc rb[9], char& t, int& x,
    int& y, int& at, int& bc, int& z, int& zn, bool& ms, int& ws, int& wg, int& pfX, int& pfY, bool& fm, bool& tp, bool& wm, bool& db, int& mc, Node*& hd, Node*& ts)
{
    do//work until you press n or q
    {
        exe_2(txt, rd, ro, rt, b, f, rc, cw, ar, aw, ah, rs, wb, w, wc, sw, rb, t, x, y, at, bc, z);//exectute needed functions after button pressed
        zn = getch();
        //check which button was pressed
        if (zn == 0)
            cursor(zn, z, y, x);
        else if (zn == 's' || zn == 'l')
            save_load_exe(b, rd, ro, rt, t, ms, ws, wg, pfX, pfY, wc, fm, tp, wm, rc, cw, ah, ar, aw, db, mc, w, rs, sw, zn);
        else if (zn == 'r' && !ms && !w)
            roll(t, rd, ro, rt, wc, ms, b, rb, wb, db);
        else if (zn == 'i' && t != 'N' && ms && !w)
            i_button(b, t, wg, ws, ro, rt, ar, aw, pfX, pfY, f, rb, wb, wm, wc, hd, mc, db, ms, rd, fm, tp, x, y, ts);
        else if (zn == 't' && ms && !w)
        {
            tp = 1;
            wc = 5;
        }
        else if (zn == 'm' && ms && !w)
            m_exe(ms, rd, wc, fm, tp, wm, t);
        else if (zn == 'v' && w)
            v_exe(b, hd, ts);
    } while (zn != 'n' && zn != 'q');
}

int main()
{
    int zn = 0, x = 40, y = 12, attr = 7, back = 0, zero = 0, dor = 0/*diece_one_result*/, dtr = 0/*diece_two_result*/, ws = 0/*where_started*/, wg = 0/*where_we_go*/, pfX = 0/*put_from_x*/, pfY = 0/*put_from_y*/,
        wc = 0/*which_communicate*/, rc = 0/*red_counter*/, cw = 0/*white_counter*/, ahc = 0/*all_in_home_communicate*/, mc = 0/*moves_counter*/, rs = 0/*red_score*/, sw = 0/*white_score*/;
    char txt[32], board[h][w], t/*turn*/;
    bool rd = 0/*roll_has_been_done*/, ms = 0/*move_started*/, fm = 1/*is_it_first_move*/, tp = 0/*t_was_pressed*/, wm = 0/*there_was_an_mistake*/,
        arh = 0/*all_reds_in_home*/, awh = 0/*all_whites_in_home*/, db = 0/*double*/, won = 0;
    fc field[24]; //fields coordinates
    bc r_bar[9]/*red bar coordinates*/, w_bar[9]; /*white_bar coordinates*/
    Node* h = nullptr;//head of list
    Node* ts = nullptr;//tail of list
    fill(field, r_bar, w_bar);
    srand(time(NULL));
    do {
        exe_1(rd, ms, t, arh, awh, won, rs, sw, h, wc, fm, tp, wm, txt, dor, dtr, board, ahc);
        zn = getch();
        if (zn == 'p')
        {
            game(txt, rd, dor, dtr, board, field, rc, cw, arh, awh, ahc, rs, w_bar, won, wc, sw, r_bar, t, x, y, attr, back, zero, zn, ms, ws, wg, pfX, pfY, fm, tp, wm, db, mc, h, ts);
        }
    } while (zn != 'q');

    return 0;
}