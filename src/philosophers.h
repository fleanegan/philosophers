#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include "unistd.h"
# include <sys/time.h>
# include "unistd.h"
# include <string.h>
# define MAX_THREADS 300

typedef struct t_philosopher_shared_data
{
	int	philo_count;
	int	rounds_to_survive;
	int	time_to_sleep;
	int	time_to_eat;
	int	time_to_die;
} 	t_philosopher_shared_data;

typedef struct s_philosopher_local_data
{
}	t_philosopher_local_data;

// time
unsigned long	get_day_ms(void);

// init
t_philosopher_shared_data create_philosopher_shared_data( \
							const int argc, const char **argv);
int							is_input_valid(int argc, char **argv);

// helpers
int							ft_isdigit(int c);
int							ft_atoi_unsigned(const char *in);


#endif //PHILOSOPHERS_H
