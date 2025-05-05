/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:15:55 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/05 20:47:41 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_game(t_player *player)
{
	mlx_destroy_image(player->map->mlx_ptr, player->map->map_collectibles);
	mlx_destroy_image(player->map->mlx_ptr, player->map->map_exit);
	mlx_destroy_image(player->map->mlx_ptr, player->map->map_wall);
	mlx_destroy_image(player->map->mlx_ptr, player->pac_man[0]);
	mlx_destroy_image(player->map->mlx_ptr, player->pac_man_up);
	mlx_destroy_image(player->map->mlx_ptr, player->pac_man_down);
	mlx_destroy_image(player->map->mlx_ptr, player->pac_man_left);
	mlx_destroy_image(player->map->mlx_ptr, player->monster[0]);
	mlx_destroy_image(player->map->mlx_ptr, player->monster[1]);
	mlx_destroy_image(player->map->mlx_ptr, player->pac_man_right);
	mlx_destroy_window(player->map->mlx_ptr, player->map->mlx_win);
	mlx_destroy_display(player->map->mlx_ptr);
	free(player->pac_man);
	free(player->monster);
	free(player->map->mlx_ptr);
	ft_free(player->map->map_matrix, player->map->width);
	free(player->map);
	free(player);
	exit(0);
}

int	key_hook(int keycode, t_player *player)
{
	if (keycode == KEY_ESC)
		close_game(player);
	if (keycode == KEY_A)
		move_player(player, 'A');
	if (keycode == KEY_S)
		move_player(player, 'S');
	if (keycode == KEY_D)
		move_player(player, 'D');
	if (keycode == KEY_W)
		move_player(player, 'W');
	return (1);
}

void	move_player(t_player *player, char behavior)
{
	int	coin;

	coin = count_coins(player->map);
	player->map->y = -1;
	player_position(player->map, &player->map->x, &player->map->y);
	if (behavior == 'A')
	{
		player->pac_man[1] = player->pac_man_left;
		move_left(player, player->map->x, player->map->y, coin);
	}
	else if (behavior == 'S')
	{
		player->pac_man[1] = player->pac_man_down;
		move_bottom(player, player->map->x, player->map->y, coin);
	}
	else if (behavior == 'W')
	{
		player->pac_man[1] = player->pac_man_up;
		move_top(player, player->map->x, player->map->y, coin);
	}
	else if (behavior == 'D')
	{
		player->pac_man[1] = player->pac_man_right;
		move_right(player, player->map->x, player->map->y, coin);
	}
}

void	render(t_player *player)
{
	player->map->y = -1;
	mlx_clear_window(player->map->mlx_ptr, player->map->mlx_win);
	while (++(player->map->y) < player->map->width)
	{
		player->map->x = -1;
		while (++(player->map->x) < player->map->height)
			choose_img(player, player->map->x, player->map->y);
	}
}
