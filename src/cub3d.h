/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:23:17 by fcornill          #+#    #+#             */
/*   Updated: 2024/11/25 15:41:10 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define HTEXT
# define WTEXT
# define W 1048
# define H 1048
# define WMAP 12
# define HMAP 12

# define RED "\033[1;31m"
# define RST "\033[0m"

typedef struct s_color
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
	uint32_t		color;
}					t_color;

typedef struct s_print_tex
{
	int				tex_i;
	int				side;
	int				x;
	int				texx;
	int				lineheight;
	double			perpwalldist;
}					t_print_tex;

typedef struct s_data
{
	double			px;
	double			py;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	float			speed;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*texture[4];
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	size_t			floor;
	size_t			ceiling;
	char			**map;
	char			**file;
	int				check;
	size_t			file_index;
	size_t			row;
	bool			flag;
	bool			check_map;
	bool			color_ceiling;
	bool			color_floor;
}					t_data;

typedef struct s_rc
{
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	double			sidedistx;
	double			sidedisty;
	int				stepx;
	int				stepy;
	int				side;
	bool			hit;
}					t_rc;

bool				parse_map(t_data *data, const char *str);
void				print_error(const char *msg);
void				get_texture_path(char *line, t_data *data, int flag);
void				get_floor_ceiling_color(char *line, t_data *data, int flag);
void				scan_line(char *line, t_data *data);
bool				check_data(t_data *data);
void				replace_space(t_data *data);
bool				get_file_data(const char *file, t_data *data);
bool				get_map(const char *file, t_data *data);
bool				check_map(t_data *data);
bool				check_right_border(t_data *data);
bool				check_left_border(t_data *data);
bool				check_extension(const char *str);
size_t				ft_atoi_rgb(char *str);
size_t				rgb_to_hex(size_t red, size_t green, size_t blue, \
size_t alpha);
bool				count_row(char **file, t_data *data);
char				*skip_space(char *s);
bool				check_map_content(t_data *data);
void				get_player_position(t_data *data);
char				*ft_custom_strdup(const char *s1);
bool				fill_map(char **file, t_data *data);
void				set_direction(t_data *data, char direction);
t_print_tex			init_print_tex(t_rc *rc, int x, t_data *data);
void				input(void *param);
void				verline(t_print_tex texs, int y1, int y2, t_data *data);
void				rt(t_data *data);
void				init_mlx(t_data *data);
void				init_text(t_data *data);
void				free_ev(t_data *data);
void				free_arri(char **arr);

#endif