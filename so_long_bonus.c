/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:20:18 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/05 18:45:51 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	player_init(t_player *player)
{
	player->map->all_size = SIZE;
	player->pac_man = (void **)malloc(sizeof(void *) * 2);
	if (!(player->pac_man))
		return (0);
	player->pac_man[0] = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Pac-Man/pac_closed.xpm", &player->map->all_size,
			&player->map->all_size);
	player->pac_man_left = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Pac-Man/pac_open_left.xpm", &player->map->all_size,
			&player->map->all_size);
	player->pac_man[1] = player->pac_man_left;
	player->pac_man_right = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Pac-Man/pac_open_right.xpm", &player->map->all_size,
			&player->map->all_size);
	player->pac_man_up = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Pac-Man/pac_open_up.xpm", &player->map->all_size,
			&player->map->all_size);
	player->pac_man_down = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Pac-Man/pac_open_down.xpm", &player->map->all_size,
			&player->map->all_size);
	if (!(player->pac_man[0]) || !(player->pac_man_left)
		|| !(player->pac_man_right) || !(player->pac_man_up)
		|| !(player->pac_man_down))
		return (ft_putstr_fd("Error: Image load failed!\n", 2), 0);
	return (1);
}

int	update_animation(t_player *player)
{
	if (player->map->behavior >= FRAME_DELAY)
	{
		player->current_frame = (player->current_frame + 1) % 2;
		player->last_frame_time = player->map->behavior;
		render(player);
	}
	if (player->map->behavior == FRAME_DELAY)
		player->map->behavior = 0;
	else
		++(player->map->behavior);
	return (0);
}
