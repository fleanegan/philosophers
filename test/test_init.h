#include "test_utils.h"

Test(test_init, parse_times_from_argv)
{
	int		argc = 4;
	char	*argv[] = {"path", "1", "2", "3", "4"};

	t_shared_data	*result =	create_philosopher_shared_data( \
											argc,(const char **) argv);

	cr_assert_eq(result->philo_count, 1);
	cr_assert_eq(result->time_to_die, 2);
	cr_assert_eq(result->time_to_eat, 3);
	cr_assert_eq(result->time_to_sleep, 4);
	free(result->forks);
}

Test(test_init, two_philosophers_have_two_forks_in_total)
{
	char	*argv[] = {"path", "2", "0", "0", "0"};
	t_local_data	**local = set_up(5, (char **) argv);

	cr_assert_not_null(local);
	cr_assert_not_null(local[0]);
	cr_assert_eq(local[0]->left_fork, &local[0]->shared_data->forks[1]);
	cr_assert_eq(local[0]->right_fork, &local[0]->shared_data->forks[0]);
	cr_assert_eq(local[1]->left_fork, &local[1]->shared_data->forks[0]);
	cr_assert_eq(local[1]->right_fork, &local[1]->shared_data->forks[1]);
	free(local[0]->shared_data->forks);
	free_2d_array((void **) local);
}

Test(test_init, if_only_one_philosopher_left_fork_empty)
{
	char	*argv[] = {"path", "1", "0", "0", "0"};
	t_local_data	**local = set_up(5, (char **) argv);

	cr_assert_not_null(local);
	cr_assert_not_null(local[0]);
	cr_assert_null(local[0]->left_fork);
	cr_assert_eq(local[0]->right_fork, &local[0]->shared_data->forks[0]);
	free(local[0]->shared_data->forks);
	free_2d_array((void **) local);
}