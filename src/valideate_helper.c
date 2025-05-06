/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valideate_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:15:59 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/06 20:21:36 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_correct_str(char *str, int len)
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
			&& str[i] != PERSONAGE && str[i] != '0' && str[i] != MONSTER
			&& str[i] != '\n')
			return (0);
	return (1);
}

void	flood_fill(t_player *player, int x, int y, char new)
{
	if (x < 0 || y < 0 || x >= player->map->width || y >= player->map->height
		|| (*player->arr)[x][y] == '1' || (*player->arr)[x][y] == 'X'
		|| (*player->arr)[x][y] == 'M')
		return ;
	(*player->arr)[x][y] = new;
	flood_fill(player, x - 1, y, new);
	flood_fill(player, x + 1, y, new);
	flood_fill(player, x, y - 1, new);
	flood_fill(player, x, y + 1, new);
}

int	ft_validate(char *file_name, t_map *map)
{
	map->width = 0;
	if (!is_correct_name(file_name))
		return (0);
	map->fd = open(file_name, O_RDONLY);
	if (map->fd < 0)
		return (0);
	map->str = get_next_line(map->fd);
	if (!(map->str))
		return (0);
	map->height = ft_strlen(map->str) - 1;
	if (map->height < 0)
		return (free(map->str), get_next_line(-1), close(map->fd), 0);
	while (map->str)
	{
		if (!is_correct_str(map->str, map->height))
			return (free(map->str), get_next_line(-1), close(map->fd), 0);
		++(map->width);
		free(map->str);
		map->str = get_next_line(map->fd);
	}
	close(map->fd);
	return (1);
}

int	is_correct_name(char *name)
{
	char	*tmp;
	char	*dup_str;

	tmp = ft_strrchr(name, '.');
	if (!tmp)
		return (0);
	dup_str = ft_strdup(tmp);
	if (ft_strcmp(dup_str, ".ber"))
		return (free(dup_str), 0);
	return (free(dup_str), 1);
}
