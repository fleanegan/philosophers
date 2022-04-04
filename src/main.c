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

int	update_death_record(t_local_data *local);

int	is_done(t_local_data **local);

void	*supervise(t_local_data **local)
{
	int				tmp;

	while (1)
	{
		pthread_mutex_lock(&local[0]->shared_data->general_lock);
		tmp = update_death_record(*local);
		pthread_mutex_unlock(&local[0]->shared_data->general_lock);
		if (tmp != 0)
		{
			print_message(*(local + tmp - 1), "died\n");
			return (local);
		}
		if (is_done(local))
		{
			ft_fast_putstr("everybody ate\n");
			return (local);
		}
		pthread_mutex_unlock(&local[0]->shared_data->general_lock);
		usleep(500);
	}
}

int	is_done(t_local_data **local)
{
	int	i;

	i = 0;
	while (i < local[0]->shared_data->philo_count)
	{
		if (local[i]->meal_count < local[0]->shared_data->rounds_to_survive)
			return (0);
		i++;
	}
	local[0]->shared_data->death_record = -1;
	return (1);
}

int	update_death_record(t_local_data *local)
{
	int				i;
	unsigned long	last_meal;
	unsigned long	time_to_die;
	unsigned long	now;

	i = 0;
	while (i < local[0].shared_data->philo_count)
	{
		last_meal = local->time_last_meal;
		time_to_die = local->shared_data->time_to_die;
		now = us_since_start(local);
		fflush(stdout);
		if (last_meal && now - last_meal > time_to_die)
		{
			local->shared_data->death_record = local->id;
			return (local->id);
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
	ft_fast_putstr("reached thread\n");
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
	ft_fast_putstr("is valid\n");
	local = set_up(argc, argv);
	ft_fast_putstr("set up done\n");
	if (! local)
		return (1);
	run_threads(local);
	destroy_muteces(local[0]->shared_data);
	free_shared(&local[0]->shared_data);
	free_2d_array((void **) local);
	return (0);
}

#endif
