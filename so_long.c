/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:25:39 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/03 21:21:53 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	key_behavior(t_player *player)
{
	mlx_hook(player->map->mlx_win, 2, 1L << 0, key_hook, player);
	mlx_hook(player->map->mlx_win, 17, 1L << 0, close_game, player);
}

int	img_init(t_player *player)
{
	player->map->all_size = SIZE;
	player->map->map_wall = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Other/Walls/wall.xpm", &player->map->all_size,
			&player->map->all_size);
	if (!(player->map->map_wall))
		return (0);
	player->map->map_collectibles = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Other/Pacdots/pacdot_powerup.xpm",
			&player->map->all_size, &player->map->all_size);
	if (!(player->map->map_collectibles))
		return (mlx_destroy_image(player->map->mlx_ptr, player->map->map_wall),
			0);
	player->map->map_exit = mlx_xpm_file_to_image(player->map->mlx_ptr,
			"./sprites/Other/Portal/portal.xpm", &player->map->all_size,
			&player->map->all_size);
	if (!(player->map->map_exit))
		return (mlx_destroy_image(player->map->mlx_ptr, player->map->map_wall),
			mlx_destroy_image(player->map->mlx_ptr,
				player->map->map_collectibles), 0);
	if (!player_init(player))
		return (mlx_destroy_image(player->map->mlx_ptr, player->map->map_wall),
			mlx_destroy_image(player->map->mlx_ptr,
				player->map->map_collectibles),
			mlx_destroy_image(player->map->mlx_ptr, player->map->map_exit), 0);
	return (1);
}
// map->map_personage = mlx_xpm_file_to_image(map->mlx_ptr,
// 		"./sprites/Pac-Man/pac_closed.xpm", &map->all_size ,&map->all_size );
// if (!(map->map_personage))

int	ft_draw_map(char *file_name, t_map *map, t_player *player)
{
	map->map_matrix = matrix(file_name, map->width);
	if (!img_init(player) || !(map->map_matrix) || !is_correct_map(map))
		return (close_game(player), 0);
	render(player);
	return (1);
}

int	ft_draw(char *file_name, t_map *map)
{
	t_player	*player;

	map->behavior = 0;
	player = malloc(sizeof(t_player));
	player->map = map;
	player->last_frame_time = 0;
	player->current_frame = 0;
	if (!player)
		return (0);
	map->mlx_ptr = mlx_init();
	if (!(map->mlx_ptr))
		return (0);
	map->mlx_win = mlx_new_window(map->mlx_ptr, (map->height * SIZE),
			(map->width * SIZE), "so_long");
	if (!map->mlx_win)
		return (mlx_destroy_display(map->mlx_ptr), free(player),
			free(map->mlx_ptr), 0);
	if (!ft_draw_map(file_name, map, player))
		return (mlx_destroy_display(map->mlx_ptr), free(player),
			free(map->mlx_ptr), 0);
	key_behavior(player);
	mlx_loop_hook(player->map->mlx_ptr, update_animation, player);
	mlx_loop(map->mlx_ptr);
	return (1);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		print_error(NULL, "Error\n", STDERR_FILENO);
	if (argc != 2)
		print_error(map, "Error\n", STDERR_FILENO);
	if (!ft_validate(argv[1], map))
		print_error(map, "Error\n", STDERR_FILENO);
	if (!ft_draw(argv[1], map))
		print_error(map, "Error\n", STDERR_FILENO);
}
