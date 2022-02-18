#include "test_utils.h"

Test(test_output, printing_at_second_zero_prints_seven_zeros_before_text)
{
	t_local_data	philosopher_data;
	memset(&philosopher_data, 0, sizeof (t_local_data));
	philosopher_data.time_init = get_day_ms();
	precise_wait(2);

	cr_redirect_stdout();
	print_message(&philosopher_data, "has taken a fork", 0);

	cr_bugfix_assert_str_stdout("0000002 philosopher 0 has taken a fork");
}