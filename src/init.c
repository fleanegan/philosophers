#include <stdio.h>
#include "philosophers.h"

t_local_data	**set_up(int argc, char** argv)
{
	t_shared_data	*shared;
	t_local_data	**local;

	shared = create_philosopher_shared_data(argc, (const char **) argv);
	local = malloc(sizeof(t_local_data *) * (shared->philo_count + 1));
	if (! local)
		return (NULL);
	local[shared->philo_count] = NULL;
	for (int i = 0; i < shared->philo_count; i++)
	{
		local[i] = sit_down(shared, i + 1);
		if (! local[i])
		{
			free_2d_array((void **) local);
			return (NULL);
		}
		identify_my_forks(local[i], shared);
	}
	return (local);
}

t_shared_data	*create_philosopher_shared_data( \
							const int argc, const char **argv)
{
	t_shared_data	*result;

	result = malloc(sizeof(t_shared_data));
	if (! result)
		return (NULL);
	result->philo_count = ft_atoi_unsigned(argv[1]);
	result->time_to_die = ft_atoi_unsigned(argv[2]);
	result->time_to_eat = ft_atoi_unsigned(argv[3]);
	result->time_to_sleep = ft_atoi_unsigned(argv[4]);
	if (argc == 5)
		result->rounds_to_survive = ft_atoi_unsigned(argv[4]);
	else
		result->rounds_to_survive = 1;
	result->forks = malloc(sizeof(pthread_mutex_t) * result->philo_count);
	if (! result->forks)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

void initalize_muteces(t_shared_data *shared)
{
	int	i;

	i = 0;
	pthread_mutex_init(&shared->death_record.mutex, NULL);
	while (i < shared->philo_count)
	{
		pthread_mutex_init(&shared->forks[i], NULL);
		i++;
	}
}

t_local_data	*sit_down(t_shared_data *data, int id)
{
	t_local_data	*result;

	result = malloc(sizeof(t_local_data));
	if (! result)
		return (NULL);
	result->id = id;
	result->shared_data = data;
	result->time_init = 0;
	result->time_last_meal = 0;
	return (result);
}

void	identify_my_forks(t_local_data *local, t_shared_data *shared)
{
	int	left_id;
	int	right_id;

	right_id = local->id - 1;
	left_id = (local->id) % shared->philo_count;
	local->right_fork = &shared->forks[right_id];
	if (right_id == left_id)
		local->left_fork = NULL;
	else
		local->left_fork = &shared->forks[left_id];
}
// 	printf("own id: %d, left: %d, right: %d\n", local->id, left_id, right_id);