#include "test_utils.h"

Test(precise_wait, waiting_zero_milliseconds_does_nothing)
{
	unsigned int	start = get_day_ms();
	precise_wait(0);
	unsigned int	end = get_day_ms();

	cr_assert_eq(start, end, "act: %u", end - start);
}

Test(precise_wait, waiting_one_millisecond)
{
	unsigned int	start = get_day_ms();
	precise_wait(1);
	unsigned int	end = get_day_ms();

	cr_assert_eq(start, end - 1, "act: %u", end - start);
}

Test(test_timing, compare_itoa)
{
	unsigned int start = get_day_us();
	printf("012345\n");
	unsigned int end = get_day_us();
	printf("took %u to print with putnbr\n", end - start);

	start = get_day_us();
	ft_fast_putstr("012345\n");
	end = get_day_us();
	printf("took %u to print with itoa and fastput\n", end - start);
}
