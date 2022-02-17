#include "test_utils.h"

Test(test_init, parse_times_from_argv)
{
	int		argc = 4;
	char	*argv[] = {"path", "1", "2", "3", "4"};

	t_shared_data	result =	create_philosopher_shared_data( \
											argc,(const char **) argv);

	cr_assert_eq(result.philo_count, 1);
	cr_assert_eq(result.time_to_die, 2);
	cr_assert_eq(result.time_to_eat, 3);
	cr_assert_eq(result.time_to_sleep, 4);
	free(result.forks);
}

Test(test_init, two_philosophers_have_two_forks_in_total)
{
	t_test_data t = set_up_n_philosophers(2);

	cr_assert_eq(t.local[0].left_fork, &t.shared.forks[1]);
	cr_assert_eq(t.local[0].right_fork, &t.shared.forks[0]);
	cr_assert_eq(t.local[1].left_fork, &t.shared.forks[0]);
	cr_assert_eq(t.local[1].right_fork, &t.shared.forks[1]);
	free(t.shared.forks);
}

Test(test_init, if_only_one_philosopher_left_fork_empty)
{
	t_test_data t = set_up_n_philosophers(1);

	cr_assert_null(t.local[0].left_fork);
	cr_assert_eq(t.local[0].right_fork, &t.shared.forks[0]);
	free(t.shared.forks);
}