/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschlute <fschlute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:46:35 by fschlute          #+#    #+#             */
/*   Updated: 2022/04/04 17:46:54 by fschlute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"

int	update_death_record(t_local_data **local);

int	is_done(t_local_data **local);

void	*supervise(t_local_data **local)
{
	int				tmp;

	while (1)
	{
		pthread_mutex_lock(&local[0]->shared_data->general_lock);
		tmp = update_death_record(local);
		if (tmp != 0)
		{
			print_message(*(local + tmp - 1), "died\n");
			pthread_mutex_unlock(&local[0]->shared_data->general_lock);
			return (local);
		}
		if (is_done(local))
		{
			pthread_mutex_unlock(&local[0]->shared_data->general_lock);
			return (local);
		}
		pthread_mutex_unlock(&local[0]->shared_data->general_lock);
		usleep(1000);
	}
}

int	is_done(t_local_data **local)
{
	int	i;

	i = 0;
	while (i < local[0]->shared_data->philo_count)
	{
		if (local[0]->shared_data->rounds_to_survive < 0 \
			|| local[i]->meal_count < local[0]->shared_data->rounds_to_survive)
			return (0);
		i++;
	}
	local[0]->shared_data->death_record = -1;
	return (1);
}

int	update_death_record(t_local_data **local)
{
	int				i;
	unsigned long	last_meal;
	unsigned long	time_to_die;
	unsigned long	now;

	i = 0;
	while (i < local[0]->shared_data->philo_count)
	{
		last_meal = local[i]->time_last_meal;
		time_to_die = local[i]->shared_data->time_to_die;
		now = us_since_start(local[i]);
		if (last_meal && now - last_meal > time_to_die)
		{
			local[i]->shared_data->death_record = local[i]->id;
			return (local[i]->id);
		}
		i++;
	}
	return (0);
}

int	run_threads(t_local_data **local)
{
	pthread_t	*thread_ids;
	int			i;

	i = -1;
	thread_ids = malloc(sizeof(pthread_t) * local[0]->shared_data->philo_count);
	if (thread_ids == NULL)
		return (1);
	pthread_mutex_lock(&local[0]->shared_data->general_lock);
	while (++i < local[0]->shared_data->philo_count)
		if (pthread_create(\
			&thread_ids[i], NULL, philosophizing, local[i]))
			ft_fast_putstr("error while creating threads");
	local[0]->shared_data->time_start = get_day_us();
	pthread_mutex_unlock(&local[0]->shared_data->general_lock);
	supervise(local);
	i = -1;
	while (++i < local[0]->shared_data->philo_count)
		if (pthread_join(thread_ids[i], NULL))
			ft_fast_putstr("error while joining threads");
	free(thread_ids);
	return (0);
}

#ifndef IS_TEST

int	main(int argc, char **argv)
{
	t_local_data	**local;

	if (! is_input_valid(argc, argv))
		return (1);
	local = set_up(argc, argv);
	if (! local)
	{
		ft_fast_putstr("error\n");
		return (1);
	}
	run_threads(local);
	destroy_muteces(local[0]->shared_data);
	free_shared(&local[0]->shared_data);
	free_2d_array((void **) local);
	return (0);
}

#endif
