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
		current_time = get_day_us();
		for (int i = 0; i < local[0]->shared_data->philo_count; i++)
		{
			last_meal = local[i]->time_last_meal * 1000;
			time_to_die = local[0]->shared_data->time_to_die * 1000;
			if (last_meal && current_time - last_meal > time_to_die)
			{
				pthread_mutex_lock(&local[i]->shared_data->print_token);
				print_message(local[i], "died\n");
				local[0]->shared_data->death_record = local[i]->id;
				pthread_mutex_unlock(&local[i]->shared_data->print_token);
				//printf("curr %u, last %u, time to die %u, did not eating since %u\n", current_time, last_meal, time_to_die, current_time - last_meal);
				return (arg);
			}
			//else printf("curr %u, last %u, time to die %u, did not eating since %u\n", current_time, last_meal, time_to_die, current_time - last_meal);
		}
		usleep(5);
	}
}

void	run_threads(t_shared_data *shared, t_local_data **local)
{
	pthread_t threadId[shared->philo_count];
	initalize_muteces(shared);
	for (int i = 0; i < shared->philo_count; i++)
		if (pthread_create(&threadId[i], NULL, philosophizing, local[i]))
			puts("error while creating threads");
	supervise((void* )local);
}

#ifndef IS_TEST

int	main(int argc, char **argv)
{
	printf("argc : %d, first %s\n", argc, argv[1]);
	printf("day time in ms: %u\n", get_day_ms());
	return (0);
}

#endif
