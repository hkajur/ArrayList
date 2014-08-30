#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"

/**
 * Function createArrayList
 * ------------------------
 * Dynamically allocate space for a new ArrayList
 * Initialize its internal to be of length length
 * or DEFAULT_INIT_LEN, 10, whichever is greater.
 * Properly initialize pointers in the array to NULL
 * Set the size and capacity members of the list
 *
 * Returns a pointer to the new ArrayList
 * Returns NULL if calls to malloc fails
 */

ArrayList *createArrayList(int length){

	int index;
	ArrayList *list = NULL;

	if(length < DEFAULT_INIT_LEN)
		length = DEFAULT_INIT_LEN;

	list = (ArrayList *)malloc(sizeof(ArrayList));
	
	if(list == NULL)		return NULL;

	list->array = (char **)malloc(length * sizeof(char *));
	
	if(list->array == NULL)		return NULL;
	
	list->size = 0;
	list->capacity = length;
	
	for(index = 0; index < length; index++)
		list->array[index] = NULL;

	printf("-> Created new ArrayList of size %d.\n", length);
	
	return list;
}

/**
 * Function: destroyArrayList
 * --------------------------
 * Free any dynamically alloacted memory associated with list
 * Return NULL
 */

ArrayList *destroyArrayList(ArrayList *list){

	int index;
	int length;

	if(list == NULL)		return NULL;

	length = getSize(list);

	for(index = 0; index < length; index++)
		if(list->array[index] != NULL)
			free(list->array[index]);

	free(list->array);
	free(list);

	return NULL;
}

/**
 * Function: expandArrayList
 * -------------------------
 * Dynamically allocate a new array of length length
 * Copy the contents of list's old array into new array
 * Free any memory associated with the old list->array 
 * Then set list->array to point to newly created array
 * Be sure all pointers are properly initialized
 * Update the size and capacity of ArrayList if needed
 * 
 * Note: If length is less than or equal to list's 
 * current array capacity or if the list pointer is NULL,
 * you shouldn't modify the ArrayList at all. If so,
 * return from the function right away producing no output
 *
 * Returns a pointer to the ArrayList
 * Returns NULL if any calls to malloc() fails
 */

ArrayList *expandArrayList(ArrayList *list, int length){

	int index;
	char ** array = NULL;

	if(list == NULL)		return NULL;

	if(length <= list->capacity)
		return list;
	
	array = (char **)malloc(length * sizeof(char *));
	
	if(array == NULL)		return NULL;

	for(index = 0; index < list->capacity; index++)
	{
		if(list->array[index] != NULL)
			array[index] = list->array[index];
		else
			array[index] = NULL;
	}

	for(index = list->capacity; index < length; index++)
		array[index] = NULL;

	free(list->array);
	
	list->array = array;
	list->capacity = length;

	printf("-> Expanded ArrayList to size %d.\n", length);

	return list;
}

/**
 * Function: trimArrayList
 * -----------------------
 * If list's capacity is greater than its current size,
 * trim the length of the array to the current size
 * Malloc a new array of the current size
 * Copy the members of the array into new array
 * Free the old array to avoid any memory leaks
 * 
 * Returns a pointer to the ArrayList
 * Returns NULL if malloc() fails or list ptr is NULL
 */

ArrayList *trimArrayList(ArrayList *list){

	int index, size;
	char ** array = NULL;

	if(list == NULL)		return NULL;

	size = getSize(list);

	if(list->capacity <= size)
		return list;
	
	array = (char **) malloc(size * sizeof(char*));

	if(array == NULL)		return NULL;

	for(index = 0; index < size; index++)
		array[index] = list->array[index];
	
	free(list->array);

	list->array = array;
	list->capacity = size;

	printf("-> Trimmed ArrayList to size %d.\n", size);

	return list;
}

/**
 * Function: put
 * -------------
 * Insert a copy of str into the next unused cell of array
 * If list is already full, call expandArrayList() to grow 
 * the array of the length (capacity * 2 + 1) before inserting
 * new element. When copying str into the array, allocate
 * the minimum amount of space necessary to store the string
 *
 * Returns a pointer to the copy of new string inserted into array
 * Returns NULL if the string couldn't be added or list is NULL
 */

char *put(ArrayList *list, char *str){

	int index, stringLength;

	if(list == NULL || str == NULL)	return NULL;

	if(list->capacity == getSize(list))
	{
		list = expandArrayList(list, list->capacity * 2 + 1);
	
		if(list == NULL)	return NULL;
	}
	
	index = getSize(list);
	stringLength = strlen(str);

	list->array[index] = (char *)malloc(stringLength+1);
	
	if(list->array[index] == NULL)	return NULL;

	strncpy(list->array[index], str, stringLength);
	list->array[index][stringLength] = '\0';

	list->size = getSize(list) + 1;

	return list->array[index];
}

/**
 * Function: get
 * -------------
 * Attempts to return the element at specified index
 * Protect user from index out of bounds error with array
 * 
 * Returns a pointer to string at position index of array
 * Returns NULL if index was out of bounds or ptr is NULL
 */

char *get(ArrayList *list, int index){

	if(list == NULL)		return NULL;
	if(getSize(list) == -1) 	return NULL;
	if(index > getSize(list) - 1)  	return NULL;
	if(index < 0)  			return NULL;
	if(list->array[index] == NULL)	return NULL;
	
	return list->array[index];
}

/**
 * Function: set
 * -------------
 * If the array already has valid string at position index
 * replace it with copy of str. Otherwise, the opeartion
 * fails and we simply returns NULL. 
 * Ensure that no more space is used to store new 
 * copy of str than is absolutely necessary
 * 
 * Returns a pointer to the copy of string placed in ArrayList
 * Returns NULL if operation failed for any reason
 */

char *set(ArrayList *list, int index, char *str){

	if(list == NULL)		return NULL;
	if(getSize(list) == -1) 	return NULL;
	if(index > getSize(list) - 1)  	return NULL;
	if(index < 0)  			return NULL;
	if(list->array[index] == NULL)	return NULL;
	if(str == NULL)			return NULL;	
	
	free(list->array[index]);

	list->array[index] = (char *)malloc(strlen(str)+1);

	if(list->array[index] == NULL)	return NULL;
	
	strncpy(list->array[index], str, strlen(str));
	list->array[index][strlen(str)] = '\0';

	return list->array[index];
}

/**
 * Function: insertElement
 * -----------------------
 * Insert a copy of str at the specified index in array
 * Any elements to right of index are shifted one space to right
 * If specified index is greater than ArrayList's size, 
 * the element being inserted should be placed in 
 * first empty position in the list.
 * 
 * Returns a pointer to the copy of string inserted into list
 * Returns NULL if insertion fails for any reason
 */

char *insertElement(ArrayList *list, int index, char *str){

	int startPos, endPos, i;
	char * tmp;

	if(list == NULL || str == NULL)	return NULL;

	if(list->capacity == getSize(list))
		list = expandArrayList(list, list->capacity * 2 + 1);
	
	if(index > getSize(list)){
		tmp = put(list, str);
		if(tmp == NULL)		return NULL;
		return tmp;
	}
	else {
		startPos = index;
		endPos = getSize(list);

		for(i = endPos; i > startPos; i--)
			list->array[i] = list->array[i-1];

		list->array[index] = (char *)malloc(strlen(str) + 1);
		tmp = list->array[index];

		if(tmp == NULL)		return NULL;

		strncpy(tmp, str, strlen(str));
		tmp[strlen(str)] = '\0';

		list->size = getSize(list) + 1;

		return tmp;
	}

}

/**
 * Function: removeElement
 * -----------------------
 * Remove the string to the specified index in the array
 * Strings to the right of index are shifted one space to left
 * ArrayList's size member should be updated accordingly
 * 
 * Returns 1 if an element was successfully removed from array
 * Returns 0 if list ptr is NULL or if index greater than size
 */

int removeElement(ArrayList *list, int index){

	int startPos, endPos, i;

	if(list == NULL)		return 0;
	if(index > getSize(list) - 1)	return 0;

	free(list->array[index]);

	startPos = index;
	endPos = getSize(list) - 1;

	for(i = startPos; i < endPos; i++)
		list->array[i] = list->array[i+1];
	
	list->size = getSize(list) - 1;
	
	return 1;
}

/**
 * Function: getSize
 * -----------------
 * Returns the number of elements currently in the list
 * Returns -1 if list ptr is NULL
 */

int getSize(ArrayList *list){

	if(list == NULL)
		return -1;

	return list->size;
}

/**
 * Function: printArrayList
 * ------------------------
 * Print all strings currently in the array
 * 
 * Returns the string "(empty list)" if list ptr is NULL
 * or if the list array has no elements inside them
 */

void printArrayList(ArrayList *list){

	int index;

	if(list == NULL)	printf("(empty list)\n");
	if(getSize(list) == 0)	printf("(empty list)\n");

	for(index = 0; index < getSize(list); index++)
		printf("%s\n", get(list, index));
}
