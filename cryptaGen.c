/*
 * CryptaGen - A secure password generator written in C.
 *
 * This program generates a secure password by combining random characters,
 * including uppercase and lowercase letters, digits, and special symbols.
 * It utilizes the standard C library functions such as rand() to ensure
 * randomness and srand(time(NULL)) to seed the generator.
 *
 * Features:
 * - Generates strong, random passwords.
 * - Supports customizable password length.
 * - Uses a mix of characters for enhanced security
 * - Simple and efficient command-line interface.
 * - Automatically stores generated passwords in a .txt file.
 *
 * Author: Luca "Lucacux" Lombardo
 * Date: 04-02-2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARR 100 // Lower this value if NULL pointer is common in main func.
#define TRUE 1
#define FALSE 0
#define DEFAULT 4
// Function prototypes are defined.
int passwordLength();
void storePassword(char password[]);
void seePassword(char password[]);
void passwordLogic(int length, char password[]);
void cleanScreen();
void menu();

int main() {
    char* dynamicArray = (char*) malloc(sizeof(char) * MAX_ARR);
    if (dynamicArray != NULL) {
        menu(dynamicArray);
        free(dynamicArray);
    } else {
        printf("Failed to assign memory to the program\n");
    }
    return 0;
}

int passwordLength() {
    int length;
    printf("Please enter the length of the password to generate\n");
    scanf("%d", &length);
    getchar(); // Cleans buffer to prevent errors.
    return length;
}
// Functions are defined.
void passwordLogic(int length, char password[]) {
    int val;
    srand(time(NULL));

    for (int i = 0; i < length; i++) {
        password[i] = (rand() % (126 - 33 + 1)) + 33; // Generates ASCII characters from 33 to 126.
    }

    password[length] = '\0';
    printf("Your new password is:\n", password);
    printf("------------------------------------\n");
    printf("%s\n", password);
    printf("------------------------------------\n");
    printf("Try another password?\n");
    printf("1. Yes, 0. Keep actual password\n");
    scanf("%d", &val);
    getchar();
    system("clear");
    if (val != TRUE) {
        storePassword(password);
    }

    return;
}

void storePassword(char password[]) {
    FILE *file = fopen("passwords.txt", "a");

    if (file != NULL) {
        fprintf(file, "Password: %s\n", password);
        printf("Success! : Your password was stored at 'passwords.txt'\n.");
        fclose(file);
    } else {
        printf("Failed to store your password, try again later.\n");
    }

    return;
}

void seePassword(char password[]) {
  FILE *file = fopen("passwords.txt", "r");

  if (file != NULL) {

  while (fscanf(file,"Password: %99s", password ) == TRUE) {
      printf("Stored password:\n");
      printf("%s\n", password);
  }
      fclose(file);
  } else {
  printf("Failed to read your stored password, try again later\n");
  }

  return;
}

void cleanScreen() {
  system("clear");
  return;
}
void menu(char password[]) {
    int option;

    do {
        printf("----------------------------------------------------------------\n");
        printf("Welcome to CryptaGen: a strong password generator written in C!\n");
        printf("1. Generate password\n");
        printf("2. See stored passwords\n");
        printf("3. Clean screen\n");
        printf("4. Exit program\n");
        printf("----------------------------------------------------------------\n");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                int ret_length = passwordLength();
                passwordLogic(ret_length, password);
                break;
            case 2:
                seePassword(password);
                break;
            case 3:
                cleanScreen();
                break;
            case 4:
                printf("Exiting CryptaGen... Stay secure !\n");
                break;
        }

    } while (option != DEFAULT);

    return;
}
