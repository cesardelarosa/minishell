/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:53:37 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/03/02 18:58:39 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_int_power(int base, int exp)
{
	int	result;

	result = 1;
	while (exp > 0)
	{
		result *= base;
		exp--;
	}
	return (result);
}

static char	*ft_pad_fraction(const char *frac_str, int precision)
{
	int		len;
	int		diff;
	char	*pad;
	char	*result;
	int		i;

	len = ft_strlen(frac_str);
	if (len >= precision)
		return (ft_strdup(frac_str));
	diff = precision - len;
	pad = malloc(diff + 1);
	if (!pad)
		return (NULL);
	i = 0;
	while (i < diff)
	{
		pad[i] = '0';
		i++;
	}
	pad[i] = '\0';
	result = ft_strjoin(pad, frac_str);
	free(pad);
	return (result);
}

static char	*ft_join_parts(const char *int_str, const char *frac_str, int sign)
{
	char	*tmp;
	char	*result;
	char	*final;

	tmp = ft_strjoin(int_str, ".");
	result = ft_strjoin(tmp, frac_str);
	free(tmp);
	if (sign)
	{
		final = ft_strjoin("-", result);
		free(result);
		return (final);
	}
	return (result);
}

static char	*ft_get_fraction(double n, long long int_part, int precision)
{
	double		fraction;
	int			power;
	long long	frac_val;
	char		*frac_str;
	char		*padded_frac;

	fraction = n - int_part;
	power = ft_int_power(10, precision);
	frac_val = (long long)(fraction * power + 0.5);
	frac_str = ft_itoa(frac_val);
	padded_frac = ft_pad_fraction(frac_str, precision);
	free(frac_str);
	return (padded_frac);
}

char	*ft_ftoa(double n, int precision)
{
	int			sign;
	long long	int_part;
	char		*int_str;
	char		*padded_frac;
	char		*result;

	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	int_part = (long long)n;
	int_str = ft_itoa(int_part);
	padded_frac = ft_get_fraction(n, int_part, precision);
	result = ft_join_parts(int_str, padded_frac, sign);
	free(int_str);
	free(padded_frac);
	return (result);
}
