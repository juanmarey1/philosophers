/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrey-roj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:17:38 by jrey-roj          #+#    #+#             */
/*   Updated: 2024/09/16 12:17:40 by jrey-roj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	ft_strncmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_destroy_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->eat_mutex[i]);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->init);
	if (data->eat_mutex)
		free(data->eat_mutex);
	if (data->philo_threads)
		free(data->philo_threads);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

int	ft_error(char *str, t_data	*data)
{
	printf("%s\n", str);
	if (data)
		ft_destroy_data(data);
	return (1);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return (time.tv_sec * 1000
		+ (time.tv_usec / 1000));
}

void	ft_usleep(size_t	time, t_data *data)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(data->philo_num * 2);
}
