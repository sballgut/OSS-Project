#include <Windows.h>
#include<stdio.h>
#include<conio.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

void gotoxy(int x, int y);
void SetConsole();
void textcolor(int color_number);
int getKeyDown();
void SelectGame();
void StartNumberBaseball();
void StartNPuzzle();
void StartTetris();
void main_ui();

int main() {
	main_ui();
	return 0;
}

//게임 시작 화면 메인ui
void main_ui() {
	int keyInput = getKeyDown();
	int state = 1;
	system("cls");
	SetConsole();
	gotoxy(8, 0);
	textcolor(7);
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
		Sleep(100);
		if (state == 1) {
			gotoxy(5, 6);
			textcolor(4);
			printf("게임시작");
		}

		else if (state == 2) {
			gotoxy(17, 6);
			textcolor(1);
			printf("게임종료");
		}
		
		if (state == 1 && GetAsyncKeyState(VK_RIGHT)) {
			state = 2;
			gotoxy(5, 6);
			textcolor(7);
			printf("게임시작");
		}
		
		else if (state == 2 && GetAsyncKeyState(VK_LEFT)) {
			state = 1;
			gotoxy(17, 6);
			textcolor(7);
			printf("게임종료");
		}
		
		if (state == 1 && GetAsyncKeyState(VK_UP)) {
			SelectGame();
			break;
		}
		
		else if (state == 2 && GetAsyncKeyState(VK_UP)) {
			gotoxy(0, 20);
			textcolor(7);
			break;
		}
	}
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

//게임선택화면 메인ui
void SelectGame() {
	int game = 1;
	system("cls");
	system("mode con: cols=70 lines=30");
	Sleep(200);
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
	while (1) {
		Sleep(100);
		if (game == 1) {
			gotoxy(7, 6);
			textcolor(4);
			printf("숫자야구");
		}
		
		else if (game == 2) {
			gotoxy(19, 6);
			textcolor(6);
			printf("n*n퍼즐");
		}
		
		else if (game == 3) {
			gotoxy(31, 6);
			textcolor(1);
			printf("테트리스");
		}
		
		if (game == 1 && GetAsyncKeyState(VK_RIGHT)) {
			game = 2;
			gotoxy(6, 6);
			textcolor(7);
			printf("숫자야구");
		}
		
		else if (game == 2 && GetAsyncKeyState(VK_LEFT)) {
			game = 1;
			gotoxy(19, 6);
			textcolor(7);
			printf("n*n퍼즐");
		}
		
		else if (game == 2 && GetAsyncKeyState(VK_RIGHT)) {
			game = 3;
			gotoxy(19, 6);
			textcolor(7);
			printf("n*n퍼즐");
		}
		
		else if (game == 3 && GetAsyncKeyState(VK_LEFT)) {
			game = 2;
			gotoxy(31, 6);
			textcolor(7);
			printf("테트리스");
		}
		
		//숫자야구 선택
		if (game == 1 && GetAsyncKeyState(VK_UP)) {
			StartNumberBaseball();
			break;
		}
		
		//n*n퍼즐 선택
		else if (game == 2 && GetAsyncKeyState(VK_UP)) {
			StartNPuzzle();
			break;
		}
		
		//테트리스 선택
		else if (game == 3 && GetAsyncKeyState(VK_UP)) {
			StartTetris();
			break;
		}
	}
}

//숫자야구 메인 ui
void StartNumberBaseball() {
	system("cls");
	Sleep(200);
	int state = 1;
	gotoxy(20, 0);
	textcolor(7);
	printf("숫자야구");
	gotoxy(0, 3);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■    게임시작       게임설명       홈으로      ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	while (1) {
		Sleep(100);
		if (state == 1) {
			gotoxy(5, 6);
			textcolor(4);
			printf("게임시작");
		}
		
		if (state == 2) {
			gotoxy(20, 6);
			textcolor(6);
			printf("게임설명");
		}

		if (state == 3) {
			gotoxy(35, 6);
			textcolor(1);
			printf("홈으로");
		}
		
		if (state == 1 && GetAsyncKeyState(VK_RIGHT)) {
			state = 2;
			gotoxy(5, 6);
			textcolor(7);
			printf("게임시작");
		}
	
		else if (state == 2 && GetAsyncKeyState(VK_LEFT)) {
			state = 1;
			gotoxy(20, 6);
			textcolor(7);
			printf("게임설명");
		}
	
		else if (state == 2 && GetAsyncKeyState(VK_RIGHT)) {
			state = 3;
			gotoxy(20, 6);
			textcolor(7);
			printf("게임설명");
		}
	
		else if (state == 3 && GetAsyncKeyState(VK_LEFT)) {
			state = 2;
			gotoxy(35, 6);
			textcolor(7);
			printf("홈으로");
		}

		//숫자야구 실행
		if (state == 1 && GetAsyncKeyState(VK_UP)) {
			gotoxy(0, 0);
			NumBaseball();
			break;
		}

		//숫자야구 게임 설명
		else if (state == 2 && GetAsyncKeyState(VK_UP)) {
			gotoxy(0, 0);
			explainNumberBaseball();
			break;
		}

		//첫화면으로
		else if (state == 3 && GetAsyncKeyState(VK_UP)) {
			gotoxy(0, 0);
			main_ui();
			break;
		}
	}
}

//n*n퍼즐 메인ui
void StartNPuzzle() {
	system("cls");
	Sleep(200);
	int state = 1;
	gotoxy(20, 0);
	textcolor(7);
	printf("n*n퍼즐");
	gotoxy(0, 3);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■    게임시작       게임설명       홈으로      ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	while (1) {
		Sleep(100);
		if (state == 1) {
			gotoxy(5, 6);
			textcolor(4);
			printf("게임시작");
		}

		else if (state == 2) {
			gotoxy(20, 6);
			textcolor(6);
			printf("게임설명");
		}

		else if (state == 3) {
			gotoxy(35, 6);
			textcolor(1);
			printf("홈으로");
		}
		
		if (state == 1 && GetAsyncKeyState(VK_RIGHT)) {
			state = 2;
			gotoxy(5, 6);
			textcolor(7);
			printf("게임시작");
		}
	
		else if (state == 2 && GetAsyncKeyState(VK_LEFT)) {
			state = 1;
			gotoxy(20, 6);
			textcolor(7);
			printf("게임설명");
		}
	
		else if (state == 2 && GetAsyncKeyState(VK_RIGHT)) {
			state = 3;
			gotoxy(20, 6);
			textcolor(7);
			printf("게임설명");
		}
	
		else if (state == 3 && GetAsyncKeyState(VK_LEFT)) {
			state = 2;
			gotoxy(35, 6);
			textcolor(7);
			printf("홈으로");
		}

		//n*n퍼즐 실행
		if (state == 1 && GetAsyncKeyState(VK_UP)) {
			gotoxy(0, 0);
			NPuzzle();
			break;
		}

		//n*n퍼즐 게임 설명
		else if (state == 2 && GetAsyncKeyState(VK_UP)) {
			gotoxy(0, 0);
			explainNPuzzle();
			break;
		}
			
		//첫화면으로
		else if (state == 3 && GetAsyncKeyState(VK_UP)) {
			gotoxy(0, 0);
			main_ui();
			break;
		}
	
		Sleep(100);
	}
}

//테트리스 메인ui
void StartTetris() {
	system("cls");
	Sleep(200);
	int state = 1;
	gotoxy(20, 0);
	textcolor(7);
	printf("테트리스");
	gotoxy(0, 3);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■    게임시작       게임설명       홈으로      ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	while (1) {
		Sleep(100);
		if (state == 1) {
			gotoxy(5, 6);
			textcolor(4);
			printf("게임시작");
		}

		else if (state == 2) {
			gotoxy(20, 6);
			textcolor(6);
			printf("게임설명");
		}

		else if (state == 3) {
			gotoxy(35, 6);
			textcolor(1);
			printf("홈으로");
		}
		
		if (state == 1 && GetAsyncKeyState(VK_RIGHT)) {
			state = 2;
			gotoxy(5, 6);
			textcolor(7);
			printf("게임시작");
		}
	
		else if (state == 2 && GetAsyncKeyState(VK_LEFT)) {
			state = 1;
			gotoxy(20, 6);
			textcolor(7);
			printf("게임설명");
		}
	
		else if (state == 2 && GetAsyncKeyState(VK_RIGHT)) {
			state = 3;
			gotoxy(20, 6);
			textcolor(7);
			printf("게임설명");
		}
	
		else if (state == 3 && GetAsyncKeyState(VK_LEFT)) {
			state = 2;
			gotoxy(35, 6);
			textcolor(7);
			printf("홈으로");
		}

		//테트리스 실행
		if (state == 1 && GetAsyncKeyState(VK_UP)) {
			gotoxy(0, 0);
			Tetris();
			break;
		}

		//테트리스 게임 설명
		else if (state == 2 && GetAsyncKeyState(VK_UP)) {
			gotoxy(0, 0);
			explainTetris();
			break;
		}

		//첫화면으로
		else if (state == 3 && GetAsyncKeyState(VK_UP)) {
			gotoxy(0, 0);
			main_ui();
			break;
		}
	}
}
