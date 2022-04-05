/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschlute <fschlute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:46:20 by fschlute          #+#    #+#             */
/*   Updated: 2022/04/04 17:46:22 by fschlute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	arrange_philo_with_forks(t_shared_data **shared, t_local_data **local)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(*shared)->general_lock, NULL))
		return (1);
	while (i < (*shared)->philo_count)
	{
		if (pthread_mutex_init(&(*shared)->forks[i], NULL))
			return (1);
		local[i] = sit_down((*shared), i + 1);
		if (! local[i])
			return (1);
		identify_my_forks(local[i], (*shared));
		i++;
	}
	return (0);
}

t_local_data	**set_up(int argc, char **argv)
{
	t_shared_data	*shared;
	t_local_data	**local;

	shared = create_philosopher_shared_data(argc, (const char **) argv);
	if (shared == NULL)
		return (NULL);
	local = malloc(sizeof(t_local_data *) * (shared->philo_count + 1));
	if (local == NULL)
	{
		free_shared(&shared);
		return (NULL);
	}
	local[shared->philo_count] = NULL;
	if (arrange_philo_with_forks(&shared, local))
	{
		free_2d_array((void **) local);
		free(shared);
		return (NULL);
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
	result->death_record = 0;
	result->philo_count = ft_atoi_unsigned(argv[1]);
	result->time_to_die = ft_atoi_unsigned(argv[2]) * 1000;
	result->time_to_eat = ft_atoi_unsigned(argv[3]) * 1000;
	result->time_to_sleep = ft_atoi_unsigned(argv[4]) * 1000;
	result->rounds_to_survive = 1;
	if (argc == 6)
		result->rounds_to_survive = ft_atoi_unsigned(argv[5]);
	result->forks = NULL;
	if (result->philo_count != 0)
		result->forks = malloc(sizeof(pthread_mutex_t) * result->philo_count);
	if (result->forks == NULL || result->time_to_die < 60000 \
		|| result->time_to_sleep < 60000 || result->time_to_eat < 60000 \
		|| result->rounds_to_survive == 0)
	{
		free(result->forks);
		free(result);
		return (NULL);
	}
	return (result);
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
	result->meal_count = 0;
	return (result);
}

void	identify_my_forks(t_local_data *local, t_shared_data *shared)
{
	int	left_id;
	int	right_id;

	right_id = local->id - 1;
	left_id = (local->id) % shared->philo_count;
	local->right_fork = &shared->forks[right_id];
	local->left_fork = &shared->forks[left_id];
	if (local->id % 2 == 0)
	{
		local->right_fork = &shared->forks[left_id];
		local->left_fork = &shared->forks[right_id];
	}
	if (right_id == left_id)
		local->left_fork = NULL;
}
