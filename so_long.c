/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:25:39 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/01 17:40:44 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	key_behavior(t_map *map)
{
	mlx_hook(map->mlx_win, 2, 1L << 0, key_hook, map);
	mlx_hook(map->mlx_win, 17, 1L << 0, close_game, map);
}

int	img_init(t_map *map)
{
	int	all_size;

	all_size = SIZE;
	map->map_wall = mlx_xpm_file_to_image(map->mlx_ptr,
			"./sprites/Other/Walls/wall.xpm", &all_size, &all_size);
	if (!(map->map_wall))
		return (0);
	map->map_collectibles = mlx_xpm_file_to_image(map->mlx_ptr,
			"./sprites/Other/Pacdots/pacdot_powerup.xpm", &all_size, &all_size);
	if (!(map->map_collectibles))
		return (mlx_destroy_image(map->mlx_ptr, map->map_wall), 0);
	map->map_exit = mlx_xpm_file_to_image(map->mlx_ptr,
			"./sprites/Other/Portal/portal.xpm", &all_size, &all_size);
	if (!(map->map_exit))
		return (mlx_destroy_image(map->mlx_ptr, map->map_wall),
			mlx_destroy_image(map->mlx_ptr, map->map_collectibles), 0);
	map->map_personage = mlx_xpm_file_to_image(map->mlx_ptr,
			"./sprites/Pac-Man/pac_closed.xpm", &all_size, &all_size);
	if (!(map->map_personage))
		return (mlx_destroy_image(map->mlx_ptr, map->map_wall),
			mlx_destroy_image(map->mlx_ptr, map->map_collectibles),
			mlx_destroy_image(map->mlx_ptr, map->map_exit), 0);
	return (1);
}

int	ft_draw_map(char *file_name, t_map *map)
{
	map->map_matrix = matrix(file_name, map->width);
	if (!img_init(map) || !(map->map_matrix) || !is_correct_map(map))
		return (close_game(map), 0);
	render(map);
	return (1);
}

int	ft_draw(char *file_name, t_map *map)
{
	map->mlx_ptr = mlx_init();
	if (!(map->mlx_ptr))
		return (0);
	map->mlx_win = mlx_new_window(map->mlx_ptr, (map->height * SIZE),
			(map->width * SIZE), "so_long");
	if (!map->mlx_win)
		return (mlx_destroy_display(map->mlx_ptr), free(map->mlx_ptr), 0);
	if (!ft_draw_map(file_name, map))
		return (mlx_destroy_display(map->mlx_ptr), free(map->mlx_ptr), 0);
	key_behavior(map);
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
