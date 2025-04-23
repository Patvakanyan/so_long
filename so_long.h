/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:22:15 by apatvaka          #+#    #+#             */
/*   Updated: 2025/04/23 18:38:05 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <stdio.h>
# include <string.h>

typedef struct s_map
{
	char	*map_wall;
	char	*map_collectibles;
	char	*map_exit;
	char	*personage;
	int		height;
	int		width;
}			t_map;

# define SIZE 64
# define wall '1'
# define collectibles 'C'
# define exit_map 'E'
# define position 'P'

int			ft_valide(char *str, t_map *map);
void		print_error(t_map *map, char *str, int code);
#endif
