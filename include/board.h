#ifndef BOARD_H_
#define BOARD_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>

#include "util.h"

#define NUM_ROWS 8
#define NUM_COLS 8
#define TRUE 1
#define FALSE 0

void cleanup(char** board, size_t row);
char** init_board(void);
void set_piece(char** board, short row, short col, char piece);
char get_piece(char** board, short row, short col);
void draw_board(char** board);

#ifdef BOARD_IMPLEMENTATION_

/*********************************************************************
* void cleanup(char** board, size_t row)
*
* 	PURPOSE ::
*  		free the memory allocated for the board and its row 
*  			-needs to free each row individually, 
*     			(pointer to pointers)
* 	@param 
*	 - board :: 2d character array
*	 - row   :: the row to start deallocating at 
*	    	    (in case of error in init)
*	 @return
*	 - void :: no need to return anything
*********************************************************************/
void cleanup(char** board, size_t row)
{
	for (size_t i = 0; i < row; ++i)
	{
		board[i] = NULL;
		free(board[i]);
	}
	board = NULL;
	free(board);
	return;
}

/*********************************************************************
* char** init_board(void)
*
*   	PURPOSE ::
*		- initialize a 2 dimensional (row and column)
*		character array that will represent our chess board.
*		Lowercase pieces will represent the "black" pieces,
*		Uppercase pieces will represent the "white" pieces.
*     			(pointer to pointers)
* 	@param 
*	 - board :: 2d character array
*	 - row   :: the row to start deallocating at 
*	    	    (in case of error in init)
*	 @return
*	 - void :: no need to return anything
*********************************************************************/
char** init_board(void)
{
	char **board = (char**)malloc(NUM_ROWS * sizeof(char*));	
	if(!board)
	{
		cleanup(board, 0);
		error_nomem();
	}

	const char init_board[8][8] = {
		{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' },
		{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' }, 
		{'.', '.', '.', '.', '.', '.', '.', '.' },
		{'.', '.', '.', '.', '.', '.', '.', '.' },
		{'.', '.', '.', '.', '.', '.', '.', '.' },
		{'.', '.', '.', '.', '.', '.', '.', '.' },
		{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' }, 
		{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' }
	};

	for(size_t row = 0; row < NUM_ROWS; ++row)
	{
  board[row] = (char*) malloc(NUM_COLS * sizeof(char));
		if(!board[row])
		{
			cleanup(board, row);
			error_nomem();
		}
		for(size_t col = 0; col < NUM_COLS; ++col)
			board[row][col] = init_board[row][col];
	}
	return board;
}
/*********************************************************************
* void set_piece(char** board, short row, short col, char piece)
*
* 	PURPOSE ::
*  		set the piece on <board> at coordinate <row>,<col>
*    to the provided <piece>
* 
* 	@param 
*	 - board :: 2d character array
*	 - row   :: numerical value representing the row coordinate 
*             (0 <= row <= 7)
*  - col   :: numerical value representing the col coordinate 
*             (0 <= col <= 7)
*	 - piece :: char piecetype 
*
* 	@return
*	 - void :: no need to return anything
*********************************************************************/
void set_piece(char** board, short row, short col, char piece)
{
  if(!board)
		  ERR_NOEXIST(board, "set_piece");
		
		board[row][col] = piece;
		return;
}
/*********************************************************************
* char get_piece(char** board, short row, short col)
*
* 	PURPOSE ::
*  		get the piece on <board> at <row>,<col> 
* 
* 	@param 
*	 - board :: 2d character array
*	 - row   :: numerical value representing the row coordinate 
*             (0 <= row <= 7)
*  - col   :: numerical value representing the col coordinate 
*             (0 <= col <= 7)
*
* 	@return
*	 - char :: piecetype at specified coordinate 
*********************************************************************/
char get_piece(char** board, short row, short col)
{
  if(!board)
		  ERR_NOEXIST(board, "get_piece");
		return board[row][col];
}
/*********************************************************************
* void draw_board(char** board)
*
* 	PURPOSE ::
*  		print each {row}{col} of the board
* 
* 	@param 
*	 - board :: 2d character array
*
* 	@return
*	 - void :: no need to return anything
*********************************************************************/
void draw_board(char** board)
{
	if(!board)
	{
		error_noexist("board", "draw_board");
		return;
	}

	for(size_t row = 0; row < NUM_ROWS; ++row)
	{
		for(size_t col = 0; col < NUM_COLS; ++col)
			printf("%c ", board[row][col]);
		printf("\n");
	}
	printf("\n");
	return;
}
#endif //BOARD_IMPLEMENTATION_
#endif //BOARD_H_

