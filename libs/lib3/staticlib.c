#include "staticlib.h"

char * static_show()
{
	char *site = malloc(15 * sizeof(char));
	strcpy(site, "www.abcd.com");
	return site;
}