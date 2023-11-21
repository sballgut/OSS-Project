#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#define LEFT      75
#define RIGHT   77
#define UP        72
#define DOWN  80
#include <time.h>


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


    if (cpu_time_used < 5000) {
        
        hardpuzzle();
    }

    return 0;
}


int easypuzzle() {
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
}





int get_directionkey1() {
    int key = _getch();
    if (key == 224) {
        return _getch();
    }
    return 0;
}

void print_puzzle1(int puzzle[][4]) {
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

int is_ending1(int puzzle[][4]) {
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

int hardpuzzle() {

    int puzzle[4][4] = {
       {14, 2, 4, 15},
      {5, 8, 11, 6},
      {9, 10, 7, 13},
      {12, 1, 3, 0}
    };

    int row = 3;
    int col = 3;
    int key = 0;

    while (!is_ending1(puzzle)) {
        print_puzzle1(puzzle);
        printf(">> 방향키 선택 \n");
        key = get_directionkey1();

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
    return 0;
}
