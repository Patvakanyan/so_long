/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:22:15 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/01 17:47:36 by apatvaka         ###   ########.fr       */
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

typedef struct s_player
{
	int		px;
	int		py;
	char	***arr;
	t_map	*map;
}			t_player;

# define SIZE 32
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define WALL '1'
# define COLLECTIBLES 'C'
# define EXIT_MAP 'E'
# define PERSONAGE 'P'

int			is_correct_map(t_map *map);
int			ft_validate(char *str, t_map *map);
void		print_error(t_map *map, char *str, int code);
void		ft_free(char **str, int width);
void		move_player(t_map *map, char behavior);
int			key_hook(int keycode, t_map *map);
int			close_game(t_map *map);
void		player_position(t_map *map, int *x, int *y);

void		move_left(t_map *map, int x, int y, int coin);
void		move_right(t_map *map, int x, int y, int coin);
void		move_bottom(t_map *map, int x, int y, int coin);
void		move_top(t_map *map, int x, int y, int coin);

void		render(t_map *map);
int			count_coins(t_map *map);
char		**matrix(char *file_name, int width);
#endif
