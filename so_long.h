/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:22:15 by apatvaka          #+#    #+#             */
/*   Updated: 2025/04/24 18:50:05 by apatvaka         ###   ########.fr       */
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
	char	**map_matrix;
	void	*mlx_ptr;
	void	*mlx_win;
	void	*map_wall;
	void	*map_collectibles;
	void	*map_exit;
	void	*map_personage;
	int		height;
	int		width;
}			t_map;

# define SIZE 32
# define wall '1'
# define collectibles 'C'
# define exit_map 'E'
# define personage 'P'

int			ft_valide(char *str, t_map *map);
void		print_error(t_map *map, char *str, int code);
void		ft_free(char **str);

#endif
