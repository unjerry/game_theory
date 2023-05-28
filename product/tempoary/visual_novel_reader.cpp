#include <Windows.h>
#include <stdio.h>
#include <string>
#include <string.h>

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main()
{
    char name[100];
    scanf("%s", name);
    FILE *fi = fopen(name, "rb");
    while (1)
    {
        char ch;
        char s[1000];
        ch = GetAsyncKeyState(VK_DOWN);
        HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO infoo;
        GetConsoleScreenBufferInfo(hd, &infoo);
        // printf("%d %d\n", infoo.srWindow.Right, infoo.srWindow.Bottom);
        if (ch == 1)
        {
            printf("sdfsdf\n");
            system("cls");
            fgets(s, 1000, fi);
            gotoxy(((infoo.srWindow.Right) / 2) - strlen(s) / 2 + 1, infoo.srWindow.Bottom - 5);
            printf("%s", s);
        }
    }
    fclose(fi);
    return 0;
}
