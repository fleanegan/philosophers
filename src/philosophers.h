/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschlute <fschlute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:44:49 by fschlute          #+#    #+#             */
/*   Updated: 2022/04/04 17:45:28 by fschlute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include "unistd.h"
# include <sys/time.h>
# include "unistd.h"
# include "stdlib.h"
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# define MAX_THREADS 200
# define SPACE_NULLTERMIN 1

typedef struct s_philosopher_shared_data
{
	long int		philo_count;
	long int		rounds_to_survive;
	unsigned long	time_start;
	unsigned long	time_to_sleep;
	unsigned long	time_to_eat;
	unsigned long	time_to_die;
	pthread_mutex_t	*forks;
	long int		death_record;
	pthread_mutex_t	general_lock;
}	t_shared_data;

typedef struct s_philosopher_local_data
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	unsigned long	time_last_meal;
	unsigned long	time_init;
	t_shared_data	*shared_data;
	int				meal_count;
}	t_local_data;

//
void			*philosophizing(void *arg);
int				run_threads(t_local_data **local);

// time
unsigned int	get_day_us(void);
unsigned int	us_since_start(t_local_data *local);
void			precise_wait_us(unsigned int i);
unsigned int	ref_since_0(void);

// printing
int				print_message(t_local_data *local, const char *message);
void			ft_putnbr_fd(int nb, int fd);
void			ft_fast_putstr(char *str);

// parsing
int				is_input_valid(int argc, char **argv);

// init
t_local_data	**set_up(int argc, char **argv);
t_shared_data	*create_philosopher_shared_data( \
				int argc, const char **argv);
t_local_data	*sit_down(t_shared_data *data, int id);
void			identify_my_forks(t_local_data *local, \
				t_shared_data *shared);
int				arrange_philo_with_forks(\
				t_shared_data **shared, t_local_data **local);

// helpers
int				ft_isdigit(int c);
int				ft_atoi_unsigned(const char *in);
char			*ft_itoa(int n);

// tear down
void			destroy_muteces(t_shared_data *shared);
void			free_2d_array(void **mem);
void			free_shared(t_shared_data **in);

#endif //PHILOSOPHERS_H
