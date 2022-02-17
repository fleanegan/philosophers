#include <stdio.h>
#include "philosophers.h"

void die_if_necessary(t_local_data *data);

void * philosophizing(void * arg)
{
	t_local_data	*data;

	data = (t_local_data*) arg;
	data->time_init = get_day_ms();
	data->time_last_meal = data->time_init;
	///*
	pthread_mutex_lock(data->left_fork);
	pthread_mutex_lock(data->right_fork);
	printf("philosopher %d has started eating %u ms after start\n", data->id, get_day_ms() - data->time_init);
	printf("	and took fork %p and %p \n", data->left_fork, data->right_fork);
	usleep(data->shared_data->time_to_eat * 1000);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	//die_if_necessary(data);
	return (arg);
}

void die_if_necessary(t_local_data *data) {
	///*
	pthread_mutex_lock(&data->shared_data->death_record.mutex);
	printf("did not eat since %u, tolerance %u\n", get_day_ms() - data->time_last_meal , data->shared_data->time_to_die);
	if (! data->shared_data->death_record.value \
		&& get_day_ms() - data->time_last_meal > data->shared_data->time_to_die)
	{
		puts("died");
		data->shared_data->death_record.value++;
	}
	//*/
	pthread_mutex_unlock(&data->shared_data->death_record.mutex);
}
