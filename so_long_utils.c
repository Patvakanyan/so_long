/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:50:22 by apatvaka          #+#    #+#             */
/*   Updated: 2025/04/28 17:50:31 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	mlx_clear_window(map->mlx_ptr, map->mlx_win);
	while (++y < map->width)
	{
		x = -1;
		while (++x < map->height)
		{
			if (map->map_matrix[y][x] == wall)
				mlx_put_image_to_window(map->mlx_ptr, map->mlx_win,
					map->map_wall, x * SIZE, y * SIZE);
			else if (map->map_matrix[y][x] == exit_map)
				mlx_put_image_to_window(map->mlx_ptr, map->mlx_win,
					map->map_exit, x * SIZE, y * SIZE);
			else if (map->map_matrix[y][x] == personage
				|| map->map_matrix[y][x] == 'T')
				mlx_put_image_to_window(map->mlx_ptr, map->mlx_win,
					map->map_personage, x * SIZE, y * SIZE);
			else if (map->map_matrix[y][x] == collectibles)
				mlx_put_image_to_window(map->mlx_ptr, map->mlx_win,
					map->map_collectibles, x * SIZE, y * SIZE);
		}
	}
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
			if (map->map_matrix[i][j] == collectibles)
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
			if (map->map_matrix[*y][*x] == personage
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
