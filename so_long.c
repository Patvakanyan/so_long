/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:25:39 by apatvaka          #+#    #+#             */
/*   Updated: 2025/04/23 18:52:52 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_draw_map(char *file_name, t_map *map, void *mlx_ptr, void *mlx_win)
{
	int	x;
	int	y;

	map->
}

int	ft_draw(char *file_name, t_map *map)
{
	void	*mlx_ptr;
	void	*mlx_win;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (0);
	mlx_win = mlx_new_window(mlx_ptr, (map->width * SIZE), (map->height * SIZE),
			"so_long");
	if (!mlx_win)
		return (mlx_destroy_display(mlx_ptr), free(mlx_ptr), 0);
	map->map_wall = "./sprites/Other/Walls/wall.xpm";
	map->map_exit = "./sprites/Other/Portal/portal.xpm";
	map->personage = "./sprites/Pac-Man/pac_closed.xpm";
	map->map_collectibles = "./sprites/Other/Pacdots/pacdot_powerup.xpm";
	if (!ft_draw_map(file_name, map, mlx_ptr, mlx_win))
		return (mlx_destroy_display(mlx_ptr), free(mlx_ptr), 0);
	mlx_loop(mlx_ptr);
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
	if (!ft_valide(argv[1], map))
		print_error(map, "Error\n", STDERR_FILENO);
	if (!ft_draw(argv[1], map))
		print_error(map, "Ehhhrror\n", STDERR_FILENO);
}
