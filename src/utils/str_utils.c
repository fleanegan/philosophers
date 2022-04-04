#include "../philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void	ft_fast_putstr(char *str)
{
	int	size;

	size = ft_strlen(str);
	write(1, str, size);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

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

int	print_message(t_local_data *local, const char *message)
{
	unsigned int	time_since_zero;
	char			result[100];
	char			*time_str;
	char			*philosoph_id_str;
	size_t			current_len;

	time_since_zero = us_since_start(local) / 1000;
	current_len = 7;
	memset(result, '0', sizeof(char) * 100);
	time_str = ft_itoa(time_since_zero);
	ft_strlcpy(result + 7 - ft_strlen(time_str), \
	time_str, ft_strlen(time_str) + 1);
	current_len = ft_strlcat(result, " ", \
	current_len + ft_strlen(" philosopher ") + 1);
	philosoph_id_str = ft_itoa(local->id);
	current_len = ft_strlcat(result, philosoph_id_str, \
	current_len + ft_strlen(philosoph_id_str) + 2);
	current_len = ft_strlcat(result, " ", current_len + ft_strlen(" ") + 1);
	ft_strlcat(result, message, current_len + ft_strlen(message) + 1);
	free(philosoph_id_str);
	free(time_str);
	if (local->shared_data->death_record != 0 && message[0] != 'd')
		return (-1);
	ft_fast_putstr(result);
	return (0);
}
