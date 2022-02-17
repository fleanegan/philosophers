#include "philosophers.h"

void destroy_muteces(t_local_data *local_data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&local_data->shared_data->death_record.mutex);
	while (i < local_data->shared_data->philo_count)
	{
		pthread_mutex_destroy(&local_data->shared_data->forks[i]);
		i++;
	}
}