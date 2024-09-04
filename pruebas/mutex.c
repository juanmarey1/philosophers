#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct data_s{
	int	num;
	pthread_mutex_t mutex;
} data_t;

data_t *init_data()
{
	data_t	*data;

	data = malloc(sizeof(data_t));
	if (!data)
		exit(1);
	data->num = 0;
	pthread_mutex_init(&data->mutex, NULL);
	return (data);
}

void	free_data(data_t *data)
{
	pthread_mutex_destroy(&data->mutex);
	free(data);
}

void	exit_error(data_t *data, int exit_status)
{
	free(data);
	exit(exit_status);
}

void	*routine (void *args)
{
	data_t *data;
	int	i = 0;

	data = (data_t *)args;
	while (i < 100000000)
	{
		pthread_mutex_lock(&data->mutex);
		data->num++;
		pthread_mutex_unlock(&data->mutex);
		i++;
	}
	return (NULL);
}

void	example()
{
	data_t	*data;
	pthread_t t1;
	pthread_t t2;

	data = init_data();
	if (pthread_create(&t1, NULL, routine, data))
		exit_error(data, 2);
	if (pthread_create(&t2, NULL, routine, data))
		exit_error(data, 2);
	if (pthread_join(t1, NULL))
		exit_error(data, 3);
	if (pthread_join(t2, NULL))
		exit_error(data, 3);
	printf("Num: %d\n", data->num);
	free_data(data);
}

int	main()
{
	example();
	return (0);
}