/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrey-roj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:17:52 by jrey-roj          #+#    #+#             */
/*   Updated: 2024/09/16 12:17:54 by jrey-roj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (data.meals_to_eat == 0)
	{
		ft_destroy_data(&data);
		return (0);
	}
	if (data.philo_num == 1)
	{
		if (init_one_philo(&data))
			return (1);
	}
	else
	{
		if (init_threads(&data))
			return (1);
	}
	ft_destroy_data(&data);
	return (0);
}
