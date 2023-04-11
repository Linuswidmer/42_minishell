#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>


int main (void)
{
	struct dirent *d;
	
	DIR *dh;

	dh = opendir("./");

	while ((d = readdir(dh)) != NULL)
		printf("%s  ", d->d_name);
	return (0);
}


