#include <Windows.h>
#include<stdio.h>
#include<conio.h>

#define UP 72
#define LEFT 75
#define RIGHT 77

void gotoxy(int x, int y);
void SetConsole();
void textcolor(int color_number);
int getKeyDown();

int main() {
	int keyInput = getKeyDown();
	SetConsole();
	gotoxy(8, 0);
	printf("추억의 미니게임");
	gotoxy(0, 3);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                            ■\n");
	printf("■                            ■\n");
	printf("■    게임시작    게임종료    ■\n");
	printf("■                            ■\n");
	printf("■                            ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	
	while (1) {
		if (GetAsyncKeyState(VK_LEFT)) {
			gotoxy(15, 6);
			printf(" ");
			gotoxy(3, 6);
			printf(">");
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			gotoxy(3, 6);
			printf(" ");
			gotoxy(15, 6);
			printf(">");
		}
	}
	return 0;
}

void gotoxy(int x, int y)
{
	COORD xyPos;
	xyPos.X = x;
	xyPos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xyPos);
}

void SetConsole() {
	system("Title Main");
	system("mode con:cols=50 lines=40");

	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void textcolor(int color_number) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

int getKeyDown() {
	if (_kbhit()) return _getch();
	else return -1;
}
