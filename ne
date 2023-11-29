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
		for (int c = 0; c < 3; c++) {
			if (puzzle[r][c]) {
				printf("%3d", puzzle[r][c]);
			}
			else {
				printf("   ");
			}
		}
		printf("\n");
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
	int puzzle[3][3];
	EshufflePuzzle(puzzle);

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
		case LEFT:
			if (col < 2) {
				puzzle[row][col] = puzzle[row][col + 1];
				puzzle[row][col + 1] = 0;
				col++;
			}
			break;
		case UP:
			if (row < 2) {
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

void HprintPuzzle(int puzzle[][PUZZLE_SIZE]) {
	system("cls");
	for (int r = 0; r < PUZZLE_SIZE; r++) {
		for (int c = 0; c < PUZZLE_SIZE; c++) {
			if (puzzle[r][c]) {
				printf("%4d", puzzle[r][c]);
			}
			else {
				printf("    ");
			}
		}
		printf("\n");
	}
}

int HisEnding(int puzzle[][PUZZLE_SIZE]) {
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
	int puzzle[PUZZLE_SIZE][PUZZLE_SIZE];
	HshufflePuzzle(puzzle);

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

	printf("게임 클리어!\n");
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

	if (cpu_time_used > 10)
		printf("But game out gg");
	
	else if(cpu_time_used < 10) hardpuzzle();
	

	return 0;
}
