/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophizing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschlute <fschlute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:47:12 by fschlute          #+#    #+#             */
/*   Updated: 2022/04/04 17:47:18 by fschlute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init(const void *arg, t_local_data **data);
int		eating(t_local_data *data);
int		sleeping(t_local_data *data);
int		thinking(t_local_data *data);

void	*philosophizing(void *arg)
{
	t_local_data	*data;

	init(arg, &data);
	while (1)
	{
		if (data->shared_data->philo_count <= 1)
			return (arg);
		if (data->shared_data->death_record != -1 \
			|| thinking(data) == -1 \
			|| eating(data) == -1 \
			|| sleeping(data) == -1)
		{
			pthread_mutex_unlock(&(data)->shared_data->general_lock);
			return (arg);
		}
	}
	return (arg);
}

int	eating(t_local_data *data)
{
	pthread_mutex_lock(data->left_fork);
	pthread_mutex_lock(&(data)->shared_data->general_lock);
	if (data->shared_data->death_record != 0)
	{
		pthread_mutex_unlock(data->left_fork);
		return (-1);
	}
	print_message(data, "has taken a fork\n");
	pthread_mutex_unlock(&(data)->shared_data->general_lock);
	pthread_mutex_lock(data->right_fork);
	pthread_mutex_lock(&(data)->shared_data->general_lock);
	if (data->shared_data->death_record != 0)
	{
		pthread_mutex_unlock(data->right_fork);
		pthread_mutex_unlock(data->left_fork);
		return (-1);
	}
	print_message(data, "has taken a fork\n");
	data->time_last_meal = us_since_start(data);
	print_message(data, "is eating\n");
	pthread_mutex_unlock(&(data)->shared_data->general_lock);
	precise_wait_us(data->shared_data->time_to_eat);
	pthread_mutex_unlock(data->right_fork);
	pthread_mutex_unlock(data->left_fork);
	return (0);
}

void	init(const void *arg, t_local_data **data)
{
	*data = (t_local_data *) arg;
	pthread_mutex_lock(&(*data)->shared_data->general_lock);
	(*data)->time_init = us_since_start(*data);
	(*data)->time_last_meal = (*data)->time_init;
	print_message(*data, "is thinking\n");
	pthread_mutex_unlock(&(*data)->shared_data->general_lock);
	if ((*data)->id % 2)
		precise_wait_us((*data)->shared_data->time_to_eat);
	if ((*data)->id == 1 && (*data)->shared_data->philo_count % 2)
		precise_wait_us((*data)->shared_data->time_to_eat / 2);
}

int	sleeping(t_local_data *data)
{
	pthread_mutex_lock(&(data)->shared_data->general_lock);
	if (data->shared_data->death_record != 0)
		return (-1);
	data->meal_count++;
	print_message(data, "is sleeping\n");
	pthread_mutex_unlock(&(data)->shared_data->general_lock);
	precise_wait_us(data->shared_data->time_to_sleep);
	return (0);
}

int	thinking(t_local_data *data)
{
	pthread_mutex_lock(&(data)->shared_data->general_lock);
	if (data->shared_data->death_record != 0)
		return (-1);
	if (data->meal_count)
		print_message(data, "is thinking\n");
	pthread_mutex_unlock(&(data)->shared_data->general_lock);
	if (data->shared_data->philo_count % 2 && data->meal_count > 0)
		usleep(2 * data->shared_data->time_to_eat \
				+ data->shared_data->time_to_sleep \
				- (us_since_start(data) - data->time_last_meal));
	return (0);
}
