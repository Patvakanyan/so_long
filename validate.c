/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:31:34 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/03 22:59:56 by apatvaka         ###   ########.fr       */
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

void	flood_fill(t_player *player, int x, int y, char new)
{
	if (x < 0 || y < 0 || x >= player->map->width || y >= player->map->height
		|| (*player->arr)[x][y] == '1' || (*player->arr)[x][y] == 'X')
		return ;
	(*player->arr)[x][y] = new;
	flood_fill(player, x - 1, y, new);
	flood_fill(player, x + 1, y, new);
	flood_fill(player, x, y - 1, new);
	flood_fill(player, x, y + 1, new);
}

static int	ft_correct_WALL(char **map_copy, t_map *map)
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
				&& map_copy[player->px][player->py] != '1')
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
	if (!ft_correct_WALL(map_copy, map))
		return (ft_free(map_copy, map->width), 0);
	return (ft_free(map_copy, map->width), 1);
}

int	is_correct_str(char *str, int len)
{
	int	i;
	int	actual_len;

	actual_len = ft_strlen(str);
	if (str[actual_len - 1] == '\n')
		--actual_len;
	if (str[0] != '1' || str[actual_len - 1] != '1')
		return (0);
	if (actual_len != len)
		return (0);
	i = -1;
	while (str[++i])
		if (str[i] != WALL && str[i] != COLLECTIBLES && str[i] != EXIT_MAP
			&& str[i] != PERSONAGE && str[i] != '0' && str[i] != '\n')
			return (0);
	return (1);
}

int	is_correct_name(char *name)
{
	char	*tmp;
	char	*dup_str;

	tmp = ft_strrchr(name, '.');
	dup_str = ft_strdup(tmp);
	if (ft_strcmp(dup_str, ".ber"))
		return (free(dup_str), 0);
	return (free(dup_str), 1);
}

int	ft_validate(char *file_name, t_map *map)
{
	int		fd;
	char	*str;

	map->width = 0;
	if (!is_correct_name(file_name))
		return (0);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	str = get_next_line(fd);
	map->height = ft_strlen(str) - 1;
	if (map->height < 0)
		return (free(str), get_next_line(-1), close(fd), 0);
	while (str)
	{
		if (!is_correct_str(str, map->height))
			return (free(str), get_next_line(-1), close(fd), 0);
		++(map->width);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	if (map->height == map->width)
		return (0);
	return (1);
}
