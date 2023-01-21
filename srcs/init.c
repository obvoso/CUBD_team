/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:48:21 by tson              #+#    #+#             */
/*   Updated: 2023/01/21 18:34:47 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "MY");
	game->screen.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->screen.data = (int *)mlx_get_data_addr(game->screen.img, &game->screen.bpp, &game->screen.size_line, &game->screen.endian);
	game->identifiers[NORTH] = ft_strdup(NO_ID);
	game->identifiers[SOUTH] = ft_strdup(SO_ID);
	game->identifiers[EAST] = ft_strdup(EA_ID);
	game->identifiers[WEST] = ft_strdup(WE_ID);
	// ft_strdup NULL guard

	//game->ceiling = 0x234567;
	//game->floor = 0x765432;
	game->ceiling = -1;
	game->floor = -1;
	game->textures[0].img = NULL;
	game->textures[1].img = NULL;
	game->textures[2].img = NULL;
	game->textures[3].img = NULL;

	game->p_info.dir.x = 0;
	game->p_info.dir.y = 1;
	game->p_info.plane.x = 0.66;
	game->p_info.plane.y = 0;
	game->p_info.pos.x = 20;
	game->p_info.pos.y = 20;
}
