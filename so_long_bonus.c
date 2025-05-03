/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:20:18 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/03 23:00:24 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	player_init(t_player *player)
{
	int	all_size;

	all_size = SIZE;
	player->pac_man[0] = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Pac-Man/pac_closed.xpm", &all_size, &all_size);
	player->pac_man[1] = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Pac-Man/pac_open_left.xpm", &all_size, &all_size);
	if (!(player->pac_man[0]) || !(player->pac_man[1]))
		return (0);
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
