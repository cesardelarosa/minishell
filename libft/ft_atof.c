/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-la-r <code@cesardelarosa.xyz>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:27:41 by cde-la-r          #+#    #+#             */
/*   Updated: 2025/02/19 12:50:32 by cde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static const char	*skip_whitespace(const char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

static int	parse_sign(const char **str_ptr)
{
	int	sign;

	sign = 1;
	if (**str_ptr == '+' || **str_ptr == '-')
	{
		if (**str_ptr == '-')
			sign = -1;
		(*str_ptr)++;
	}
	return (sign);
}

static double	parse_integer(const char **str_ptr)
{
	double	result;

	result = 0;
	while (**str_ptr >= '0' && **str_ptr <= '9')
	{
		result = result * 10 + (**str_ptr - '0');
		(*str_ptr)++;
	}
	return (result);
}

static double	parse_fraction(const char **str_ptr)
{
	double	frac;
	double	div;

	frac = 0;
	div = 10;
	if (**str_ptr == '.')
	{
		(*str_ptr)++;
		while (**str_ptr >= '0' && **str_ptr <= '9')
		{
			frac += ((**str_ptr - '0') / div);
			div *= 10;
			(*str_ptr)++;
		}
	}
	return (frac);
}

double	ft_atof(const char *str)
{
	double	result;
	double	frac;
	int		sign;

	str = skip_whitespace(str);
	sign = parse_sign(&str);
	result = parse_integer(&str);
	frac = parse_fraction(&str);
	return (sign * (result + frac));
}
