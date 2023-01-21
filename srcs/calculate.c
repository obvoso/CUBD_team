/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:52:54 by tson              #+#    #+#             */
/*   Updated: 2023/01/20 14:52:54 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

extern int worldMap[MAP_HEIGHT][MAP_WIDTH];

void	dda(t_game *game, t_hit_point *hit_point)
{
	t_dda_values	values;

	init_dda_values(game, hit_point->ray, &values);
	while (TRUE)
	{
		if (is_hit_wall(game, hit_point, &values) == TRUE)
			break ;
	}
	hit_point->map_x = values.map_x;
	hit_point->map_y = values.map_y;
}

t_vector	calculate_ray(t_game *game, int i)
{
	t_vector	ray;
	double		camera_x;

	camera_x = 2 * i / (double)SCREEN_WIDTH - 1;
	ray.x = game->p_info.dir.x + game->p_info.plane.x * camera_x;
	ray.y = game->p_info.dir.y + game->p_info.plane.y * camera_x;
	return (ray);
}

t_bool	is_hit_wall(t_game *game, t_hit_point *hit_point, t_dda_values *values)
{
	if (values->side_x < values->side_y)
	{
		if (hit_point->ray.x < 0)
			values->map_x -= 1;
		else
			values->map_x += 1;
		values->side_x += values->delta_x;
		hit_point->is_hit_ns = FALSE;
		hit_point->where = values->map_x;
	}
	else
	{
		if (hit_point->ray.y < 0)
			values->map_y -= 1;
		else
			values->map_y += 1;
		values->side_y += values->delta_y;
		hit_point->is_hit_ns = TRUE;
		hit_point->where = values->map_y;
	}
	if (worldMap[values->map_x][values->map_y] > 0)
		return (TRUE);
	return (FALSE);
}

double	calculate_perp_dist(t_game *game, t_hit_point hit_point)
{
	double	perp_wall_dist;

	if (hit_point.is_hit_ns)
	{
		if (hit_point.ray.y < 0)
			perp_wall_dist = (hit_point.where - game->p_info.pos.y + 1) / hit_point.ray.y;
		else
			perp_wall_dist = (hit_point.where - game->p_info.pos.y) / hit_point.ray.y;
	}
	else
	{
		if (hit_point.ray.x < 0)
			perp_wall_dist = (hit_point.where - game->p_info.pos.x + 1) / hit_point.ray.x;
		else
			perp_wall_dist = (hit_point.where - game->p_info.pos.x) / hit_point.ray.x;
	}
	return (perp_wall_dist);
}

void	init_dda_values(t_game *game, t_vector ray, t_dda_values *values)
{
	values->map_x = (int)game->p_info.pos.x;
	values->map_y = (int)game->p_info.pos.y;
	values->delta_x = fabs(1 / ray.x);
	values->delta_y = fabs(1 / ray.y);
	if (ray.x < 0)
		values->side_x = (game->p_info.pos.x - values->map_x) * values->delta_x;
	else
		values->side_x = (values->map_x + 1.0 - game->p_info.pos.x) * values->delta_x;
	if (ray.y < 0)
		values->side_y = (game->p_info.pos.y - values->map_y) * values->delta_y;
	else
		values->side_y = (values->map_y + 1.0 - game->p_info.pos.y) * values->delta_y;
}
