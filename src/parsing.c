/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschlute <fschlute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:47:02 by fschlute          #+#    #+#             */
/*   Updated: 2022/04/04 17:47:04 by fschlute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_containing_non_digit_chars(char *current_arg);
static int	is_trying_to_create_too_many_philosophers( \
			int argc, const char *current_arg);

int	is_input_valid(int argc, char **argv)
{
	int		ctr;
	char	*current_arg;

	if (argc < 5 || argc > 6)
	{
		ft_fast_putstr("please enter 4 or 5 parameter\n");
		return (0);
	}
	ctr = argc;
	while (--ctr)
	{
		current_arg = argv[ctr];
		if (is_trying_to_create_too_many_philosophers(ctr, current_arg) \
			|| is_containing_non_digit_chars(current_arg))
		{
			ft_fast_putstr("an error occurred while generating philosophers\n");
			return (0);
		}
	}
	return (1);
}

static	int	is_containing_non_digit_chars(char *current_arg)
{
	while (current_arg && *current_arg)
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
	return (! argc && ft_atoi_unsigned(current_arg) > MAX_THREADS);
}
