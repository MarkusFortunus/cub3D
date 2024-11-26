/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:28:02 by fcornill          #+#    #+#             */
/*   Updated: 2024/11/26 13:07:11 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_custom_strdup(const char *s1)
{
	char	*s_dup;
	size_t	len;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	s_dup = malloc(len * sizeof(char));
	if (s_dup == NULL)
		return (NULL);
	ft_strcpy(s_dup, s1);
	return (s_dup);
}

void	replace_space(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < data->row)
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == ' ' || data->map[y][x] == '\n')
				data->map[y][x] = '1';
			x++;
		}
		y++;
	}
}
