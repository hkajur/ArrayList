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

ArrayList *destroyArrayList(ArrayList *list){

	int index;
	int length;

	if(list == NULL)
		return NULL;

	length = list->size;

	for(index = 0; index < length; index++)
		free(list->array[index]);

	free(list);

	return NULL;
}

ArrayList *expandArrayList(ArrayList *list, int length){

	char ** arr = NULL;

	int index, cap, size;
	
	cap = list->capacity;
	size = list->size;

	if(length <= cap)
		return list;
	
	arr = (char **)malloc(length * sizeof(char *));
	
	if(arr == NULL)
		return NULL;

	for(index = 0; index < size; index++)
		arr[index] = list->array[index];

	for(index = size; index < length; index++)
		arr[index] = NULL;

	free(list->array);

	list->array = arr;
	
	return list;
}
