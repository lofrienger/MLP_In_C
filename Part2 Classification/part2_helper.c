#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "part2_helper.h"

void get_data(char *line, double **data, char *filename)
{
    FILE *stream = fopen(filename, "r");
    int i = 0;
    while (fgets(line, 1024, stream)) //read line by line
    {
        int j = 0;
        char *tok;
        char *tmp = strdup(line);
        for (tok = strtok(line, ","); tok && *tok; j++, tok = strtok(NULL, ",\n"))
        {
            data[i][j] = atof(tok); //convert to double
        }
        i++;
        free(tmp);
    }
    fclose(stream);
}

void print_data(double **data, int row, int col)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%f\t", data[i][j]);
        }
        printf("\n");
    }
}

int get_row(char *filename)
{
    char line[1024];
    int i = 0;
    FILE *stream = fopen(filename, "r");
    while (fgets(line, 1024, stream))
    {
        i++;
    }
    fclose(stream);
    return i;
}

int get_col(char *filename)
{
    char line[1024];
    int i = 0;
    FILE *stream = fopen(filename, "r");
    fgets(line, 1024, stream);
    char *token = strtok(line, ",");
    while (token)
    {
        token = strtok(NULL, ",");
        i++;
    }
    fclose(stream);
    return i;
}
