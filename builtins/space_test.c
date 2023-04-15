#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>



int main (void)
{

        char *args[] = {"echo", "-l","-a",  NULL};
        execve("/bin/echo", args, NULL);
		return (0);
}
