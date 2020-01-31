#include <stdlib.h>
#include <random>
#include <set>
#include "Sudoku_Solver.h"

enum
{
	DIFFICULTY_EASY,
	DIFFICULTY_MEDIUM,
	DIFFICULTY_HARD
};


/*This algorithm is inefficient for producing boards with clues < 32. The time to find a board skyrockets*/
int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> tile_number_dis(1, 9);		//get a random tile number
	std::uniform_int_distribution<int> box_collumn_dis(0, 2);		//get a random collumn in a box
	std::uniform_int_distribution<int> box_row_dis(0, 2);			//get a random row in a box
	std::uniform_int_distribution<int> row_dis(0, 8);				//get a random row on the board
	std::uniform_int_distribution<int> collumn_dis(0, 8);			//get a random collumn on the board
	std::uniform_int_distribution<int> tile_coordinate_dis(0, 8);	//get a random coordinate for a random tile
	std::uniform_int_distribution<int> clues_easy_dis(37, 45);		//get a random amount of clues for an easy board
	std::uniform_int_distribution<int> clues_medium_dis(29, 36);	//get a random amount of clues for a medium board

	int count = 0;
	int shuffle_amount = 200;
	int clues = 0;
	int boards_checked = 0;
	const int difficulty_level = DIFFICULTY_HARD;

	for (int i = 0; i < 2000; i++)
	{

		if (difficulty_level == DIFFICULTY_EASY)
		{
			clues = clues_easy_dis(gen);
		}
		else if (difficulty_level == DIFFICULTY_MEDIUM)
		{
			clues = clues_medium_dis(gen);
		}
		else if (difficulty_level == DIFFICULTY_HARD)
		{
			clues = 28;
		}


		/*********************************Begin Shuffle*****************************************************************/

		Sudoku_Solver sudoku_solver;	//Solves the sudoku_board and sends the puzzle and solution to a file
		do
		{

			int tiles[9][9] =
			{
			{1, 2, 3, 4, 5, 6, 7, 8, 9},
			{4, 5, 6, 7, 8, 9, 1, 2, 3},
			{7, 8, 9, 1, 2, 3, 4, 5, 6},
			{2, 3, 1, 5, 6, 4, 8, 9, 7},
			{5, 6, 4, 8, 9, 7, 2, 3, 1},
			{8, 9, 7, 2, 3, 1, 5, 6, 4},
			{3, 1, 2, 6, 4, 5, 9, 7, 8},
			{6, 4, 5, 9, 7, 8, 3, 1, 2},
			{9, 7, 8, 3, 1, 2, 6, 4, 5}
			};

			/*Will swap tile positions Tile[swap_pos1.first][swap_pos1.second] and Tile[swap_pos2.first][swap_pos2.second]*/
			std::pair<int, int> swap_pos1;
			std::pair<int, int> swap_pos2;

			for (int i = 0; i < shuffle_amount; i++)
			{

				/*Shuffle numbers*/
				int first_number = tile_number_dis(gen);
				int second_number = tile_number_dis(gen);
				while (first_number == second_number)
				{
					second_number = tile_number_dis(gen);
				}

				/*Swaps all tile numbers on the board according to first_number and second_number*/
				for (int j = 0; j < 9; j++)
				{
					for (int k = 0; k < 9; k++)
					{
						if (first_number == tiles[j][k])
						{
							swap_pos1 = { j, k };
						}
						else if (second_number == tiles[j][k])
						{
							swap_pos2 = { j, k };
						}

					}
					int temp_number = tiles[swap_pos1.first][swap_pos1.second];
					tiles[swap_pos1.first][swap_pos1.second] = tiles[swap_pos2.first][swap_pos2.second];
					tiles[swap_pos2.first][swap_pos2.second] = temp_number;
				}


				/*Shuffle Rows*/
				/*The rows need to stay in their corresponding boxes*/
				int box_row_pos1 = box_row_dis(gen);
				int box_row_pos2 = box_row_dis(gen);
				int row_number = row_dis(gen);
				while (box_row_pos1 == box_row_pos2)
				{
					box_row_pos2 = box_row_dis(gen);
				}

				/*Finds the first position(left top corner) of the box that the row is in and sets row_number equal to that*/
				if (row_number % 3 != 0)
				{
					if ((row_number + 1) % 3 == 0)
					{
						row_number = row_number - 2;
					}
					else if ((row_number - 1) % 3 == 0)
					{
						row_number = row_number - 1;
					}
				}

				/*Swaps the whole row on the board according to box_row_pos1 and box_row_pos2, while keeping the numbers in their corresponding boxes*/
				for (int i = 0; i < 9; i++)
				{
					int temp_number = tiles[row_number + box_row_pos1][i];
					tiles[row_number + box_row_pos1][i] = tiles[row_number + box_row_pos2][i];
					tiles[row_number + box_row_pos2][i] = temp_number;
				}



				/*Shuffle Collumns*/
				/*The collumns need to stay in their corresponding boxes*/
				int box_collumn_pos1 = box_collumn_dis(gen);
				int box_collumn_pos2 = box_collumn_dis(gen);
				int collumn_number = collumn_dis(gen);
				while (box_collumn_pos1 == box_collumn_pos2)
				{
					box_collumn_pos2 = box_collumn_dis(gen);
				}

				/*Finds the first position(top left corner) of the box and sets collumn_number equal to that*/
				if (collumn_number % 3 != 0)
				{
					if ((collumn_number + 1) % 3 == 0)
					{
						collumn_number = collumn_number - 2;
					}
					else if ((collumn_number - 1) % 3 == 0)
					{
						collumn_number = collumn_number - 1;
					}
				}

				/*Swaps while collumn on the board according to box_collumn_pos1 and box_collum_pos2, while keeps the numbers in their corresponding boxes*/
				for (int i = 0; i < 9; i++)
				{
					int temp_number = tiles[i][collumn_number + box_collumn_pos1];
					tiles[i][collumn_number + box_collumn_pos1] = tiles[i][collumn_number + box_collumn_pos2];
					tiles[i][collumn_number + box_collumn_pos2] = temp_number;

				}

			}
			/*************************End Shuffle*************************************************/


			/*Hide random Tiles that will not be clues*/
			int hide_amount = 81 - clues;
			std::set<std::pair<int, int>> pos;
			while (pos.size() < hide_amount)
			{
				pos.insert({ tile_coordinate_dis(gen), tile_coordinate_dis(gen) });
			}

			for (auto hide_position_iterator = pos.begin(); hide_position_iterator != pos.end(); hide_position_iterator++)
			{
				tiles[hide_position_iterator->first][hide_position_iterator->second] = 0;
			}

			/*Solve the board and check for a unique solution*/
			sudoku_solver.set_board(tiles);
			sudoku_solver.solve();
			printf("boards checked = %d\n", ++boards_checked);
		} while (sudoku_solver.solutions() != 1);


		sudoku_solver.send_puzzle_to_file();
	}

	return 0;
}