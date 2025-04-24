/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:25:39 by apatvaka          #+#    #+#             */
/*   Updated: 2025/04/24 19:52:32 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		return (free(map->map_wall), 0);
	map->map_exit = mlx_xpm_file_to_image(map->mlx_ptr,
			"./sprites/Other/Portal/portal.xpm", &all_size, &all_size);
	if (!(map->map_exit))
		return (free(map->map_wall), free(map->map_collectibles), 0);
	map->map_personage = mlx_xpm_file_to_image(map->mlx_ptr,
			"./sprites/Pac-Man/pac_semi_up.xpm", &all_size, &all_size);
	if (!(map->map_personage))
		return (free(map->map_wall), free(map->map_collectibles),
			free(map->map_exit), 0);
	return (1);
}

char	**matrix(char *file_name, int width, int height)
{
	int		fd;
	int		i;
	char	**ret;

	i = -1;
	fd = open(file_name, O_RDONLY);
	ret = (char **)malloc(sizeof(char *) * (width));
	if (!ret || fd < 0)
		return (NULL);
	while (++i < width)
	{
		ret[i] = (char *)malloc(height);
		if (!ret[i])
			return (ft_free(ret), close(fd), NULL);
		ret[i] = get_next_line(fd);
		if (!ret[i])
			return (ft_free(ret), NULL);
	}
	close(fd);
	return (ret);
}

int	ft_draw_map(char *file_name, t_map *map, void *mlx_ptr, void *mlx_win)
{
	int	x;
	int	y;

	map->map_matrix = matrix(file_name, map->width, map->height); // free
	if (!img_init(map) || !(map->map_matrix))
		return (0);
	y = -1;
	while (++y < map->width)
	{
		x = -1;
		while (++x < map->height)
		{
			if (map->map_matrix[y][x] == wall)
				mlx_put_image_to_window(mlx_ptr, mlx_win, map->map_wall, x
					* SIZE, y * SIZE);
			if (map->map_matrix[y][x] == exit_map)
				mlx_put_image_to_window(mlx_ptr, mlx_win, map->map_exit, x
					* SIZE, y * SIZE);
			if (map->map_matrix[y][x] == personage)
				mlx_put_image_to_window(mlx_ptr, mlx_win, map->map_personage, x
					* SIZE, y * SIZE);
			if (map->map_matrix[y][x] == collectibles)
				mlx_put_image_to_window(mlx_ptr, mlx_win, map->map_collectibles,
					x * SIZE, y * SIZE);
		}
	}
	return (1);
}

int	ft_draw(char *file_name, t_map *map)
{
	map->mlx_ptr = mlx_init();
	if (!(map->mlx_ptr))
		return (0);
	map->mlx_win = mlx_new_window(map->mlx_ptr, (map->height * SIZE), (map->width * SIZE), "so_long");
	if (!map->mlx_win)
		return (mlx_destroy_display(map->mlx_ptr), free(map->mlx_ptr), 0);
	if (!ft_draw_map(file_name, map, map->mlx_ptr, map->mlx_win))
		return (mlx_destroy_display(map->mlx_ptr), free(map->mlx_ptr), 0);
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
	if (!ft_valide(argv[1], map))
		print_error(map, "Error\n", STDERR_FILENO);
	if (!ft_draw(argv[1], map))
		print_error(map, "Error\n", STDERR_FILENO);
}
