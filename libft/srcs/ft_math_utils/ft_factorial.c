/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_factorial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:24:31 by myeow             #+#    #+#             */
/*   Updated: 2024/08/10 22:30:12 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FACTORIAL_MAX 20

unsigned long long	ft_factorial(int x)
{
	static unsigned long long	factorial_cache[FACTORIAL_MAX + 1] = {1};
	unsigned long long			dst;

	if (x < 0)
		return (0);
	if (x == 0)
		return (1);
	if (x <= FACTORIAL_MAX)
	{
		if (factorial_cache[x] == 0)
			factorial_cache[x] = x * ft_factorial(x - 1);
		return (factorial_cache[x]);
	}
	dst = 1;
	while (x > 1)
		dst *= num--;
	return (dst);
}
