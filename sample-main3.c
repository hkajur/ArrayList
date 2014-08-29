#include <stdio.h>
#include "ArrayList.h"

void nullAssert(void *ptr, char *s)
{
	if (ptr != NULL)
		printf("ERROR: %s failed to return NULL as required.\n", s);
}

int main(void)
{
	char *str = NULL;

	ArrayList *myList = createArrayList(0);
	ArrayList *list = NULL;

	list = destroyArrayList(NULL);
	nullAssert(list, "destroyArrayList()");

	str = put(myList, NULL);
	nullAssert(str, "put()");

	str = get(NULL, -1);
	nullAssert(str, "get() (1/2)");

	str = get(myList, -1);
	nullAssert(str, "get() (2/2)");

	return 0;
}
