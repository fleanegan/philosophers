#include <stdio.h>
#include "philosophers.h"

void	init(const void *arg, t_local_data **data);

void	eating(t_local_data *data);
void	sleeping(t_local_data *data);
void	thinking(t_local_data *data);

void * philosophizing(void * arg)
{
	t_local_data	*data;
	char			toggle;

	init(arg, &data);
	toggle = 0;
	while (++toggle)
	{
		thinking(data);
		if (toggle % 2 == data->id % 2)
		{
			toggle = data->id % 2 + 1;
			precise_wait(data->shared_data->time_to_eat * 0.85);
		}
		eating(data);
		sleeping(data);
	}
	return (arg);
}


void eating(t_local_data *data)
{
	if (data->left_fork == data->right_fork)
	{
		print_message(data, "help, my forks are the same!", 0);
		data->shared_data = 0;
	}
	pthread_mutex_lock(&data->time_last_meal.mutex);
	pthread_mutex_lock(data->right_fork);
	print_message(data, "took a fork\n", 0);
	pthread_mutex_lock(data->left_fork);
	print_message(data, "took a fork\n", 0);
	data->time_last_meal.value = get_day_ms();
	print_message(data, "is eating\n", 0);
	precise_wait(data->shared_data->time_to_eat);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	pthread_mutex_unlock(&data->time_last_meal.mutex);
}

void	init(const void *arg, t_local_data **data)
{
	*data = (t_local_data*) arg;
	(*data)->time_init = get_day_ms();
	pthread_mutex_lock(&(*data)->time_last_meal.mutex);
	(*data)->time_last_meal.value = (*data)->time_init;
	pthread_mutex_unlock(&(*data)->time_last_meal.mutex);
}

void	sleeping(t_local_data *data)
{
	print_message(data, "is sleeping\n", 0);
	precise_wait(data->shared_data->time_to_sleep);
}

void	thinking(t_local_data *data)
{
	print_message(data, "is thinking\n", 0);
	(void) data;
}
