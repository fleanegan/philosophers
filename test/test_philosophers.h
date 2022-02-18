#include "test_utils.h"

Test(test_philosophers, no_eating_if_dying_instanty, .disabled=1)
{
	char	**argv = generate_argv(2, 0, 1000, 0);
	t_local_data	**local = set_up(5, argv);
	cr_assert_eq(local[0]->shared_data->philo_count, 2);

	cr_redirect_stdout();
	run_threads(local[0]->shared_data, local);

	cr_bugfix_assert_str_stdout("0000000 philosopher 1 is thinking\n0000000 philosopher 1 died\n");
	cr_assert_eq(local[0]->shared_data->death_record, 1);
	destroy_muteces(local[0]->shared_data);
}

Test(test_philosophers, slow_eating_causes_death, .disabled=0)
{
	char	**argv = generate_argv(2, 10, 1000, 0);
	t_local_data	**local = set_up(5, argv);
	cr_assert_eq(local[0]->shared_data->philo_count, 2);

	cr_redirect_stdout();
	run_threads(local[0]->shared_data, local);

	cr_bugfix_assert_str_stdout("0000000 philosopher 1 is thinking\n0000000 philosopher 2 is thinking\n0000000 philosopher 2 is eating\n0000010 philosopher 1 died\n");
	cr_assert_eq(local[0]->shared_data->death_record, 1);
	destroy_muteces(local[0]->shared_data);
}

Test(test_philosophers, no_fast_eater_ever_dies, .disabled=1)
{
	char	**argv = generate_argv(2, 1000, 100, 0);
	t_local_data	**local = set_up(5, argv);
	cr_assert_eq(local[0]->shared_data->philo_count, 2);

	run_threads(local[0]->shared_data, local);

	cr_assert_eq(local[0]->shared_data->death_record, 0);
	destroy_muteces(local[0]->shared_data);
}
