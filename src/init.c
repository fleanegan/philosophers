#include "philosophers.h"

t_philosopher_shared_data	create_philosopher_shared_data( \
							const int argc, const char **argv)
{
	t_philosopher_shared_data	result;

	memset(&result, 0, sizeof(result));
	result.philo_count = ft_atoi_unsigned(argv[1]);
	result.time_to_die = ft_atoi_unsigned(argv[2]);
	result.time_to_eat = ft_atoi_unsigned(argv[3]);
	result.time_to_sleep = ft_atoi_unsigned(argv[4]);
	if (argc == 5)
		result.rounds_to_survive = ft_atoi_unsigned(argv[4]);
	else
		result.rounds_to_survive = 1;
	// TODO: result.forks =
	return (result);
}