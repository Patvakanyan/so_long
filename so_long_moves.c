/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:15:55 by apatvaka          #+#    #+#             */
/*   Updated: 2025/04/26 20:07:44 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_game(t_map *map)
{
	mlx_destroy_window(map->mlx_ptr, map->mlx_win);
	free(map->map_matrix);
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

void	move_left(t_map *map, int x, int y, int coin)
{
	if (coin && map->map_matrix[y][x - 1] == exit_map)
	{
		map->map_matrix[y][x - 1] = 'T';
		map->map_matrix[y][x] = '0';
		render(map);
	}
	else if (!coin && map->map_matrix[y][x - 1] == exit_map)
		close_game(map);
	else if (map->map_matrix[y][x - 1] != '1')
	{
		map->map_matrix[y][x - 1] = 'P';
		if (map->map_matrix[y][x] == 'T')
			map->map_matrix[y][x] = 'E';
		else
			map->map_matrix[y][x] = '0';
		render(map);
	}
}

void	move_right(t_map *map, int x, int y, int coin)
{
	if (coin && map->map_matrix[y][x + 1] == exit_map)
	{
		map->map_matrix[y][x + 1] = 'T';
		map->map_matrix[y][x] = '0';
		render(map);
	}
	else if (!coin && map->map_matrix[y][x + 1] == exit_map)
		close_game(map);
	else if (map->map_matrix[y][x + 1] != '1')
	{
		map->map_matrix[y][x + 1] = 'P';
		if (map->map_matrix[y][x] == 'T')
			map->map_matrix[y][x] = 'E';
		else
			map->map_matrix[y][x] = '0';
		render(map);
	}
}

void	move_bottom(t_map *map, int x, int y, int coin)
{
	if (coin && map->map_matrix[y + 1][x] == exit_map)
	{
		map->map_matrix[y + 1][x] = 'T';
		map->map_matrix[y][x] = '0';
		render(map);
	}
	else if (!coin && map->map_matrix[y + 1][x] == exit_map)
		close_game(map);
	else if (map->map_matrix[y + 1][x] != '1')
	{
		map->map_matrix[y + 1][x] = 'P';
		if (map->map_matrix[y][x] == 'T')
			map->map_matrix[y][x] = 'E';
		else
			map->map_matrix[y][x] = '0';
		render(map);
	}
}
void	move_top(t_map *map, int x, int y, int coin)
{
	if (coin && map->map_matrix[y - 1][x] == exit_map)
	{
		map->map_matrix[y - 1][x] = 'T';
		map->map_matrix[y][x] = '0';
		render(map);
	}
	else if (!coin && map->map_matrix[y - 1][x] == exit_map)
		close_game(map);
	else if (map->map_matrix[y - 1][x] != '1')
	{
		map->map_matrix[y - 1][x] = 'P';
		if (map->map_matrix[y][x] == 'T')
			map->map_matrix[y][x] = 'E';
		else
			map->map_matrix[y][x] = '0';
		render(map);
	}
}

void	move_player(t_map *map, char behavior)
{
	int	x;
	int	y;
	int	coin;

	coin = count_coins(map);
	y = -1;
	player_position(map, &x, &y);
	ft_printf("coin = %d\n", coin);
	if (behavior == 'A')
		move_left(map, x, y, coin);
	else if (behavior == 'S')
		move_bottom(map, x, y, coin);
	else if (behavior == 'W')
		move_top(map, x, y, coin);
	else if (behavior == 'D')
		move_right(map, x, y, coin);
}
