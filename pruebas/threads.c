#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void	*routine(void *args)
{
	int	*num;
	int i;

	num = (int *)args;
	i = 0;
	while (i < 100)
	{
		(*num)++;
		i++;
	}
	return (NULL);
}

void	exit_free(int *num, int exit_status)
{
	free(num);
	exit(exit_status);
}

void	*print_hello(void	*args)
{
	int	i = 0;

	while (i < 100)
	{
		printf("hello\n");
		i++;
		usleep(10000);
	}
	return (NULL);
}

void	*print_world(void *args)
{
	int i = 0;

	while (i < 100)
	{
		printf("World\n");
		i++;
		usleep(10000);
	}
	return (NULL);
}

void	example1(){

	print_hello(NULL);
	print_world(NULL);
}

void	example2(){
	pthread_t t1;
	pthread_t t2;
	if (pthread_create(&t1, NULL, print_hello, NULL))
		exit(1);
	if (pthread_create(&t2, NULL, print_world, NULL))
		exit(1);
	
	if (pthread_join(t1, NULL))
		exit(1);
	if (pthread_join(t2, NULL))
		exit(1);
}

void	example3(){
	int	*num;

	pthread_t t1;
	pthread_t t2;

	num = malloc(sizeof(int));
	if (!num)
		exit(1);
	*num = 0;
	if (pthread_create(&t1, NULL, routine, num))
		exit_free(num, 1);
	if (pthread_create(&t2, NULL, routine, num))
		exit_free(num, 1);
	
	if (pthread_join(t1, NULL))
		exit_free(num, 2);
	if (pthread_join(t2, NULL))
		exit_free(num, 2);
	printf("num: %d\n", *num);
}

int	main(){
	example3();
	return (0);
}

/*
USE MUTEX TO AVOID PROBLEMS WITH THE ROUTINE FUNCTIONS
*/