#include "test_utils.h"

Test(test_parse, argv_containing_non_digit_is_invalid)
{
	int		argc = 4;
	char	*argv[] = {"0c","1","2", "3"};

	cr_assert_not(is_input_valid(argc, argv));
}

Test(test_parse, argv_containing_only_containing_four_pure_digits_is_valid)
{
	int		argc = 4;
	char	*argv[] = {"0","1","2", "3"};

	cr_assert(is_input_valid(argc, argv));
}

Test(test_parse, fewer_args_than_four_is_invalid)
{
	int		argc = 1;
	char	*argv[] = {"0"};

	cr_assert_not(is_input_valid(argc, argv));
}

Test(test_parse, number_of_philosophers_should_be_smaller_than_LIMIT)
{
	int		argc = 4;
	char	*argv[] = {"301", "1","2", "3"};
	cr_assert_not(is_input_valid(argc, argv));
}

Test(test_parse, more_args_than_five_is_invalid)
{
	int		argc = 6;
	char	*argv[] = {"0","1","2", "3", "4", "5"};

	cr_assert_not(is_input_valid(argc, argv));
}
