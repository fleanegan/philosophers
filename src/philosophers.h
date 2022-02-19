#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include "unistd.h"
# include <sys/time.h>
# include "unistd.h"
# include "stdlib.h"
# include <string.h>
# include <pthread.h>
# define MAX_THREADS 300
# define SPACE_NULLTERMIN 1

typedef struct s_shared_uint
{
	pthread_mutex_t mutex;
	unsigned int	value;
}       t_shared_uint;


typedef struct s_philosopher_shared_data
{
	int				philo_count;
	int				rounds_to_survive;
	unsigned int	time_to_sleep;
	unsigned int	time_to_eat;
	unsigned int	time_to_die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_token;
	int				death_record;
} 	t_shared_data;

typedef struct s_philosopher_local_data
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_shared_uint	time_last_meal;
	unsigned int	time_init;
	t_shared_data	*shared_data;
}	t_local_data;

//
void	*philosophizing(void * arg);
void run_threads(t_local_data **local);

// time
unsigned int	get_day_ms(void);
unsigned int	get_day_us(void);
void			precise_wait(int i);

// printing
int print_message(t_local_data *local, const char *message, int force_printing);
void    		ft_putnbr_fd(int nb, int fd);
void    		ft_fast_putstr(char *str);

// parsing
int				is_input_valid(int argc, char **argv);

// init
t_local_data	**set_up(int argc, char** argv);
t_shared_data * create_philosopher_shared_data( \
				int argc, const char **argv);
t_local_data * sit_down(t_shared_data *data, int id);
void			identify_my_forks(t_local_data *local, \
				t_shared_data *shared);
void initalize_muteces(t_shared_data *shared, t_local_data *local);

// helpers
int				ft_isdigit(int c);
int				ft_atoi_unsigned(const char *in);
char			*ft_itoa(int i);

// tear down
void			destroy_muteces(t_shared_data *shared);
void			free_2d_array(void **mem);

#endif //PHILOSOPHERS_H
