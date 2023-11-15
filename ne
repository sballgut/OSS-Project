#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#define LEFT      75
#define RIGHT   77
#define UP        72
#define DOWN  80

int easypuzzle();

int hardpuzzle();

int get_directionkey()//방향키를 입력받는 함수
{
	int key;
	key = _getch();
	if (key == 224)//방향키
	{
		return _getch(); //어떤 방향 키인지 반환
	}
	return 0;    //방향키가 아님
}

void print_puzzle(int puzzle[][3])
{
	int r, c;
	system("cls"); //콘솔 화면을 지우기
	for (r = 0; r < 3; r++)//열 반복
	{
		for (c = 0; c < 3; c++)//행 반복
		{
			if (puzzle[r][c])//참이면(0이 아니면)
			{
				printf("%3d", puzzle[r][c]);//퍼즐의 수를 출력
			}
			else//거짓(0)이면
			{
				printf("   ");//공백 출력
			}

		}
		printf("\n");//개행
	}
}

int is_ending(int puzzle[][3])
{
	int r, c;

	for (r = 0; r < 3; r++)//열 반복
	{
		for (c = 0; c < 3; c++)//행 반복
		{
			if (puzzle[r][c] != r * 3 + c + 1)
			{
				return (r == 2) && (c == 2);
			}
		}
	}
	return 0;

}





int main() {
	
	clock_t start, end;
	start = clock();
	for(int count=0; count==1; count++)
	easypuzzle();


	
	float time =  easypuzzle();

	if (time < 1000) {

		hardpuzzle();
	}

}

int easypuzzle() {



	clock_t start, end;
	start = clock();
	// 시간 측정을 실행할 함수..



	int puzzle[3][3] = { { 1,3,2 },{ 7,8,4 },{ 6,5,0 } };
	int row = 2;
	int col = 2;
	int key = 0;

	while (!is_ending(puzzle))
	{
		print_puzzle(puzzle);
		printf(">> 방향키 선택 \n");
		key = get_directionkey();

		switch (key)
		{
		case RIGHT:
			if (col > 0)
			{
				puzzle[row][col] = puzzle[row][col - 1];
				puzzle[row][col - 1] = 0;
				col--;
			}

			break;
		case LEFT:
			if (col < 3 - 1)
			{
				puzzle[row][col] = puzzle[row][col + 1];
				puzzle[row][col + 1] = 0;
				col++;
			}
			break;
		case UP:
			if (row < 3 - 1)
			{
				puzzle[row][col] = puzzle[row + 1][col];
				puzzle[row + 1][col] = 0;
				row++;
			}
			break;
		case DOWN:
			if (row > 0)
			{
				puzzle[row][col] = puzzle[row - 1][col];
				puzzle[row - 1][col] = 0;
				row--;
			}
			break;
		}
	}


	end = clock();
	printf("[time : %f]\n", (float)(end - start) / CLOCKS_PER_SEC);
	float time1 = (float)(end - start) / CLOCKS_PER_SEC;
	return time1;
	
}







int get_directionkey2() {
	int key = _getch();
	if (key == 224) {
		return _getch();
	}
	return 0;
}

void print_puzzle2(int puzzle[][4]) {
	system("cls");
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
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

int is_ending2(int puzzle[][4]) {
	int num = 1;
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (puzzle[r][c] != num && (r != 3 || c != 3)) {
				return 0;  // 아직 정렬되지 않음
			}
			num = (num + 1) % (4 * 4);
		}
	}
	return 1;  // 정렬 완료
}



int hardpuzzle()
{
	clock_t start, end;
	start = clock();
	// 시간 측정을 실행할 함수..




	int puzzle[4][4] = {
	  {14, 2, 4, 15},
	  {5, 8, 11, 6},
	  {9, 10, 7, 13},
	  {12, 1, 3, 0}
	};

	int row = 3;
	int col = 3;
	int key = 0;

	while (!is_ending2(puzzle)) {
		print_puzzle2(puzzle);
		printf(">> 방향키 선택 \n");
		key = get_directionkey2();

		switch (key) {
		case RIGHT:
			if (col > 0) {
				puzzle[row][col] = puzzle[row][col - 1];
				puzzle[row][col - 1] = 0;
				col--;
			}
			break;

		case LEFT:
			if (col < 3) {
				puzzle[row][col] = puzzle[row][col + 1];
				puzzle[row][col + 1] = 0;
				col++;
			}
			break;

		case UP:
			if (row < 3) {
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


	end = clock();
	printf("[time : %f]\n", (float)(end - start) / CLOCKS_PER_SEC);

}
