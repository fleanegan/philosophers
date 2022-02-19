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


void precise_wait(int i)
{
	unsigned int	start = get_day_ms();
	while (get_day_ms() != start + i)
		usleep(100);
	(void) i;
}
