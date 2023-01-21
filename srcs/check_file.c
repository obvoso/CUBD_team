/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:24:52 by tson              #+#    #+#             */
/*   Updated: 2023/01/21 19:06:59 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"
#include "libft/libft.h"

extern void	*img;
extern int		*img_data;
extern int		bpp, size_line, endian;
extern int worldMap[MAP_WIDTH][MAP_HEIGHT];

t_bool	is_valid_file_name(char *file_name)
{
	int	idx;

	idx = ft_strchr(file_name, '.');
	if (idx == -1 || ft_strncmp(file_name + idx, FILE_EXTENSION, ft_strlen(file_name + idx)) != SAME_STR)
		return (FALSE);
	return (TRUE);
}

void	load_image(t_game *game, char *file_name, int idx)
{
	game->textures[idx].img = mlx_xpm_file_to_image(game->mlx, file_name, &game->textures[idx].width, &game->textures[idx].height);
	game->textures[idx].data = (int *)mlx_get_data_addr(game->textures[idx].img, &game->textures[idx].bpp, &game->textures[idx].size_line, &game->textures[idx].endian);
}

int		check_set_texture(t_game *g)
{
	return (!g->textures[0].img || !g->textures[1].img || \
			!g->textures[2].img  || !g->textures[3].img);
}

int	check_texture_idx(t_game *game, char **split)
{
	if (!(ft_strncmp(NO_ID, split[0], 3)) && !(game->textures[0].img))
		return (NORTH);
	else if (!(ft_strncmp(SO_ID, split[0], 3)) && !(game->textures[1].img))
		return (SOUTH);
	else if (!(ft_strncmp(WE_ID, split[0], 3)) && !(game->textures[2].img))
		return (WEST);
	else if (!(ft_strncmp(EA_ID, split[0], 3)) && !(game->textures[3].img))
		return (EAST);
	else
		error_handle(FILE_CONFIG_ERR_MES); // 수정, free
	return (0);
}

void	set_textures(t_game *game, int fd)
{
	int		i;
	int		xpm_fd;
	char	*str;
	char	**splits;

	while (check_set_texture(game))
	{
		str = get_next_line(fd);
		if (*str == '\n')
		{
			free(str);
			continue ;
		}
		if (str == NULL)
			error_handle(MALLOC_FAIL_MES);
		splits = ft_split(str, ' ');
		if (splits == NULL)
			error_handle(MALLOC_FAIL_MES);
		i = check_texture_idx(game, splits); // 줄 모자라면 86행으로 빼기
		// if (ft_strncmp(splits[0], game->identifiers[i], ft_strlen(splits[0])) != SAME_STR)
		// 	error_handle(FILE_CONFIG_ERR_MES);
		xpm_fd = open(ft_strdup_no_nl(splits[1]), O_RDONLY);
		if (xpm_fd == OPEN_FAIL)
			error_handle(XPM_FILE_NAME_ERR_MES);
		// if (splits[2] != NULL)
		// 	error_handle(FILE_CONFIG_ERR_MES);
		load_image(game, ft_strdup_no_nl(splits[1]), i);
		close(xpm_fd);
	}
}

void	check_colors(t_game *game, char *str, char *c)
{
	char	**rgb;
	int		tmp[3];

	rgb = ft_split(str, ',');
	if (!rgb)
		error_handle(FILE_CONFIG_ERR_MES);
	tmp[0] = ft_atoi(rgb[0]);
	tmp[1] = ft_atoi(rgb[1]);
	tmp[2] = ft_atoi(rgb[2]);
	if (0 > tmp[0] || 255 < tmp[0] || 0 > tmp[1] || 255 < tmp[1] || 0 > tmp[2] || 255 < tmp[2])
		error_handle(RGB_COLOR_ERR_MES); // 수정, free
	if (!ft_strncmp(c, "F", 2))
		game->floor = (tmp[0] << 16 | tmp[1] << 8 | tmp[2]);
	else if (!ft_strncmp(c, "C", 2))
		game->ceiling = (tmp[0] << 16 | tmp[1] << 8 | tmp[2]);
	else
		error_handle(FILE_CONFIG_ERR_MES); // 수정, free
}

void	set_colors(t_game *game, int fd)
{
	char	*str;
	char	**splits;
	char	**rgb;

	str = ft_strdup("\n");
	while (game->floor == -1 || game->ceiling == -1)
	{
		free(str);
		str = get_next_line(fd);
		while(*str == '\n')
		{
			free(str);
			str = get_next_line(fd);
		}
		splits = ft_split(str, ' ');
		if (str == NULL || splits == NULL)
			error_handle(MALLOC_FAIL_MES);
		check_colors(game, splits[1], splits[0]);
	}
}

t_bool	is_correct_arg(int argc, char *argv[], t_game *game)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2 || is_valid_file_name(argv[1]) == FALSE || fd == OPEN_FAIL)
		return (FALSE);
	set_textures(game, fd);
	set_colors(game, fd);
	return (TRUE);
}
