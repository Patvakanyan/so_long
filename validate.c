/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:31:34 by apatvaka          #+#    #+#             */
/*   Updated: 2025/04/23 18:26:57 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_correct_str(char *str, int len)
{
	int	i;
	int	actual_len;

	actual_len = ft_strlen(str);
	if (actual_len != len)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != wall && str[i] != collectibles && str[i] != exit_map
			&& str[i] != position && str[i] != '0' && str[i] != '\n')
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
	map->height  = ft_strlen(str);
	while (str)
	{
		if (!is_correct_str(str, map->height ))
			return (free(str), 0);
		++(map->width);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (1);
}
