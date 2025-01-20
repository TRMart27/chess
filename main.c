#include "board.h"
#include "move.h"
#include "util.h"
#include "move_list.h"

int main(void)
{
	char** board = init_board();
	if(!board)
	{
		perror("Something bad happened\n");
		exit(EXIT_FAILURE);

	}
	draw_board(board);

	free_rows(board, NUM_ROWS);
	free(board);
	
	return 0;
}
