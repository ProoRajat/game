#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void displayMenu(int* difficulty) {
    int choice = 0;
    
    while (1) {
        system("cls");
        printf("\n");
        printf("      ===== DODGE GAME =====\n\n");
        printf("        Select Difficulty:\n\n");
        printf("  %s 1. EASY (Slow obstacles)\n", choice == 0 ? ">" : " ");
        printf("  %s 2. MEDIUM (Normal speed)\n", choice == 1 ? ">" : " ");
        printf("  %s 3. HARD (Fast obstacles)\n\n", choice == 2 ? ">" : " ");
        printf("  Use UP/DOWN arrows and press ENTER\n");
        
        if (_kbhit()) {
            char ch = getch();
            
            if (ch == 72 && choice > 0)           // UP arrow
                choice--;
            else if (ch == 80 && choice < 2)      // DOWN arrow
                choice++;
            else if (ch == 13) {                  // ENTER
                *difficulty = choice;
                return;
            }
        }
        
        Sleep(100);
    }
}

int main() {
    srand(time(0));

    int difficulty = 0;          // 0=easy, 1=medium, 2=hard
    int delayTime[] = {100, 70, 40};  // speeds for each difficulty
    int score = 0;
    int lives = 3;
    int x = 1;                   // player position (0 to 2)
    int step = 0;                // obstacle vertical movement
    int obstaclePos = rand() % 3; // 0,1,2 lane

    // Show menu
    displayMenu(&difficulty);

    while (1) {

        // ---- INPUT ----
        if (_kbhit()) {
            char ch = getch();

            if (ch == 75 && x > 0)        // LEFT arrow
                x--;

            if (ch == 77 && x < 2)        // RIGHT arrow
                x++;
        }

        // ---- DRAW ----
        system("cls");
        printf("|--- --- ---|\n");

        for (int i = 0; i < 10; i++) {
            if (i == step) {

                if (obstaclePos == 0)
                    printf("| %c         |\n", 79);

                else if (obstaclePos == 1)
                    printf("|     %c     |\n", 79);

                else if (obstaclePos == 2)
                    printf("|        %c  |\n", 79);

            } else {
                printf("|           |\n");
            }
        }

        // ---- PLAYER ----
        if (x == 0)
            printf("| %c         |\n", 64);
        else if (x == 1)
            printf("|     %c     |\n", 64);
        else if (x == 2)
            printf("|        %c  |\n", 64);

        // ---- UI ----
        printf("\nScore: %d  |  Lives: %d  |  Difficulty: ", score, lives);
        printf(difficulty == 0 ? "EASY\n" : (difficulty == 1 ? "MEDIUM\n" : "HARD\n"));

        // ---- COLLISION ----
        if (step == 10 && x == obstaclePos) {
            lives--;
            
            if (lives <= 0) {
                system("cls");
                printf("\n========== GAME OVER! ==========\n");
                printf("Final Score: %d\n", score);
                printf("=================================\n\n");
                break;
            }
            
            // Reset obstacle on collision
            step = 0;
            obstaclePos = rand() % 3;
        }

        // ---- SCORING ----
        if (step == 10 && x != obstaclePos) {
            score += (difficulty + 1) * 10;  // easy=10, medium=20, hard=30 per dodge
        }

        Sleep(delayTime[difficulty]);

        // Move obstacle down
        step++;

        // Reset when reaches bottom
        if (step > 10) {
            step = 0;
            obstaclePos = rand() % 3;
        }
    }

    return 0;
}
