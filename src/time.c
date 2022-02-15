#include "philosophers.h"

unsigned long	get_day_ms(void)
{
	struct timeval tmp;
	gettimeofday(&tmp, NULL);
	return (tmp.tv_sec * 1000 + tmp.tv_usec / 1000);
}