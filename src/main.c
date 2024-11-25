/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:25:43 by fcornill          #+#    #+#             */
/*   Updated: 2024/11/25 14:05:24 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse_map(t_data *data, const char *str)
{
	if (!check_extension(str))
	{
		free(data);
		exit(EXIT_FAILURE);
	}
	if (!get_file_data(str, data))
		return (false);
	if (!get_map(str, data))
	{
		free_arri(data->file);
		return (false);
	}
	if (!check_map(data))
	{
		free_ev(data);
		exit(EXIT_FAILURE);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (print_error("Error!\nFormat: <./cub3D> <map.cub>"),
			EXIT_FAILURE);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (print_error("Failed to initialize data"), EXIT_FAILURE);
	if (!parse_map(data, argv[1]))
	{
		free_ev(data);
		exit(EXIT_FAILURE);
	}
	data->speed = 0.2;
	init_mlx(data);
	init_text(data);
	mlx_loop_hook(data->mlx, input, data);
	mlx_loop(data->mlx);
	return (0);
}
