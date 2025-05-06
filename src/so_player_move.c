/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_player_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:45:31 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/06 18:59:29 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_left(t_player *player, int x, int y, int coin)
{
	if (player->map->map_matrix[y][x - 1] == MONSTER)
		close_game(player);
	if (coin && player->map->map_matrix[y][x - 1] == EXIT_MAP)
	{
		player->map->map_matrix[y][x - 1] = 'T';
		player->map->map_matrix[y][x] = '0';
		render(player);
	}
	else if (!coin && player->map->map_matrix[y][x - 1] == EXIT_MAP)
		close_game(player);
	else if (player->map->map_matrix[y][x - 1] != '1')
	{
		player->map->map_matrix[y][x - 1] = 'P';
		if (player->map->map_matrix[y][x] == 'T')
			player->map->map_matrix[y][x] = 'E';
		else
			player->map->map_matrix[y][x] = '0';
		++(player->counter);
		render(player);
	}
}

void	move_right(t_player *player, int x, int y, int coin)
{
	if (player->map->map_matrix[y][x + 1] == MONSTER)
		close_game(player);
	if (coin && player->map->map_matrix[y][x + 1] == EXIT_MAP)
	{
		player->map->map_matrix[y][x + 1] = 'T';
		player->map->map_matrix[y][x] = '0';
		render(player);
	}
	else if (!coin && player->map->map_matrix[y][x + 1] == EXIT_MAP)
		close_game(player);
	else if (player->map->map_matrix[y][x + 1] != '1')
	{
		player->map->map_matrix[y][x + 1] = 'P';
		if (player->map->map_matrix[y][x] == 'T')
			player->map->map_matrix[y][x] = 'E';
		else
			player->map->map_matrix[y][x] = '0';
		++(player->counter);
		render(player);
	}
}

void	move_bottom(t_player *player, int x, int y, int coin)
{
	if (player->map->map_matrix[y + 1][x] == MONSTER)
		close_game(player);
	if (coin && player->map->map_matrix[y + 1][x] == EXIT_MAP)
	{
		player->map->map_matrix[y + 1][x] = 'T';
		player->map->map_matrix[y][x] = '0';
		render(player);
	}
	else if (!coin && player->map->map_matrix[y + 1][x] == EXIT_MAP)
		close_game(player);
	else if (player->map->map_matrix[y + 1][x] != '1')
	{
		player->map->map_matrix[y + 1][x] = 'P';
		if (player->map->map_matrix[y][x] == 'T')
			player->map->map_matrix[y][x] = 'E';
		else
			player->map->map_matrix[y][x] = '0';
		++(player->counter);
		render(player);
	}
}

void	move_top(t_player *player, int x, int y, int coin)
{
	if (player->map->map_matrix[y - 1][x] == MONSTER)
		close_game(player);
	if (coin && player->map->map_matrix[y - 1][x] == EXIT_MAP)
	{
		player->map->map_matrix[y - 1][x] = 'T';
		player->map->map_matrix[y][x] = '0';
		render(player);
	}
	else if (!coin && player->map->map_matrix[y - 1][x] == EXIT_MAP)
		close_game(player);
	else if (player->map->map_matrix[y - 1][x] != '1')
	{
		player->map->map_matrix[y - 1][x] = 'P';
		if (player->map->map_matrix[y][x] == 'T')
			player->map->map_matrix[y][x] = 'E';
		else
			player->map->map_matrix[y][x] = '0';
		++(player->counter);
		render(player);
	}
}
