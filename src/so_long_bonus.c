/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:20:18 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/03 00:41:25 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	pac_man_init(t_player *player)
{
	player->pac_man_left = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Pac-Man/pac_open_left.xpm", &player->map->all_size,
			&player->map->all_size);
	if (!player->pac_man_left)
		return (0);
	player->pac_man_right = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Pac-Man/pac_open_right.xpm", &player->map->all_size,
			&player->map->all_size);
	if (!player->pac_man_right)
		return (mlx_destroy_image(player->map->mlx_ptr, player->pac_man_left),
			0);
	player->pac_man_up = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Pac-Man/pac_open_up.xpm", &player->map->all_size,
			&player->map->all_size);
	if (!player->pac_man_up)
		return (mlx_destroy_image(player->map->mlx_ptr, player->pac_man_left),
			mlx_destroy_image(player->map->mlx_ptr, player->pac_man_right), 0);
	player->pac_man_down = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Pac-Man/pac_open_down.xpm", &player->map->all_size,
			&player->map->all_size);
	if (!player->pac_man_down)
		return (mlx_destroy_image(player->map->mlx_ptr, player->pac_man_left),
			mlx_destroy_image(player->map->mlx_ptr, player->pac_man_right),
			mlx_destroy_image(player->map->mlx_ptr, player->pac_man_up), 0);
	return (1);
}

void	monster_left_right(t_player *player, int x)
{
	if (player->map->map_matrix[player->py][player->px + x] != EXIT_MAP
		&& player->map->map_matrix[player->py][player->px + x] != WALL
		&& player->monster_behavior == MONSTER_STEP)
	{
		if (player->map->map_matrix[player->py][player->px + x] == PERSONAGE
			|| player->map->map_matrix[player->py][player->px + x] == 'T')
			player->map->map_matrix[player->py][player->px + x] = 'K';
		else
			player->map->map_matrix[player->py][player->px + x] = MONSTER;
		if (x != 0)
			player->map->map_matrix[player->py][player->px] = '0';
	}
}

void	is_wall_monster(t_player *player)
{
	int	next_x;
	int	next_y;

	next_x = player->px + player->is_wall_x;
	next_y = player->py;
	if (player->map->map_matrix[next_y][next_x] == WALL
		|| player->map->map_matrix[next_y][next_x] == EXIT_MAP
		|| player->map->map_matrix[next_y][next_x] == COLLECTIBLES)
	{
		player->is_wall_x *= -1;
		return ;
	}
}

int	is_between(t_player *player)
{
	if ((player->map->map_matrix[player->py][player->px + 1] == WALL
		|| player->map->map_matrix[player->py][player->px + 1] == EXIT_MAP
		|| player->map->map_matrix[player->py][player->px + 1] == 'C')
		&& (player->map->map_matrix[player->py][player->px - 1] == WALL
		|| player->map->map_matrix[player->py][player->px - 1] == EXIT_MAP
		|| player->map->map_matrix[player->py][player->px
		- 1] == COLLECTIBLES))
		return (0);
	else
		return (1);
}

void	monster_step(t_player *player)
{
	int	flag;

	player->py = -1;
	monster_position(player->map, &(player->px), &(player->py));
	if (player->py == -1 && player->px == -1)
		return ;
	if (player->map->map_matrix[player->py][player->px] == 'K')
		close_game(player);
	flag = is_between(player);
	is_wall_monster(player);
	if (flag)
		monster_left_right(player, player->is_wall_x);
	if (player->monster_step == MONSTER_STEP)
		player->monster_step = 0;
	else
		++(player->monster_step);
}
