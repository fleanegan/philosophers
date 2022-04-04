/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tear_down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschlute <fschlute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:47:28 by fschlute          #+#    #+#             */
/*   Updated: 2022/04/04 17:47:29 by fschlute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_muteces(t_shared_data *shared)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&shared->general_lock);
	while (i < shared->philo_count)
	{
		pthread_mutex_destroy(&shared->forks[i]);
		i++;
	}
}

void	free_2d_array(void **mem)
{
	void	**sav;

	sav = mem;
	if (mem == NULL)
		return ;
	while (*mem)
		free(*mem++);
	free(sav);
}

void	free_shared(t_shared_data **in)
{
	free_2d_array((void **)(*in)->forks);
	free(*in);
	*in = NULL;
}
