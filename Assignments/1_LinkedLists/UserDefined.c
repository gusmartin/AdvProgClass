/**
 * @copyright (c) 2018
 *
 * @file    UserDefined.c
 *
 * @author  Gustavo Martin
 *
 * @date    Sat 03 Feb 2018
 *
 * @brief   Implements all the user defined functions for handling the
 *          specific user-defined data structure that is pointed to
 *          by the doubly linked list node in Glib.
 *
 * References:
 *          Code based on the requirements of the userDefined.h documentation
 *
 * Revision history:
 *          Fri 02 Feb 2018 -- File created
 *			Sat 03 Feb 2018 -- Implemented all the functions of the userDefined.h file
 *          Mon 05 Feb 2018 -- Added comments 
 *          Sun 11 Feb 2018 -- added strdup function when copying a node, checked for malloc mallfunctions, changed CompareItemsWithKey
 *
 *
 */
 
#include <stdlib.h>                      /* Used for malloc definition */
#include <stdio.h>                       /* Used for printf */
#include <string.h>                      /* Used for strcmp() */
#include "UserDefined.h"           

/**
 *
 * @brief Print the contents of the user-defined data structure.
 *
 * @b PrintItem will traverse the user-defined structure and print each
 * field according to the user's formatting.
 *
 * @param  data_p is a pointer to a user-defined structure element.
 * @return @c EXIT_SUCCESS the item was printed with no problems. Otherwise,
 *         return @c EXIT_FAILURE.
 *
 * @code
 *  PrintItem(item_p->data_p);
 * @endcode
 *
 */
int PrintItem (const void *data_p){
	
	if(data_p!= NULL){ //Check if data_p is not empty, if it is return EXIT_FAILURE
		
		printf("%d %s\n",((node_p)data_p)->number, ((node_p)data_p)->theString); //print the number and the string of the userDefined Sructure
		return EXIT_SUCCESS;	
	}
	
	return EXIT_FAILURE;
}

/**
 *
 * @brief Print all the elements of a list, based on a user-defined
 * function that handles the actual printing of each data element.
 *
 * @b PrintList will print all the elements of @p myList_p. It calls
 * the user-defined functon @c PrintItem which handles the format of
 * the data portion of the items in the list.
 *
 * @param  myList_p is a pointer to the list to be printed.
 * @return @c EXIT_SUCCESS if the list was sorted with no
 *         problems, otherwise return @c EXIT_FAILURE.
 * @code
 *  if (PrintList(theList_p) != EXIT_SUCCESS)
 *     printf("Error printing the list\n");
 * @endcode
 *
 * @warning This function @b requires a user-defined function to do the
 *          actual printing of the data element.
 *
 */
int PrintList (GList * myList_p){
	
	if(myList_p != NULL){		//checks that myList_p is not empty
	
		GList *current = NULL;		//Create pointer to traverse myList_p
	
		for(current = myList_p; current; current = current->next){ 		//stops until current is NULL
			
			if(PrintItem(current->data)) 			//Checks if PrintItem fails, if it does returns EXIT_FAILURE
				return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

/**
 *
 * @brief Allocate memory to a node of the user-defined data structure.
 *
 * @b NewItem will allocate the @c string and @c number inside the
 * user-defined data structure @c myData. The input string will be
 * copied so the caller can dispose of the input argument after
 * calling @c NewItem. The string stored in the new node may not be
 * NULL terminated.
 *
 * @param @c theNumber is the integer input.
 * @param @c theString is the copy of the input string.
 *
 * @code
 *  newNode_p = NewItem(13,"Hello");
 * @endcode
 *
 * @return @c node_p is a pointer to the memory block that holds a copy
 *         of the input string and the input number.
 *
 */
node_p NewItem (int theNumber, char * theString){
	
	node_p node = (node_p)malloc(sizeof(node_p));  //allocate space for the node
	
	//assign values to the node
	node->number = theNumber;			
	node->theString = theString;
		
	return node;
	
}

/**
 *
 * @brief De-allocate memory assigned to user-defined data structure.
 *
 * @b FreeItem will de-allocate the @c string inside the user-defined
 * data structure @c myData.
 *
 * @param  data_p is a pointer to the user-defined data structure.
 * @return @c EXIT_SUCCESS the item was de-allocated with no
 *         problems, otherwise return @c EXIT_FAILURE
 *
 * @code
 *  FreeItem(item_p->data_p);
 * @endcode
 *
 * @warning This function must be passed as a parameter when calling
 *          @c DestroyList() since it will call it to de-allocate the
 *          user-defined structure.
 */
int FreeItem (const void *data_p){
		
	if(data_p != NULL){ 	//check data_p is not empty
		
		g_free((node_p)data_p);  // this should work the same way as free but I´m not sure
		
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;		
}

/**
 *
 * @brief De-allocate memory assigned to each user-defined data structure
 * in the list. It also deallocates memory for the list.
 *
 * @b DestroyList() will de-allocate the user-defined data structure
 * @c myData for each element in the list.
 *
 * @param  theList_p is a pointer to the list.
 * @return @c EXIT_SUCCESS the list was de-allocated with no problems.
 *         Otherwise return @c EXIT_FAILURE.
 *
 * @code
 *   DestroyList(theList_p);
 * @endcode
 *
 * @see FreeItem()
 *
 */
int DestroyList (GList * theList_p){
	
	if(theList_p != NULL){ //check theList_p is not empty
		
		/* Note: 	g_list_free_full requires a void function to destroy the nodes 
		* 			of the list, FreeItem returns an int, but since we are implementing
		*			glib in our code we can´t check if the function executed correctly
       	*/
		
		g_list_free_full(theList_p,(GDestroyNotify)FreeItem); //use glib function to free list space
		
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

/**
 *
 * @brief Compare the user-defined nodes of two list elements using a
 * numeric field in the @c myData structure.
 *
 * @b CompareItems() is a user-defined function needed to compare the
 * user-defined data structure. Only the first numeric field of the
 * user-defined data structure is compared. If other fileds are needed use
 * the @c CompareItemsWithKey() function.
 * The return value matches the expected values for @c g_list_sort().
 *
 * @param item1_p is a pointer to the first @c myData item (user-defined).
 * @param item2_p is a pointer to the second @c myData item (user-defined).
 *
 * @return @c LESS     if input1  < input2.
 *         @c EQUAL    if input1 == input2.
 *         @c GREATER  if input1  > input2.
 * @code
 *   if (CompareItems(p1->data, p2->data) == EQUAL) {
 *       return (p);
 *    } else {
 *       ...
 * @endcode
 *
 */
int CompareItems (const void *item1_p, const void *item2_p){
	
	int compare = ((node_p)item1_p)->number - ((node_p)item2_p)->number; //substract the two items to know whos greater
	
	//translate the result to the expected output
	if(compare > 0)
		return GREATER;
		
	else if(compare > 0)
		return LESS;
		
	else
		return EQUAL;	
}

/**
 *
 * @brief Compare a filed of the data portion of two list elements using
 *  some user-defined key.
 *
 * @b CompareItemWithKey() is a user-defined function needed to identify
 * the particular data structure fields to compare.
 * This function can compare the integer portion (@p key = INT), the
 * string portion (@p key = STR), compare an arbitrary string to the
 * string field (@p key = SINGLESTR), or compare the contents of an
 * arbitrary pointer to an integer to the integer field (@p key = SINGLEINT)
 * in the user-defined data structure.
 *
 * @param item1_p is a pointer to the first @c myData item (user-defined).
 * @param item2_p is a pointer to the second @c myData item (user-defined)
 *        or to a string if @p key = SINGLESTR.
 * @param key is an integer that corresponds to the desired field in the
 *        user-defined data structure. The key is an enum of type @c theKey.
 * @return @c LESS     if input1  < input2.
 *         @c EQUAL    if input1 == input2.
 *         @c GREATER  if input1  > input2.
 *         @c NOTEQUAL if the comparison can't be made.
 *
 * @code
 *        if (CompareItemsWithKey(p->data, "Hello", SINGLESTR) == EQUAL) {
 *           return (p);
 *        } else {
 *           ...
 * @endcode
 *
 *
 */
int CompareItemsWithKey (const void *item1_p, const void *item2_p, int key){
	
	
	int compare;	//store result of comparisson
	
	switch(key){
	
		//compare a myData node with a string, return NOTEQUAL if they are not the same	
		case SINGLESTR:
			compare = strcmp(((node_p)item1_p)->theString, item2_p);
			
			if(compare)
				return NOTEQUAL;
				
			break;
		
		//compare the Sting data of two myData nodes, return NOTEQUAL if they are not the same	
		case STR:
			compare = strcmp(((node_p)item1_p)->theString, ((node_p)item2_p)->theString);
			
			if(compare)
				return NOTEQUAL;
				
			break;
		
		//compare a myData node with an int
		case SINGLEINT:
			compare = ((node_p)item1_p)->number - *(int*)item2_p;
			break;
		
		//compare the Integer data of two myData nodes		
		case INT:
			compare = ((node_p)item1_p)->number - ((node_p)item1_p)->number;
			break;
	}
	
	//after the comparisson is made return the expected output in the correct format
	if (compare > 0)
		return GREATER;
			
	else if (compare < 0)
		return LESS;
			
	else
		return EQUAL;
}

/**
 *
 * @brief Allocate memory to hold a copy of a user-defined item.
 *
 * @b CopyItems() will allocate memory and copy the user defined
 * data structure @c myData. The caller is responsible for
 * de-allocating the new item.
 *
 * @param  source_p is a pointer to the user-defined data structure.
 * @return pointer to the new data item @c data_p or NULL.
 *
 * @code
 *      myList_p = CreateList(FreeItem, PrintItem, CompareItems,
 *                            CopyItems);
 *        NodeData(dstNode_p) = sourceList_p->copy(NodeData(srcNode_p));
 * @endcode
 *
 * @see CreateList()
 *
 * @warning This function must be passed as a parameter when calling
 *          CopyList () since it will call it to allocate the
 *          user-defined structure.
 *          The caller is responsible for de-allocating the new item.
 */
void * CopyItems (const void *source_p){
	
	if(source_p != NULL){
	
		node_p node = (node_p)malloc(sizeof(node_p));  //allocate memory for the new node created
		
		//Check that the malloc functioned correctly
		if(node == NULL){
			
			perror("malloc malfunction, not enough space");
			return NULL;
		}
		
		else{
		
			//copy the data from the source node to the newly created node
			node->number = ((node_p)source_p)->number;
			
			//use strdup to create another string because theString is a pointer
			node->theString = strdup(((node_p)source_p)->theString);
			
			return node;
		}
	}
	
	return NULL;
}

/**
 *
 * @brief Perform a deep copy of an input list.
 *
 * @b DuplicateList() will perform a deep copy of an input list
 * allocating memory for each data element by calling the user-defined
 * CopyItems() function.
 *
 * @param  inputList_p pointer to the list to be copied.
 * @return pointer to the new list.
 *
 * @code
 *  outputList_p = CopyList(inputList_p);
 *  if (outputList == NULL){
 *     printf("Error: failed to find selected node \n");
 *  }
 * @endcode
 *
 * @note   The user must check if the returned pointer is NULL
 *         before de-referencing it.
 */
GList * CopyList (GList * inputList){
	
	if(inputList != NULL){
	
		GList * outputList;
		
		//perform a deep copy passing each node to the CopyItem function
		outputList = g_list_copy_deep (inputList, (GCopyFunc)CopyItems, (inputList)->data); //although CopyItems is of type void(same as GCopyFunc), the cast is required for it to work
		
		return outputList;
	}
	return NULL;	
}

/**
 *
 * @brief Attempts to find a user-defined value in a list
 *
 * @b FindInList() will try to find the user-defined value pointed by
 * @p value_p that matches a particular field @p key in the user-defined
 * data structure which is part of every data portion of the nodes in the
 * linked list.
 *
 * @param  myList_p pointer to the list to be searched.
 * @param  value_p pointer to the user-defined data value to match.
 * @param  key integer that represents which field in the user-defined
 *         data structure to match against @p value_p
 * @return pointer to the element in the list that matches the value
 *         @p value_p. NULL if no match was found.
 *
 * @code
 *  aNode = FindInList(theList_p, "Louie", SINGLESTR);
 *  if (aNode == NULL){
 *     printf("Error: failed to find selected node \n");
 *  }
 * @endcode
 *
 * @note   The user must check if the returned pointer is NULL
 *         before de-referencing it.
 *
 */
GList * FindInList (GList * myList_p, const void *value_p, int key){
	
	GList *current = NULL;
	
	int compare;
	
	for(current = myList_p; current; current = current->next){  //traverse list to find node
		
		compare = CompareItemsWithKey(current->data, value_p, key); //make a compare of the current node and the node to find according to the key
								
		if(compare == EQUAL) // if compare is 0(EQUAL) stop serching and return the node 
			break;
		
	}
	return current; //will return NULL if nothing is found
}





