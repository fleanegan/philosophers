#include "philosophers.h"

unsigned int	get_day_ms(void)
{
	struct timeval tmp;
	gettimeofday(&tmp, NULL);
	return (tmp.tv_sec * 1000 + tmp.tv_usec / 1000);
}

unsigned int	get_day_us(void)
{
	struct timeval tmp;
	gettimeofday(&tmp, NULL);
	return (tmp.tv_sec * 1000000 + tmp.tv_usec);
}


void precise_wait_(int i)
{
	unsigned int	start = get_day_us();
	while (get_day_us() < start + i * 1000)
		usleep(5);
	(void) i;
}

void	precise_wait(int msec)
{
	unsigned int		start;
	unsigned int		now;
	unsigned int		waited;
	unsigned int		goal;
	unsigned int	wait_interval;

	wait_interval = 70;
	goal = msec * 1000;
	start = get_day_us();
	now = get_day_us();
	waited = now - start;
	while (waited < goal)
	{
			usleep(wait_interval);
		now = get_day_us();
		waited = now - start;
	}
}
