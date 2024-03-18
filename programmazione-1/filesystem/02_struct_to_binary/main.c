#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USER_NAME_LENGTH 100

typedef struct User {
    int id;
    char name[200];
} User;

/* Write a User structure inside a random access file */
bool writeUserToFile(const char *filename, User *user, long position) {
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        perror("Error opening file");
        return false;
    }
    // move the file pointer to the desired position
    if (fseek(file, position * sizeof(User), SEEK_SET) != 0) {
        perror("Error seeking in file");
        return false;
    }
    // write the user structure to the file
    if(fwrite(user, sizeof(User), 1, file) == 0) return false;
    fclose(file);
    return true;
}

/* Read a User structure inside a random access file at a certain `position` and return
 * a pointer to the allocated struct */
User *readUserFromFile(const char *filename, long position) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    // move the file pointer to the desired position
    if (fseek(file, position * sizeof(User), SEEK_SET) != 0) {
        perror("Error seeking in file");
        exit(EXIT_FAILURE);
    }
    User *user = malloc(sizeof(User));
    // write the user structure to the file
    fread(user, sizeof(User), 1, file);
    fclose(file);
    return user;
}

int main() {
    const char *filename = "users.dat";
    User *user1 = malloc(sizeof(User));
    user1->id = 123;
    strcpy(user1->name, "Mario1 Rossi1");

    User *user2 = malloc(sizeof(User));
    user2->id = 1234;
    strcpy(user2->name, "Mario2 Rossi2");

    User *user3 = malloc(sizeof(User));
    user3->id = 12345;
    strcpy(user3->name, "Mario3 Rossi3");
    
    writeUserToFile(filename, user1, 0);
    writeUserToFile(filename, user2, 1);
    writeUserToFile(filename, user3, 2);
    // free allocated memory
    free(user1);
    free(user2);
    free(user3);

    int uindex = 0;
    printf("Which user do you want to show? (0-2)\n");
    scanf("%d", &uindex);
    User *res = readUserFromFile("users.dat", uindex);
    printf("User id: %d\n", res->id);
    printf("User name: %s\n", res->name);

    free(res);
    return 0;
}