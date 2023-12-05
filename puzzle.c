#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#define LEFT      75
#define RIGHT   77
#define UP        72
#define DOWN  80
#include <time.h>


int EgetDirectionKey() {
	int key = _getch();
	if (key == 224) {
		return _getch();
	}
	return 0;
}

void EprintPuzzle(int puzzle[][3]) {
	system("cls");
	for (int r = 0; r < 3; r++) {
		printf("\n\n");
		for (int c = 0; c < 3; c++) {
			if (puzzle[r][c]) {
				// 각 숫자를 출력할 때 일정한 간격을 확보
				if (puzzle[r][c] < 10) {
					printf("   %d   ", puzzle[r][c]);
				}
				else {
					printf("  %d   ", puzzle[r][c]);
				}
			}
			else {
				// 빈 칸은 공백 출력
				printf("       ");
			}
		}
		printf("\n\n");
	}
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














#define PUZZLE_SIZE 4

int HgetDirectionKey() {
	int key = _getch();
	if (key == 224) {
		return _getch();
	}
	return 0;
}

void HprintPuzzle(int puzzle[][4]) {
	system("cls");
	for (int r = 0; r < 4; r++) {
		printf("\n\n");
		for (int c = 0; c < 4; c++) {
			if (puzzle[r][c]) {
				// 각 숫자를 출력할 때 일정한 간격을 확보
				if (puzzle[r][c] < 10) {
					printf("     %d   ", puzzle[r][c]);
				}
				else {
					printf("    %d   ", puzzle[r][c]);
				}
			}
			else {
				// 빈 칸은 공백 출력
				printf("       ");
			}
		}
		printf("\n\n\n");
	}
}


int HisEnding(int puzzle[][4]) {
	int count = 1;
	for (int r = 0; r < PUZZLE_SIZE; r++) {
		for (int c = 0; c < PUZZLE_SIZE; c++) {
			if (puzzle[r][c] != count) {
				return 0;
			}
			count = (count == PUZZLE_SIZE * PUZZLE_SIZE - 1) ? 0 : count + 1;
		}
	}
	return 1;
}

void HshufflePuzzle(int puzzle[][PUZZLE_SIZE]) {
	srand(time(NULL));

	int flatPuzzle[PUZZLE_SIZE * PUZZLE_SIZE];
	for (int i = 0; i < PUZZLE_SIZE * PUZZLE_SIZE - 1; i++) {
		flatPuzzle[i] = i + 1;
	}
	flatPuzzle[PUZZLE_SIZE * PUZZLE_SIZE - 1] = 0;  // 0은 빈 칸을 나타냄

	for (int i = PUZZLE_SIZE * PUZZLE_SIZE - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = flatPuzzle[i];
		flatPuzzle[i] = flatPuzzle[j];
		flatPuzzle[j] = temp;
	}

	for (int r = 0; r < PUZZLE_SIZE; r++) {
		for (int c = 0; c < PUZZLE_SIZE; c++) {
			puzzle[r][c] = flatPuzzle[r * PUZZLE_SIZE + c];
		}
	}
}

int hardpuzzle() {
	srand(time(NULL));

	// 1부터 10까지의 난수 생성
	int randomnumber = rand() % 5 + 1;

	int puzzle[4][4];
	if (randomnumber == 1) {
		    puzzle[0][0] = 14; puzzle[0][1] = 2; puzzle[0][2] = 13; puzzle[0][3] = 10;
			puzzle[1][0] = 11; puzzle[1][1] = 1; puzzle[1][2] = 7; puzzle[1][3] = 5;
			puzzle[2][0] = 12; puzzle[2][1] = 9; puzzle[2][2] = 15; puzzle[2][3] = 4;
			puzzle[3][0] = 8; puzzle[3][1] = 6; puzzle[3][2] = 3; puzzle[3][3] = 0;
	}
	else if (randomnumber == 2) {
		puzzle[0][0] = 1; puzzle[0][1] = 2; puzzle[0][2] = 10; puzzle[0][3] = 11;
		puzzle[1][0] = 9; puzzle[1][1] = 12; puzzle[1][2] = 6; puzzle[1][3] = 5;
		puzzle[2][0] = 14; puzzle[2][1] = 13; puzzle[2][2] = 8; puzzle[2][3] = 15;
		puzzle[3][0] = 4; puzzle[3][1] = 7; puzzle[3][2] = 3; puzzle[3][3] = 0;
	}
	else if (randomnumber == 3) {
		puzzle[0][0] = 1; puzzle[0][1] = 7; puzzle[0][2] = 12; puzzle[0][3] = 4;
		puzzle[1][0] = 6; puzzle[1][1] = 3; puzzle[1][2] = 11; puzzle[1][3] = 2;
		puzzle[2][0] = 9; puzzle[2][1] = 13; puzzle[2][2] = 15; puzzle[2][3] = 5;
		puzzle[3][0] = 10; puzzle[3][1] = 14; puzzle[3][2] = 8; puzzle[3][3] = 0;
	}
	else if (randomnumber == 4) {
		puzzle[0][0] = 2; puzzle[0][1] = 10; puzzle[0][2] = 6; puzzle[0][3] = 3;
		puzzle[1][0] = 11; puzzle[1][1] = 12; puzzle[1][2] = 5; puzzle[1][3] = 1;
		puzzle[2][0] = 9; puzzle[2][1] = 7; puzzle[2][2] = 4; puzzle[2][3] = 8;
		puzzle[3][0] = 13; puzzle[3][1] = 14; puzzle[3][2] = 15; puzzle[3][3] = 0;
	}
	else if (randomnumber == 5) {
		puzzle[0][0] = 12; puzzle[0][1] = 13; puzzle[0][2] = 1; puzzle[0][3] = 4;
		puzzle[1][0] = 9; puzzle[1][1] = 6; puzzle[1][2] = 8; puzzle[1][3] = 7;
		puzzle[2][0] = 11; puzzle[2][1] = 3; puzzle[2][2] = 5; puzzle[2][3] = 15;
		puzzle[3][0] = 14; puzzle[3][1] = 10; puzzle[3][2] = 2; puzzle[3][3] = 0;
	}

	int row, col;
	for (int r = 0; r < PUZZLE_SIZE; r++) {
		for (int c = 0; c < PUZZLE_SIZE; c++) {
			if (puzzle[r][c] == 0) {
				row = r;
				col = c;
			}
		}
	}

	int key = 0;

	while (!HisEnding(puzzle)) {
		HprintPuzzle(puzzle);
		printf("\n\n\n");
		printf(">> 방향키 선택\n");
		key = HgetDirectionKey();

		switch (key) {
		case RIGHT:
			if (col > 0) {
				puzzle[row][col] = puzzle[row][col - 1];
				puzzle[row][col - 1] = 0;
				col--;
			}
			break;
		case LEFT:
			if (col < PUZZLE_SIZE - 1) {
				puzzle[row][col] = puzzle[row][col + 1];
				puzzle[row][col + 1] = 0;
				col++;
			}
			break;
		case UP:
			if (row < PUZZLE_SIZE - 1) {
				puzzle[row][col] = puzzle[row + 1][col];
				puzzle[row + 1][col] = 0;
				row++;
			}
			break;
		case DOWN:
			if (row > 0) {
				puzzle[row][col] = puzzle[row - 1][col];
				puzzle[row - 1][col] = 0;
				row--;
			}
			break;
		}
	}


	return 0;
}


int main()
{
	clock_t start_time, end_time;
	double cpu_time_used;

	start_time = clock();  // 시작 시간 기록

	// 실행 시간을 측정하고자 하는 작업
	easypuzzle();

	end_time = clock();  // 끝 시간 기록

	// 실행 시간 계산 (초 단위)
	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	printf("Elapsed CPU time: %.6f seconds\n", cpu_time_used);

	int choose;

	if (cpu_time_used > 30) {
		printf("But game out(시간50초를 넘기셨습니다)\n");
		printf("게임을 다시하겠습니까?\n");
		printf("1.YES    2.NO\n");
		scanf_s("%d", &choose);
		if (choose == 1) {
			for (; cpu_time_used > 30;) {
				start_time = clock();  // 시작 시간 기록

				// 실행 시간을 측정하고자 하는 작업
				easypuzzle();

				end_time = clock();  // 끝 시간 기록
				cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
			}
			hardpuzzle();
		}

	}
	else if (cpu_time_used < 30) {
		printf("게임 클리어!\n");
		hardpuzzle();
	}


	return 0;
}