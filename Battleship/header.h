#define HEADER_H

#include <stdio.h>
#include <stdlib.h>



#define ROWS 10
#define COLS 10

typedef struct stats
{
	int total_shots;
	int hits;
	int misses;
	double hits_misses_ratio;
} Stats;

void init_game_board (char board[ROWS][COLS], int num_rows, int num_cols);
void print_game_board (char board[ROWS][COLS], int num_rows, int num_cols);
int generate_direction (void);
void generate_starting_pt (int direction, int ship_length, int *row, int *col);
void place_ship (char board[ROWS][COLS], int row, int col, int direction, int ship_length, char ship_symbol);
Stats output_stats(char board[ROWS][COLS], int num_rows, int num_cols);
int welcome (void);
int check_point(char board[ROWS][COLS], int row, int col,int direction, int ship_length,char ship_symbol);
int random_ship_placement(char board[ROWS][COLS], int row, int col, int direction, int ship_length, char ship_symbol);
void rand_target (int *target_row, int *target_col);
void manually_place_ships(char game_board[10][10]);
int shot_check(char game_board[ROWS][COLS], int target_row, int target_col);
void get_target (int *target_row, int *target_col);
int print_menu (void);
void update_board(int hit_or_miss, char *target);
int who_goes_first(int start);
int shot_check(char board[ROWS][COLS], int target_row, int target_col);
int search_ships(char game_board[10][10], int num_rows, int num_cols, char ship);
