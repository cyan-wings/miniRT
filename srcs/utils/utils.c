/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 00:00:00 by myeow             #+#    #+#             */
/*   Updated: 2025/10/01 00:00:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}

int	is_valid_extension(const char *filename, const char *ext)
{
	int	filename_len;
	int	ext_len;

	if (!filename || !ext)
		return (0);
	filename_len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (filename_len < ext_len)
		return (0);
	return (ft_strcmp(filename + filename_len - ext_len, ext) == 0);
}

void	error_exit(const char *message)
{
	ft_putendl_fd("Error", 2);
	if (message)
		ft_putendl_fd((char *)message, 2);
	exit(1);
}

void	cleanup_and_exit(t_minirt *minirt, const char *message)
{
	if (minirt)
	{
		cleanup_mlx(&minirt->mlx_data);
		objects_free(&minirt->scene);
	}
	error_exit(message);
}

char	**ft_split_whitespace(char const *s)
{
	if (!s)
		return (NULL);
	return (ft_split(s, ' '));
}

double	random_double(void)
{
	return ((double)rand() / ((double)RAND_MAX + 1.0));
}

double	random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}