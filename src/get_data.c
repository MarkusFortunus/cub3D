/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:24:04 by fcornill          #+#    #+#             */
/*   Updated: 2024/11/25 15:39:45 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture_path(char *line, t_data *data, int flag)
{
	while (*line && *line != '.')
		line++;
	if (*line == '.')
	{
		if (flag == 1 && !data->north)
			data->north = ft_custom_strdup(line);
		else if (flag == 1 && data->north)
			data->check++;
		else if (flag == 2 && !data->south)
			data->south = ft_custom_strdup(line);
		else if (flag == 2 && data->south)
			data->check++;
		else if (flag == 3 && !data->east)
			data->east = ft_custom_strdup(line);
		else if (flag == 3 && data->east)
			data->check++;
		else if (flag == 4 && !data->west)
			data->west = ft_custom_strdup(line);
		else if (flag == 4 && data->west)
			data->check++;
	}
}

void	get_floor_ceiling_color(char *line, t_data *data, int flag)
{
	size_t	red;
	size_t	green;
	size_t	blue;
	char	**color;

	color = ft_split(line, ',');
	if (!color)
		return (print_error("Malloc failed"));
	else if (!color[0] || !color[1] || !color[2] || color[3] != NULL)
		return (free_arri(color));
	red = ft_atoi_rgb(color[0]);
	green = ft_atoi_rgb(color[1]);
	blue = ft_atoi_rgb(color[2]);
	if (red == 256 || green == 256 || blue == 256)
	{
		data->color_floor = false;
		return (free_arri(color), print_error("Wrong color value"));
	}
	else if (flag == 1 && !data->floor)
		data->floor = rgb_to_hex(red, green, blue, 255);
	else if (flag == 2 && !data->ceiling)
		data->ceiling = rgb_to_hex(red, green, blue, 255);
	else
		data->check++;
	free_arri(color);
}

void	scan_line(char *line, t_data *data)
{
	line = skip_space(line);
	if (!ft_strncmp(line, "NO", 2))
		get_texture_path(line, data, 1);
	else if (!ft_strncmp(line, "SO", 2))
		get_texture_path(line, data, 2);
	else if (!ft_strncmp(line, "EA", 2))
		get_texture_path(line, data, 3);
	else if (!ft_strncmp(line, "WE", 2))
		get_texture_path(line, data, 4);
	else if (!ft_strncmp(line, "F", 1))
	{
		data->color_ceiling = true;
		get_floor_ceiling_color(line, data, 1);
	}
	else if (!ft_strncmp(line, "C", 1))
	{
		data->color_floor = true;
		get_floor_ceiling_color(line, data, 2);
	}
	else if (*line && *line != '1' && *line != '0' && *line != '\n')
		data->check++;
}

bool	check_data(t_data *data)
{
	if ((!data->north || !data->south || !data->east || !data->west
			|| !data->color_floor || !data->color_ceiling) || data->check != 0)
		return (print_error("Error: Invalid file"), false);
	return (true);
}

bool	get_file_data(const char *file, t_data *data)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error(strerror(errno)), false);
	line = get_next_line(fd);
	while (line)
	{
		data->file_index++;
		scan_line(line, data);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!check_data(data))
		return (false);
	return (true);
}
