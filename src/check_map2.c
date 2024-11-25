/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:20:37 by fcornill          #+#    #+#             */
/*   Updated: 2024/11/25 13:37:16 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_left_border(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 1;
	while (y < data->row - 1)
	{
		x = 0;
		while (data->map[y][x] == ' ' || data->map[y][x] == '\t')
			x++;
		if (data->map[y][x] != '1')
			return (false);
		y++;
	}
	return (true);
}

bool	check_right_border(t_data *data)
{
	size_t	y;
	size_t	x;
	size_t	len;

	y = 1;
	while (y < data->row - 1)
	{
		x = 0;
		len = ft_strlen(data->map[y]);
		while (x < len)
		{
			if ((x > ft_strlen(data->map[y - 1]) - 2 || x > \
ft_strlen(data->map[y + 1])) && data->map[y][x] == '0')
				return (false);
			if (x == len - 1 && (data->map[y][x - 1] != '1' && \
data->map[y][x - 1] != ' '))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	check_map_content(t_data *data)
{
	size_t	is_player;
	size_t	y;
	size_t	x;

	y = 0;
	is_player = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (!ft_strchr("10NWES", data->map[y][x]))
				return (print_error("Error: unexpected character in map"),
					false);
			if (ft_strchr("NSEW", data->map[y][x]))
				is_player++;
			x++;
		}
		y++;
	}
	if (is_player != 1)
		return (print_error("Error: There should be one player"), false);
	return (true);
}

void	set_direction(t_data *data, char direction)
{
	if (direction == 'N')
	{
		data->dirx = -1.0;
		data->planey = 0.66;
	}
	else if (direction == 'S')
	{
		data->dirx = 1.0;
		data->planey = -0.66;
	}
	else if (direction == 'E')
	{
		data->diry = 1.0;
		data->planex = 0.66;
	}
	else if (direction == 'W')
	{
		data->diry = -1.0;
		data->planex = -0.66;
	}
}

void	get_player_position(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				data->px = (double)y + 0.5;
				data->py = (double)x + 0.5;
				set_direction(data, data->map[y][x]);
				data->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
