#ifndef MOVE_H_ 
#define MOVE_H_

///user defined
#include "board.h"
#include "util.h"
///standard
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>


void move_piece(char** board, Move move);
short is_path_clear(char** board,  const short origin[2], const short dest[2]);


//validate piece-type moves (pawn, rook, etc)
//   ~move to different file (validate.h/c)?
short validate_pawn(char** board, const short row_diff, const short col_diff,
		const short initial_row,  const short origin_row,
	       	const char origin_piece, const char dest_piece);
short validate_rook(char** board, const short row_diff, const short col_diff,
		const char origin_piece, const char dest_piece, Move move);
short validate_knight(char** board, const short row_diff, const short col_diff,
		const char origin_piece, const char dest_piece);
short validate_bishop(char** board, const short row_diff, const short col_diff,
		const char origin_piece, const char dest_piece);
short validate_king(char** board, const short row_diff, const short col_diff,
		const char origin_piece, const char dest_piece);


short is_move_legal(char** board,  Move move);

//considering moving these functioins to a separete file
short is_checkmate(char** board,  Move move);

#ifdef MOVE_IMPLEMENTATION_

/*********************************************************************
* void move_piece(char** board, Move move)
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

void move_piece(char** board, Move move)
{
	if(!board)
	{
		perror("Board does not exist!\n\t{move_piece}\n");
		return;
	}
	
	char piece = board[move.origin[0]][move.origin[1]];
	board[move.dest[0]][move.dest[1]] = piece;
	board[move.origin[0]][move.origin[1]] = '.';
	return;
}
/*********************************************************************
* short is_path_clear(char** board,  Move move)
*
* 	PURPOSE ::
*  		free the memory allocated for the board and its row 
*  			-needs to free each row individually, 
*     			(pointer to pointers)
* 	@param 
*	 - board :: 3d character array
*	 - row   :: the row to start deallocating at 
*	    	    (in case of error in init)
*	 @return
*	 - void :: no need to return anything
*********************************************************************/
short is_path_clear(char** board,  const short origin[2], const short dest[2])
{
	if(!board)
	{
		perror("Board does not exist!\n\t{is_path_clear}\n");
		return -1;
	}
	
	short origin_row = origin[0];
	short origin_col = origin[1];
	short dest_row   = dest[0];
	short dest_col   = dest[1];

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

	//calculate the next square to travel to, ensure it is empty
	short next_square[2] = { (origin_row + row_step), (origin_col + col_step) };
	if(board[next_square[0]][next_square[1]] != '.')
		return FALSE;
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

//piece-type validation
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
*	
*	@return
*	 - void :: short integer
*	 	- non-zero ( negative ) :: something bad happened
*	 	- zero (or poisitive)   :: something good happened
*********************************************************************/
short validate_pawn(char** board, const short row_diff, const short col_diff,
		const short initial_row, const short origin_row, const char origin_piece, const char dest_piece)
{
	if(!board)
	{
		error_noexist("board", "validate_pawn");
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
	else if (islower(dest_piece) != islower(origin_piece))
		if(col_diff == 1 && row_diff == 1)
			return TRUE;
	return FALSE;
}
/*********************************************************************
* short validate_rook(char** board, const short row_diff, const short col_diff,
*		const char origin_piece, const char dest_piece,
*		 Move move)
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
		 Move move)
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
			if(is_path_clear(board, move.origin, move.dest) == TRUE)
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
* int is_move_legal(char** board,  Move move[2]
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
short is_move_legal(char** board,  Move move)
{
	if(!board)
	{
		perror("Board does not exist!\n\t{is_move_legal}\n");
		return -1;
	}
	
	short origin_row  = move.origin[0];
	short origin_col  = move.origin[1];
	short dest_row    = move.dest[0];
	short dest_col    = move.dest[1];

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
	char conditional = tolower(origin_piece);

	switch(conditional)
	{
		case 'p':
		{
			return validate_pawn(board, 
			                     row_diff, col_diff, 
				      	     initial_row, origin_row,
			 		     origin_piece, dest_piece);
		}
		case 'r':
		{
			return validate_rook(board, 
				     	     row_diff, col_diff, 
				             origin_piece, dest_piece,
				             move);
		}
		case 'n':
		{	
			return validate_knight(board, 
					       row_diff, col_diff,
					       origin_piece, dest_piece);
		}
		case 'b':
		{
			return validate_bishop(board,
					       row_diff, col_diff,
					       origin_piece, dest_piece);
		}
		case 'q':
		{
			if(validate_rook(board, row_diff, col_diff, origin_piece, dest_piece, move) == TRUE || 
			   validate_bishop(board, row_diff, col_diff, origin_piece, dest_piece) == TRUE)
				return TRUE;
			return FALSE;	
		}
		case 'k':
		{
			return validate_king(board,
				       	     row_diff, col_diff,
				 	     origin_piece, dest_piece);
		}
		default: 
			return FALSE;
	}
}
#endif //MOVE_IMPLEMENTATION_
#endif //MOVE_H_
