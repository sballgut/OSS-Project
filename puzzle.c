#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define LEFT      75
#define RIGHT   77
#define UP        72
#define DOWN  80
#include <time.h>

void gotoxy(int x, int y);

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int EgetDirectionKey() {
	int key = _getch();
	if (key == 224) {
		return _getch();
	}
	return 0;
}

void EprintPuzzle(int puzzle[][3]) {
	
	system("cls");
	printf("\n\n");
	printf("■■■■■■■■■■■■■\n");
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			printf("■");
			if (puzzle[r][c]) {
				// 각 숫자를 출력할 때 일정한 간격을 확보
				if (puzzle[r][c] < 10) {
					printf("   %d  ", puzzle[r][c]);
				}
				else {
					printf("    %d   ", puzzle[r][c]);
				}
			}
			else {
				// 빈 칸은 공백 출력
				printf("      ");
			}
		}
		printf("■\n");
		if (r < 2) {
			for (int c = 0; c < 1; c++) {
				printf("■■■■■■■■■■■■■");
			}
			printf("\n");
		}

	}
	printf("■■■■■■■■■■■■■\n\n");

	gotoxy(28, 4);
	printf("    ■■■■■\n");
	gotoxy(28, 5);
	printf("    ■ 3*3  ■\n");
	gotoxy(28, 6);
	printf("    ■■■■■\n");
}

int EisEnding(int puzzle[][3]) {
	int count = 1;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (puzzle[r][c] != count) {
				return 0;
			}
			count = (count == 8) ? 0 : count + 1;
		}
	}
	return 1;
}

void EshufflePuzzle(int puzzle[][3]) {
	srand(time(NULL));

	int flatPuzzle[9];
	for (int i = 0; i < 8; i++) {
		flatPuzzle[i] = i + 1;
	}
	flatPuzzle[8] = 0;  // 0은 빈 칸을 나타냄

	for (int i = 8; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = flatPuzzle[i];
		flatPuzzle[i] = flatPuzzle[j];
		flatPuzzle[j] = temp;
	}

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			puzzle[r][c] = flatPuzzle[r * 3 + c];
		}
	}
}

int easypuzzle() {
	srand(time(NULL));

	// 1부터 10까지의 난수 생성
	int randomnumber = rand() % 5 + 1;

	int puzzle[3][3];
	if (randomnumber == 1) {
		puzzle[0][0] = 8; puzzle[0][1] = 3; puzzle[0][2] = 5;
		puzzle[1][0] = 1; puzzle[1][1] = 4; puzzle[1][2] = 6;
		puzzle[2][0] = 2; puzzle[2][1] = 7; puzzle[2][2] = 0;
	}
	else if (randomnumber == 2) {
		puzzle[0][0] = 7; puzzle[0][1] = 6; puzzle[0][2] = 3;
		puzzle[1][0] = 8; puzzle[1][1] = 1; puzzle[1][2] = 2;
		puzzle[2][0] = 5; puzzle[2][1] = 4; puzzle[2][2] = 0;
	}
	else if (randomnumber == 3) {
		puzzle[0][0] = 2; puzzle[0][1] = 3; puzzle[0][2] = 4;
		puzzle[1][0] = 1; puzzle[1][1] = 7; puzzle[1][2] = 8;
		puzzle[2][0] = 6; puzzle[2][1] = 5; puzzle[2][2] = 0;
	}
	else if (randomnumber == 4) {
		puzzle[0][0] = 2; puzzle[0][1] = 7; puzzle[0][2] = 6;
		puzzle[1][0] = 3; puzzle[1][1] = 4; puzzle[1][2] = 8;
		puzzle[2][0] = 1; puzzle[2][1] = 5; puzzle[2][2] = 0;
	}
	else if (randomnumber == 5) {
		puzzle[0][0] = 8; puzzle[0][1] = 3; puzzle[0][2] = 1;
		puzzle[1][0] = 2; puzzle[1][1] = 4; puzzle[1][2] = 7;
		puzzle[2][0] = 6; puzzle[2][1] = 5; puzzle[2][2] = 0;
	}

	int row, col;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (puzzle[r][c] == 0) {
				row = r;
				col = c;
			}
		}
	}

	int key = 0;

	while (!EisEnding(puzzle)) {
		EprintPuzzle(puzzle);
		printf("\n\n\n\n");
		printf(">> 방향키 선택\n");
		key = EgetDirectionKey();

		switch (key) {
		case RIGHT:
			if (col > 0) {
				puzzle[row][col] = puzzle[row][col - 1];
				puzzle[row][col - 1] = 0;
				col--;
			}
			break;
			// LEFT 방향 이동
		case LEFT:
			if (col < 2) {
				puzzle[row][col] = puzzle[row][col + 1];
				puzzle[row][col + 1] = 0;
				col++;
			}
			break;
			// UP 방향 이동
		case UP:
			if (row < 2) {
				puzzle[row][col] = puzzle[row + 1][col];
				puzzle[row + 1][col] = 0;
				row++;
			}
			break;
			// DOWN 방향 이동
		case DOWN:
			if (row > 0) {
				puzzle[row][col] = puzzle[row - 1][col];
				puzzle[row - 1][col] = 0;
				row--;
			}
			break;
		}
	}

	printf("게임 클리어!\n");
	return 0;
}
