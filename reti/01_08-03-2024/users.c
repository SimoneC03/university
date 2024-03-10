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
        strcat(final, ";");
        strcat(final, users[i].lastname);
        strcat(final, ";");
        char age[10];
        sprintf(age, "%d", users[i].age);
        strcat(final, age);
        strcat(final, ";");
        strcat(final, delimiter);
    }
    return final;
}

/**
 * @param users to the concatenated users string
 * @returns a pointer to the User array
*/
User **parseUsers(char *users) {
    // count users to allocate required space
    int n = 0;
    for(size_t i = 0; users[i] != '\0'; i++) {
        if(users[i] == '-' && users[i+1] == '-') n++;
    }
    // allocate final array to return
    User **users_arr = malloc(sizeof(User*) * n);
    int user_index = 0; // keep track of insert users
    char *temp = malloc(sizeof(User)); // save the current parsed user string
    int temp_i = 0; 
    for(size_t i = 0; users[i] != '\0'; i++) {
        if(users[i] == '-' && users[i+1] == '-') {
            // insert user inside final array
            char *name = malloc(50);
            char *lastname = malloc(50);
            short int *age;
            sscanf(temp, "%[a-zA-Z0-9];%[a-zA-Z0-9];%hd;", name, lastname, age);
            User *u = malloc(sizeof(User));
            strcpy(u->name, name);
            strcpy(u->lastname, lastname);
            u->age = *age;
            users_arr[user_index] = u;
            user_index++;
            temp_i = 0;
            i++;
        } else {
            temp[temp_i] = users[i];
            temp_i++;
        }
    }
    return users_arr;
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
    printf("\nConcatenated users string is: \n%s\n\nParsing users from string...\n", concatenated);
    // build `users2` array from the concatenated string
    User **users2 = parseUsers(concatenated);
    // print all the parsed users
    for(int i = 0; i < n_users; i++) {
        printf("\nUser %d\nName: %s\n", i+1, users2[i]->name);
        printf("Lastname: %s\n", users2[i]->lastname);
        printf("Age: %hd\n", users2[i]->age);
    }
    return 0;
}