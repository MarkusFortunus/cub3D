/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:24:31 by fcornill          #+#    #+#             */
/*   Updated: 2024/11/25 12:44:26 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	walli_init(t_rc *rc, t_data *data, t_print_tex *texs)
{
	if (rc->side == 1)
	{
		if (rc->mapy > data->py)
			texs->tex_i = 0;
		else
			texs->tex_i = 1;
	}
	else
	{
		if (rc->mapx > data->px)
			texs->tex_i = 2;
		else
			texs->tex_i = 3;
	}
}

t_print_tex	init_print_tex(t_rc *rc, int x, t_data *data)
{
	t_print_tex	texs;
	double		wallx;

	walli_init(rc, data, &texs);
	if (rc->side == 0)
		wallx = data->py + rc->perpwalldist * rc->raydiry;
	else
		wallx = data->px + rc->perpwalldist * rc->raydirx;
	wallx -= floor(wallx);
	texs.texx = (int)(wallx * (double)data->texture[texs.tex_i]->width);
	texs.perpwalldist = rc->perpwalldist;
	texs.lineheight = (int)(H / texs.perpwalldist);
	texs.side = rc->side;
	texs.x = x;
	return (texs);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init(W, H, "42balls", false);
	if (!data->mlx)
	{
		free(data->mlx);
		free_ev(data);
		exit(0);
	}
	data->img = mlx_new_image(data->mlx, W, H);
	if (!data->img)
	{
		mlx_close_window(data->mlx);
		free_ev(data);
	}
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
	{
		mlx_close_window(data->mlx);
		free_ev(data);
		exit(0);
	}
}

void	init_text(t_data *data)
{
	data->texture[0] = mlx_load_png(data->east);
	data->texture[1] = mlx_load_png(data->west);
	data->texture[2] = mlx_load_png(data->south);
	data->texture[3] = mlx_load_png(data->north);
	if (!data->texture[0] || !data->texture[1] || !data->texture[2]
		|| !data->texture[3])
	{
		print_error("not a good texture");
		if (data->texture[0])
			mlx_delete_texture(data->texture[0]);
		if (data->texture[1])
			mlx_delete_texture(data->texture[1]);
		if (data->texture[2])
			mlx_delete_texture(data->texture[2]);
		if (data->texture[3])
			mlx_delete_texture(data->texture[3]);
		free_ev(data);
		exit(1);
	}
}
