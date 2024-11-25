/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:25:18 by fcornill          #+#    #+#             */
/*   Updated: 2024/11/25 11:25:34 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	key_a(t_data *data)
{
	double	olddirx;
	double	oldplanex;

	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(0.1) - data->diry * sin(0.1);
		data->diry = olddirx * sin(0.1) + data->diry * cos(0.1);
		oldplanex = data->planex;
		data->planex = data->planex * cos(0.1) - data->planey * sin(0.1);
		data->planey = oldplanex * sin(0.1) + data->planey * cos(0.1);
	}
}

static void	key_d(t_data *data)
{
	double	oldplanex;
	double	olddirx;

	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(-(0.1)) - data->diry * sin(-(0.1));
		data->diry = olddirx * sin(-(0.1)) + data->diry * cos(-(0.1));
		oldplanex = data->planex;
		data->planex = data->planex * cos(-(0.1)) - data->planey * sin(-(0.1));
		data->planey = oldplanex * sin(-(0.1)) + data->planey * cos(-(0.1));
	}
}

static void	key_w(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (data->map[(int)(data->px + data->dirx
				* data->speed)][(int)(data->py)] == 48)
			data->px += data->dirx * data->speed;
		if (data->map[(int)(data->px)][(int)(data->py + data->diry
				* data->speed)] == 48)
			data->py += data->diry * data->speed;
	}
}

static void	key_s(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (data->map[(int)(data->px - (data->dirx
					* data->speed))][(int)(data->py)] == 48)
			data->px -= data->dirx * data->speed;
		if (data->map[(int)(data->px)][(int)(data->py - (data->diry
					* data->speed))] == 48)
			data->py -= data->diry * data->speed;
	}
}

void	input(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_texture(data->texture[0]);
		mlx_delete_texture(data->texture[1]);
		mlx_delete_texture(data->texture[2]);
		mlx_delete_texture(data->texture[3]);
		mlx_terminate(data->mlx);
		mlx_close_window(data->mlx);
		free_ev(data);
		exit(0);
	}
	key_a(data);
	key_s(data);
	key_d(data);
	key_w(data);
	rt(data);
}
