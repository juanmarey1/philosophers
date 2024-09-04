#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

void	example1(){
	struct timeval	start;
	struct timeval	end;

	long	requested_sleep;
	long	actual_sleep;

	requested_sleep = 1000 * 1000;
	gettimeofday(&start, NULL);
	usleep(requested_sleep);
	gettimeofday(&end, NULL);
	actual_sleep = ((end.tv_sec - start.tv_sec) * 1000000) + ((end.tv_usec - start.tv_usec));
	printf("ACTUAL: %ld\n", actual_sleep);
	printf("REQUESTED: %ld\n", requested_sleep);
}

int	main(){
	example1();
	return (0);
}

/*
NO ES PRECISO EL TIEMPO DEL SLEEP CON GETTIMEOFDAY
*/