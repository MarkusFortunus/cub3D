/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:29:36 by fcornill          #+#    #+#             */
/*   Updated: 2024/11/25 14:04:20 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_color(t_data *data, t_print_tex texs, int texy)
{
	t_color	color;
	int		index;

	index = (texy * data->texture[texs.tex_i]->width + texs.texx) * 4;
	color.r = data->texture[texs.tex_i]->pixels[index + 0];
	color.g = data->texture[texs.tex_i]->pixels[index + 1];
	color.b = data->texture[texs.tex_i]->pixels[index + 2];
	color.a = data->texture[texs.tex_i]->pixels[index + 3];
	color.color = (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
	return (color.color);
}

void	put_texture(t_data *data, t_print_tex texs, int y1, int y2)
{
	double		step;
	double		tex_pos;
	int			texy;
	uint32_t	color;

	step = 1.0 * data->texture[texs.tex_i]->height / texs.lineheight;
	tex_pos = (y1 - H / 2 + texs.lineheight / 2) * step;
	while (y1 < y2)
	{
		texy = (int)tex_pos % (data->texture[texs.tex_i]->height - 1);
		tex_pos += step;
		color = get_color(data, texs, texy);
		mlx_put_pixel(data->img, texs.x, y1, color);
		y1++;
	}
}

void	verline(t_print_tex texs, int y1, int y2, t_data *data)
{
	int	i;

	i = 0;
	while (i < y1)
	{
		mlx_put_pixel(data->img, texs.x, i, data->ceiling);
		i++;
	}
	put_texture(data, texs, y1 + 1, y2);
	i = y2;
	while (i != H)
	{
		mlx_put_pixel(data->img, texs.x, i, data->floor);
		i++;
	}
}
