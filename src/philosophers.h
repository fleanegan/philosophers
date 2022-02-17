#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include "unistd.h"
# include <sys/time.h>
# include "unistd.h"
# include "stdlib.h"
# include <string.h>
# include <pthread.h>
# define MAX_THREADS 300

typedef struct s_shared_int
{
	pthread_mutex_t	mutex;
	int				value;
}	t_shared_int;

typedef struct s_philosopher_shared_data
{
	int				philo_count;
	int				rounds_to_survive;
	unsigned int	time_to_sleep;
	unsigned int	time_to_eat;
	unsigned int	time_to_die;
	pthread_mutex_t	*forks;
	t_shared_int	death_record;
} 	t_shared_data;

typedef struct s_philosopher_local_data
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	unsigned int	time_last_meal;
	unsigned int	time_init;
	t_shared_data	*shared_data;
}	t_local_data;

//
void	*philosophizing(void * arg);
void	run_threads(t_shared_data *shared, t_local_data *local);

// time
unsigned int	get_day_ms(void);

// parsing
int				is_input_valid(int argc, char **argv);

// init
t_shared_data	create_philosopher_shared_data( \
				int argc, const char **argv);
t_local_data	sit_down(t_shared_data *data, int id);
void			identify_my_forks(t_local_data *local, \
				t_shared_data *shared);
void initalize_muteces(t_shared_data *shared);

// helpers
int				ft_isdigit(int c);
int				ft_atoi_unsigned(const char *in);

// tear down
void destroy_muteces(t_local_data *local_data);

#endif //PHILOSOPHERS_H
