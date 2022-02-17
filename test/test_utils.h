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
# include <criterion/criterion.h>
# include <criterion/theories.h>
# include <criterion/redirect.h>
# include <ctype.h>
# include <string.h>
# include <limits.h>

typedef struct s_test_data
{
	t_shared_data shared;
	t_local_data local[9];
} t_test_data;


char **generate_argv_for_n_LESS_THAN_TEN(int n);

t_test_data	set_up_n_philosophers(int n)
{
	t_test_data	t;
	char **argv = generate_argv_for_n_LESS_THAN_TEN(n);
	t.shared =	create_philosopher_shared_data( \
											5,(const char **) argv);
	free(argv[1]);
	free(argv);
	for (int i = 0; i < n; i++)
	{
		t.local[i] = sit_down(&t.shared, i + 1);
		identify_my_forks(&t.local[i], &t.shared);
	}
	return (t);
}

char **generate_argv_for_n_LESS_THAN_TEN(int n) {
	char	**argv = malloc(5 * sizeof(char *));
	argv[0] = "path";
	argv[1] = malloc(sizeof (char) * 2);
	argv[1][0] = '0' + n;
	argv[1][1] = 0;
	argv[2] = "0";
	argv[3] = "0";
	argv[4] = "0";
	return argv;
}

#endif	 // TEST_UTILS_H
