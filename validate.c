/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:31:34 by apatvaka          #+#    #+#             */
/*   Updated: 2025/04/24 19:49:04 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_correct_str(char *str, int len)
{
	int	i;
	int	actual_len;

	actual_len = ft_strlen(str) - 1;
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
	while (str)
	{
		if (!is_correct_str(str, map->height))
			return (free(str), 0);
		++(map->width);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	ft_printf("map_heigt = %d\n map_width = %d\n", map->height, map->width);
	return (1);
}
