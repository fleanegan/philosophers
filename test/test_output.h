#include "test_utils.h"

Test(test_output, printing_at_second_zero_prints_seven_zeros_before_text)
{
	t_local_data	philosopher_data;
	memset(&philosopher_data, 0, sizeof (t_local_data));
	philosopher_data.time_init = get_day_ms();
	precise_wait(2);

	char	*result = generate_message(&philosopher_data, "has taken a fork");

	cr_assert_arr_eq(result, "0000002", 7 * sizeof(char), "act: %s", result);
	cr_assert_str_eq(result + 8, "philosopher 0 has taken a fork");
	free(result);
}