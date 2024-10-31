#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int throw_hands(int choice, int *winning_moves, int round)
{
    printf("Your move: (0: Rock, 1: Paper, 2: Scissors)\n");
    int u;
    scanf("%d", &u);
    
    if ((u < 0 || u > 2))
    {
        puts("Invalid move! No cheating >:(.");
        exit(0);
    }
    
    if (((u == 0 && choice == 1) || ((u == 1 && choice == 2) || ((u == 2 && choice == 0) || choice == u))))
    {
        int winning_move;
        if (choice == 0) {
            winning_move = 1;
        } else if (choice == 1) {
            winning_move = 2;
        } else {
            winning_move = 0;
        }
        printf("Womp womp, I win!\n");
        printf("This is the move I'd have made: %d\n", winning_move);
        winning_moves[round] = winning_move;
    } else {
        winning_moves[round] = u;
    }
    
}

void make_moves(char* in, int* out)
{
    int32_t delta = 0;
    
    for (int i = 0; i <= 9; i += 1)
    {
        in[i] += delta;
        char rax_12 = in[i];
        char rdx_6 = ((rax_12 >> 7) >> 6);
        out[i] = (((rax_12 + rdx_6) & 3) - rdx_6);
        delta = ((in[i] + 0x1ca3) % 0x15);
    }
}

int32_t main()
{
    void* fsbase;
    // int64_t rax = *(fsbase + 0x28);
    char flag[0x64];
    puts("Welcome to Rock-Paper-Scissors! …");
    printf("Enter your name: ");
    char name[0x64];
    int32_t result;
    int moves[10];
    int winning_moves[10];

    
    if (fgets(&name, 0x64, stdin) == 0)
    {
        puts("Error reading name!");
        result = 1;
    }
    else
    {
        uint64_t rax_3 = strlen(&name);
        
        if ((rax_3 != 0 && name[(rax_3 - 1)] == 0xa))
            name[(rax_3 - 1)] = 0;
        
        if (rax_3 <= 0xa)
        {
            puts("That can't be right, enter a lon…");
            exit(0);
            /* no return */
        }
        
        printf("Hello, %s! Let's start the game.… \n", &name);
        int moves[0xa];
        make_moves(&name, &moves);
        printf("playing game\n");
        
        for (int i = 0; i < 10; i += 1) { 
            printf("Round %d of 10 rounds \n", i + 1);
            throw_hands(moves[i], winning_moves, i);
        }

        printf("\nGame Over! Here's a summary of each round:\n");
        for (int i = 0; i < 10; i++) {
            if (winning_moves[i] == moves[i]) {
                printf("Round %d: You won with move %d\n", i + 1, winning_moves[i]);
            } else {
                printf("Round %d: To win (with the same name), play %d\n", i + 1, winning_moves[i]);
            }
        }
    }
    return 0;
}
