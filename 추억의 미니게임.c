#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

//n*n퍼즐, 테트리스 공용 상
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

//숫자야구 상수
#define RANKING_FILE "ranking.txt"
#define MAX_RANKING_ENTRIES 10

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

//게임선택화면 ui
void SelectGame() {
	int game = 1;
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

//숫자야구 메인ui
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
	textcolor(7);
	printf("3자리, 4자리, 5자리의 난이도를 정하여 게임을 시작할 수 있습니다.\n");
	printf("정답을 맞출 때마다 각각 5점, 7점, 10점을 획득하실 수 있습니다.\n");
	printf("점수는 계속 쌓이는 방식이며 얻은 점수로 상점에서 아이템을 구매할 수 있습니다.\n");
	printf("상점은 게임이 끝난 후 이용하실 수 있습니다.\n");
	printf("단, 게임을 그만둘 시 얻은 점수는 리셋됩니다.\n");
	printf("게임 종료 후 자신의 이름을 입력하면 랭킹에 등록됩니다.");
}
//숫자야구 함수 끝

//n*n퍼즐 메인 함수
void NPuzzle() {
	system("cls");
	textcolor(7);
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
		printf("      But game out(30초를 넘기셨습니다)\n");
		printf("            게임을 다시하겠습니까?\n\n");
		printf("              1.YES    2.NO\n");
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
	printf("■■■■■■■■■■■■■■■\n");
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
			printf("■■■■■■■■■■■■■■■\n");
		}
		else {
			printf("■■■■■■■■■■■■■■■\n");
		}
	}
	gotoxy(35, 5);
	printf("    ■■■■■\n");
	gotoxy(35, 6);
	printf("    ■ 4*4  ■\n");
	gotoxy(35, 7);
	printf("    ■■■■■\n");
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


	return 0;
}

void explainNPuzzle() {

}
//n*n퍼즐 함수 끝
