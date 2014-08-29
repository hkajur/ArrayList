#include <stdio.h>
#include <string.h>
#include "ArrayList.h"

// Does this segfault for you? If so, you might be re-allocating your entire
// array list struct inside the expandArrayList() function. Since there's no way
// to get that pointer back to myList in main() via the put() function, you
// should ensure that your expandArrayList() function only re-allocates the
// array *within* the array list struct. (I.e., leave the struct intact, but
// stuff a new array inside of it.)

int main(void)
{
	int i; char myString[100], *temp;
	ArrayList *myList = createArrayList(10);

	// add some strings to the array list
	for (i = 0; i < 30; i++)
	{
		// format my string
		sprintf(myString, "(string %02d)", i);

		// add string to end of array list
		temp = put(myList, myString);

		// print a little notification that the string was added
		printf("Added string: %s\n", temp);
	}

	// print out the contents of the array list.
	printArrayList(myList);

	return 0;
}
