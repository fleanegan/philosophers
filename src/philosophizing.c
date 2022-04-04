#include "philosophers.h"

void	init(const void *arg, t_local_data **data);
int		eating(t_local_data *data);
int		sleeping(t_local_data *data);
int		thinking(t_local_data *data);

void	*philosophizing(void *arg)
{
	t_local_data	*data;

	init(arg, &data);
	while (1)
	{
		if (data->shared_data == NULL)
			ft_fast_putstr("nonono\n");
		if (data->shared_data->philo_count <= 1 \
			|| thinking(data) == -1 \
			|| eating(data) == -1 \
			|| sleeping(data) == -1)
		{
			pthread_mutex_unlock(&(data)->shared_data->general_lock);
			return (arg);
		}
		if (data->shared_data->philo_count % 2)
			usleep(500);
	}
	return (arg);
}

int	eating(t_local_data *data)
{
	pthread_mutex_lock(data->left_fork);
	pthread_mutex_lock(&(data)->shared_data->general_lock);
	if (data->shared_data->death_record != 0)
	{
		pthread_mutex_unlock(data->left_fork);
		return (-1);
	}
	print_message(data, "has taken a fork\n");
	pthread_mutex_unlock(&(data)->shared_data->general_lock);
	pthread_mutex_lock(data->right_fork);
	pthread_mutex_lock(&(data)->shared_data->general_lock);
	if (data->shared_data->death_record != 0)
	{
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		return (-1);
	}
	print_message(data, "has taken a fork\n");
	data->time_last_meal = us_since_start(data);
	print_message(data, "is eating\n");
	pthread_mutex_unlock(&(data)->shared_data->general_lock);
	precise_wait_us(data->shared_data->time_to_eat);
	pthread_mutex_unlock(data->right_fork);
	pthread_mutex_unlock(data->left_fork);
	return (0);
}

void	init(const void *arg, t_local_data **data)
{
	*data = (t_local_data *) arg;
	pthread_mutex_lock(&(*data)->shared_data->general_lock);
	(*data)->time_init = us_since_start(*data);
	(*data)->time_last_meal = (*data)->time_init;
	pthread_mutex_unlock(&(*data)->shared_data->general_lock);
	if ((*data)->id % 2)
		precise_wait_us((*data)->shared_data->time_to_eat);
	if ((*data)->id == 1 && (*data)->shared_data->philo_count % 2)
		precise_wait_us((*data)->shared_data->time_to_eat / 2);
}

int	sleeping(t_local_data *data)
{
	pthread_mutex_lock(&(data)->shared_data->general_lock);
	if (data->shared_data->death_record != 0)
		return (-1);
	data->meal_count++;
	print_message(data, "is sleeping\n");
	pthread_mutex_unlock(&(data)->shared_data->general_lock);
	precise_wait_us(data->shared_data->time_to_sleep);
	return (0);
}

int	thinking(t_local_data *data)
{
	pthread_mutex_lock(&(data)->shared_data->general_lock);
	if (data->shared_data->death_record != 0)
		return (-1);
	print_message(data, "is thinking\n");
	pthread_mutex_unlock(&(data)->shared_data->general_lock);
	return (0);
}
