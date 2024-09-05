#ifndef	PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdint.h>

# define INVALID_ARG "Invalid arguments"
# define MALLOC_ERR "Malloc error"
# define ERR_MONITOR "Monitor thread error"
# define ERR_PHILO "Philosopher thread error"
# define ERR_JOIN "Thread join error"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

struct s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				meals_count;
	int				status;
	int				eating;
	size_t			last_ate;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t *eat;
}	t_philo;

typedef struct	s_data
{
	int				init_mutex;
	int				philo_num;
	int				meals_to_eat;
	int				dead;
	int				finished;
	pthread_t		monitor_thread;
	pthread_t		*philo_threads;
	t_philo			*philos;
	size_t			death_t;
	size_t			eat_t;
	size_t			sleep_t;
	size_t			start_t;
	pthread_mutex_t	init;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t *eat_mutex;
}	t_data;

void	ft_destroy_data(t_data *data);
int		ft_error(char *str, t_data	*data);

int	check_num(char *num, int index);

int	ft_atoi(char *str);
int	ft_strncmp(const char *s1, const char *s2);

size_t	get_current_time(void);
void	ft_usleep(size_t	time, t_data *data);
void	ft_eat(t_philo *philo);

int	init_all(char **argv, t_data *data);

int		init_threads(t_data *data);
void	ft_messages(char *str, t_philo *philo);

#endif