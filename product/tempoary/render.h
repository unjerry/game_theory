#include <Windows.h>
#include <stdio.h>

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoxydraw(int x, int y, char ch)
{
    gotoxy(x, y);
    printf("%c", ch);
}
