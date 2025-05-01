/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:15:55 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/01 17:48:36 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_game(t_map *map)
{
	mlx_destroy_image(map->mlx_ptr, map->map_collectibles);
	mlx_destroy_image(map->mlx_ptr, map->map_exit);
	mlx_destroy_image(map->mlx_ptr, map->map_wall);
	mlx_destroy_image(map->mlx_ptr, map->map_personage);
	mlx_destroy_window(map->mlx_ptr, map->mlx_win);
	mlx_destroy_display(map->mlx_ptr);
	free(map->mlx_ptr);
	ft_free(map->map_matrix, map->width);
	free(map);
	exit(0);
}

int	key_hook(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
		close_game(map);
	if (keycode == KEY_A)
		move_player(map, 'A');
	if (keycode == KEY_S)
		move_player(map, 'S');
	if (keycode == KEY_D)
		move_player(map, 'D');
	if (keycode == KEY_W)
		move_player(map, 'W');
	return (1);
}

void	move_player(t_map *map, char behavior)
{
	int	x;
	int	y;
	int	coin;

	coin = count_coins(map);
	y = -1;
	player_position(map, &x, &y);
	if (behavior == 'A')
		move_left(map, x, y, coin);
	else if (behavior == 'S')
		move_bottom(map, x, y, coin);
	else if (behavior == 'W')
		move_top(map, x, y, coin);
	else if (behavior == 'D')
		move_right(map, x, y, coin);
}
