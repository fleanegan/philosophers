#include <stdio.h>
#include "philosophers.h"

void	*supervise(void *arg)
{
	t_local_data	*local;
	unsigned int	current_time;

	local = (t_local_data *)arg;
	while (1)
	{
		current_time = get_day_ms();
		printf("philo count %d\n", local->shared_data->philo_count);
		for (int i = 0; i < local->shared_data->philo_count - 1; i++) {
			if (current_time - local[i].time_last_meal > local->shared_data->time_to_die)
			{
				printf("philosoph %d died \n", local[i].id);
				printf("curr %u, last %u, time to die %u\n", current_time, local[i].time_last_meal, local[i].shared_data->time_to_die);
			}
			else
				puts("test");
		}
		/*for (int i = 0; i < local[i].shared_data->philo_count; i++)
			if (current_time - local[i].time_last_meal > local[i].shared_data->time_to_die)
			{
				printf("curr %u, last %u, time to die %u\n", current_time, local[i].time_last_meal, local[i].shared_data->time_to_die);
				printf("philosoph %d died \n", local[i].id);
				return (arg);
			}*/
		usleep(50000000);
	}
	(void) current_time;
	(void) local;
}

void	run_threads(t_shared_data *shared, t_local_data *local) {
	pthread_t threadId[shared->philo_count];
	pthread_t supervisor;
	for (int i = 0; i < shared->philo_count; i++)
		local[i].shared_data = shared;
	initalize_muteces(shared);
	for (int i = 0; i < shared->philo_count; i++)
		if (pthread_create(&threadId[i], NULL, philosophizing, &local[i]))
			puts("error while creating threads");
	usleep(100);
	pthread_create(&supervisor, NULL, supervise, local);
	for (int i = 0; i < shared->philo_count; i++)
		if ( pthread_detach(threadId[i]))
			puts("error while joining threads");
	pthread_join(supervisor, NULL);
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
