/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:22:15 by apatvaka          #+#    #+#             */
/*   Updated: 2025/04/28 17:42:14 by apatvaka         ###   ########.fr       */
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
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define wall '1'
# define collectibles 'C'
# define exit_map 'E'
# define personage 'P'

int			ft_valide(char *str, t_map *map);
void		print_error(t_map *map, char *str, int code);
void		ft_free(char **str, int width);
void		move_player(t_map *map, char behavior);
int			key_hook(int keycode, t_map *map);
int			close_game(t_map *map);
void		player_position(t_map *map, int *x, int *y);
void		render(t_map *map);
int			count_coins(t_map *map);
char		**matrix(char *file_name, int width);
#endif
