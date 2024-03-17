#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ROW_LENGTH 100

/**
 * @param filename path to the file to update
 * @param row_index index of the line to replace
 * @param *s pointer to the new string to replace with
 * @returns true if the line has been replaced 
*/
bool replaceLine(char *filename, int row_index, char *s) {
    char *tempfname = malloc(strlen(filename+strlen("temp__"))+1);
    strcat(tempfname, "temp__");
    strcat(tempfname, filename);

    FILE *f = fopen(filename, "r+"); 
    if(f == NULL) return false;

    FILE *tempf = fopen(tempfname, "w");
    if(tempf == NULL) return false;

    int row_i = 0;
    char *row = malloc(MAX_ROW_LENGTH);
    int rowN;
    bool replaced = false;
    while(!feof(f)) {
        fscanf(f, "%d %s", &rowN, row);
        if(row_i == row_index) {
            // check if is the last row before enter new line
            if(feof(f)) fprintf(tempf, "%d %s", rowN, s);
            else fprintf(tempf, "%d %s\n", rowN, s);
            replaced = true;
        } else {
            // check if is the last row before enter new line
            if(feof(f)) fprintf(tempf, "%d %s", rowN, row);
            else fprintf(tempf, "%d %s\n", rowN, row);
        }
        row_i++;
    }
    fclose(f);
    fclose(tempf);
    remove(filename);
    rename(tempfname, filename);
    return replaced;
}

int main() {
    int toReplace = -1;
    char newRow[MAX_ROW_LENGTH];
    printf("Insert the index of the line you want to replace: ");
    scanf("%d", &toReplace);
    printf("Insert the string to replace with (max 100). ");
    scanf("%s", newRow);
    fflush(stdin);
    if (replaceLine("data.txt", toReplace, newRow) ) {
        printf("Row %d replaced successfully\n", toReplace);
    } else {
        printf("An error has occurred while replacing row %d\n", toReplace);
    }
    return 0;
}