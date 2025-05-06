/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_bonus_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:25:58 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/06 19:29:49 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	monster_position(t_map *map, int *x, int *y)
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
