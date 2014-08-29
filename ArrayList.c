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

	int index, size;
	char ** array = NULL;

	if(list == NULL)
		return NULL;

	size = list->size;

	if(length <= list->capacity)
		return list;
	
	array = (char **)malloc(length * sizeof(char *));
	
	if(arr == NULL)
		return NULL;

	for(index = 0; index < size; index++)
		array[index] = list->array[index];

	for(index = size; index < length; index++)
		array[index] = NULL;

	free(list->array);
	
	list->array = array;
	list->capacity = length;

	printf("-> Expanded ArrayList to size %d.\n", length);

	return list;
}

ArrayList *trimArrayList(ArrayList *list){

	int index, size;
	char ** array = NULL;

	if(list == NULL)
		return NULL;

	size = list->size;

	if(list->capacity <= list->size)
		return list;
	
	array = (char **) malloc(size * sizeof(char*));

	for(index = 0; index < size; index++)
		array[index] = list->array[index];
	
	free(list->array);

	list->array = array;
	list->capacity = list->size;

	printf("-> Trimmed ArrayList to size %d.\n", list->size);

	return list;
}
