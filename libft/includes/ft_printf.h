/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:59:52 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:50:33 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "ft_mem_utils.h"
# include "ft_string_utils.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>

# ifndef FT_PRINTF_FLAGS
#  define FT_PRINTF_FLAGS "-0# +"
# endif

# ifndef FT_PRINTF_SPECIFIERS
#  define FT_PRINTF_SPECIFIERS "cspdiuxX"
# endif

# ifndef FT_PRINTF_BASE10
#  define FT_PRINTF_BASE10 "0123456789"
# endif

# ifndef FT_PRINTF_BASE16
#  define FT_PRINTF_BASE16 "0123456789abcdef"
# endif

# ifndef FT_PRINTF_BASE16CAPS
#  define FT_PRINTF_BASE16CAPS "0123456789ABCDEF"
# endif

# ifndef FT_PRINTF_BUFFER_SIZE
#  define FT_PRINTF_BUFFER_SIZE 4096
# endif

typedef enum s_printf_error
{
	FT_PRINTF_OK = 0,
	FT_PRINTF_MALLOC_ERROR = -1337,
	FT_PRINTF_PARSE_ERROR = -42,
	FT_PRINTF_WIDTH_ERROR = -44,
	FT_PRINTF_PRECISION_ERROR = -55,
	FT_PRINTF_UNDEFINED_ERROR = -28,
}	t_printf_error;

typedef struct s_flags
{
	int		hyphen;
	int		zero;
	int		sharp;
	int		space;
	int		cross;
	int		width;
	int		precision;
	char	specifier;
}	t_flags;

typedef struct s_data
{
	size_t		count;
	va_list		*args;
	char		*buffer;
	size_t		buffer_idx;
	t_flags		flags;
}	t_data;

int		ft_atowp(const char **str);
int		ft_in(char *s, char c);
int		ft_nbrlen_base(long long int n, int base_len);
int		check_zero_int(t_data *data, long long int n);

void	ft_flush_buffer(t_data *data);
void	ft_write_buffer(t_data *data, int c);
void	ft_appendchar_buffer(t_data *data, int c, int n);
void	ft_appendstr_buffer(t_data *data, const char *str, int n);
void	ft_appendnbr_buffer(t_data *data, long long int n, \
		char *base, int base_len);

int		ft_printchar(t_data *data, int c);
int		ft_printstring(t_data *data, const char *str);
int		ft_printnbr(t_data *data, long long int n, char *base, int base_len);
int		ft_printaddr(t_data *data, uintptr_t n, char *base);

void	ft_format_addr(t_data *data);
int		ft_format(t_data *data, const char **sptr);
void	ft_format_specifier(t_data *data);
int		ft_printf(const char *str, ...);

#endif
