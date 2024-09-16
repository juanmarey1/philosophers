/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrey-roj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:16:53 by jrey-roj          #+#    #+#             */
/*   Updated: 2024/09/16 12:16:56 by jrey-roj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	ft_wait_for_all_threads(t_data *data)
{
	pthread_mutex_lock(&data->init);
	while (data->init_mutex)
		;
	pthread_mutex_unlock(&data->init);
}

void	ft_messages(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_current_time() - philo->data->start_t;
	if (philo->data->dead == 0 && philo->data->finished
		!= philo->data->philo_num)
		printf("%d %d %s\n", time, philo->id, str);
	if (philo->data->dead == 1 && ft_strncmp(str, DEAD) == 0)
		printf("%d %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_messages(FORK, philo);
	pthread_mutex_lock(philo->l_fork);
	ft_messages(FORK, philo);
	pthread_mutex_lock(philo->eat);
	philo->eating = 1;
	philo->meals_count++;
	philo->last_ate = get_current_time();
	ft_messages(EAT, philo);
	if (philo->meals_count == philo->data->meals_to_eat)
		philo->data->finished++;
	ft_usleep(philo->data->eat_t, philo->data);
	philo->eating = 0;
	pthread_mutex_unlock(philo->eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
