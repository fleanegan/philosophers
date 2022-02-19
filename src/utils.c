#include <stdio.h>
#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t  ft_strlen(const char *s)
{
	size_t  len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

int     ft_atoi_unsigned(const char *in)
{
	long int res;

	res = 0;
	while (ft_isdigit(*in))
		res = 10 * res + (*in++ - '0');
	return ((int) res);
}

size_t  ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t  i;

	i = 0;
	if (! size)
		return (ft_strlen(src));
	while (src[i] && i < size - SPACE_NULLTERMIN)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}

size_t  ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t  dst_len;
	size_t  src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
	{
		return (src_len + size);
	}
	else
	{
		if (dst_len + src_len < size)
			ft_strlcpy(&dst[dst_len], src, src_len + SPACE_NULLTERMIN);
		else
			ft_strlcpy(&dst[dst_len], src, size - dst_len);
		return (dst_len + src_len);
	}
}


static void     translate_int_to_char_array(unsigned int n, char *result,
											int digits_to_hold_number);
static char     *allocate_memory_and_zero_init(char **result,
											   int digits_to_hold_number);
static int      calc_digits_in_number(int in);

int print_message(t_local_data *local, const char *message, int force_printing)
{
	unsigned int	time_since_zero;
	char			result[100];
	char			*time_str;
	char			*philosoph_id_str;
	size_t			current_len;

	time_since_zero = get_day_ms() - local->time_init;
	//printf("%u\n", time_since_zero);
	//return 1;
	current_len = 7;
	memset(result, '0', sizeof(char) * 100);
	time_str = ft_itoa(time_since_zero);
	ft_strlcpy(result + 7 - ft_strlen(time_str), time_str, ft_strlen(time_str) + 1);
	current_len = ft_strlcat(result, " philosopher ", current_len + ft_strlen(" philosopher ") + 1);
	philosoph_id_str = ft_itoa(local->id);
	current_len = ft_strlcat(result, philosoph_id_str, current_len + ft_strlen(philosoph_id_str) + 2);
	current_len = ft_strlcat(result, " ", current_len + ft_strlen(" ") + 1);
	current_len = ft_strlcat(result, message, current_len + ft_strlen(message) + 1);
	free(philosoph_id_str);
	free(time_str);
	if (force_printing)
	{
		ft_fast_putstr(result);
		return (0);
	}
	if (! local->shared_data->death_record)
	{
		pthread_mutex_lock(&local->shared_data->print_token);
		ft_fast_putstr(result);
		pthread_mutex_unlock(&local->shared_data->print_token);
	}
	return (0);
}

char    *ft_itoa(int n)
{
	char                    *result;
	int                             digits_to_hold_number;
	unsigned int    tmp;

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

static void     translate_int_to_char_array(unsigned int n, char *result,
											int digits_to_hold_number)
{
	int     current_index;

	current_index = digits_to_hold_number - SPACE_NULLTERMIN;
	if (! n)
		result[0] = '0';
	while (n > 0)
	{
		result[current_index--] = '0' + (n % 10);
		n = n / 10;
	}
}

static char     *allocate_memory_and_zero_init(char **result,
											   int digits_to_hold_number)
{
	*result = malloc(sizeof(char) * (digits_to_hold_number
									 + SPACE_NULLTERMIN));
	if (!*result)
		return (NULL);
	memset(*result, 0, digits_to_hold_number + SPACE_NULLTERMIN);
	return (*result);
}

static int      calc_digits_in_number(int in)
{
	int                             result;
	unsigned int    tmp;

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


void	ft_fast_putstr(char *str)
{
	int	size;

	size = ft_strlen(str);
	write(1, str, size);
}

static void     print_nbr(int i, int fd)
{
	write(1, &i, fd);
}

void    ft_putnbr_fd(int nb, int fd)
{
	unsigned int    nbr;

	if (nb < 0)
	{
		write(1, "-", fd);
		nbr = -nb;
	}
	else
		nbr = nb;
	if (nbr / 10 == 0)
		print_nbr(nbr + '0', fd);
	else
	{
		ft_putnbr_fd(nbr / 10, fd);
		print_nbr(nbr % 10 + '0', fd);
	}
}
