#include "test_utils.h"

Test(precise_wait, waiting_zero_milliseconds_does_nothing)
{
	unsigned int	start = get_day_ms();
	precise_wait(0);
	unsigned int	end = get_day_ms();

	cr_assert_eq(start, end);
}

Test(precise_wait, waiting_one_millisecond)
{
	unsigned int	start = get_day_ms();
	precise_wait(1);
	unsigned int	end = get_day_ms();

	cr_assert_eq(start, end - 1);
}

//Test(test_timing, compare_itoa)
//{
//	unsigned int start = get_day_us();
//	ft_putnbr_fd(INT_MAX, 1);
//	unsigned int end = get_day_us();
//	printf("took %u to print with putnbr\n", end - start);
//
//	start = get_day_us();
//	char *a = ft_itoa(INT_MAX);
//	ft_fast_putstr(a);
//	free(a);
//	end = get_day_us();
//	printf("took %u to print with itoa and fastput\n", end - start);
//}
