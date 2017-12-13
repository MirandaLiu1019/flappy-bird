#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <conio.h>

#define P_ 80	/*Frame width<=80*/
#define Q_ 40	/*Frame height<=43*/
#define U_ 8	/*Pillar width*/
#define PIN ' '
#define ZHUZI '$'
#define BIRD '#'
#define KUANG	'*'
#define BIAO_X 17	/*Position of bird*/

int t = 0;
int k, j = 0;		/*j is number of calls£¬k is random column*/
int i = 20;
char zhu[P_][Q_];
int Fall[30] = { -2, -1, -1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

int map(int h);
int fall(void);
void Pause(void);


int gap;
int V_;   /*Space between consecutive pillars*/
int R_;   /*Open space in pillars*/
int score;

int main()
{
    char ready, replay;
    int h, n, sum;
    sum = 0;

BEGIN:printf("\n\n\t\t********************************************\n\t\tPlease maximize window before starting game!\n\t\t********************************************\n\n\n\n\n\t\t    Please select difficulty and start game\n\n\t\t\tPRESS    DIFFICULTY\n\n\t\t\t E      Easy\n\t\t\t N      Normal\n\t\t\t H      Hard\n\t\t\t X      Impossible\n\n\n\tNotes:\n\t\t1.Press 'W' to ascend the bird.\n\t\t2.Press 'P' during game to pause and resume.");

    do
    {
        ready = getch();
    }
    while (ready != 'e' && ready != 'E' && ready != 'n' && ready != 'N' && ready != 'h' && ready != 'H' && ready != 'x' && ready != 'X');

    if (ready == 'e' || ready == 'E') gap = 50, V_ = 20, R_ = 14;
    if (ready == 'n' || ready == 'N') gap = 45, V_ = 18, R_ = 12;
    if (ready == 'h' || ready == 'H') gap = 35, V_ = 16, R_ = 10;
    if (ready == 'x' || ready == 'X') gap = 30, V_ = 18, R_ = 12;

    do
    {
        h = fall();
        n = map(h);
    }
    while (n != 0);
	system("CLS");
    printf("\n\n\n\n\t\t\t ****************************\n\t\t\t\t   GAME  OVER\n\n\t\t\t\tYOUR SCORE IS %d\n\n\t\t\t     Enter Y to play again\n\t\t\t     Enter N to exit\n\t\t\t ****************************", score);

    do
    {
        replay = getch();
    }
    while (replay != 'y' && replay != 'Y' && replay != 'n' && replay != 'N');

	if (replay == 'y' || replay == 'Y')
	{
		t = 0;
		j = 0;
		i = 20;
		sum = 0;
		system("CLS");
		goto BEGIN;
	}
    return 0;
}

int map(int h)
{
    char kong1[P_ + 1] = "\0", kong2[P_ + 1] = "\0", kong3[P_ + 1] = "\0", gai1, gai2, gai3, gai4, gai5;
    int i, ii, iii, m = 1, n;

    /*Cursor*/
    HANDLE hout;
    COORD coord;
    srand(time(NULL));
	srand(rand());

    coord.X = 0;
    coord.Y = 0;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, coord);


    if (h < 3)
    {
        m = 0;
        h = 2;
        if (j % 2 == 0)
            h = 3;
    }
    if ( h > Q_ - 5)
    {
        m = 0;
        h = Q_ - 3;
        if (j % 2 == 0)
            h = Q_ - 4;
    }
    /*input*/

    /*1st time*/
    if (!j)
    {
        for (i = 0; i < P_; i++)
        {
            for (ii = 0; ii < Q_ - 1; ii++)
                zhu[i][ii] = PIN;
        }
        for (i = 0; i < P_; i++)
            zhu[i][Q_ - 1] = '\0';
    }
    /* 1st time*/

    /*Generating the third last pillar*/
    if (j % (U_ + V_) == 0)
        k = Q_ / 4 + rand() % (Q_ / 2);
    if (j % (U_ + V_) < U_)
    {
        for (i = 0; i < Q_ - 1; i++)
        {
            if (i < k + R_ / 2 && i > k - R_ / 2)
                zhu[P_ - 4][i] = PIN;
            else
                zhu[P_ - 4][i] = ZHUZI;
        }
    }
    else
    {
        for (i = 0; i < Q_ - 1; i++)
            zhu[P_ - 4][i] = PIN;
    }
    /*Generating pillars*/

    /*Bird*/

    gai1 = zhu[BIAO_X - 1][h];
    gai2 = zhu[BIAO_X][h];
    gai3 = zhu[BIAO_X + 1][h];
    if (t > 5 || t == 0 || t == 1)
    {
        gai4 = zhu[BIAO_X - 1][h - 1];
        gai5 = zhu[BIAO_X][h - 1];
        zhu[BIAO_X - 1][h - 1] = BIRD;
        zhu[BIAO_X][h - 1] = BIRD;
    }
    else
    {
        gai4 = zhu[BIAO_X - 1][h + 1];
        gai5 = zhu[BIAO_X][h + 1];
        zhu[BIAO_X - 1][h + 1] = BIRD;
        zhu[BIAO_X][h + 1] = BIRD;
    }
    zhu[BIAO_X - 1][h] = BIRD;
    zhu[BIAO_X][h] = BIRD;
    zhu[BIAO_X + 1][h] = BIRD;


    for (i = 2; i < P_ - 4; i++)
        strncpy(zhu[i], zhu[i + 1], Q_);
    for (i = 0; i < Q_ - 1; i++)
    {
        strcpy(kong2, kong3);
        if (i < 2 || i > Q_ - 4)
        {
            kong1[0] = KUANG;
            for (iii = 0; iii < P_ - 1; iii++)
            {
                strcat(kong2, kong1);
            }
        }
        else
        {
            for (ii = 0; ii < P_ - 1; ii++)
            {
                zhu[ii][0] = zhu[ii][i];
                strcpy(kong1, kong3);
                strncpy(kong1, zhu[ii], 1);
                strcat(kong2, kong1);
            }
        }
        kong2[0] = KUANG;
        kong2[1] = KUANG;
        kong2[P_ - 2] = KUANG;
        kong2[P_ - 3] = KUANG;
        puts(kong2);
    }

    coord.X = P_ / 2;
    coord.Y = Q_ / 4;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, coord);
    n = (j - P_ + BIAO_X + 5 + U_ + V_) / (U_ + V_);
    printf("%d", n > 0 ? n : 0);
    score = n;



    if ((( gai1 == ZHUZI || gai2 == ZHUZI) || (gai3 == ZHUZI || gai4 == ZHUZI)) || gai5 == ZHUZI)
        m = 0;


	/*
	coord.X = 0;
    coord.Y = 0;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, coord);
	*/

    zhu[BIAO_X - 2][h] = gai1;
    zhu[BIAO_X - 1][h] = gai2;
    zhu[BIAO_X ][h] = gai3;
    gai1 = zhu[BIAO_X - 1][h];
    gai2 = zhu[BIAO_X][h];
    gai3 = zhu[BIAO_X + 1][h];
    if (t > 5 || t <= 1)
    {
        zhu[BIAO_X - 2][h - 1] = gai4  ;
        zhu[BIAO_X - 1][h - 1] = gai5;
    }
    else
    {
        zhu[BIAO_X - 2][h + 1] = gai4;
        zhu[BIAO_X - 1][h + 1] = gai5 ;
    }
    j++;
    return m;
}



int fall(void)
{
    char cot;

    Sleep(gap);
	if (kbhit())
    {
        cot = getch();
        if (cot == 'w' || cot == 'W')
        {
            t = 0;
        }
        if (cot == 'p' || cot == 'P')
        {
            Pause();
        }
    }
    i = i + Fall[t];
    t++;
    return i;
}

void Pause(void)
{
    char temp;
    printf("\n\n\t\t   PAUSING... enter p/P to continue");
    while (1)
    {
        temp = getch();
        if (temp == 'p' || temp == 'P')
        {
            system("CLS");
            return;
        }
    }
}
