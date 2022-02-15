int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int     ft_atoi_unsigned(const char *in)
{
	long int res;

	res = 0;
	while (ft_isdigit(*in))
		res = 10 * res + (*in++ - '0');
	return ((int) res);
}