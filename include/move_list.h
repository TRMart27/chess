#ifndef MOVE_LIST_H
#define MOVE_LIST_H

#include "util.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Move_List
{
	Move* moves;
	size_t size;
	size_t capacity;

} Move_List;

//memory-involved functions/
void free_move(Move* move);
void free_list(Move_List *list);
Move_List init_list(size_t capacity);

//add / remove
short add_move(Move_List *list, Move move);
short compare_move(Move m1, Move m2);
short remove_move(Move_List *list, Move move);


#define MOVE_LIST_IMPLEMENTATION_

/*******************************************************
 * void free_move(Move* move);
 *   
 *   PURPOSE ::
 *   	free a individual move, pointed to by
 *   	parameter <move>
 *
 *   	@param 
 *  	   - move :: a Move structure that contains a
 *  	   	     short origin[2], dest[2] pair
 *  	@return
 *  	   - void :: nothing
 *
 *
 *******************************************************/
void free_move(Move* move)
{
	free(move);
	return;
}
/*******************************************************
 * void free_list(Move_List *list);
 *   
 *   PURPOSE ::
 *   	free an entire list, pointed to by
 *   	parameter <list>. Calls free_move()
 *   	iteratively to free each move, decrements
 *   	size per iteration
 *
 *   	@param 
 *  	   - move :: a Move structure that contains a
 *  	   	     short origin[2], dest[2] pair
 *  	@return
 *  	   - void :: nothing
 *
 *
 *******************************************************/
void free_list(Move_List *list)
{
	for(size_t i = 0; i < list->size; ++i)
	{
		free_move(list->moves[i]);
		list->size--;	
	}
	return;
}
/*******************************************************
 * void init_list(size_t *capacity);
 *   
 *   PURPOSE ::
 *	Initialize a new list of moves,
 *	where each element contains a 
 *	short origin[2], dest[2] pair
 *
 *
 *   	@param 
 *  	   - move :: a Move structure that contains a
 *  	   	     short origin[2], dest[2] pair
 *
 *  	@return
 *  	   - NULL :: on failure
 *  	   - list :: newly created list on success
 *
 *
 *******************************************************/
Move_List init_list(size_t capacity)
{
	if(capacity < 1)
	{
		fprintf(stderr, "Capacity must be non-zero!\n");
		return;
	}

	Move_List list;
	list = {
		.moves = NULL,
		.size = 0,
		.capacity = capacity
	};
	return NULL;
}
/*******************************************************
 * short add_move(Move_List *list, Move move)
 *   
 *   PURPOSE ::
 *	Initialize a new list of moves,
 *	where each element contains a 
 *	short origin[2], dest[2] pair
 *
 *
 *   	@param 
 *  	   - move :: a Move structure that contains a
 *  	   	     short origin[2], dest[2] pair
 *
 *  	@return
 *  	   - NULL :: on failure
 *  	   - list :: newly created list on success
 *
 *
 *******************************************************/
short add_move(Move_List *list, Move move)
{
	if(!list)
	{
		error_noexist(#list, #add_move);
		return FAILURE;
	}
	
	list->moves[size - 1] = move;
	list->size++;

	if(list->size >= list->capacity / 2)
	{	
		list->capacity = list->capacity * 2;
		list->moves = (Move*)realloc(list->moves, list->capacity * sizeof(Move));
		if(!list->moves)
		{
			error_nomem();
			return FAILURE;
		}
	}
	
	return 0;
}
/*******************************************************
 * short compare_move(Move *m1, Move *m2)
 *   
 *   PURPOSE ::
 *	Initialize a new list of moves,
 *	where each element contains a 
 *	short origin[2], dest[2] pair
 *
 *
 *   	@param 
 *  	   - m1 :: a Move structure that contains a
 *  	   	     short origin[2], dest[2] pair
 **  	   - m2 :: a Move structure that contains a
 *  	   	     short origin[2], dest[2] pair
 
 *  	@return
 *  	   - FALSE :: false
 *  	   - TRUE  :: true...?
 *
 *******************************************************/
short compare_move(Move *m1, Move *m2)
{
	assert(m1);
	assert(m2);

	if(m1->origin[0] != m2->origin[0])	return FALSE;
	if(m1->dest[0] != m2->dest[0])		return FALSE;

	if(m1->origin[1] != m2->origin[1]) 	return FALSE;
	if(m1->dest[1] != m2->origin[1])	return FALSE;

	return TRUE;
}
/*******************************************************
 * short remove_move(Move_List *list, Move move)
 *   
 *   PURPOSE ::
 *	Initialize a new list of moves,
 *	where each element contains a 
 *	short origin[2], dest[2] pair
 *
 *
 *   	@param 
 *  	   - move :: a Move structure that contains a
 *  	   	     short origin[2], dest[2] pair
 *
 *  	@return
 *  	   - NULL :: on failure
 *  	   - list :: newly created list on success
 *
 *
 *******************************************************/
short remove_move(Move_List *list, Move move)
{
	Move *curr_move = list->move[0];
	
	for(size_t i = 0; i < list->size; ++i)
	{
		if(compare_move(curr_move, move)
		{
			free_move(curr_move);
			list->size--;
			return 0;
		}
		curr_move = list->move[i+1]
	}
	return FAILURE;
}
#endif //MOVE_LIST_IMPLEMENTATION_
#endif //MOVE_LIST_H
