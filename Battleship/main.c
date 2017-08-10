/*
 * Programmer: Kevin Rogers
 * Class: Cpt S 121, Spring 2011; PA 6
 * Programming Assignment: Computations PA5 (pt1)
 * Date: March 28, 2012 
 *
 * Description:  This is a program that simulate the game Battleship!*/



#include "header.h"

int main (void)
{
	FILE *outfile;
	char game_board1[ROWS][COLS] = {{'~', '~'}, {'~'}};
	char game_board2[10][10] = {{'~', '~'}, {'~'}};
	char game_board_shots[ROWS][COLS] = {{'~', '~'}, {'~'}};

	int ship_lengths[5] = {5, 4, 3, 3, 2};
	char ship_symbols[5] = {'c', 'b', 's', 'r', 'd'};

	int direction = 0, ship_length = 5,
		row = 0, col = 0, index = 0, check = 0,
		choice = 0, choice1 = 0, target_row = 0, target_col = 0,
		hit_miss = 0, number_of_ships1 = 0, number_of_ships2 = 0,
		starts = 0, turn = 0, carrier1 = 0, battleship1 = 0, cruiser1 = 0,
		submarine1 = 0, destroyer1 = 0, carrier2 = 0, battleship2 = 0,
		cruiser2 = 0, submarine2 = 0, destroyer2 = 0;
		
	char ship = '\0';

	Stats player1 = {0, 0, 0, 0.0}, 
		  computer = {0, 0, 0, 0.0};

	srand ((unsigned) time (NULL));

	outfile = fopen("battleship.log", "w");
	
	choice = welcome();  //welcome prompt w/ play and exit options
	
	switch(choice)
	{
	case 1:
		choice = print_menu();
		break;
	case 2:
		exit(1);
		break;
	}

	init_game_board (game_board1, ROWS, COLS);
	init_game_board (game_board2, ROWS, COLS);
	init_game_board (game_board_shots, ROWS, COLS);
	//print_game_board (game_board, ROWS, COLS);
	
	
	
	switch(choice)
	{
	case 1:
//start of case 1
	for (index = 0; index < 5; index++)
	{
		direction = generate_direction ();
		generate_starting_pt (direction, ship_lengths[index],
		                  &row, &col);
		check = check_point(game_board1, row, col, direction, ship_length, ship_symbols);
	
	if (check == 0)
		place_ship (game_board1, row, col, direction,
		        ship_lengths[index], ship_symbols[index]);
	else
		index--;
	}
		/*place_ship (game_board, row, col, direction,
		        ship_lengths[index], ship_symbols[index]);*/

		print_game_board (game_board1, ROWS, COLS);
		break;
//end of case 1
	case 2:
		 manually_place_ships(game_board1);
		break;
	}


		for (index = 0; index < 5; index++)
	{
		direction = generate_direction ();
		generate_starting_pt (direction, ship_lengths[index],
		                  &row, &col);
		check = check_point(game_board2, row, col, direction, ship_length, ship_symbols);
	
	if (check == 0)
		place_ship (game_board2, row, col, direction,
		        ship_lengths[index], ship_symbols[index]);
	else
		index--;
	}
		/*place_ship (game_board, row, col, direction,
		        ship_lengths[index], ship_symbols[index]);*/

		print_game_board (game_board2, ROWS, COLS);
		printf("\n");
		number_of_ships1 = 5;
		number_of_ships2 = 5;
		
		printf("OK! Let's who goes first!\n");
		system("pause");
		starts = select_who_starts_first(starts);
		if (starts = 1)
		{
			printf("You go first!\n");
			turn = 1;
		}
		else
		{
			printf("Computer goes first...\n");
			turn = 0;
		}

		while (number_of_ships1 != 0 && number_of_ships2 != 0)
		{
			if (turn == 1)
			{
				print_game_board(game_board_shots, ROWS, COLS);
				get_target(&target_row, &target_col);
				hit_miss = shot_check(game_board2, target_row, target_col);
				update_board(hit_miss, game_board2, target_row, target_col);
				update_board(hit_miss, game_board_shots, target_row, target_col);
				carrier1 = search_ships(game_board2, ROWS, COLS, 'c');
				battleship1 = search_ships(game_board2, ROWS, COLS, 'b');
				cruiser1 = search_ships(game_board2, ROWS, COLS, 'r');
				submarine1 = search_ships(game_board2, ROWS, COLS, 's');
				destroyer1 = search_ships(game_board2, ROWS, COLS, 'd');
				number_of_ships1 = carrier1 + battleship1 + cruiser1 + submarine1 + destroyer1;
				printf("\n\nYour Shots so Far\n\n\n");
				print_game_board(game_board_shots, ROWS, COLS);
				system("pause");
				system("cls");
				turn++;
			}
			else
			{
				rand_target(&target_row, &target_col);
				hit_miss = shot_check(game_board1, target_row, target_col);
				update_board(hit_miss, game_board1, target_row, target_col);
				carrier2 = search_ships(game_board1, ROWS, COLS, 'c');
				battleship2 = search_ships(game_board1, ROWS, COLS, 'b');
				cruiser2 = search_ships(game_board1, ROWS, COLS, 'r');
				submarine2 = search_ships(game_board1, ROWS, COLS, 's');
				destroyer2 = search_ships(game_board1, ROWS, COLS, 'd');
				number_of_ships2 = carrier2 + battleship2 + cruiser2 + submarine2 + destroyer2;
				printf("Your Board\n");
				print_game_board(game_board1, ROWS, COLS);
				system("pause");
				system("cls");
				turn--;
			}
			if (number_of_ships2 == 0)
			{	
				printf("Sorry you lost. Better luck next time.\n");
			}
			else if (number_of_ships1 == 0)
			{
				printf("Congratulations! You won!\n");
		
			}
		}
player1 = output_stats(game_board2, ROWS, COLS);
computer = output_stats(game_board1, ROWS, COLS);
fprintf(outfile, "Player Stats\n\n\n");
fprintf(outfile, "Player total shots taken: %d\n", player1.total_shots);
fprintf(outfile, "Player hits: %d\n", player1.hits);
fprintf(outfile, "Player misses: %d\n", player1.misses);
fprintf(outfile, "Player hit-to-miss: %d\n\n", player1.hits_misses_ratio);
fprintf(outfile, "Computer Stats\n\n\n");
fprintf(outfile, "Computer total shots taken: %d\n", computer.total_shots);
fprintf(outfile, "Computer hits: %d\n", computer.hits);
fprintf(outfile, "Computer misses: %d\n", computer.misses);
fprintf(outfile, "Computer hit-to-miss: %d\n", computer.hits_misses_ratio);

fclose(outfile);


		
	return 0;
}

