#include "inc/philo.h"

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (ft_error(INVALID_ARG, NULL));
	while (i < argc)
	{
		if (check_num(argv[i], i))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (check_args(argc, argv))
		return (1);
	if (init_all(argv, &data))
		return (1);
	if (init_thread(&data))
		return (1);
	ft_destroy_data(&data);
	return (0);
}

/*
1. Comprobar argumentos y crear funcion de error
2. Iniciar mallocs, mutex y philo
3. 
*/