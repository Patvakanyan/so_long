/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_player_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:45:31 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/01 17:46:02 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_left(t_map *map, int x, int y, int coin)
{
	if (coin && map->map_matrix[y][x - 1] == EXIT_MAP)
	{
		map->map_matrix[y][x - 1] = 'T';
		map->map_matrix[y][x] = '0';
		render(map);
	}
	else if (!coin && map->map_matrix[y][x - 1] == EXIT_MAP)
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
	if (coin && map->map_matrix[y][x + 1] == EXIT_MAP)
	{
		map->map_matrix[y][x + 1] = 'T';
		map->map_matrix[y][x] = '0';
		render(map);
	}
	else if (!coin && map->map_matrix[y][x + 1] == EXIT_MAP)
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
	if (coin && map->map_matrix[y + 1][x] == EXIT_MAP)
	{
		map->map_matrix[y + 1][x] = 'T';
		map->map_matrix[y][x] = '0';
		render(map);
	}
	else if (!coin && map->map_matrix[y + 1][x] == EXIT_MAP)
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
	if (coin && map->map_matrix[y - 1][x] == EXIT_MAP)
	{
		map->map_matrix[y - 1][x] = 'T';
		map->map_matrix[y][x] = '0';
		render(map);
	}
	else if (!coin && map->map_matrix[y - 1][x] == EXIT_MAP)
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
