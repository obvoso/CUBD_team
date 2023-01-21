/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:50:29 by tson              #+#    #+#             */
/*   Updated: 2023/01/20 14:50:30 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

extern int worldMap[MAP_WIDTH][MAP_HEIGHT];

void	render(t_game *game)
{
	int			i;
	t_hit_point	hit_point;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		hit_point.ray = calculate_ray(game, i);
		dda(game, &hit_point);
		hit_point.perp_dist = calculate_perp_dist(game, hit_point);
		draw_one_line(game, hit_point, i, (int)(SCREEN_HEIGHT / hit_point.perp_dist));
		i++;
	}
}

void	draw_one_line(t_game *game, t_hit_point hit_point, int col, int length)
{
	t_rendering	ren;

	set_start_end(&ren, length);
	set_tex_idx(&ren, hit_point);
	set_tex_x(game, &ren, hit_point);

	draw_ceiling(game, ren, col);
	draw_texture(game, ren, col, length);
	draw_floor(game, ren, col);
}

void	draw_texture(t_game *game, t_rendering ren, int col, int length)
{
	int		i;
	int		tex_y;
	int		color;

	ren.step = 1.0 * game->textures[ren.tex_idx].height / length;
	ren.tex_pos = (ren.draw_start - SCREEN_HEIGHT / 2 + length / 2) * ren.step;
	i = ren.draw_start;
	while (i < ren.draw_end)
	{
		tex_y = (int)ren.tex_pos & (game->textures[ren.tex_idx].height - 1);
		ren.tex_pos += ren.step;
		color = game->textures[ren.tex_idx].data[game->textures[ren.tex_idx].height * tex_y + ren.tex_x];
		game->screen.data[i * SCREEN_WIDTH + col] = color;
		i++;
	}
}

void	draw_ceiling(t_game *game, t_rendering ren, int col)
{
	int	i;

	i = 0;
	while (i < ren.draw_start)
	{
		game->screen.data[i * SCREEN_WIDTH + col] = game->ceiling;
		i++;
	}
}

void	draw_floor(t_game *game, t_rendering ren, int col)
{
	int	i;

	i = ren.draw_end;
	while (i < SCREEN_HEIGHT)
	{
		game->screen.data[i * SCREEN_WIDTH + col] = game->floor;
		i++;
	}
}

void	set_start_end(t_rendering *ren, int length)
{
	ren->draw_start = -length / 2 + SCREEN_HEIGHT / 2;
	ren->draw_end = length / 2 + SCREEN_HEIGHT / 2;
	if (ren->draw_start < 0)
		ren->draw_start = 0;
	if (ren->draw_end >= SCREEN_HEIGHT)
		ren->draw_end = SCREEN_HEIGHT - 1;
}

void	set_tex_idx(t_rendering *ren, t_hit_point hit_point)
{
	if (hit_point.is_hit_ns && hit_point.ray.y > 0)
		ren->tex_idx = SOUTH;
	else if (hit_point.is_hit_ns && hit_point.ray.y < 0)
		ren->tex_idx = NORTH;
	else if (!hit_point.is_hit_ns && hit_point.ray.x > 0)
		ren->tex_idx = WEST;
	else
		ren->tex_idx = EAST;
}

void	set_tex_x(t_game *game, t_rendering *ren, t_hit_point hit_point)
{
	double	wall_x;

	if (hit_point.is_hit_ns)
		wall_x = game->p_info.pos.x + hit_point.perp_dist * hit_point.ray.x;
	else
		wall_x = game->p_info.pos.y + hit_point.perp_dist * hit_point.ray.y;
	wall_x -= floor(wall_x);
	ren->tex_x = (int)(wall_x * (double)game->textures[ren->tex_idx].width);
	if(hit_point.is_hit_ns == FALSE && hit_point.ray.x > 0)
		ren->tex_x = game->textures[ren->tex_idx].width - ren->tex_x - 1;
	if(hit_point.is_hit_ns == TRUE && hit_point.ray.y < 0)
		ren->tex_x = game->textures[ren->tex_idx].width - ren->tex_x - 1;
}

void	init_screen(t_game *game)
{
	for (int i = 0; i < SCREEN_HEIGHT; i++)
		for (int j = 0; j < SCREEN_WIDTH; j++)
			game->screen.data[i * SCREEN_WIDTH + j] = 0;
}
