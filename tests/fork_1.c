#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>





int fork_funk(int i, int end)
{
	pid_t   pid;
    int     n;
	int 	a;
	
	if (i < end) 	
	{
    	pid = 1;
    	n = 0;

    	while (n++ < 3 && pid)
    	{
			
        	pid = fork ();

        	if (!pid)
        	{
				if (n == 3)
				{
					a = 0;
					while (a < 1000000)
						a++;
				}
            	printf ("child %i from  parent%i \n", n, i);
				if (n == 1)
					fork_funk(i + 1, end);
        	}
    	}
		if (pid)
		{
			while ( n--)
				waitpid(-1, NULL, 0);
			printf("parent %i finsihed\n", i);	
		}
		else
			printf("child %i | parrent %i finsihed\n", n - 1, i);	
		return (0);
	
	}
	return (1);
}	



int main (void)
{

	int i;
	int end;
	
	i = 1;
	end = 3;
	fork_funk(i, end);
	
	
	return (0);
}	
	
	
