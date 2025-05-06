/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:20:18 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/06 12:27:11 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	pac_man_init(t_player *player)
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

int	player_init(t_player *player)
{
	player->pac_man = (void **)malloc(sizeof(void *) * 2);
	if (!(player->pac_man))
		return (0);
	if (!monster_init(player))
		return (free(player->pac_man), 0);
	player->pac_man[0] = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Pac-Man/pac_closed.xpm", &player->map->all_size,
			&player->map->all_size);
	if (!player->pac_man[0])
		return (mlx_destroy_image(player->map->mlx_ptr, player->monster[0]),
			mlx_destroy_image(player->map->mlx_ptr, player->monster[1]),
			free(player->monster), 0);
	if (!pac_man_init(player))
		return (mlx_destroy_image(player->map->mlx_ptr, player->monster[0]),
			mlx_destroy_image(player->map->mlx_ptr, player->monster[1]),
			free(player->monster), mlx_destroy_image(player->map->mlx_ptr,
				player->pac_man[0]), 0);
	player->pac_man[1] = player->pac_man_left;
	return (1);
}

int	monster_init(t_player *player)
{
	player->monster_step = 0;
	player->map->all_size = SIZE;
	player->monster = (void **)malloc(sizeof(void *) * 2);
	if (!(player->monster))
		return (0);
	player->monster[0] = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Ghosts/Panic/ghost_panic1a.xpm", &player->map->all_size,
			&player->map->all_size);
	if (!(player->monster[0]))
		return (free(player->monster),
			ft_putstr_fd("Error: Image load failed!\n", 2), 0);
	player->monster[1] = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Ghosts/Panic/ghost_panic2a.xpm", &player->map->all_size,
			&player->map->all_size);
	if (!(player->monster[1]))
		return (mlx_destroy_image(player->map->mlx_ptr, player->monster[0]),
			free(player->monster), ft_putstr_fd("Error: Image load failed!\n",
				2), 0);
	return (1);
}

int	update_animation(t_player *player)
{
	if (player->map->behavior >= FRAME_DELAY)
	{
		player->current_frame = (player->current_frame + 1) % 2;
		render(player);
	}
	if (player->map->behavior == FRAME_DELAY)
		player->map->behavior = 0;
	else
		++(player->map->behavior);
	update_monster(player);
	return (0);
}

int	update_monster(t_player *player)
{
	if (player->monster_behavior >= MONSTER_RENDER)
	{
		player->monster_frame = (player->monster_frame + 1) % 2;
		render(player);
	}
	if (player->monster_behavior == MONSTER_RENDER)
		player->monster_behavior = 0;
	else
		++(player->monster_behavior);
	monster_step(player);
	return (0);
}

static void	monster_position(t_map *map, int *x, int *y)
{
	while (++(*y) < map->width)
	{
		*x = -1;
		while (++(*x) < map->height)
			if (map->map_matrix[*y][*x] == MONSTER
				|| map->map_matrix[*y][*x] == 'K')
				return ;
	}
	*x = -1;
	*y = -1;
}
void	monster_left_right(t_player *player)
{
	// ft_printf("%d\n", player->is_wall);
	if (player->map->map_matrix[player->py][player->px + 1] == EXIT_MAP
		|| player->map->map_matrix[player->py][player->px + 1] == WALL)
		player->is_wall = -1;
	else
		player->is_wall = 1;
	if (player->map->map_matrix[player->py][player->px + 1] != EXIT_MAP
		&& player->map->map_matrix[player->py][player->px + 1] != WALL
		&& player->monster_behavior == MONSTER_STEP && player->is_wall == 1)
	{
		if (player->map->map_matrix[player->py][player->px + 1] == PERSONAGE)
			player->map->map_matrix[player->py][player->px + 1] = 'K';
		else
			player->map->map_matrix[player->py][player->px + 1] = MONSTER;
		player->map->map_matrix[player->py][player->px] = '0';
	}
	else if (player->map->map_matrix[player->py][player->px - 1] != EXIT_MAP
		&& player->map->map_matrix[player->py][player->px - 1] != WALL
		&& player->monster_behavior == MONSTER_STEP && player->is_wall == -1)
	{
		if (player->map->map_matrix[player->py][player->px - 1] == PERSONAGE)
			player->map->map_matrix[player->py][player->px - 1] = 'K';
		else
			player->map->map_matrix[player->py][player->px - 1] = MONSTER;
		player->map->map_matrix[player->py][player->px] = '0';
	}
}

void	monster_step(t_player *player)
{
	player->py = -1;
	monster_position(player->map, &(player->px), &(player->py));
	if (player->py == -1 && player->px == -1)
		return ;
	if (player->map->map_matrix[player->py][player->px] == 'K')
		close_game(player);
	monster_left_right(player);
	if (player->monster_step == MONSTER_STEP)
		player->monster_step = 0;
	else
		++(player->monster_step);
	render(player);
}
