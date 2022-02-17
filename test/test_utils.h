#ifndef TEST_UTILS_H
# define TEST_UTILS_H

# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "philosophers.h"
# include "../src/philosophers.h"
#include "../criterion-v2.3.3/include/criterion/assert.h"
#include "../criterion-v2.3.3/include/criterion/criterion.h"
#include "../criterion-v2.3.3/include/criterion/redirect.h"
# include <criterion/criterion.h>
# include <criterion/theories.h>
# include <criterion/redirect.h>
# include <ctype.h>
# include <string.h>
# include <limits.h>

char	*ft_itoa(int n);

char **generate_argv(int n, int time_to_die, int time_to_eat, int time_to_sleep) {
	char	**argv = malloc(7 * sizeof(char *));
	argv[0] = "path";
	argv[1] = ft_itoa(n);
	argv[2] = ft_itoa(time_to_die);
	argv[3] = ft_itoa(time_to_eat);
	argv[4] = ft_itoa(time_to_sleep);
	argv[5] = "0";
	argv[6] = NULL;
	return argv;
}

int replacement_for_broken_criterion_stdout_matcher(char *compare_string, FILE *f_stream) {
	size_t read;
	char buf[1];
	size_t len = strlen(compare_string);
	size_t	ctr = 0;
	int matches = 1;

	while ((read = fread(buf, 1, sizeof(char), f_stream)) > 0) {
		ctr++;
		if (!compare_string || *buf != *compare_string++)
			matches = 0;
	}
	if (read)
		while (fread(buf, 1, sizeof (buf), f_stream) > 0) ctr++;
	if (len != ctr)
		matches = 0;
	return (matches);
}

void cr_bugfix_assert_str_stdout(char *compare_string)
{
	cr_assert(replacement_for_broken_criterion_stdout_matcher(compare_string, cr_get_redirected_stdout()));
}


#endif	 // TEST_UTILS_H
