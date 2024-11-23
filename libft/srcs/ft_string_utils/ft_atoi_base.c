/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:03:56 by myeow             #+#    #+#             */
/*   Updated: 2024/08/07 21:55:51 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

static int	get_val(int *hash_tab, char c)
{
	unsigned char	c2;

	c2 = c;
	return (hash_tab[(int)c2]);
}

static void	set_val(int *hash_tab, char c, int val)
{
	unsigned char	c2;

	c2 = c;
	hash_tab[(int)c2] = val;
}

static int	find_base(char *base, int *hash_tab)
{
	int	b;

	b = -1;
	while (++b < 256)
		hash_tab[b] = -1;
	b = -1;
	while (base[++b])
	{
		if (get_val(hash_tab, base[b]) != -1)
			return (0);
		if (base[b] == '+' || base[b] == '-' || is_space(base[b]))
			return (0);
		set_val(hash_tab, base[b], b);
	}
	return (b);
}

int	ft_atoi_base(char *str, char *base)
{
	int				b;
	int				hash_tab[256];
	int				i;
	int				sign;
	long long int	result;

	b = find_base(base, hash_tab);
	if (b < 2)
		return (0);
	i = 0;
	while (is_space(str[i]) && str[i])
		++i;
	sign = 1;
	while ((str[i] == '-' || str[i] == '+') && str[i])
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	result = 0;
	while (get_val(hash_tab, str[i]) != -1)
	{
		result = result * b + get_val(hash_tab, str[i]);
		++i;
	}
	return ((int)(result * sign));
}
