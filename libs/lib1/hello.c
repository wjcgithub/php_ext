#include "hello.h"
#include <stdio.h>

char * show_site()
{
	char *site = malloc(12 * sizeof(char));
	strcpy(site, "www.abc.com");
	return site;
}

int main(int argc, char const *argv[])
{
	char *str = NULL;
	str = show_site();
	/* code */
	fprintf(stdout, "%s\n", str);
	return 0;
}