/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:50:22 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/03 23:12:01 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	choose_img(t_player *player, int x, int y)
{
	if (player->map->map_matrix[y][x] == WALL)
		mlx_put_image_to_window(player->map->mlx_ptr, player->map->mlx_win,
			player->map->map_wall, x * SIZE, y * SIZE);
	else if (player->map->map_matrix[y][x] == EXIT_MAP)
		mlx_put_image_to_window(player->map->mlx_ptr, player->map->mlx_win,
			player->map->map_exit, x * SIZE, y * SIZE);
	else if (player->map->map_matrix[y][x] == PERSONAGE
		|| player->map->map_matrix[y][x] == 'T')
		mlx_put_image_to_window(player->map->mlx_ptr, player->map->mlx_win,
			player->pac_man[player->current_frame], x * SIZE, y * SIZE);
	else if (player->map->map_matrix[y][x] == COLLECTIBLES)
		mlx_put_image_to_window(player->map->mlx_ptr, player->map->mlx_win,
			player->map->map_collectibles, x * SIZE, y * SIZE);
}

int	count_coins(t_map *map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (++i < map->width)
	{
		j = -1;
		while (++j < map->height)
		{
			if (map->map_matrix[i][j] == COLLECTIBLES)
				++count;
		}
	}
	return (count);
}

void	player_position(t_map *map, int *x, int *y)
{
	while (++(*y) < map->width)
	{
		*x = -1;
		while (++(*x) < map->height)
			if (map->map_matrix[*y][*x] == PERSONAGE
				|| map->map_matrix[*y][*x] == 'T')
				return ;
	}
}

void	print_error(t_map *map, char *str, int code)
{
	if (map)
		free(map);
	ft_putstr_fd(str, 2);
	exit(code);
}

void	ft_free(char **str, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		free(str[i]);
		++i;
	}
	free(str);
}
