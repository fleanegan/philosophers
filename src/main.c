#include "unistd.h"

#ifndef IS_TEST

int	main(void)
{
	write(1, "no test\n", 5);
	return (0);
}

#endif
