/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:15:55 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/03 23:11:39 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_game(t_player *player)
{
	mlx_destroy_image(player->map->mlx_ptr, player->map->map_collectibles);
	mlx_destroy_image(player->map->mlx_ptr, player->map->map_exit);
	mlx_destroy_image(player->map->mlx_ptr, player->map->map_wall);
	mlx_destroy_image(player->map->mlx_ptr, player->pac_man[0]);
	mlx_destroy_image(player->map->mlx_ptr, player->pac_man[1]);
	mlx_destroy_window(player->map->mlx_ptr, player->map->mlx_win);
	mlx_destroy_display(player->map->mlx_ptr);
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
	int	x;
	int	y;
	int	coin;

	coin = count_coins(player->map);
	y = -1;
	player_position(player->map, &x, &y);
	if (behavior == 'A')
		move_left(player, x, y, coin);
	else if (behavior == 'S')
		move_bottom(player, x, y, coin);
	else if (behavior == 'W')
		move_top(player, x, y, coin);
	else if (behavior == 'D')
		move_right(player, x, y, coin);
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
