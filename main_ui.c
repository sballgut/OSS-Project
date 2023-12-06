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
void StartNumberBaseball();
void StartNPuzzle();
void StartTetris();

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
		if (game == 1 && GetAsyncKeyState(VK_RIGHT)) {
			game = 2;
			gotoxy(6, 6);
			textcolor(7);
			printf("숫자야구");
			gotoxy(19, 6);
			textcolor(6);
			printf("n*n퍼즐");
		}

		if (game == 2 && GetAsyncKeyState(VK_LEFT)) {
			game = 1;
			gotoxy(19, 6);
			textcolor(7);
			printf("n*n퍼즐");
			gotoxy(6, 6);
			textcolor(4);
			printf("숫자야구");
		}

		if (game == 2 && GetAsyncKeyState(VK_RIGHT)) {
			game = 3;
			gotoxy(19, 6);
			textcolor(7);
			printf("n*n퍼즐");
			gotoxy(31, 6);
			textcolor(1);
			printf("테트리스");
		}

		if (game == 3 && GetAsyncKeyState(VK_LEFT)) {
			game = 2;
			gotoxy(31, 6);
			textcolor(7);
			printf("테트리스");
			gotoxy(19, 6);
			textcolor(6);
			printf("n*n퍼즐");
		}

		Sleep(500);
		if (game == 1 && GetAsyncKeyState(VK_RETURN)) {
			StartNumberBaseball();
		}
		else if (game == 2 && GetAsyncKeyState(VK_RETURN)) {
			StartNPuzzle();
		}
		else if (game == 3 && GetAsyncKeyState(VK_RETURN)) {
			StartTetris();
		}
	}
}

void StartNumberBaseball() {
	system("cls");
	gotoxy(8, 0);
	printf("숫자야구");
	gotoxy(0, 3);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■       게임시작       ■\n");
	printf("■         상점         ■\n");
	printf("■       게임설명       ■\n");
	printf("■        홈으로        ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■\n");
}

void StartNPuzzle() {
	system("cls");
	gotoxy(9, 0);
	printf("n*n퍼즐");
	gotoxy(0, 3);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■       게임시작       ■\n");
	printf("■       게임설명       ■\n");
	printf("■        홈으로        ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■\n");
}

void StartTetris() {
	system("cls");
	gotoxy(8, 0);
	printf("테트리스");
	gotoxy(0, 3);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■       게임시작       ■\n");
	printf("■       게임설명       ■\n");
	printf("■        홈으로        ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■                      ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■\n");
}
