#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>

void	example_1()
{
	struct timeval time;
	if (gettimeofday(&time, NULL))
		return ;
	printf("%ld microseconds\n", time.tv_usec);
}

uint64_t	get_time(){
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / (uint64_t)1000));
}

void	example_2()
{
	uint64_t start_time;
	uint64_t now;

	start_time = get_time();
	usleep(1000000);
	now = get_time();
	printf("miliseconds passed: %ld", now - start_time);
}

int	main(void)
{
	example_1();
	example_2();
	return (0);
}

/*
APRENDE EL TIEMPO QUE TARDA EN CORRER EL PROGRAMA
SABER EL TIEMPO QUE HA HECHO UN SLEEP
*/