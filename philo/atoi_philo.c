#include "inc/philo.h"

int	check_special_cases(long n, int index)
{
	if (n > INT_MAX)
		return (ft_error(INVALID_ARG, NULL));
	if (n == 0 && index != 5)
		return (ft_error(INVALID_ARG, NULL));
	if (index == 1 && n > 200)
		return (ft_error(INVALID_ARG, NULL));
	if ((index == 2 && n < 60 || index == 3 && n < 60) || index == 4 && n < 60)
		return (ft_error(INVALID_ARG, NULL));
	return (0);
}

int	check_num(char *num, int index)
{
	long	n;
	int		i;

	n = 0;
	i = 0;
	while (num[i])
		i++;
	if (i > 10)
		return (ft_error(INVALID_ARG, NULL));
	i = 0;
	while (num[i] != '\0')
	{
		if (num[i] >= '0' && num[i] <= '9')
		{
			n = n * 10;
			n = n + (num[i] - '0');
			i++;
		}
		else
			return (ft_error(INVALID_ARG, NULL));
	}
	if (check_special_cases(n, index))
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (str[i] != '\0')
	{
		n = n * 10;
		n = n + (str[i] - '0');
		i++;
	}
	return (n);
}