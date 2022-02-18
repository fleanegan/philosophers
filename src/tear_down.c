#include "philosophers.h"

void destroy_muteces(t_shared_data *shared)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&shared->death_record.mutex);
	pthread_mutex_destroy(&shared->print_token);
	while (i < shared->philo_count)
	{
		pthread_mutex_destroy(&shared->forks[i]);
		i++;
	}
}

void    free_2d_array(void **mem)
{
	void    **sav;

	sav = mem;
	while (*mem)
		free(*mem++);
	free(sav);
}