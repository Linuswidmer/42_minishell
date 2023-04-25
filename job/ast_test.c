#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>


int main (void)
{
	struct dirent *d;
	
	DIR *dh;

	dh = opendir("./");

	while ((d = readdir(dh)) != NULL)
		printf("%s  ", d->d_name);
	dh = opendir("./");
	while ((d = readdir(dh)) != NULL)
        printf("%s  ", d->d_name);

	free(dh);
	return (0);
}


