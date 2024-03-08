#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Struct representing a user
*/
typedef struct User {
    char name[50];
    char lastname[50];
    short int age;
} User;


/**
 * @param users[] User array to concatenate
 * @param n number of users 
 * @returns concatenated users string
*/
char *concatenate(User users[], const int n)  {
    char *delimiter = "--";
    // allocate required space for the final string: to serialize the struct, 
    // to delimit every users and every user field (+3)
    char *final = malloc((sizeof(User)+strlen(delimiter)+3)*n);
    if(final == NULL) exit(137);
    for(int i = 0; i < n; i++) {
        strcat(final, users[i].name);
        final = strcat(final, ";");
        final = strcat(final, users[i].lastname);
        final = strcat(final, ";");
        char age[10];
        sprintf(age, "%d", users[i].age);
        final = strcat(final, age);
        final = strcat(final, ";");
        final = strcat(final, delimiter);
    }
    return final;
}

/**
 * @param users to the concatenated users string
 * @param n number of users 
 * @returns a pointer to the User array
*/
User *parseUsers(char *users, const int n) {
    
}

int main(int argc, char **argv) {
    // Users to insert
    const int n_users = 2;

    User users[n_users];
    // Insert users fields
    for(int i = 0; i < n_users; i++) {
        printf("User %d\nName: ", i+1);
        scanf("%s", users[i].name);
        printf("Lastname: ");
        scanf("%s", users[i].lastname);
        printf("Age: ");
        scanf("%hd", &users[i].age);
    }
    printf("Users insert. Concatenating...\n");
    // concatenate all the users
    char *concatenated = concatenate(users, n_users);
    printf("Concatenated users string is: \n%s\nParsing users from string...\n", concatenated);
    // build `users2` array from the concatenated string
    // User *users2 = parseUsers(concatenated, n_users);
    // // print all the parsed users
    // for(int i = 0; i < n_users; i++) {
    //     printf("User %d\nName: %s", i+1, users[i].name);
    //     printf("Lastname: %s", users[i].lastname);
    //     printf("Age: %s", users[i].age);
    // }
    return 0;
}