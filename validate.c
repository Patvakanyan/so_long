/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:31:34 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/06 19:24:34 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**matrix(char *file_name, int width)
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
		ret[i] = get_next_line(fd);
		if (!ret[i])
			return (ft_free(ret, width), NULL);
	}
	close(fd);
	return (ret);
}

static int	is_correct_count(t_map *map, char c)
{
	int	count;
	int	i;
	int	j;

	i = -1;
	count = 0;
	while (++i < map->width)
	{
		j = -1;
		while (++j < map->height)
		{
			if (map->map_matrix[i][j] == c)
				++count;
		}
	}
	return (count);
}

int	ft_correct_wall(char **map_copy, t_map *map)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (0);
	player->py = -1;
	player->arr = &map_copy;
	player->map = map;
	player_position(map, &(player->px), &(player->py));
	flood_fill(player, player->py, player->px, 'X');
	player->px = -1;
	while (++player->px < map->width)
	{
		player->py = -1;
		while (++player->py < map->height)
		{
			if (map_copy[player->px][player->py] != 'X'
				&& map_copy[player->px][player->py] != '1'
				&& map_copy[player->px][player->py] != 'M')
				return (free(player), 0);
		}
	}
	return (free(player), 1);
}

int	is_correct_map(t_map *map)
{
	char	**map_copy;
	int		i;

	i = -1;
	if (is_correct_count(map, 'P') != 1 || is_correct_count(map, 'C') < 1
		|| is_correct_count(map, 'E') != 1)
		return (0);
	map_copy = (char **)malloc(sizeof(char *) * map->width);
	if (!map_copy)
		return (0);
	while (++i < map->width)
	{
		map_copy[i] = ft_strdup(map->map_matrix[i]);
		if (!map_copy[i])
			return (ft_free(map_copy, i), 0);
	}
	if (!ft_correct_wall(map_copy, map))
		return (ft_free(map_copy, map->width), 0);
	return (ft_free(map_copy, map->width), 1);
}
