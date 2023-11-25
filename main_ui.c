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
void SelectGame();

int main() {
	int keyInput = getKeyDown();
	int state = 0;
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
			state = 1;
			gotoxy(15, 6);
			printf(" ");
			gotoxy(3, 6);
			printf(">");
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			state = 2;
			gotoxy(3, 6);
			printf(" ");
			gotoxy(15, 6);
			printf(">");
		}
		else if (GetAsyncKeyState(VK_RETURN)) {
			if (state == 1) {
				SelectGame();
			}
			else if (state == 2) {
				gotoxy(0, 20);
				break;
			}
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

void SelectGame() {
	int x;
	x = 5;
	system("cls");
	system("mode con: cols=70 lines=30");
	gotoxy(18, 1);
	printf("게임 선택");
	gotoxy(0, 3);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                          ■\n");
	printf("■                                          ■\n");
	printf("■      숫자야구    n*n퍼즐     테트리스    ■\n");
	printf("■                                          ■\n");
	printf("■                                          ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(x, 6);
	printf(">");
	while (1) {
		if (x <= 5 && GetAsyncKeyState(VK_LEFT)) {
			gotoxy(5, 6);
			printf(" ");
			gotoxy(5, 6);
			printf(">");
		}
		else if (GetAsyncKeyState(VK_LEFT)) {
			gotoxy(x, 6);
			printf(" ");
			x -= 12;
			gotoxy(x, 6);
			printf(">");
		}
		if (x >= 29 && GetAsyncKeyState(VK_RIGHT)) {
			gotoxy(29, 6);
			printf(" ");
			gotoxy(29, 6);
			printf(">");
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			gotoxy(x, 6);
			printf(" ");
			x += 12;
			gotoxy(x, 6);
			printf(">");
		}
		if (x == 5) {

		}
		else if (x == 17) {

		}
		else if (x == 29) {

		}
		Sleep(200);
	}
}
