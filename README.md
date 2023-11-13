#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void generateRandomNumber(int *number, int digitCount);
void getUserInput(int *guess, int digitCount);
void checkGuess(int *targetNumber, int *userGuess, int digitCount, int *strikes, int *balls);

int main() {
    int difficulty;
    int strikes, balls;
    int maxAttempts = 7; 

    printf("난이도를 선택하세요 (1: 3자리, 2: 4자리, 3: 5자리): ");
    scanf("%d", &difficulty);

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
            printf("올바른 난이도를 선택하세요.\n");
            return 1;
    }

    srand(time(NULL)); 

    int targetNumber[digitCount];
    int userGuess[digitCount];

    generateRandomNumber(targetNumber, digitCount);

    printf("=== 숫자야구 게임 시작 (난이도: %d) ===\n", digitCount);

    int attempts = 0;
    do {
        getUserInput(userGuess, digitCount);
        checkGuess(targetNumber, userGuess, digitCount, &strikes, &balls);

        printf("스트라이크: %d, 볼: %d\n", strikes, balls);

        attempts++;

    } while (strikes != digitCount && attempts < maxAttempts);

    if (strikes == digitCount) {
        printf("축하합니다! 정답을 맞추셨습니다.\n");
    } else {
        printf("게임 오버! 정답은 ");
        for (int i = 0; i < digitCount; ++i) {
            printf("%d", targetNumber[i]);
        }
        printf("입니다.\n");
    }

    return 0;
}


void generateRandomNumber(int *number, int digitCount) {
    for (int i = 0; i < digitCount; ++i) {
        number[i] = rand() % 10;
    }
}


void getUserInput(int *guess, int digitCount) {
    printf("%d자리 숫자를 입력하세요: ", digitCount);
    for (int i = 0; i < digitCount; ++i) {
        scanf("%1d", &guess[i]);
    }
}


void checkGuess(int *targetNumber, int *userGuess, int digitCount, int *strikes, int *balls) {
    *strikes = 0;
    *balls = 0;

    for (int i = 0; i < digitCount; ++i) {
        for (int j = 0; j < digitCount; ++j) {
            if (userGuess[i] == targetNumber[j]) {
                if (i == j) {
                    (*strikes)++;
                } else {
                    (*balls)++;
                }
            }
        }
    }
}
