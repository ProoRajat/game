#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void ShowGame(char arr[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            printf("%c ", arr[i][j]);
        printf("\n");
    }
}

bool checkDraw(char arr[][3])
{
    bool draw = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arr[i][j] == '-')
                draw = false;
        }
    }
    if (draw)
        return true;
    return false;
}

int CheckGame(char arr[][3])
{
    // 0 - draw
    // 1 - user win
    // 2 - comp win
    // 3 - continue playing

    if (checkDraw(arr))
        return 0;

    char inputs[2] = {'X', 'O'};
    for (int i = 0; i < 2; i++)
    {
        char winnerChecker = inputs[i];
        for (int j = 0; j < 3; j++)
        {
            int counter = 0;
            for (int k = 0; k < 3; k++)
            {
                if (arr[j][k] != winnerChecker)
                    break;
                counter++;
            }
            if (counter == 3)
                return (winnerChecker == 'X') ? 1 : 2;
        }
    }

    for (int i = 0; i < 2; i++)
    {
        char winnerChecker = inputs[i];
        for (int j = 0; j < 3; j++)
        {
            int counter = 0;
            for (int k = 0; k < 3; k++)
            {
                if (arr[k][j] != winnerChecker)
                    break;
                counter++;
            }
            if (counter == 3)
                return (winnerChecker == 'X') ? 1 : 2;
        }
    }

    for (int i = 0; i < 2; i++)
    {
        char winnerChecker = inputs[i];
        bool flag = true;
        for (int j = 0; j < 3; j++)
        {
            if (arr[j][j] != winnerChecker)
                flag = false;
        }
        if (flag)
            return (winnerChecker == 'X') ? 1 : 2;
    }

    for (int i = 0; i < 2; i++)
    {
        char winnerChecker = inputs[i];
        bool flag = true;
        for (int j = 0; j < 3; j++)
        {
            if (arr[j][2-j] != winnerChecker)
                flag = false;
        }
        if (flag)
            return (winnerChecker == 'X') ? 1 : 2;
    }

    return 3;
}

int main(void)
{
    char Game[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            Game[i][j] = '-';
    }

    srand((unsigned)time(NULL));
    int x, y;
    bool gameEnd = false;

    printf("----Tick Tack Toe----\nX - User\nO - Computer\nEnter your input in the form x,y\n");

    printf("Indexes:\n(1,1) (1,2) (1,3)\n(2,1) (2,2) (2,3)\n(3,1) (3,2) (3,3)\n\n");
    ShowGame(Game);

    while (!gameEnd)
    {
        // User input validation loop
        while (1)
        {
            printf("Enter the coordinate: ");
            scanf("%d,%d", &x, &y);

            // Check bounds
            if (x < 1 || x > 3 || y < 1 || y > 3)
            {
                printf("Invalid input! Coordinates must be between 1 and 3.\n");
                continue;
            }

            // Convert to 0-indexed
            x--;
            y--;

            // Check if cell is already occupied
            if (Game[x][y] != '-')
            {
                printf("Cell already occupied! Try again.\n");
                continue;
            }

            Game[x][y] = 'X';
            break;
        }

        // Computer move
        while (1)
        {
            if (checkDraw(Game))
                break;
            x = rand() % 3;
            y = rand() % 3;
            if (Game[x][y] == '-')
            {
                Game[x][y] = 'O';
                break;
            }
        }

        ShowGame(Game);

        if (CheckGame(Game) == 0)
        {
            printf("Game is DRAW\n");
            break;
        }
        else if (CheckGame(Game) == 1)
        {
            printf("You Won\n");
            break;
        }
        else if (CheckGame(Game) == 2)
        {
            printf("Computer Won\n");
            break;
        }
        else
            continue;
    }

    return 0;
}