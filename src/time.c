#include "philosophers.h"

unsigned int	get_day_us(void)
{
	struct timeval			tmp;

	gettimeofday(&tmp, NULL);
	return (tmp.tv_sec * 1000000 + tmp.tv_usec);
}

unsigned int	us_since_start(t_local_data *local)
{
	if (local == NULL || local->shared_data == NULL)
	{
		ft_fast_putstr("oh no");
		return (0);
	}
	return (get_day_us() - local->shared_data->time_start);
}

void	precise_wait_us(unsigned int i)
{
	usleep(i);
}
