/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrey-roj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:18:01 by jrey-roj          #+#    #+#             */
/*   Updated: 2024/09/16 12:18:02 by jrey-roj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	*routine_one_philo(void	*data_in_void)
{
	t_data	*data;
	int		time;

	data = (t_data *)data_in_void;
	time = get_current_time() - data->start_t;
	printf("%d %d %s\n", time, data->philos[0].id, FORK);
	ft_usleep(data->death_t, data);
	time = get_current_time() - data->start_t;
	printf("%d %d %s\n", time, data->philos[0].id, DEAD);
	return ((void *)0);
}

int	init_one_philo(t_data *data)
{
	pthread_t	t_one_philo;

	data->start_t = get_current_time();
	if (pthread_create(&t_one_philo, NULL, &routine_one_philo, data))
		ft_error(ERR_PHILO, data);
	if (pthread_join(t_one_philo, NULL))
		ft_error(ERR_JOIN, data);
	return (0);
}

void	*monitor(void	*data)
{
	t_data	*supervisor;
	int		j;

	supervisor = (t_data *)data;
	ft_wait_for_all_threads(supervisor);
	while (supervisor->dead == 0 && supervisor->finished
		< supervisor->philo_num)
	{
		j = -1;
		while ((++j < supervisor->philo_num && supervisor->dead == 0)
			&& (supervisor->finished < supervisor->philo_num))
		{
			pthread_mutex_lock(supervisor->philos[j].eat);
			if (((get_current_time() - supervisor->philos[j].last_ate)
					> supervisor->death_t) && supervisor->philos[j].eating != 1)
			{
				supervisor->dead = 1;
				ft_messages(DEAD, &supervisor->philos[j]);
			}
			pthread_mutex_unlock(supervisor->philos[j].eat);
		}
	}
	return ((void *)0);
}

void	*routine(void	*argv)
{
	t_philo	*philo;

	philo = (t_philo *)argv;
	ft_wait_for_all_threads(philo->data);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->eat_t / 2, philo->data);
	while (philo->data->dead == 0 && philo->data->finished
		< philo->data->philo_num)
	{
		if (philo->meals_count == philo->data->meals_to_eat)
			break ;
		ft_eat(philo);
		ft_messages(SLEEP, philo);
		ft_usleep(philo->data->sleep_t, philo->data);
		ft_messages(THINK, philo);
	}
	return ((void *)0);
}

int	init_threads(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_create(&data->monitor_thread, NULL, &monitor, data))
		ft_error(ERR_MONITOR, data);
	while (++i < data->philo_num)
	{
		data->philos[i].last_ate = get_current_time();
		if (pthread_create(&(data->philo_threads[i]),
				NULL, &routine, &data->philos[i]))
			ft_error(ERR_PHILO, data);
	}
	data->start_t = get_current_time();
	data->init_mutex = 0;
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->philo_threads[i], NULL))
			ft_error(ERR_JOIN, data);
	}
	if (pthread_join(data->monitor_thread, NULL))
		ft_error(ERR_JOIN, data);
	return (0);
}
