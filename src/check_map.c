/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:18:52 by fcornill          #+#    #+#             */
/*   Updated: 2024/11/26 13:05:46 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_line_border(char *line)
{
	size_t	x;

	x = 0;
	while (line[x])
	{
		if (line[x] != '1' && line[x] != ' ' && line[x] != '\n')
			return (false);
		x++;
	}
	return (true);
}

static bool	check_borders(t_data *data)
{
	if (!check_line_border(data->map[0])
		|| !check_line_border(data->map[data->row - 1]))
		return (false);
	if (!check_left_border(data) || !check_right_border(data))
		return (false);
	return (true);
}

static bool	check_invalid_space_at(t_data *data, size_t y, size_t x)
{
	size_t	len;

	len = ft_strlen(data->map[y]);
	if (x > 0 && data->map[y][x - 1] == ' ')
		return (false);
	if (x < len - 1 && data->map[y][x + 1] == ' ')
		return (false);
	if (y > 0 && x < ft_strlen(data->map[y - 1]) && data->map[y - 1][x] == ' ')
		return (false);
	if (y < data->row && x < ft_strlen(data->map[y + 1]) && \
data->map[y + 1][x] == ' ')
		return (false);
	return (true);
}

static bool	check_invalide_space(t_data *data)
{
	size_t	y;
	size_t	x;
	size_t	len;

	y = 0;
	while (y < data->row)
	{
		x = 0;
		while (data->map[y][x] == ' ')
			x++;
		len = ft_strlen(data->map[y]);
		while (x < len)
		{
			if (data->map[y][x] == '0' && !check_invalid_space_at(data, y, x))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	check_map(t_data *data)
{
	if (!check_borders(data))
		return (print_error("Error\nMap is not closed"), false);
	if (!check_invalide_space(data))
		return (print_error("Error\nMap has unclosed spaces"), false);
	replace_space(data);
	if (!check_map_content(data))
		return (false);
	get_player_position(data);
	return (true);
}
