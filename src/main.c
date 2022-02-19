#include <stdio.h>
#include "philosophers.h"

void	*supervise(void *arg)
{
	t_local_data	**local;
	unsigned int	current_time;
	unsigned int	last_meal;
	unsigned int	time_to_die;

	local = (t_local_data **)arg;
	while (1)
	{
		///*
		current_time = get_day_us();
		for (int i = 0; i < local[0]->shared_data->philo_count; i++)
		{
			pthread_mutex_lock(&local[i]->time_last_meal.mutex);
			last_meal = local[i]->time_last_meal.value * 1000;
			time_to_die = local[0]->shared_data->time_to_die * 1000;
			if (last_meal && current_time - last_meal > time_to_die)
			{
				//pthread_mutex_lock(&local[i]->shared_data->print_token);
				local[0]->shared_data->death_record = local[i]->id;
				print_message(local[i], "died\n", 1);
				//pthread_mutex_unlock(&local[i]->shared_data->print_token);
				//printf("curr %u, last %u, time to die %u, did not eating since %u\n", current_time, last_meal, time_to_die, current_time - last_meal);
				return (arg);
			}
			pthread_mutex_unlock(&local[i]->time_last_meal.mutex);
			//else printf("curr %u, last %u, time to die %u, did not eating since %u\n", current_time, last_meal, time_to_die, current_time - last_meal);
		}
		//*/
		usleep(500);

	}

		(void) local;
		(void) current_time;
		(void) last_meal;
		(void) time_to_die;
		return arg;
}

void run_threads(t_local_data **local)
{
	pthread_t threadId[local[0]->shared_data->philo_count];
	initalize_muteces(local[0]->shared_data, *local);
	for (int i = 0; i < local[0]->shared_data->philo_count; i++)
		if (pthread_create(&threadId[i], NULL, philosophizing, local[i]))
			puts("error while creating threads");
	supervise((void* )local);
}

#ifndef IS_TEST

int	main(int argc, char **argv)
{
	t_local_data	**local;

	if (! is_input_valid(argc, argv))
		return (1);
	ft_fast_putstr("is valid\n");
	local = set_up(5, argv);
	ft_fast_putstr("set up done\n");
	if (! local)
		return (1);
	ft_fast_putstr("reached thread\n");
	run_threads(local);
	return (0);
}

#endif
