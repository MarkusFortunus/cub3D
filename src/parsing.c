/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:28:35 by fcornill          #+#    #+#             */
/*   Updated: 2024/11/25 11:41:22 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_extension(const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 4 || ft_strncmp(&str[len - 4], ".cub", 4) != 0)
	{
		print_error("Error\nOnly files with the .cub extension are accepted!");
		return (false);
	}
	return (true);
}

bool	count_row(char **file, t_data *data)
{
	size_t	i;
	char	*line;

	i = 0;
	while (file[i])
	{
		line = skip_space(file[i]);
		if (*line == '1' || *line == '0')
			data->row++;
		i++;
	}
	if (data->row == 0)
		return (print_error("No map"), false);
	data->map = ft_calloc((data->row + 1), sizeof(char *));
	if (!data->map)
		return (print_error("Malloc: failed to initialize map"), false);
	if (!fill_map(data->file, data))
		return (false);
	return (true);
}

bool	fill_map(char **file, t_data *data)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	j = 0;
	while (file[i])
	{
		line = skip_space(file[i]);
		if (*line == '1' || *line == '0')
		{
			data->check_map = true;
			data->map[j] = ft_strdup(file[i]);
			j++;
		}
		if ((*line != '1' && *line != '0') && data->check_map)
			return (print_error("Invalid map"), false);
		i++;
	}
	data->map[j] = NULL;
	return (true);
}

bool	get_map(const char *file, t_data *data)
{
	size_t	i;
	int		fd;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error(strerror(errno)), false);
	data->file = ft_calloc((data->file_index + 1), sizeof(char *));
	while (i < data->file_index)
	{
		data->file[i] = get_next_line(fd);
		i++;
	}
	data->file[i] = NULL;
	close(fd);
	if (!count_row(data->file, data))
		return (false);
	free_arri(data->file);
	return (true);
}
