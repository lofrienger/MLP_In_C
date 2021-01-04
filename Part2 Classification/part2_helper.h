#ifndef PART2_HELPER
#define PART2_HELPER

// Get data from file and store in a 2-D array
void get_data(char *line, double **data, char *filename);
// Print 2-D array
void print_data(double **data, int row, int col);
// Get number of rows in file
int get_row(char *filename);
// Get number of columns in file
int get_col(char *filename);

#endif