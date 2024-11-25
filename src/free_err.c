/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:23:34 by fcornill          #+#    #+#             */
/*   Updated: 2024/11/25 11:41:05 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arri(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_ev(t_data *data)
{
	if (data->north)
		free(data->north);
	if (data->south)
		free(data->south);
	if (data->east)
		free(data->east);
	if (data->west)
		free(data->west);
	if (data->map)
		free_arri(data->map);
	if (data)
		free(data);
}

void	print_error(const char *msg)
{
	printf(RED "%s\n" RST, msg);
}
