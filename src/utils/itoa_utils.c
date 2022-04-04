/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschlute <fschlute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:45:55 by fschlute          #+#    #+#             */
/*   Updated: 2022/04/04 17:46:01 by fschlute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

char	*allocate_memory_and_zero_init(\
			char **result, int digits_to_hold_number)
{
	*result = malloc(\
				sizeof(char) * (digits_to_hold_number + SPACE_NULLTERMIN));
	if (!*result)
		return (NULL);
	memset(*result, 0, digits_to_hold_number + SPACE_NULLTERMIN);
	return (*result);
}

int	calc_digits_in_number(int in)
{
	int				result;
	unsigned int	tmp;

	tmp = in;
	result = 1;
	if (! in)
		return (result);
	if (in < 0)
	{
		result++;
		tmp = -in;
	}
	while (tmp / 10 > 0)
	{
		result++;
		tmp = tmp / 10;
	}
	return (result);
}

void	translate_int_to_char_array(unsigned int n, char *result,
									int digits_to_hold_number)
{
	int	current_index;

	current_index = digits_to_hold_number - SPACE_NULLTERMIN;
	if (! n)
		result[0] = '0';
	while (n > 0)
	{
		result[current_index--] = '0' + (n % 10);
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	char			*result;
	int				digits_to_hold_number;
	unsigned long	tmp;

	tmp = n;
	if (n < 0)
		tmp = -n;
	digits_to_hold_number = calc_digits_in_number(n);
	result = allocate_memory_and_zero_init(&result, digits_to_hold_number);
	if (! result)
		return (NULL);
	translate_int_to_char_array(tmp, result, digits_to_hold_number);
	if (n < 0)
		result[0] = '-';
	return (result);
}
