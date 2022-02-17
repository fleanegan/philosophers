#include "test_utils.h"

Test(test_philosophers, slow_eating_causes_death)
{
	t_test_data	t = set_up_n_philosophers(2);

	t.shared.time_to_die = 0;
	t.shared.time_to_eat = 1000;

	run_threads(&t.shared, t.local);

	cr_assert_eq(t.shared.death_record.value, 1);
	destroy_muteces(t.local);
}
//printf("address of shared in local %p, real address %p\n", t.local[0].shared_data, &t.shared);

Test(test_philosophers, no_fast_eater_ever_dies)
{
	t_test_data	t = set_up_n_philosophers(2);
	initalize_muteces(&t.shared);
	t.shared.time_to_die = 1000;
	t.shared.time_to_eat = 0;

	run_threads(&t.shared, t.local);

	cr_assert_eq(t.shared.death_record.value, 0);
	destroy_muteces(t.local);
}