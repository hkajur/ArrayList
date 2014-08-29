#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

ArrayList *createArrayList(int length){

	int index;
	ArrayList *list = NULL;

	if(length < DEFAULT_INIT_LEN)
		length = DEFAULT_INIT_LEN;

	list = (ArrayList *)malloc(sizeof(ArrayList));
	
	if(list == NULL)
		return NULL;

	list->array = (char **)malloc(length * sizeof(char *));
	
	if(list->array == NULL)
		return NULL;
	
	list->size = 0;
	list->capacity = length;
	
	for(index = 0; index < length; index++)
		list->array[index] = NULL;

	printf("-> Created new ArrayList of Size %d\n", length);
	
	return list;
}

