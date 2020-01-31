#ifndef SUDOKU_SOLVER
#define SUDOKU_SOLVER

#include <vector>
#include <utility>

struct Sudoku_Solver
{
	int row;
	int collumn;
	bool multiple_solutions;
	int puzzle[9][9];
	int tiles[9][9];
	int solution[9][9];
	int solution_count;
	std::vector<std::pair<int, int>> clues;
	static int board_number;

	Sudoku_Solver();
	void set_board(int(&)[9][9]);
	void solve();
	void set_solution();
	bool is_full();
	bool can_put_on_board(int);
	void add(int);
	void remove(int);
	int solutions();
	void print_solution();
	int(&get_solution())[9][9];
	void send_puzzle_to_file();

};

#endif