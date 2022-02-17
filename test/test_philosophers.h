#include "test_utils.h"

Test(test_philosophers, slow_eating_causes_death)
{
	char	**argv = generate_argv(2, 0, 1000, 0);
	t_local_data	**local = set_up(5, argv);
	cr_assert_eq(local[0]->shared_data->philo_count, 2);

	run_threads(local[0]->shared_data, local);

	cr_assert_eq(local[0]->shared_data->death_record.value, 1);
	destroy_muteces(local[0]->shared_data);
}

Test(test_philosophers, no_fast_eater_ever_dies, .disabled=0)
{
	char	**argv = generate_argv(2, 1000, 100, 0);
	t_local_data	**local = set_up(5, argv);
	cr_assert_eq(local[0]->shared_data->philo_count, 2);

	run_threads(local[0]->shared_data, local);

	cr_assert_eq(local[0]->shared_data->death_record.value, 0);
	destroy_muteces(local[0]->shared_data);
}
