#include "wt.h"
 
char * show_site()
{
    char *site = malloc(15 * sizeof(char));
    strcpy(site, "123.abcd.456");
    return site;
}