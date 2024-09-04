#include "inc/philo.h"

void	ft_messages(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_current_time() - philo->data->start_t;
	if (philo->data->dead == 0 && philo->data->finished != philo->data->philo_num)
		printf("%d %d %s\n", time, philo->id, str);
	if (philo->data->dead == 1 && str == DEAD)
		printf("%d %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_messages(FORK, philo);
	pthread_mutex_lock(philo->l_fork);
	ft_messages(FORK, philo);
	pthread_mutex_lock(&philo->data->eat);
	philo->eating == 1;
	philo->meals_count++;
	philo->last_ate == get_current_time();
	ft_messages(EAT, philo);
	ft_usleep(philo->data->eat_t);
	if (philo->meals_count == philo->data->meals_to_eat)
		philo->data->finished++;
	pthread_mutex_unlock(&philo->data->eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	ft_messages(SLEEP, philo);
	ft_usleep(philo->data->sleep_t);
}