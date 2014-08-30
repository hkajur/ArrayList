#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"

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

char *get(ArrayList *list, int index){

	if(list == NULL)		return NULL;
	if(getSize(list) == -1) 	return NULL;
	if(index > getSize(list) - 1)  	return NULL;
	if(index < 0)  			return NULL;
	if(list->array[index] == NULL)	return NULL;
	
	return list->array[index];
}

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
	
	return 0;
}

int getSize(ArrayList *list){

	if(list == NULL)
		return -1;

	return list->size;
}

void printArrayList(ArrayList *list){

	int index;

	if(list == NULL)	printf("(empty list)\n");
	if(getSize(list) == 0)	printf("(empty list)\n");

	for(index = 0; index < getSize(list); index++)
		printf("%s\n", get(list, index));
}
