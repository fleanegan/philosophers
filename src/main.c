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
		current_time = get_day_ms();
		for (int i = 0; i < local[0]->shared_data->philo_count; i++)
		{
			last_meal = local[i]->time_last_meal;
			time_to_die = local[0]->shared_data->time_to_die;
			if (last_meal && current_time - last_meal > time_to_die)
			{
				printf("philosoph %d died \n", local[i]->id);
				printf("curr %u, last %u, time to die %u, did not eat since %u\n", current_time, last_meal, time_to_die, current_time - last_meal);
				local[0]->shared_data->death_record.value = local[i]->id;
				return (arg);
			}
			else
			{
//				printf("curr %u, last %u, time to die %u, did not eat since %u\n", current_time, last_meal, time_to_die, current_time - last_meal);
//				printf("philo no %d did not eat since %u\n", local[i]->id, current_time - last_meal);
//				puts("\n");
			}
		}
		usleep(5);
	}
	(void) current_time;
	(void) local;
}
//		printf("philo count %d\n", local[0]->shared_data->philo_count);

void	run_threads(t_shared_data *shared, t_local_data **local) {
	if (! shared || ! local)
	{
		puts("run threads received NULL");
		return ;
	}
	pthread_t threadId[shared->philo_count];
	initalize_muteces(shared);
	for (int i = 0; i < shared->philo_count; i++)
		if (pthread_create(&threadId[i], NULL, philosophizing, local[i]))
			puts("error while creating threads");
	printf("in programm: address of shared in local %p, real address %p\n", local[0]->shared_data, shared);
	supervise((void* )local);
	(void) local;
	(void) threadId;
}

#ifndef IS_TEST

int	main(int argc, char **argv)
{
	printf("argc : %d, first %s\n", argc, argv[1]);
	printf("day time in ms: %u\n", get_day_ms());
	return (0);
}

#endif
