#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRIES 6

void displayWord(char *word, int *guessed) {
    for (int i = 0; i < strlen(word); i++) {
        if (guessed[i]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int isWordGuessed(char *word, int *guessed) {
    for (int i = 0; i < strlen(word); i++) {
        if (!guessed[i]) {
            return 0;
        }
    }
    return 1;
}

int checkGuess(char letter, char *word, int *guessed) {
    int correct = 0;
    for (int i = 0; i < strlen(word); i++) {
        if (word[i] == letter && !guessed[i]) {
            guessed[i] = 1;
            correct = 1;
        }
    }
    return correct;
}

void drawHangman(int attempts) {
    switch (attempts) {
        case 0:
            printf("\n\n\n\n\n\n");
            break;
        case 1:
            printf("\n\n\n\n\n___|___\n");
            break;
        case 2:
            printf("\n   |\n   |\n   |\n   |\n___|___\n");
            break;
        case 3:
            printf("   _______\n   |\n   |\n   |\n   |\n___|___\n");
            break;
        case 4:
            printf("   _______\n   |     |\n   |\n   |\n   |\n___|___\n");
            break;
        case 5:
            printf("   _______\n   |     |\n   |     O\n   |\n   |\n___|___\n");
            break;
        case 6:
            printf("   _______\n   |     |\n   |     O\n   |    /|\\\n   |    / \\\n___|___\n");
            break;
    }
}

int main() {
    char *words[] = {"programming", "computer", "language", "developer", "algorithm"};
    int numWords = sizeof(words) / sizeof(words[0]);
    
    srand(time(NULL));
    char *word = words[rand() % numWords];
    int length = strlen(word);

    int guessed[length];
    for (int i = 0; i < length; i++) {
        guessed[i] = 0;
    }

    int attempts = 0;
    char guess;
    int correctGuess;

    printf("==== WELCOME TO HANGMAN ====\n");
    printf("Guess the word letter by letter.\n");
    printf("You have %d attempts.\n\n", MAX_TRIES);

    while (attempts < MAX_TRIES) {
        drawHangman(attempts);
        displayWord(word, guessed);

        printf("\nEnter a letter: ");
        scanf(" %c", &guess);

        correctGuess = checkGuess(guess, word, guessed);

        if (!correctGuess) {
            printf("Incorrect guess!\n");
            attempts++;
        } else {
            printf("Correct guess!\n");
        }

        if (isWordGuessed(word, guessed)) {
            printf("\nYou guessed the word: %s!\n", word);
            printf("🎉 Congratulations! You win! 🎉\n");
            break;
        }
    }

    if (attempts == MAX_TRIES) {
        drawHangman(attempts);
        printf("\nGame Over! The word was: %s\n", word);
    }

    return 0;
}
