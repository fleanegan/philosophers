#include <stdio.h>
#include "philosophers.h"

void	eat(t_local_data *data);
void	init(const void *arg, t_local_data **data);

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
void * philosophizing(void * arg)
{
	t_local_data	*data;

	init(arg, &data);
	while (1)
	{
		wait_every_other_round();
		eat(data);
	}
	return (arg);
}

void eat(t_local_data *data)
{
	pthread_mutex_lock(data->left_fork);
	pthread_mutex_lock(data->right_fork);
	unsigned int	tmp = data->time_last_meal;
	data->time_last_meal = get_day_ms();
	ft_putnbr_fd((int) (data->time_last_meal - tmp), 1);
	print_message(data, "is eating\n");
	//	printf("philosopher %d has started eating %u ms after start, which is %u after last meal\n",
//		   data->id, get_day_ms() - data->time_init, data->time_last_meal - tmp);
//		printf("	and took fork %p and %p \n", data->left_fork,
//			   data->right_fork);
	usleep(data->shared_data->time_to_eat * 1000);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
}

void init(const void *arg, t_local_data **data)
{
	*data = (t_local_data*) arg;
	(*data)->time_init = get_day_ms();
	(*data)->time_last_meal = (*data)->time_init;
}
