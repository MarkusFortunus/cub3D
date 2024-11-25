/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:29:57 by fcornill          #+#    #+#             */
/*   Updated: 2024/11/25 11:41:37 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cal_sidedist(t_rc *rc, t_data *data)
{
	rc->mapx = (int)data->px;
	rc->mapy = (int)data->py;
	if (rc->raydirx < 0)
	{
		rc->stepx = -1;
		rc->sidedistx = (data->px - rc->mapx) * rc->deltadistx;
	}
	else
	{
		rc->stepx = 1;
		rc->sidedistx = (rc->mapx + 1 - data->px) * rc->deltadistx;
	}
	if (rc->raydiry < 0)
	{
		rc->stepy = -1;
		rc->sidedisty = (data->py - rc->mapy) * rc->deltadisty;
	}
	else
	{
		rc->stepy = 1;
		rc->sidedisty = (rc->mapy + 1 - data->py) * rc->deltadisty;
	}
}

void	dda_process(t_rc *rc, t_data *data)
{
	while (!rc->hit)
	{
		if (rc->sidedistx < rc->sidedisty)
		{
			rc->sidedistx += rc->deltadistx;
			rc->mapx += rc->stepx;
			rc->side = 0;
		}
		else
		{
			rc->sidedisty += rc->deltadisty;
			rc->mapy += rc->stepy;
			rc->side = 1;
		}
		if (data->map[rc->mapx][rc->mapy] != '0')
			rc->hit = true;
	}
	rc->hit = false;
}

void	prints_screen(t_print_tex texs, t_data *data)
{
	int	starty;
	int	endy;

	starty = -texs.lineheight / 2 + H / 2;
	if (starty < 0)
		starty = 0;
	endy = texs.lineheight / 2 + H / 2;
	if (endy >= H)
		endy = H - 1;
	verline(texs, starty, endy, data);
}

static void	rt_calculate(t_rc *rc, int x, t_data *data)
{
	rc->camerax = 2 * x / (double)W - 1;
	rc->raydirx = data->dirx + data->planex * rc->camerax;
	rc->raydiry = data->diry + data->planey * rc->camerax;
	if (rc->raydirx == 0)
		rc->deltadistx = 1e30;
	else
		rc->deltadistx = fabs(1 / rc->raydirx);
	if (rc->raydiry == 0)
		rc->deltadisty = 1e30;
	else
		rc->deltadisty = fabs(1 / rc->raydiry);
	cal_sidedist(rc, data);
	dda_process(rc, data);
	if (rc->side == 0)
		rc->perpwalldist = rc->sidedistx - rc->deltadistx;
	else
		rc->perpwalldist = rc->sidedisty - rc->deltadisty;
}

void	rt(t_data *data)
{
	int		x;
	t_rc	*rc;

	rc = ft_calloc(1, sizeof(t_rc));
	x = 0;
	while (x != W)
	{
		rt_calculate(rc, x, data);
		prints_screen(init_print_tex(rc, x, data), data);
		rc->sidedistx = 0;
		rc->sidedisty = 0;
		x++;
	}
	free(rc);
}
