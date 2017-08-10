#include "header.h"

void init_game_board (char board[ROWS][COLS], int num_rows, int num_cols)
{
	int row_index = 0, col_index = 0;

	for (row_index = 0; row_index < num_rows; row_index++)
	{
		for (col_index = 0; col_index < num_cols; col_index++)
		{
			board[row_index][col_index] = '~';
		}
	}
}

void print_game_board (char board[ROWS][COLS], int num_rows, int num_cols)
{
	int row_index = 0, col_index = 0;

	printf ("%3d%2d%2d%2d%2d%2d%2d%2d%2d%2d\n",
		    0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

	for (row_index = 0; row_index < num_rows;
		 row_index++)
	{
		printf ("%d ", row_index);
		for (col_index = 0; col_index < num_cols;
		     col_index++)
		{
			//board[row_index][col_index] = '~';
			printf ("%c ", board[row_index][col_index]);
		}

		putchar ('\n');
	}
}

int generate_direction (void)
{
	int direction = 0;

	direction = rand () % 2;
	
	return direction;
}

void generate_starting_pt (int direction, int ship_length, int *row, int *col)
{
	int row_start = 0, col_start = 0;

	if (direction == 0) // horizontal
	{
		row_start = rand () % 10;
		col_start = rand () % (10 - ship_length + 1);
	}
	else // vertical
	{
		row_start = rand () % (10 - ship_length + 1);
		col_start = rand () % 10;

	}

	*row = row_start;
	*col = col_start;
}

/*int random_ship_placement(char board[ROWS][COLS], int *row, int *col, int *direction, int ship_lengths, char ship_symbols)
{
	int index = 0, check = 0;
	

	for (index = 0; index < ship_lengths; index++)
	{

		*direction = generate_direction();
		generate_starting_pt(*direction, ship_lengths[index], row, col);
		check = check_point(board, row, col, direction, ship_lengths[index], ship_symbols[index]);
		if (check == 0)
			place_ship(board, row, col, direction, ship_lengths[index], ship_symbols[index]);
		else
			index--;
	}







}*/
int check_point(char board[ROWS][COLS], int row, int col, int direction, int ship_length,char ship_symbol)
{
	int index = 0, check = 0, temp = 0;

	for (index = 0; index < ship_length; index++)
	{
			
		if (!direction) // horizontal
			temp = board[row][col + index];
		else
			temp = board[row + index][col];
		if(temp != '~')
			return 1;
	}
	return 0;
}
	

void place_ship (char board[ROWS][COLS], int row, int col, int direction, int ship_length, char ship_symbol)
{
	int index = 0;

	for (index = 0; index < ship_length; index++)
	{
			
		if (!direction) // horizontal
		{
			board[row][col + index] = ship_symbol;
		}
		else
		{
			board[row + index][col] = ship_symbol;
		}
	}
}

Stats output_stats(char board[ROWS][COLS], int num_rows, int num_cols)
{	
	int row_index = 0, col_index = 0;
	int hit = 0, miss = 0, shots = 0;
	double ratio = 0.0;

	Stats temp;

	for (row_index = 0; row_index < num_rows; row_index++)
	{
		for (col_index = 0; col_index < num_cols; col_index++)
		{
			if(board[row_index][col_index] == '*')
			{
				hit = hit++;
			}
			if(board[row_index][col_index] = 'm')
			{
				miss = miss++;
			}
		}
	}
	shots = hit + miss;
	ratio = hit / miss;
	temp.hits = hit;
	temp.misses = miss;
	temp.total_shots = shots;
	temp.hits_misses_ratio = ratio;

	return temp;

	//still include printing file and stuctures if wanted

}

int welcome (void)
{
	int choice = 0, temp = 0;

	printf("*****************************************\n");
	printf("***************BATTLESHIP!!!*************\n");
	printf("*****************************************\n");
	printf("1. To start playing please press one.\n");
	printf("2. Or to quit please press two.\n");
	
	scanf("%d", &choice);

	switch(choice)
	{
		case 1:
			temp = 1;
			break;
		case 2:
			exit(1);
			break;
		default:
			printf("Not a valid response...");
			system("pause");
			break;
	}
	return temp;
}


void rand_target (int *target_row, int *target_col) //computer's "AI" shooting
{
	*target_row = rand() % 9 + 1;
	*target_col = rand() % 9 + 1;


}

void manually_place_ships(char board[ROWS][COLS]) 
{
    int size = 0, row_index = 0, col_index = 0, count = 0, ship = 0;
	char letter = '\0';
   while(ship < 5)
   {
	if (ship == 0)
    {
		size = 5;
		letter = 'c';
		printf("Please select where to place the Carrier by entering five sets of coordinates.\n");
    }
    if (ship == 1)
    {
		size = 4;
		letter = 'b';
		printf("Please select where to place the Battleship by entering four sets of coordinates.\n");
    }
    if (ship == 2 || ship == 3)
    {
		size = 3;
		if (ship == 2)
		{
			letter = 'r';
			printf("Please select where to place the Cruiser by entering three sets of coordinates.\n");
		}
		else
		{
			letter = 's';
			printf("Please select where to place the Submarine by entering three sets of coordinates.\n");
		}
    }
    if (ship == 4)
    {
		size = 2;
		letter = 'd';
		printf("Please select where to place Destroyer by entering two sets of coordinates.\n");
    }
	count = 0;
		while (count < size)
		{
			printf("Enter a set of coordinates: \n");
			printf("Row, Column: ");
			scanf("%d%d", &row_index, &col_index);
			//printf("Column: ");
			//scanf("%d", &col_index);
			if (board[row_index][col_index] == '~')
			{
				board[row_index][col_index] = letter;
				count++;
			
			}
			else
			{
				printf("Error illegal ship placement. Please enter another set of coordinates.");
			}
		}
		ship++;
		system("cls");
		print_game_board(board, ROWS, COLS);
	}
   
}
int shot_check(char board[ROWS][COLS], int target_row, int target_col)
{
	
	
    if (board[target_row][target_col] == '~')
    {
		printf("\nMiss...\n\n");
		return 0;
    }
    else
    {
		printf("\nHit!\n\n");
		return 1;
    }
}

void get_target (int *target_row, int *target_col)
{
    printf("Please enter a target coordinate: \n");
    printf("Row: ");
    scanf("%d", target_row);
    printf("Column: ");
    scanf("%d", target_col);
}

int print_menu (void)
{
    int choice = 0;
    
    printf("*************************\n");
    printf("****Let's Start This!****\n");
    printf("*************************\n");
    printf("1. To have them randomly placed press one.\n2. Or manually place your ships press two.\n");
    
    scanf("%d", &choice);
    
    return choice;
}

void update_board(int hit_or_miss, char board[ROWS][COLS], int target_row, int target_col)
{
    if (hit_or_miss == 1)
    {
	    board[target_row][target_col] = '*';
    }
    else
    {
		board[target_row][target_col] = 'm';
    }
}

int select_who_starts_first(int start)
{
    int random = 0;
    random = rand() % 2 + 1;
    switch (random)
    {
    case 1:
    start = 1;
    break;
    case 2:
    start = 2;
    break;
    default:
    printf("Error: first turn player could not be randomly selected.");
    break;
    }
}

int search_ships(char game_board[10][10], int num_rows, int num_cols, char ship)
{
    int row = 0, col = 0, status = 0;
	
		for (row = 0; row < num_rows; row++)
		{
			for (col = 0; col < num_cols; col++)
			{
				if (game_board[row][col] == ship)
				status += 1;
			}
		}
		if (status == 0 && ship == 'c')
			printf("Carrier is sank!\n");
		if (status == 0 && ship == 'b')
			printf("Battleship is sank!\n");
		if (status == 0 && ship == 'r')
			printf("Cruiser is sank!\n");
		if (status == 0 && ship == 's')
			printf("Submarine is sank!\n");
		if (status == 0 && ship == 'd')
			printf("Destroyer is sank!\n");
    return status;
}