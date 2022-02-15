#include <stdio.h>
#include "philosophers.h"

#ifndef IS_TEST

int	main(int argc, char **argv)
{
	printf("argc : %d, first %s\n", argc, argv[1]);
	printf("day time in ms: %lu\n", get_day_ms());
	return (0);
}

#endif
