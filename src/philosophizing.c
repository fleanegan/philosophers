#include <stdio.h>
#include "philosophers.h"

void	init(const void *arg, t_local_data **data);
void	wait_every_other_round();
void	eating(t_local_data *data);
void	sleeping(t_local_data *data);
void	thinking(t_local_data *data);

void * philosophizing(void * arg)
{
	t_local_data	*data;

	init(arg, &data);
	while (1)
	{
		thinking(data);
		wait_every_other_round();
		eating(data);
		sleeping(data);
	}
	return (arg);
}

void eating(t_local_data *data)
{
	pthread_mutex_lock(data->left_fork);
	pthread_mutex_lock(data->right_fork);
	data->time_last_meal = get_day_ms();
	print_message(data, "is eating\n", 0);
	precise_wait(data->shared_data->time_to_eat);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
}

void	init(const void *arg, t_local_data **data)
{
	*data = (t_local_data*) arg;
	(*data)->time_init = get_day_ms();
	(*data)->time_last_meal = (*data)->time_init;
}

void	wait_every_other_round()
{
	static int	solidarity_switch = 0;

	solidarity_switch = ! solidarity_switch;
	if (solidarity_switch)
	{
		usleep(5);
		solidarity_switch = 0;
	}
}

void	sleeping(t_local_data *data)
{
	print_message(data, "is sleeping\n", 0);
	precise_wait(data->shared_data->time_to_sleep);
}

void	thinking(t_local_data *data)
{
	print_message(data, "is thinking\n", 0);
}
