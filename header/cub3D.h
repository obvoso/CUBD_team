/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 14:10:05 by tson              #+#    #+#             */
/*   Updated: 2023/01/21 18:52:37 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../srcs/libft/libft.h"
# include "../mlx/mlx.h"

typedef char	t_bool;
typedef int		t_axis;
typedef int		t_color;

# define TRUE 1
# define FALSE 0
# define FILE_EXTENSION ".cub"
# define MALLOC_FAIL_MES "Memory allocate fail\n"
# define FILE_CONFIG_ERR_MES "File configuration error\n"
# define XPM_FILE_NAME_ERR_MES "Xpm file is not exist\n"
# define RGB_COLOR_ERR_MES "Rgb color error\n"
# define TEXTURE_ERR_MES "Texture error\n"
# define OPEN_FAIL -1
# define SET_TEXTURE_SUCCESS 1
# define SET_TEXTURE_FAIL 0

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define MOVE_SPEED 0.5
# define ROT_SPEED 0.05

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define NO_ID "NO"
# define SO_ID "SO"
# define WE_ID "WE"
# define EA_ID "EA"

enum e_event
{
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	KEY_EXIT = 17
};

enum e_keycode
{
	ESC = 53,
	Q = 12,
	W = 13,
	E = 14,
	R = 15,
	A = 0,
	S = 1,
	D = 2,
	LEFT_ARROW = 123,
	RIGHT_ARROW = 124
};
enum e_axis
{
	FORWARD = 1,
	BACKWARD = -1,
	LEFT = 1,
	RIGHT = -1
};

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_dda_values
{
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	int		map_x;
	int		map_y;
}	t_dda_values;

typedef struct s_player_info
{
	t_vector	dir;
	t_vector	pos;
	t_vector	plane;
}	t_player_info;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_s
{
	char	*m;
	int		length;
}t_s;
typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_s				*map;
	int				height;
	char			*(identifiers[4]);
	t_img			screen;
	t_img			textures[4];
	t_color			floor;
	t_color			ceiling;
	t_player_info	p_info;
}	t_game;

typedef struct s_prog_arg
{
	char	*n_path;
	char	*s_path;
	char	*w_path;
	char	*e_path;
}	t_prog_arg;

typedef struct s_hit_point
{
	t_bool		is_hit_ns;
	int			where;
	double		perp_dist;
	t_vector	ray;
	int			map_x;
	int			map_y;
}	t_hit_point;

typedef struct s_rendering
{
	int		draw_start;
	int		draw_end;
	int		tex_idx;
	int		tex_x;
	double	tex_pos;
	double	step;
}	t_rendering;

typedef enum e_map_type
{
	PLAYER,
	WALL,
	EMPTY,
	ERROR,
}t_map_type;



t_bool	is_valid_file_name(char *file_name);
t_bool	is_correct_arg(int argc, char *argv[], t_game *game);
int	on_keyboard_press(int keycode, t_game *game);
void	init_dda_values(t_game *game, t_vector ray, t_dda_values *values);
void	init_screen(t_game *game);
void	init_game(t_game *game);
t_vector	calculate_ray(t_game *game, int i);
t_bool	is_hit_wall(t_game *game, t_hit_point *hit_point, t_dda_values *values);
void	dda(t_game *game, t_hit_point *hit_point);
double	calculate_perp_dist(t_game *game, t_hit_point hit_point);
void	draw_one_line(t_game *game, t_hit_point hit_point, int col, int length);
void	render(t_game *game);
void	draw_texture(t_game *game, t_rendering ren, int col, int length);
void	draw_ceiling(t_game *game, t_rendering ren, int col);
void	draw_floor(t_game *game, t_rendering ren, int col);
void	set_start_end(t_rendering *ren, int length);
void	set_tex_idx(t_rendering *ren, t_hit_point hit_point);
void	set_tex_x(t_game *game, t_rendering *ren, t_hit_point hit_point);
t_map_type check_type(char a);
void	error_handle(char *s);
char	*ft_strjoin_no_nl(char *dest, char *src);
char	*ft_strdup_no_nl(char *str);
#endif
