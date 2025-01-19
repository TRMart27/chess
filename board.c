#ifndef BOARD_H_
#define BOARD_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#define NUM_ROWS 8
#define NUM_COLS 8
#define TRUE 1
#define FALSE 0

void free_rows(char** board);
char** init_board(void);
void move_piece(char** board, const int origin[2], const int dest[2]);
int is_path_clear(char** board, const int origin[2], const int dest[2]);
short validate_pawn(char** board, const short row_diff, const short col_diff,
		const short initial_row, const char origin_piece, const char dest_piece);
short validate_rook(char** board, const short row_diff, const short col_diff,
		const char origin_piece, const char dest_piece,
		const short origin[2], const short dest[2]);
short validate_knight(char** board, const short row_diff, const short col_diff,
		const char origin_piece, const char dest_piece,
	        const short origin[2], const short dest[2]);
short validate_bishop(char** board, const short row_diff, const short col_diff,
		const char origin_piece, const char dest_piece,
		const char origin[2], const char dest[2])
short validate_king(char** board, const short row_diff const short col_diff,
		const char origin_piece, const char dest_piece);
int is_move_legal(char** board, const int origin[2], const int dest[2]);
void draw_board(char** board);


#define BOARD_IMPLEMENTATION_


/*********************************************************************
* void free_rows(char** board, size_t row)
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
void free_rows(char** board, size_t row)
{
	for (size_t i = 0; i < row; ++i)
		free(board[i]);
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
		perror("Memory allocation failed for board!\n\t{init_board}\n");
		return NULL;
	}

	const char init_board[8][8] = {
		{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
		{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' }  
		{'.', '.', '.', '.', '.', '.', '.', '.' }
		{'.', '.', '.', '.', '.', '.', '.', '.' }
		{'.', '.', '.', '.', '.', '.', '.', '.' }
		{'.', '.', '.', '.', '.', '.', '.', '.' }
		{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' }  
		{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
	};

	for(size_t row = 0; row < NUM_ROWS; ++row)
	{
		board[row] = (char*) malloc(NUM_COLS * sizeof(char));
		if(!board[row])
		{
			perror("board row %d is NULL\n\t{init_board}\n");
			free_rows(board, row)
			free(board);
			return NULL;
		}
		for(size_t col = 0; col < NUM_COLS; ++col)
			board[row][col] = init_board[row][col];
	}
	return board;
}

/*********************************************************************
* void move_piece(char** board, const int origin[2], const int dest[2]);
*
* 	PURPOSE ::
*  		Move the piece at origin to dest
*  			-movement validation should occur before function 
*  			is called
*     			(pointer to pointers)
* 	@param 
*	 - board :: 2d character array
*	 - row   :: the row to start deallocating at 
*	    	    (in case of error in init)
*	 @return
*	 - void :: no need to return anything
*********************************************************************/

void move_piece(char** board, const int origin[2], const int dest[2])
{
	if(!board)
	{
		perror("Board does not exist!\n\t{move_piece}\n");
		return;
	}
	
	char piece = board[origin[0]][origin[1]];
	board[dest[0]][dest[1]] = piece;
	board[origin[0]][origin[1]] = '.';
	return;
}

/*********************************************************************
* int is_path_clear(char** board, const int origin[2], const int dest[2])
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
int is_path_clear(char** board, const int origin[2], const int dest[2])
{
	if(!board)
	{
		perror("Board does not exist!\n\t{is_path_clear}\n");
		return -1;
	}
	
	origin_row = origin[0];
	origin_col = origin[1];
	dest_row   = dest[0];
	dest_col   = dest[1];

	//if the origin and dest are the same square
	if ( (origin_row == dest_row) && (origin_col == dest_col) )
		return TRUE;
	
	//grab the row and col diff,
	//dont want negative difference, use absolute value
	short row_diff = abs(origin_row - dest_row);
	short col_diff = abs(origin_col - dest_col);

	//if origin and dest are adjacent to each other
	if(row_diff <= 1 && col_diff <=1)
		return TRUE;

	//determine which way i need to move for row, col
	short row_step = 0;
	if(dest_row > origin_row)
		row_step = 1;
	else
		 row_step = -1;

	short col_step = 0;
	if(dest_col > origin_col)
		col_step = 1;
	else
		col_step = -1;

	//determine which square we will travel to next
	int next_square[2] = { (origin_row + row_step), (origin_col + col_step)}

	//now that we know where we are traveling next,
	//lets check to see if that square is occupied
	if( board[next_square[0]][next_square[1]] != '.')
		return FALSE;

	//continue recursively to the next square
	return is_path_clear(board, next_square, dest);
}
/*********************************************************************
* short is_available(char** board, const char origin_piece const char dest_piece,
*
*
* 	PURPOSE ::
*		confirm whether or not a tile of the board
*		is either empty or occupied by oppsoing team
*
* 	@param 
*	 - board         :: 2d character array
*	 - origin_piece  :: the difference between the origin and destination rows (absolute value)
*	 - col_piece     :: the difference between the origin and destination columns (absolute value)
*
*	 @return
*	 - void :: short integer
*	 	- non-zero ( negative ) :: something bad happened
*	 	- zero (or poisitive)   :: something good happened
*********************************************************************/
short is_available(char** board, const char origin_piece, const char dest_piece)
{
	if(!board)
	{
		perror("Board does not exist!\n\t{is_available}\n");
		return -1;
	}
	
	if(dest_piece == '.' || islower(origin_piece) != islower(dest_piece))
		return TRUE;
	return FALSE;
}
/*********************************************************************
* short validate_pawn(char** board, const short row_diff, const short col_diff,
*	       	const char origin_piece, const dest_piece)
*
*
* 	PURPOSE ::
*		confirm whether or not a potential attack or 
*		movement of a pawn piecetype is within
*		the confines of the chess rules
*
* 	@param 
*	 - board        :: 2d character array
*	 - row_diff     :: the difference between the origin and destination rows (absolute value)
*	 - col_diff     :: the difference between the origin and destination columns (absolute value)
*	 - origin_piece :: the single character that represents the piece type at origin tile
*	 - dest_piece   :: the single character that represents the piece type at the requested tile
*	 @return
*	 - void :: short integer
*	 	- non-zero ( negative ) :: something bad happened
*	 	- zero (or poisitive)   :: something good happened
*********************************************************************/
short validate_pawn(char** board, const short row_diff, const short col_diff,
	       	const short initial_row, const char origin_piece, const dest_piece)
{
	if(!board)
	{
		perror("Board does not exist!\n\t{validate_pawn}\n");
		return -1;
	}

	//if we are not attacking
	if(dest_piece == '.')
	{
		//cannot move diagonally, so column difference must be 0
		if(col_diff != 0)
			return FALSE;
		//can only move one step forwrad
		if(row_diff == 1)
			return TRUE;
		//otherwise, we must be on the initial row, moving 2 steps forward
		//   **i forgot what the move was called but its valid i promise**
		else if(origin_row == initial_row && row_diff == 2)
			return TRUE;
	}
	//else if we is attacking, gotta be diagonal
	else if (islower(dest_piece) != is_lower(origin_piece))
		if(col_diff == 1 && row_diff == 1)
			return TRUE;
	return FALSE;
	//     0   1   2
	//A  | . | . | .
	//B  | . | P | .
	//C  | p | . | .
	// p @ C0
	// P @ B1

}
/*********************************************************************
* short validate_rook(char** board, const short row_diff, const short col_diff,
*		const char origin_piece, const char dest_piece,
*		const short origin[2], const short dest[2])
*
*
* 	PURPOSE ::
*		confirm whether or not a potential attack or 
*		movement of a rook piecetype is within
*		the confines of the chess rules
*
* 	@param 
*	 - board        :: 2d character array
*	 - row_diff     :: the difference between the origin and destination rows (absolute value)
*	 - col_diff     :: the difference between the origin and destination columns (absolute value)
*	 - origin_piece :: the single character that represents the piece type at origin tile
*	 - dest_piece   :: the single character that represents the piece type at the requested tile
*	 - origin       :: the coordinate points of the origin tile {row, col}
*	 - dest         :: the coordinate points of the destination tile {row, col}
*
*	 @return
*	 - void :: short integer
*	 	- non-zero ( negative ) :: something bad happened
*	 	- zero (or poisitive)   :: something good happened
*********************************************************************/
short validate_rook(char** board, const short row_diff, const short col_diff,
		const char origin_piece, const char dest_piece,
		const short origin[2], const short dest[2])
{
	if(!board)
	{
		perror("Board does not exist!\n\t{validate_rook}\n");
		return -1;
	}

	//if we moved on either x or y axis
	//  and if we attacking or occupying
	//  	and furthermore, if the path ye seek is clear, 
	//     		you may continue
	if(row_diff == 0 || col_diff == 0)
		if(is_available(board, origin_piece, dest_piece) == TRUE)
			if(is_path_clear(board, origin, dest) == TRUE)
				return TRUE;
	//otherwise its not a valid move bro
	return FALSE;
}
/*********************************************************************
* short validate_knight(char** board, const short row_diff, const short col_diff,
*		const char origin_piece, const char dest_piece,
*
*
* 	PURPOSE ::
*		confirm whether or not a potential attack or 
*		movement of a knight piecetype is within
*		the confines of the chess rules
*
* 	@param 
*	 - board        :: 2d character array
*	 - row_diff     :: the difference between the origin and destination rows (absolute value)
*	 - col_diff     :: the difference between the origin and destination columns (absolute value)
*	 - origin_piece :: the single character that represents the piece type at origin tile
*	 - dest_piece   :: the single character that represents the piece type at the requested tile
*
*	 @return
*	 - void :: short integer
*	 	- non-zero ( negative ) :: something bad happened
*	 	- zero (or poisitive)   :: something good happened
*********************************************************************/
short validate_knight(char** board, const short row_diff, const short col_diff,
		const char origin_piece, const char dest_piece)
{
	if(!board)
	{
		perror("Board does not exist!\n\t{validate_knight}\n");
		return -1;
	}
	
	//this makes an L
	//2 1 0 1 2		1 0 1
	//    1 	or 	  1
	//		 	  2
	//
	if( (row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2))
		if( is_available(board, origin_piece, dest_piece) == TRUE )
			return TRUE;
	return FALSE;
}
/*********************************************************************
* short validate_bishop(char** board, const short row_diff, const short col_diff,
*		const char origin_piece, const char dest_piece,
*
*
* 	PURPOSE ::
*		confirm whether or not a potential attack or 
*		movement of a rook piecetype is within
*		the confines of the chess rules
*
* 	@param 
*	 - board        :: 2d character array
*	 - row_diff     :: the difference between the origin and destination rows (absolute value)
*	 - col_diff     :: the difference between the origin and destination columns (absolute value)
*	 - origin_piece :: the single character that represents the piece type at origin tile
*	 - dest_piece   :: the single character that represents the piece type at the requested tile
*
*	 @return
*	 - void :: short integer
*	 	- non-zero ( negative ) :: something bad happened
*	 	- zero (or poisitive)   :: something good happened
*********************************************************************/
short validate_bishop(char** board, const short row_diff, const short col_diff,
		const char origin_piece, const char dest_piece)
{
	if(!board)
	{
		perror("Board does not exist!\n\t{validate_bishop}\n");
		return -1;
	}
	//moves in a diagonal, like y = 1x + 0,
	//so rise over run is 1 / 1,
	//so column and row should have the same difference
	if (row_diff == col_diff)
		if( is_available(board, origin_piece, dest_piece) == TRUE )
			return TRUE;
	return FALSE;

}
/*********************************************************************
* short validate_king(char** board, const short row_diff, const short col_diff,
*		const char origin_piece, const char dest_piece,
*
*
* 	PURPOSE ::
*		confirm whether or not a potential attack or 
*		movement of a rook piecetype is within
*		the confines of the chess rules
*
* 	@param 
*	 - board        :: 2d character array
*	 - row_diff     :: the difference between the origin and destination rows (absolute value)
*	 - col_diff     :: the difference between the origin and destination columns (absolute value)
*	 - origin_piece :: the single character that represents the piece type at origin tile
*	 - dest_piece   :: the single character that represents the piece type at the requested tile
*
*	 @return
*	 - void :: short integer
*	 	- non-zero ( negative ) :: something bad happened
*	 	- zero (or poisitive)   :: something good happened
*********************************************************************/
short validate_king(char** board, const short row_diff, const short col_diff,
		const char origin_piece, const char dest_piece)
{
	if(!board)
	{
		perror("Board does not exist!\n\t{validate_king}\n");
		return -1;
	}
	//king can only move one square // diagonal at a time
	//so row or column difference should never exceed 1
	if ( (row_diff <= 1 && col_diff <= 1) ) 
		if( is_available(board, origin_piece, dest_piece) == TRUE )
			return TRUE;
	return FALSE;

}






/*********************************************************************
* int is_move_legal(char** board, const int origin[2], const int dest[2]
*
* 	PURPOSE ::
*  		determine whether the provided move (origin -> dest)
*  		is within the confines of chess rules
* 	@param 
*	 - board    :: 2d character array
*	 - origin   ::  
*	 @return
*	 - void :: no need to return anything
*********************************************************************/
short is_move_legal(char** board, const int origin[2], const int dest[2])
{
	if(!board)
	{
		perror("Board does not exist!\n\t{is_path_clear}\n");
		return -1;
	}
	
	origin_row = origin[0];
	origin_col = origin[1];
	dest_row   = dest[0];
	dest_col   = dest[1];

	//if the origin and dest are the same square
	if ( (origin_row == dest_row) && (origin_col == dest_col) )
		return TRUE;
	
	//grab the row and col diff,
	//dont want negative difference, use absolute value
	const short row_diff = abs(origin_row - dest_row);
	short col_diff = abs(origin_col - dest_col);

	//confirm we are actually trying to move somewhere
	if(row_diff == 0 && col_diff == 0)
		return FALSE;

	//lets store the piece at the origin and the destination
	const char origin_piece = board[origin_row][origin_col];
	const char dest_piece = board[dest_row][dest_col];

	//i need to determine the starting row,
	//so i can validate pawn moves
	short initial_row = 6;
	if(islower(origin_piece))
		initial_row = 1;

	//create the conditional character so i know what piece is moving
	const char conditional = tolower(origin_piece);
	short is_valid = -1;
	switch(conditional)
	{
		case 'p':
		{
			 is_valid = validate_pawn(board, row_diff, col_diff, initial_row, origin_piece, dest_piece)
		}
		case 'r':
		{
			is_valid = validate_rook(board, row_diff, col_diff, origin_piece, dest_piece, origin, dest);
		}
		case 'n':
		{
			is_valid = validate_knight(board, row_diff, col_diff, origin_piece, dest_piece);
		}
		case 'b':
		{
			is_valid = validate_bishop(board, row_diff, col_diff, origin_piece, dest_piece, origin, dest);
		}
		case 'q':
		{
			if(validate_bishop(board, row_diff, col_diff, origin_piece, dest_piece) == TRUE ||
			   validate_rook(board, row_diff, col_diff, origin_piece, dest_piece) == TRUE)
				is_valid = TRUE;
		}
		case 'k':
		{
			is_valid = validate_king(board, row_diff, col_diff, origin_piece, dest_piece);
		}
		default:
			return FALSE
	}
	return -66; //-66, this should never happen, like order 66
}
/*********************************************************************
* void free_rows(char** board, size_t row)
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
void free_rows(char** board, size_t row)
{
	for (size_t i = 0; i < row; ++i)
		free(board[i]);
	return;
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
		perror("Board does not exist!\n\t{draw_board}");
		return;
	}

	for(size_t row = 0; row < NUM_ROWS; ++row)
	{
		for(size_t col = 0; row < NUM_COLS; ++col)
			printf("%c ", board[row][col];
		printf("\n");
	}
	printf("\n");
	return
}
#endif //BOARD_IMPLEMENTATION_
#endif //BOARD_H_

