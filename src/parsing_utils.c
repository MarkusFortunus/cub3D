/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:26:16 by fcornill          #+#    #+#             */
/*   Updated: 2024/11/26 12:57:09 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_atoi_rgb(char *str)
{
	size_t	result;

	result = 0;
	while (*str == 'C' || *str == 'F' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (print_error("The number has been adjusted to 0"), 0);
		str++;
	}
	else if (*str < '0' || *str > '9')
		return (256);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str != '\n' && *str != '\0')
		return (print_error("Atoi: invalid trailing characters"), 256);
	if (result > 255)
		return (print_error("The number has been adjusted to 255"), 255);
	return (result);
}

size_t	rgb_to_hex(size_t red, size_t green, size_t blue, size_t alpha)
{
	return (((red & 0xFF) << 24) | ((green & 0xFF) << 16) \
	| ((blue & 0xFF) << 8) | ((alpha & 0xFF)));
}

char	*skip_space(char *s)
{
	while (*s && ft_strchr(" ", *s))
		s++;
	return (s);
}
