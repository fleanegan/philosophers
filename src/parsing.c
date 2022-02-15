#include "philosophers.h"

static int	is_containing_non_digit_chars(char *current_arg);
static int	is_trying_to_create_too_many_philosophers( \
			int argc, const char *current_arg);

int is_input_valid(int argc, char **argv)
{
	char	*current_arg;

	if (argc < 4 || argc > 5)
		return (0);
	while (argc--)
	{
		current_arg = argv[argc];
		if (is_trying_to_create_too_many_philosophers(argc, current_arg) \
			|| is_containing_non_digit_chars(current_arg))
			return (0);
	}
	return (1);
}

static	int is_containing_non_digit_chars(char *current_arg)
{
	while (*current_arg)
	{
		if (! ft_isdigit(*current_arg))
			return (1);
		current_arg++;
	}
	return (0);
}

static int	is_trying_to_create_too_many_philosophers( \
			int argc, const char *current_arg)
{
	return ! argc && ft_atoi_unsigned(current_arg) > MAX_THREADS;
}
