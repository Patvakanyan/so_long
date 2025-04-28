/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:31:34 by apatvaka          #+#    #+#             */
/*   Updated: 2025/04/28 16:37:30 by apatvaka         ###   ########.fr       */
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
			return (get_next_line(-1), ft_free(ret, width), NULL);
	}
	close(fd);
	return (ret);
}

int	is_correct_str(char *str, int len)
{
	int	i;
	int	actual_len;

	actual_len = ft_strlen(str);
	if (str[actual_len - 1] == '\n')
		--actual_len;
	if (actual_len != len)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != wall && str[i] != collectibles && str[i] != exit_map
			&& str[i] != personage && str[i] != '0' && str[i] != '\n')
			return (0);
		++i;
	}
	return (1);
}

int	ft_valide(char *file_name, t_map *map)
{
	int		fd;
	char	*str;

	map->width = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	str = get_next_line(fd);
	map->height = ft_strlen(str) - 1;
	if (map->height < 0)
		return (0);
	while (str)
	{
		if (!is_correct_str(str, map->height))
			return (free(str), close(fd), 0);
		++(map->width);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (1);
}
