#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

//n*n퍼즐, 테트리스 공용 상수
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

//숫자야구 상수
#define RANKING_FILE "ranking.txt"
#define MAX_RANKING_ENTRIES 10

//n*n퍼즐 상수
#define PUZZLE_SIZE 4

//테트리스 상수
#define MAP_SIZE_W 10
#define MAP_SIZE_H 20
#define HALF_W 15
#define HALF_H 10
#define EXIT 100

#define WALL 5
#define EMPTY 0
#define BLOCK 1

#define SPACE 32
#define ESC 27

typedef char MData;

typedef struct _currentlocation {
	int X;
	int Y;
} Location;

//숫자야구 함수 선언
void NumBaseball();
void generateRandomNumber(int* number, int digitCount);
void getUserInput(int* guess, int digitCount);
void checkGuess(int* targetNumber, int* userGuess, int digitCount, int* strikes, int* balls);
void showShop(int* score, int* targetNumber, int* digitCount);
void buyHint(int* targetNumber, int digitCount, int* score);
void showAchievement(int attempts);
void printGameUI(int* targetNumber, int* userGuess, int digitCount, int strikes, int balls, int attempts);
void displayRanking();
void updateRanking(struct Player player);
int* userGuess;
int comparePlayers(const void* a, const void* b);
void printGameUI(int* targetNumber, int* userGuess, int digitCount, int strikes, int balls, int attempts);
void explainNumberBaseball();

struct Player {
	char name[50];
	int score;
};

//n*n퍼즐 함수 선언
void NPuzzle();
void explainNPuzzle();
void printfui();
int EgetDirectionKey();
void EprintPuzzle(int puzzle[][3]);
int EisEnding(int puzzle[][3]);
void EshufflePuzzle(int puzzle[][3]);
int easypuzzle();
int HgetDirectionKey();
void HprintPuzzle(int puzzle[][4]);
int HisEnding(int puzzle[][4]);
void HshufflePuzzle(int puzzle[][PUZZLE_SIZE]);
int hardpuzzle();

//테트리스 함수 선언
void Tetris();
void explainTetris();
int speed(int* s);
void hidecursor();
void drawWall(MData map[MAP_SIZE_H][MAP_SIZE_W]);
void drawMap(MData map[MAP_SIZE_H][MAP_SIZE_W]);
void drawSubMap(int best, int score);
void drawSubShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int shape[4][4]);
void drawShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int shape[4][4], Location curLoc);
void startTime();
void mapInit(MData map[MAP_SIZE_H][MAP_SIZE_W]);
void locationInit(Location* curLoc);
void copyBlock(int blockShape[4][4], int copy[4][4]);
void setBlock(int blockShape[4][4], int* r);
void removeShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc);
int getShapeLeftLoc(int blockShape[4][4]);
int getShapeRightLoc(int blockShape[4][4]);
int getShapeBottomLoc(int blockShape[4][4]);
int getEachBottomLoc(int blockShape[4][4], int w);
int getEachLeftLoc(int blockShape[4][4], int h);
int getEachRightLoc(int blockShape[4][4], int h);
void goLeft(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc);
void goRight(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc);
int fixShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc);
int goDown(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc, int* s);
void rotate(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc);
int goSpace(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc);
void deleteLine(MData map[MAP_SIZE_H][MAP_SIZE_W], int h);
void organizeLine(MData map[MAP_SIZE_H][MAP_SIZE_W], int h);
void checkLine(MData map[MAP_SIZE_H][MAP_SIZE_W], Location curLoc, int* score, int* removeLine);
int GameOver(MData map[MAP_SIZE_H][MAP_SIZE_W], int score, int bestScore);
int GameStart(MData map[MAP_SIZE_H][MAP_SIZE_W]);

//main_ui 함수 선언
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
	gotoxy(0, 15);
	textcolor(7);
	return 0;
}

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

	int bool = 1;
	while (bool) {
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
		if (_kbhit()) {
			char key = _getch();

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

			switch (key) {
			case RIGHT:
				if (state == 1) {
					state = 2;
					gotoxy(5, 6);
					textcolor(7);
					printf("게임시작");
				}
				break;

			case LEFT:
				if (state == 2) {
					state = 1;
					gotoxy(17, 6);
					textcolor(7);
					printf("게임종료");
				}
				break;

			case UP:
				if (state == 1) {
					SelectGame();
					bool = 0;
					break;
				}
				else if (state == 2) {
					gotoxy(0, 20);
					textcolor(7);
					bool = 0;
					exit(0);
					break;
				}
				break;
			}
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

//게임선택화면 ui
void SelectGame() {
	int game = 1;
	char key;
	int i = 0;
	system("cls");
	system("mode con: cols=70 lines=30");
	textcolor(7);
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

	int bool = 1;
	while (bool) {

		if (_kbhit()) {
			key = _getch();

			switch (key) {
			case UP:
				if (game == 1) {
					StartNumberBaseball();
					bool = 0;
					break;
				}
				else if (game == 2) {
					StartNPuzzle();
					bool = 0;
					break;
				}
				else if (game == 3) {
					StartTetris();
					bool = 0;
					break;
				}
				break;

			case DOWN:
				// DOWN 키를 처리하는 코드를 추가하세요 (필요한 경우)
				break;

			case LEFT:
				if (game == 2) {
					game = 1;
					gotoxy(19, 6);
					textcolor(7);
					printf("n*n퍼즐");
				}
				else if (game == 3) {
					game = 2;
					gotoxy(31, 6);
					textcolor(7);
					printf("테트리스");
				}
				break;

			case RIGHT:
				if (game == 1) {
					game = 2;
					gotoxy(7, 6);
					textcolor(7);
					printf("숫자야구");
				}
				else if (game == 2) {
					game = 3;
					gotoxy(19, 6);
					textcolor(7);
					printf("n*n퍼즐");
				}
				break;
			}
		}

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
	}
}
//숫자야구 메인ui
void StartNumberBaseball() {
	system("cls");
	Sleep(200);
	int state = 1;
	int key;
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

	int bool = 1;
	while (bool) {

		if (_kbhit()) {
			key = _getch();

			switch (key) {
			case UP:
				if (state == 1) {
					NumBaseball();
					bool = 0;
					break;
				}
				else if (state == 2) {
					explainNumberBaseball();
					bool = 0;
					break;
				}
				else if (state == 3) {
					main_ui();
					bool = 0;
					break;
				}
				break;

			case DOWN:
				// DOWN 키를 처리하는 코드를 추가하세요 (필요한 경우)
				break;

			case LEFT:
				if (state == 2) {
					state = 1;
					gotoxy(20, 6);
					textcolor(7);
					printf("게임설명");
				}
				else if (state == 3) {
					state = 2;
					gotoxy(35, 6);
					textcolor(7);
					printf("홈으로");
				}
				break;

			case RIGHT:
				if (state == 1) {
					state = 2;
					gotoxy(5, 6);
					textcolor(7);
					printf("게임시작");
				}
				else if (state == 2) {
					state = 3;
					gotoxy(20, 6);
					textcolor(7);
					printf("게임설명");
				}
				break;
			}
		}

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
	}
}

//n*n퍼즐 메인ui
void StartNPuzzle() {
	system("cls");
	Sleep(200);
	int state = 1;
	char key;
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

	int bool = 1;
	while (bool) {

		if (_kbhit()) {
			key = _getch();

			switch (key) {
			case UP:
				if (state == 1) {
					NPuzzle();
					bool = 0;
					break;
				}
				else if (state == 2) {
					explainNPuzzle();
					bool = 0;
				}
				else if (state == 3) {
					main_ui();
					bool = 0;
					break;
				}
				break;

			case DOWN:
				// DOWN 키를 처리하는 코드를 추가하세요 (필요한 경우)
				break;

			case LEFT:
				if (state == 2) {
					state = 1;
					gotoxy(20, 6);
					textcolor(7);
					printf("게임설명");
				}
				else if (state == 3) {
					state = 2;
					gotoxy(35, 6);
					textcolor(7);
					printf("홈으로");
				}
				break;

			case RIGHT:
				if (state == 1) {
					state = 2;
					gotoxy(5, 6);
					textcolor(7);
					printf("게임시작");
				}
				else if (state == 2) {
					state = 3;
					gotoxy(20, 6);
					textcolor(7);
					printf("게임설명");
				}
				break;
			}
		}

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
	}
}

//테트리스 메인ui
void StartTetris() {
	system("cls");
	Sleep(200);
	int state = 1;
	char key;
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

	int bool = 1;
	while (bool) {

		if (_kbhit()) {
			key = _getch();

			switch (key) {
			case UP:
				if (state == 1) {
					Tetris();
					bool = 0;
					break;
				}
				else if (state == 2) {
					explainTetris();
					bool = 0;
					break;
				}
				else if (state == 3) {
					main_ui();
					bool = 0;
					break;
				}
				break;

			case DOWN:
				// DOWN 키를 처리하는 코드를 추가하세요 (필요한 경우)
				break;

			case LEFT:
				if (state == 2) {
					state = 1;
					gotoxy(20, 6);
					textcolor(7);
					printf("게임설명");
				}
				else if (state == 3) {
					state = 2;
					gotoxy(35, 6);
					textcolor(7);
					printf("홈으로");
				}
				break;

			case RIGHT:
				if (state == 1) {
					state = 2;
					gotoxy(5, 6);
					textcolor(7);
					printf("게임시작");
				}
				else if (state == 2) {
					state = 3;
					gotoxy(20, 6);
					textcolor(7);
					printf("게임설명");
				}
				break;
			}
		}

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
	}
}

//숫자야구 메인 함수
void NumBaseball() {
	system("cls");
	textcolor(7);
	int difficulty;
	int strikes, balls;
	int maxAttempts = 7;
	int score = 0; // 새로운 변수: 점수

	while (1) {
		printf("난이도를 선택하세요 (1: 3자리, 2: 4자리, 3: 5자리): ");
		scanf("%d", &difficulty);

		if (difficulty > 3) {
			printf("올바른 난이도를 선택하세요.\n");
			continue;
		}
		else if (difficulty > 0 && difficulty < 4) {
			break;
		}
	}

	int digitCount;

	switch (difficulty) {
	case 1:
		digitCount = 3;
		break;
	case 2:
		digitCount = 4;
		break;
	case 3:
		digitCount = 5;
		break;
	default:
		return 1;
	}

	srand(time(NULL));

	int* targetNumber;
	int* userGuess;

	while (1) {

		targetNumber = malloc(digitCount * sizeof(int));
		userGuess = malloc(digitCount * sizeof(int));


		generateRandomNumber(targetNumber, digitCount);

		printf("=== 숫자야구 게임 시작 (난이도: %d) ===\n", difficulty);
		printf("\n");

		int attempts = 0;
		int strikes = 0; // 초기화 추가
		int balls = 0;
		do {
			printGameUI(targetNumber, userGuess, digitCount, strikes, balls, attempts);



			getUserInput(userGuess, digitCount);
			checkGuess(targetNumber, userGuess, digitCount, &strikes, &balls);



			attempts++;

		} while (strikes != digitCount && attempts < maxAttempts);

		if (strikes == digitCount) {
			printf("\n");

			// 업적 표시
			showAchievement(attempts);

			// 정답을 맞춘 경우에 따라 점수를 부여
			if (digitCount == 3) {
				score += 5;
			}
			else if (digitCount == 4) {
				score += 7;
			}
			else if (digitCount == 5) {
				score += 10;
			}
		}
		else {
			printf("\n");
			printf("게임 오버! 정답은 ");
			for (int i = 0; i < digitCount; ++i) {
				printf("%d", targetNumber[i]);
			}
			printf("입니다.\n\n");
		}

		// 게임이 끝난 후 메모리 해제
		free(targetNumber);
		free(userGuess);

		// 사용자에게 다시 플레이할 것인지 물어보기
		char playAgain;
		printf("다시 플레이하시겠습니까? (y/n): ");
		scanf(" %c", &playAgain);

		if (playAgain != 'y' && playAgain != 'Y') {
			break; // 게임 종료
		}

		// 다시 할 경우 난이도 선택
		while (1) {
			strikes = 0;
			balls = 0;
			printf("난이도를 선택하세요 (1: 3자리, 2: 4자리, 3: 5자리): ");
			scanf("%d", &difficulty);

			if (difficulty > 3) {
				printf("올바른 난이도를 선택하세요.\n");
				continue;
			}
			else if (difficulty > 0 && difficulty < 4) {
				break;
			}
		}

		// 다시 할 경우 메모리 재할당
		targetNumber = malloc(digitCount * sizeof(int));
		userGuess = malloc(digitCount * sizeof(int));

		// 게임 시작 메시지 다음에 빈 줄 출력
		system("cls");

		// 상점에서 힌트를 구매할 수 있도록 추가
		showShop(&score, &targetNumber, &digitCount);
	}

	// 모든 게임이 종료되면 최종 점수 출력
	printf("최종 점수: %d\n", score);
	struct Player currentPlayer;
	printf("플레이어 이름을 입력하세요: ");
	scanf("%s", currentPlayer.name);

	currentPlayer.score = score;
	updateRanking(currentPlayer);
	displayRanking();
	Sleep(2000);
	StartNumberBaseball();

	return 0;
}

//숫자 야구 함수
void generateRandomNumber(int* number, int digitCount) {
	for (int i = 0; i < digitCount; ++i) {
		number[i] = rand() % 10;
	}
}

void getUserInput(int* guess, int digitCount) {
	int validInput;

	do {
		validInput = 1; // 입력이 유효하다고 가정하고 시작

		printf("%d자리 숫자를 입력하세요: ", digitCount);

		for (int i = 0; i < digitCount; ++i) {
			if (scanf("%1d", &guess[i]) != 1) {
				printf("올바른 숫자를 입력하세요.\n");

				// 입력 버퍼 비우기
				int c;
				while ((c = getchar()) != '\n' && c != EOF);

				validInput = 0; // 입력이 유효하지 않음
				break;
			}
		}

		// 입력이 숫자가 아닌 문자를 포함하는지 확인
		if (validInput) {
			for (int i = 0; i < digitCount; ++i) {
				if (guess[i] < 0 || guess[i] > 9) {
					printf("올바른 숫자를 입력하세요.\n");
					validInput = 0; // 입력이 유효하지 않음
					break;
				}
			}
		}

	} while (!validInput);
}

void checkGuess(int* targetNumber, int* userGuess, int digitCount, int* strikes, int* balls) {
	*strikes = 0;
	*balls = 0;

	// 배열을 통해 중복된 숫자를 처리하기 위한 배열 선언
	int targetCount[10] = { 0 };
	int guessCount[10] = { 0 };

	for (int i = 0; i < digitCount; ++i) {
		if (userGuess[i] == targetNumber[i]) {
			(*strikes)++;
		}
		else {
			// 중복된 숫자를 처리
			targetCount[targetNumber[i]]++;
			guessCount[userGuess[i]]++;
		}
	}

	for (int i = 0; i < 10; ++i) {
		*balls += (targetCount[i] < guessCount[i]) ? targetCount[i] : guessCount[i];
	}
}


// showShop 함수 수정
void showShop(int* score, int* targetNumber, int* digitCount) {
	printf("===== 상점 =====\n");
	printf("현재 보유 점수: %d\n", *score);
	printf("1. 힌트 구매 (10점)\n");
	printf("================\n");

	char choice;
	printf("상점에서 무엇을 구매하시겠습니까? (0: 나가기): ");
	scanf(" %c", &choice);

	switch (choice) {
	case '1':
	case 'h':
	case 'H':
		buyHint(digitCount, score, targetNumber);
		Sleep(1000);
		break;
	case '0':
		// 나가기
		break;
	default:
		printf("잘못된 선택입니다. 다시 선택하세요.\n");
		showShop(score, targetNumber, digitCount);
		break;
	}
}


// buyHint 함수
void buyHint(int* targetNumber, int digitCount, int* score) {
	if (*score >= 10) {
		// 힌트 구매 가능한 경우
		*score -= 10; // 점수 차감

		int hintDigitCount = digitCount; // 힌트의 자릿수를 원래 숫자와 동일하게 설정

		// 힌트를 생성할 배열 동적 할당
		int* hint = malloc(hintDigitCount * sizeof(int));

		// 힌트 배열에 세 자리 수의 합 저장
		int sum = 0;
		for (int i = 0; i < digitCount; ++i) {
			sum += targetNumber[i];
		}

		// 합을 각 자리에 할당
		for (int i = hintDigitCount - 1; i >= 0; --i) {
			hint[i] = sum % 10;
			sum /= 10;
		}

		// 힌트 출력
		printf("힌트: ");
		for (int i = 0; i < hintDigitCount; ++i) {
			printf("%d", hint[i]);
		}
		printf("\n");

		// 힌트 배열 메모리 해제
		free(hint);
	}
	else {
		printf("보유 점수가 부족하여 힌트를 구매할 수 없습니다.\n");
		Sleep(1000);
	}
}



void showAchievement(int attempts) {
	if (attempts == 1) {
		printf("Perfect! 1번만에 성공하셨습니다.\n");
	}
	else if (attempts == 2) {
		printf("Fantastic! 2번만에 성공하셨습니다.\n");
	}
	else if (attempts == 3) {
		printf("Amazing! 3번만에 성공하셨습니다.\n");
	}
	else if (attempts == 4) {
		printf("Excellent! 4번만에 성공하셨습니다.\n");
	}
	else if (attempts == 5) {
		printf("Well done! 5번만에 성공하셨습니다.\n");
	}
	else if (attempts == 6) {
		printf("Good job! 6번만에 성공하셨습니다.\n");
	}
	else {
		printf("Great! %d번 만에 성공하셨습니다.\n", attempts);
	}
}
void updateRanking(struct Player player) {
	FILE* file = fopen(RANKING_FILE, "a");
	if (file == NULL) {
		printf("랭킹 파일을 열 수 없습니다.\n");
		return;
	}

	fprintf(file, "%s %d\n", player.name, player.score); // 파일에 플레이어 정보 추가
	fclose(file); // 파일 닫기
}

void displayRanking() {
	FILE* file = fopen(RANKING_FILE, "r"); // 파일 열기 (읽기 모드)
	if (file == NULL) {
		printf("랭킹 파일을 열 수 없습니다.\n");
		return;
	}

	// 플레이어 항목을 배열로 읽어들임
	struct Player players[MAX_RANKING_ENTRIES];
	int numPlayers = 0;

	while (fscanf(file, "%s %d", players[numPlayers].name, &players[numPlayers].score) == 2) {
		numPlayers++;
		if (numPlayers >= MAX_RANKING_ENTRIES) {
			break;  // 배열 크기를 초과하지 않도록 함
		}
	}

	fclose(file); // 파일 닫기

	// 플레이어를 점수에 따라 내림차순으로 정렬
	qsort(players, numPlayers, sizeof(struct Player), comparePlayers);

	printf("\n===== 랭킹 =====\n");

	// 정렬된 플레이어를 출력
	for (int i = 0; i < numPlayers; i++) {
		printf("%s - %d점\n", players[i].name, players[i].score);
	}

	printf("================\n");
	Sleep(3000);
}

int comparePlayers(const void* a, const void* b) {
	return ((struct Player*)b)->score - ((struct Player*)a)->score;
}

void printGameUI(int* targetNumber, int* userGuess, int digitCount, int strikes, int balls, int attempts) {
	system("cls");  // 화면을 지우고

	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■        Attempts: %-2d        ■\n", attempts);
	printf("■                            ■\n");
	printf("■        Strikes: %-2d         ■\n", strikes);
	printf("■        Balls  : %-2d         ■\n", balls);
	printf("■                            ■\n");
	printf("■                            ■\n");
	printf("■                            ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

	// 여기서 필요한 경우 targetNumber 등을 활용하여 게임 상태를 출력

} 

void explainNumberBaseball() {
	system("cls");
	gotoxy(0, 0);
	textcolor(7);
	int a = 0;
	while (1) {
		char key;
		key = getKeyDown();
		if (key == 't' || key == 'T') {
			system("cls");
			StartNumberBaseball();
			break;
		}
		if (a == 0) {
			printf("3자리, 4자리, 5자리의 난이도를 정하여 게임을 시작할 수 있습니다.\n");
			printf("정답을 맞출 때마다 각각 5점, 7점, 10점을 획득하실 수 있습니다.\n");
			printf("점수는 계속 쌓이는 방식이며 얻은 점수로 상점에서 아이템을 구매할 수 있습니다.\n");
			printf("상점은 게임이 끝난 후 이용하실 수 있습니다.\n");
			printf("단, 게임을 그만둘 시 얻은 점수는 리셋됩니다.\n");
			printf("게임 종료 후 자신의 이름을 입력하면 랭킹에 등록됩니다.\n");
			printf("t키를 누르면 이전 화면으로 돌아갑니다.");
		}
		a++;
	}
}
//숫자야구 함수 끝

//n*n퍼즐 메인 함수
void NPuzzle() {
	system("cls");
	textcolor(7);
	clock_t start_time, end_time;
	double cpu_time_used;
	char key;

	start_time = clock();  // 시작 시간 기록

	// 실행 시간을 측정하고자 하는 작업
	
	easypuzzle();

	end_time = clock();  // 끝 시간 기록

	// 실행 시간 계산 (초 단위)
	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	printf("Elapsed CPU time: %.3lf seconds\n", cpu_time_used);

	int choose;

	if (cpu_time_used > 30) {
		printf("      But game out(30초를 넘기셨습니다)\n");
		printf("            게임을 다시하겠습니까?\n\n");
		printf("              1.YES    2.NO\n");
		key = _getch();
		if (key == 49) {
			for (; cpu_time_used > 30;) {
				start_time = clock();  // 시작 시간 기록

				// 실행 시간을 측정하고자 하는 작업
				easypuzzle();

				end_time = clock();  // 끝 시간 기록
				cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

			}
			hardpuzzle();
		}

		else if (key == 50) {
			system("cls");
			StartNPuzzle();
		}

	}
	else if (cpu_time_used < 30) {
		gotoxy(100, 15);
		printf("\n");
		printfui();

#ifdef _WIN32
		Sleep(9000); // Windows
		system("cls");
#else


#endif

		hardpuzzle();
	}


	return 0;
}

//n*n퍼즐 함수
void printfui() {
	printf("                                                              *****\n");
	printf("      ***      *    ********       *        *****      **             **\n");
	printf("    *     *    *    *             * *       *     *              **        ***\n");
	printf("   *           *    ********     *   *      *****           **    ***       **\n");
	printf("    *     *    *    *           *******     *    *      **       *      ***    ***\n");
	printf("      ***      *    ********   *       *    *     *                        ****   ***\n");
	printf("                                                              **   ****  *****    *  *\n");
	printf("                                                          ***     **      ***  *      *\n");
	printf("                                                     *                      * **********\n");
	printf("                                                                              *         *\n");
	printf("                                                                                **********\n");
	printf("                                                                                  *      *\n");
	printf("                                                                                     * *\n");
	printf("                                                                                ");

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
	printf("■■■■■■■■■■■■■■■■■■■■■■\n");
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
				printf("■■■■■■■■■■■■■■■■■■■■■■");
			}
			printf("\n");
		}

	}
	printf("■■■■■■■■■■■■■■■■■■■■■■\n\n");

	gotoxy(28, 4);
	printf("    ■■■■■■■■\n");
	gotoxy(28, 5);
	printf("    ■  3*3 ■\n");
	gotoxy(28, 6);
	printf("    ■■■■■■■■\n");
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
	clock_t start_time, end_time;
	double cpu_time_used;
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
	start_time = clock();
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
		clock_t curr_time = clock() - start_time;
		double cpu_used_time = (double)curr_time / 1000;
		printf("%.3f", cpu_used_time);
	}

	printf("게임 클리어!\n");
	return 0;
}

int HgetDirectionKey() {
	int key = _getch();
	if (key == 224) {
		return _getch();
	}
	return 0;
}

void HprintPuzzle(int puzzle[][4]) {
	system("cls");
	printf("\n\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			printf("■");
			if (puzzle[r][c] < 10 && puzzle[r][c] > 0) {
				// 각 숫자를 출력할 때 일정한 간격을 확보
				printf("  %d  ", puzzle[r][c]);
			}
			else if (puzzle[r][c] > 9 && puzzle[r][c] < 16) {
				printf(" %d  ", puzzle[r][c]);
			}
			else {
				// 빈 칸은 공백으로 출력합니다.
				printf("     ");
			}
		}
		printf("■\n");
		// 세로선 출력
		if (r < 3) {
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		}
		else {
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		}
	}
	gotoxy(35, 5);
	printf("    ■■■■■■■■\n");
	gotoxy(35, 6);
	printf("    ■ 4*4  ■\n");
	gotoxy(35, 7);
	printf("    ■■■■■■■■\n");
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
		printf("\n\n\n\n\n");
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

	Sleep(1000);
	StartNPuzzle();

	return 0;
}

void explainNPuzzle() {
	system("cls");
	gotoxy(0, 0);
	textcolor(7);
	int a = 0;
	while (1) {
		char key;
		key = getKeyDown();
		if (key == 't' || key == 'T') {
			system("cls");
			StartNPuzzle();
			break;
		}
		if (a == 0) {
			printf("먼저 3*3퍼즐이 나옵니다. 30초 안에 3*3 퍼즐을 풀면 4*4 퍼즐이 나옵니다.\n");
			printf("4*4 퍼즐을 풀면 게임이 종료됩니다.\n");
			printf("만약 30초 안에 3*3 퍼즐을 풀지 못할 경우 '다시하기', '홈으로' 두 가지 버튼을 선택할 수 있습니다.\n");
			printf("방향키를 이용하여 퍼즐을 풀 수 있습니다.\n");
			printf("t키를 누르면 이전 화면으로 돌아갑니다.");
		}
		a++;
	}
}

//테트리스 메인 함수
void Tetris() {
	char map[MAP_SIZE_H][MAP_SIZE_W] = { 0 };   //map
	int key;
	hidecursor();
	system("cls");
	system("color 7");                      //console color
	system("mode con: cols=70 lines=40");   //console size

	while (1) {
		key = getKeyDown();
		if (key == 't' || key == 'T') {
			StartTetris();
			break;
		}
		system("cls");
		GameStart(map);
		Sleep(1000 / 3);
		system("cls");
	}
	return 0;
}

//테트리스 함수
int speed(int* s) {
	(*s)++;
	return s;
}

void hidecursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void drawWall(MData map[MAP_SIZE_H][MAP_SIZE_W]) {
	int h, w;
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 11);

	for (h = 0; h <= MAP_SIZE_H + 1; h++) {
		for (w = 0; w <= MAP_SIZE_W + 1; w++) {
			gotoxy(w + 1, h + 1);
			if (h == 0 || w == 0 || h == MAP_SIZE_H + 1 || w == MAP_SIZE_W + 1)
				printf("■");
		}
		printf("\n");
	}
	gotoxy(HALF_W, 1);
	SetConsoleTextAttribute(hand, 14);
	printf("<Next>");
	SetConsoleTextAttribute(hand, 11);

	for (h = 2; h <= 7; h++) {
		for (w = HALF_W; w <= HALF_W + 5; w++) {
			if (w == HALF_W || w == HALF_W + 5 || h == 2 || h == 7) {
				gotoxy(w, h);
				printf("■");
			}
		}
	}
	gotoxy(HALF_W, HALF_H + 1);
	printf("Best  : ");
	gotoxy(HALF_W, HALF_H + 2);
	printf("Score : ");
	gotoxy(HALF_W, HALF_H + 12);
	printf("<Exit : 't' / Pause : 'p'>");
	SetConsoleTextAttribute(hand, 7);
}

void drawMap(MData map[MAP_SIZE_H][MAP_SIZE_W]) {
	int h, w;
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

	for (h = 0; h < MAP_SIZE_H; h++) {
		for (w = 0; w < MAP_SIZE_W; w++) {
			gotoxy(w + 2, h + 2);
			if (map[h][w] == EMPTY) {
				printf("·");
			}
			else if (map[h][w] == BLOCK) {
				SetConsoleTextAttribute(hand, 14);
				printf("■");
				SetConsoleTextAttribute(hand, 7);
			}
		}
		printf("\n");
	}

}

void drawSubMap(int best, int score) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 14);
	gotoxy(HALF_W + 4, HALF_H + 1);
	printf("%4d", best);
	gotoxy(HALF_W + 4, HALF_H + 2);
	printf("%4d", score);
	SetConsoleTextAttribute(hand, 7);
}

void drawSubShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int shape[4][4]) {
	int h, w;
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

	for (h = 3; h <= 6; h++) {
		for (w = HALF_W + 1; w <= HALF_W + 4; w++) {
			gotoxy(w, h);
			printf(" ");

		}
	}
	for (h = 3; h <= 6; h++) {
		for (w = HALF_W + 1; w <= HALF_W + 4; w++) {
			if (shape[h - 3][w - HALF_W - 1] == BLOCK) {
				gotoxy(w, h);
				SetConsoleTextAttribute(hand, 14);
				printf("■");
				SetConsoleTextAttribute(hand, 7);

			}
		}
	}
}

void drawShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int shape[4][4], Location curLoc) {
	int h, w;

	for (h = 0; h < 4; h++) {
		for (w = 0; w < 4; w++) {
			if (shape[h][w] == BLOCK) {
				map[curLoc.Y + h][curLoc.X + w] = BLOCK;
				//gotoxy(curLoc.X+2+w,curLoc.Y+2+h);
				// printf("■");
			}
		}
	}

}

void startTime() {
	int i;
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

	for (i = 0; i < 3; i++) {
		gotoxy(2, 0);
		SetConsoleTextAttribute(hand, 14);
		printf("Start : %d sec", 3 - i);
		SetConsoleTextAttribute(hand, 7);
		Sleep(1000);
	}
	gotoxy(2, 0);
	printf("                       ");
}

void mapInit(MData map[MAP_SIZE_H][MAP_SIZE_W]) {
	int i, j = 0;
	for (i = 0; i < MAP_SIZE_H; i++) {
		for (j = 0; j < MAP_SIZE_W; j++) {
			map[i][j] = EMPTY;
		}
	}
}

void locationInit(Location* curLoc) {
	curLoc->X = 3;
	curLoc->Y = 0;
}

void copyBlock(int blockShape[4][4], int copy[4][4]) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			blockShape[i][j] = copy[i][j];
		}
	}
}

void setBlock(int blockShape[4][4], int* r) {

	int shape[10][4][4] = {
			{{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},
			{{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
			{{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
			{{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
			{{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
			{{0,1,0,0},{0,1,1,1},{0,0,0,0},{0,0,0,0}},
			{{0,1,1,1},{0,1,0,0},{0,0,0,0},{0,0,0,0}},
			{{0,1,0,1},{0,1,1,1},{0,0,0,0},{0,0,0,0}},
			{{0,1,1,1},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
			{{0,1,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}}
	};
	/*
	int shapeLong[4][4] = {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}};
	int shapeRock[4][4] = {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}};
	int shapeHorn[4][4] = {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}};
	int shapeStair[4][4] = {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}};
	int shapeRStair[4][4] = {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}};
	int shapeNienun[4][4] = {{0,1,0,0},{0,1,1,1},{0,0,0,0},{0,0,0,0}};
	int shapeRNieun[4][4] = {{0,1,1,1},{0,1,0,0},{0,0,0,0},{0,0,0,0}};
	int shapeU[4][4] = {{0,1,0,1},{0,1,1,1},{0,0,0,0},{0,0,0,0}};
	int shapeL[4][4] = {{0,1,1,1},{0,1,0,0},{0,1,0,0},{0,0,0,0}};
	int shape+[4][4] = {{0,1,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}};
*/
	srand((unsigned int)(time(NULL)));

	switch (rand() % (*r)) {
	case 0:
		copyBlock(blockShape, shape[0]);
		break;
	case 1:
		copyBlock(blockShape, shape[1]);
		break;
	case 2:
		copyBlock(blockShape, shape[2]);
		break;
	case 3:
		copyBlock(blockShape, shape[3]);
		break;
	case 4:
		copyBlock(blockShape, shape[4]);
		break;
	case 5:
		copyBlock(blockShape, shape[5]);
		break;
	case 6:
		copyBlock(blockShape, shape[6]);
		break;
	case 7:
		copyBlock(blockShape, shape[7]);
		break;
	case 8:
		copyBlock(blockShape, shape[8]);
		break;
	case 9:
		copyBlock(blockShape, shape[9]);
		break;
	default:
		break;
	}
}

void removeShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc) {
	int h, w;
	for (h = 0; h < 4; h++) {
		for (w = 0; w < 4; w++) {
			if (blockShape[h][w] == BLOCK)
				map[curLoc->Y + h][curLoc->X + w] = EMPTY;
		}
	}
}

int getShapeLeftLoc(int blockShape[4][4]) {
	int h, w, leftW = 4;
	for (w = 0; w < 4; w++) {
		for (h = 0; h < 4; h++) {
			if (blockShape[h][w] == BLOCK) {
				if (leftW > w)
					leftW = w;
			}
		}
	}
	return leftW;
}

int getShapeRightLoc(int blockShape[4][4]) {
	int h, w, rightW = 0;
	for (w = 3; w >= 0; w--) {
		for (h = 3; h >= 0; h--) {
			if (blockShape[h][w] == BLOCK) {
				if (rightW < w)
					rightW = w;
			}
		}
	}
	return rightW + 1;
}

int getShapeBottomLoc(int blockShape[4][4]) {
	int h, w, bottomH = 0;
	for (w = 3; w >= 0; w--) {
		for (h = 3; h >= 0; h--) {
			if (blockShape[h][w] == BLOCK) {
				if (bottomH < h)
					bottomH = h;
			}
		}
	}
	return bottomH + 1;
}

int getEachBottomLoc(int blockShape[4][4], int w) {
	int h, bottomH = -1;
	for (h = 3; h >= 0; h--) {
		if (blockShape[h][w] == BLOCK) {
			if (bottomH < h)
				bottomH = h;
		}
	}
	return bottomH;
}

int getEachLeftLoc(int blockShape[4][4], int h) {
	int w, leftW = 5;
	for (w = 0; w < 4; w++) {
		if (blockShape[h][w] == BLOCK) {
			if (leftW > w)
				leftW = w;
		}
	}
	return leftW;
}

int getEachRightLoc(int blockShape[4][4], int h) {
	int w, rightW = -1;
	for (w = 0; w < 4; w++) {
		if (blockShape[h][w] == BLOCK) {
			if (rightW < w)
				rightW = w;
		}
	}
	return rightW;
}

void goLeft(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc) {
	int leftW = getShapeLeftLoc(blockShape);
	int boundaryArr[4] = { 0 };
	int i;
	for (i = 0; i < 4; i++) {
		boundaryArr[i] = getEachLeftLoc(blockShape, i);

	}
	if ((curLoc->X) + leftW > 0) {
		if (!((boundaryArr[0] != 5 && map[curLoc->Y][curLoc->X + boundaryArr[0] - 1] != EMPTY)
			|| (boundaryArr[1] != 5 && map[curLoc->Y + 1][curLoc->X + boundaryArr[1] - 1] != EMPTY)
			|| (boundaryArr[2] != 5 && map[curLoc->Y + 2][curLoc->X + boundaryArr[2] - 1] != EMPTY)
			|| (boundaryArr[3] != 5 && map[curLoc->Y + 3][curLoc->X + boundaryArr[3] - 1] != EMPTY))) {

			removeShape(map, blockShape, curLoc);
			(curLoc->X)--;
		}
	}
}

void goRight(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc) {
	int rightW = getShapeRightLoc(blockShape);
	int boundaryArr[4] = { 0 };
	int i;
	for (i = 0; i < 4; i++) {
		boundaryArr[i] = getEachLeftLoc(blockShape, i);

	}

	if ((curLoc->X) + rightW < MAP_SIZE_W) {
		if (!((boundaryArr[0] != 5 && map[curLoc->Y][curLoc->X + boundaryArr[0] + 1] != EMPTY)
			|| (boundaryArr[1] != 5 && map[curLoc->Y + 1][curLoc->X + boundaryArr[1] + 1] != EMPTY)
			|| (boundaryArr[2] != 5 && map[curLoc->Y + 2][curLoc->X + boundaryArr[2] + 1] != EMPTY)
			|| (boundaryArr[3] != 5 && map[curLoc->Y + 3][curLoc->X + boundaryArr[3] + 1] != EMPTY))) {

			removeShape(map, blockShape, curLoc);
			(curLoc->X)++;
		}

	}
}

int fixShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc) {
	int w, h;
	for (w = 0; w < 4; w++) {
		for (h = 0; h < 4; h++) {
			if (blockShape[h][w] == 1) {
				map[curLoc->Y + h][curLoc->X + w] = BLOCK;
			}
		}
	}
}

int goDown(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc, int* s) {
	int bottomH = getShapeBottomLoc(blockShape);
	int bottomArr[4] = { 0 };
	int i;
	int speed = s;

	for (i = 0; i < 4; i++) {
		bottomArr[i] = getEachBottomLoc(blockShape, i);
	}
	if (curLoc->Y + bottomH == MAP_SIZE_H
		|| (bottomArr[1] != -1 && map[curLoc->Y + bottomArr[1] + 1][curLoc->X + 1] != EMPTY)
		|| (bottomArr[0] != -1 && map[curLoc->Y + bottomArr[0] + 1][curLoc->X + 0] != EMPTY)
		|| (bottomArr[3] != -1 && map[curLoc->Y + bottomArr[3] + 1][curLoc->X + 3] != EMPTY)
		|| (bottomArr[2] != -1 && map[curLoc->Y + bottomArr[2] + 1][curLoc->X + 2] != EMPTY)
		) {

		fixShape(map, blockShape, curLoc);

		Sleep(1000 / 8);
		return TRUE;
	}


	if (curLoc->Y + bottomH < MAP_SIZE_H) {
		removeShape(map, blockShape, curLoc);
		Sleep(1000 / (*s));
		(curLoc->Y)++;
	}
	return FALSE;
}

void rotate(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc) {
	int i, j;
	int tmp[4][4];
	int leftW, rightW, bottomH;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (blockShape[i][j] == BLOCK) {
				tmp[j][3 - i] = blockShape[i][j];
				blockShape[i][j] = EMPTY;
			}

		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (tmp[i][j] == 1) {
				blockShape[i][j] = BLOCK;
			}

		}
	}


	//벽에 붙어서 rotate 했을때. (when rotate near the wall.
	leftW = getShapeLeftLoc(blockShape);
	if (curLoc->X + leftW < 0) {
		goRight(map, blockShape, curLoc);
		if (leftW == 0) goRight(map, blockShape, curLoc); //long shape
	}

	rightW = getShapeRightLoc(blockShape);
	if (curLoc->X + rightW > MAP_SIZE_W) {
		goLeft(map, blockShape, curLoc);
		if (rightW == 4)goLeft(map, blockShape, curLoc); //long shape
	}


	bottomH = getShapeBottomLoc(blockShape);
	if (curLoc->Y + bottomH > MAP_SIZE_H) {
		removeShape(map, blockShape, curLoc);
		(curLoc->Y)--;
		if (bottomH == 4) (curLoc->Y)--;      //long shape
	}
}

int goSpace(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc) {
	int bottomH = getShapeBottomLoc(blockShape);
	int bottomArr[4] = { 0 };
	int i;
	for (i = 0; i < 4; i++) {
		bottomArr[i] = getEachBottomLoc(blockShape, i);
	}
	while (1) {
		if (curLoc->Y + bottomH == MAP_SIZE_H
			|| (bottomArr[1] != -1 && map[curLoc->Y + bottomArr[1] + 1][curLoc->X + 1] != EMPTY)
			|| (bottomArr[0] != -1 && map[curLoc->Y + bottomArr[0] + 1][curLoc->X + 0] != EMPTY)
			|| (bottomArr[3] != -1 && map[curLoc->Y + bottomArr[3] + 1][curLoc->X + 3] != EMPTY)
			|| (bottomArr[2] != -1 && map[curLoc->Y + bottomArr[2] + 1][curLoc->X + 2] != EMPTY)
			) {

			fixShape(map, blockShape, curLoc);

			Sleep(1000 / 8);
			return TRUE;
		}
		if (curLoc->Y + bottomH < MAP_SIZE_H) {
			removeShape(map, blockShape, curLoc);
			(curLoc->Y)++;
		}
	}

	return FALSE;
}

void deleteLine(MData map[MAP_SIZE_H][MAP_SIZE_W], int h) {
	int w;
	for (w = 0; w < MAP_SIZE_W; w++) {
		map[h][w] = EMPTY;
	}
}

void organizeLine(MData map[MAP_SIZE_H][MAP_SIZE_W], int h) {
	int w;
	while (h > 1) {
		for (w = 0; w < MAP_SIZE_W; w++) {
			map[h][w] = map[h - 1][w];
		}
		h--;
	}

}

void checkLine(MData map[MAP_SIZE_H][MAP_SIZE_W], Location curLoc, int* score, int* removeLine) {
	int h, w, full, count = 0;

	for (h = MAP_SIZE_H - 1; h >= (curLoc.Y - 1); h--) {
		full = 0;
		for (w = 0; w < MAP_SIZE_W; w++) {
			if (map[h][w] == EMPTY) {
				break;
			}
			else {
				full++;
			}
		}

		if (full == MAP_SIZE_W) {
			(*score) += 5;
			(*removeLine) += 1;
			deleteLine(map, h);
			organizeLine(map, h);
		}
	}

}

int GameOver(MData map[MAP_SIZE_H][MAP_SIZE_W], int score, int bestScore) {
	FILE* wfp;
	int w = 0;
	for (w = 0; w < MAP_SIZE_W; w++) {
		if (map[0][w] == BLOCK) {
			HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hand, 14);
			gotoxy(HALF_W - 7, HALF_H - 2);
			printf("====== Game Over ======");
			gotoxy(HALF_W - 6, HALF_H - 1);
			printf("Your Score : %4d\n", score);
			SetConsoleTextAttribute(hand, 7);
			gotoxy(1, MAP_SIZE_H + 3);

			if (score >= bestScore) {
				wfp = fopen("score.txt", "w");
				fprintf(wfp, "%d", score);
				fclose(wfp);
			}

			system("pause");
			return TRUE;
		}
	}

	return FALSE;
}

int GameStart(MData map[MAP_SIZE_H][MAP_SIZE_W]) {
	int key;
	int reachBottom = FALSE;
	int one = TRUE;
	int score = 0, bestScore = 0;
	int blockShape[4][4] = { 0 };
	int blockShapeSub[4][4] = { 0 };
	int stage = 1;
	int removeLine = 0;
	int i = 0;
	int s = 2;
	int r = 7;
	Location curLoc = { 2,2 };
	FILE* rfp;
	if ((rfp = fopen("score.txt", "r")) == NULL) {
		FILE* wfp;
		wfp = fopen("score.txt", "w");
		fprintf(wfp, "%d", 0);
		fclose(wfp);
	}
	fscanf(rfp, "%d", &bestScore);

	mapInit(map);
	drawWall(map);
	drawMap(map);

	locationInit(&curLoc);
	setBlock(blockShape, &r);
	startTime();
	setBlock(blockShapeSub, &r);
	drawSubShape(map, blockShapeSub);
	gotoxy(5, 0);
	printf("stage %d", stage);
	while (1) {

		if (reachBottom == TRUE) {
			if (GameOver(map, score, bestScore)) return EXIT;

			checkLine(map, curLoc, &score, &removeLine);
			checkLine(map, curLoc, &score, &removeLine);
			locationInit(&curLoc);
			copyBlock(blockShape, blockShapeSub);
			setBlock(blockShapeSub, &r);
			drawSubShape(map, blockShapeSub);
			reachBottom = FALSE;
		}

		if (removeLine >= 5) {
			//블록 수 조정
			if (r >= 10) {
				r = 10;
			}
			//블록 낙하속도 조정
			if (s >= 8) {
				s = 8;
			}

			stage++;

			if (stage % 3 == 0 && r < 10) {
				r++;
			}

			if (s < 8) {
				s++;
			}

			gotoxy(5, 0);
			printf("          ");
			Sleep(1000);
			gotoxy(5, 0);
			printf("stage %d", stage);
			mapInit(map);
			drawMap(map);
			removeLine = 0;
		}

		drawSubMap(bestScore, score);
		drawShape(map, blockShape, curLoc);
		drawMap(map);
		reachBottom = goDown(map, blockShape, &curLoc, &s);
		if (reachBottom == TRUE) continue;

		key = getKeyDown();
		if (key == 't' || key == 'T') {
			StartTetris();
			break;
		}
		if (key == 'p' || key == 'P') {
			system("pause"); system("cls");
			drawMap(map); drawWall(map);
		}
		if (key == SPACE) {
			goSpace(map, blockShape, &curLoc);
		}
		if (key == 224 || key == 0) {
			key = _getch();
			if (key == UP) {
				rotate(map, blockShape, &curLoc);
			}
			else if (key == LEFT) {
				goLeft(map, blockShape, &curLoc);
			}
			else if (key == RIGHT) {
				goRight(map, blockShape, &curLoc);
			}
		}
	}
	return EXIT;
}

//테트리스 게임 설명 함수
void explainTetris() {
	system("cls");
	textcolor(7);
	gotoxy(0, 0);
	int a = 0;
	while (1) {
		char key;
		key = getKeyDown();
		if (key == 't' || key == 'T') {
			system("cls");
			StartTetris();
			break;
		}
		if (a == 0) {
			printf("방향키 좌우 키를 이용하여 블록을 움직일 수 있습니다.\n");
			printf("방향키 위키를 누르면 블록이 시계방향으로 회전합니다.\n");
			printf("스페이스 키를 누르면 블록이 즉시 아래로 내려갑니다.\n");
			printf("5줄을 없앨 때마다 스테이지가 증가합니다. 스테이지가 증가할 때 이전에 쌓여있던 블록은 사라지고 새로 진행됩니다.\n");
			printf("스테이지가 늘어날 떄마다 블록이 떨어지는 속도가 증가합니다. 속도는 7스테이지 이후로는 증가하지 않습니다.\n");
			printf("3스테이지, 6스테이지, 9스테이지에 새로운 블록이 하나씩 추가됩니다.\n");
			printf("t키를 누르면 이전 화면으로 돌아갑니다.");
		}
		a++;
	}
}
