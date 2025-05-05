/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:22:15 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/06 00:07:16 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "mlx/mlx.h"
// # include <stdio.h>
# include <string.h>

typedef struct s_map
{
	char	**map_matrix;
	char	*str;
	int		fd;
	void	*mlx_ptr;
	void	*mlx_win;
	void	*map_wall;
	void	*map_collectibles;
	void	*map_exit;
	int		all_size;
	int		x;
	int		y;
	int		behavior;
	int		height;
	int		width;
}			t_map;

typedef struct s_player
{
	int		px;
	int		py;
	char	***arr;
	void	**pac_man;
	void	**monster;
	int		monster_frame;
	int		monster_behavior;
	int		monster_step;
	void	*pac_man_left;
	void	*pac_man_right;
	void	*pac_man_down;
	void	*pac_man_up;
	int		current_frame;
	double	current_time;
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
# define MONSTER 'M'
# define FRAME_DELAY 2000
# define MONSTER_RENDER 1000
# define MONSTER_STEP 250

int			is_correct_map(t_map *map);
int			ft_validate(char *str, t_map *map);
void		print_error(t_map *map, char *str, int code);
void		ft_free(char **str, int width);
void		move_player(t_player *player, char behavior);
int			key_hook(int keycode, t_player *player);
void		choose_img(t_player *player, int x, int y);
int			close_game(t_player *player);
void		player_position(t_map *map, int *x, int *y);

void		move_left(t_player *player, int x, int y, int coin);
void		move_right(t_player *player, int x, int y, int coin);
void		move_bottom(t_player *player, int x, int y, int coin);
void		move_top(t_player *player, int x, int y, int coin);

int			update_animation(t_player *player);
int			update_monster(t_player *player);
int			player_init(t_player *player);
void		render(t_player *player);
int			count_coins(t_map *map);
char		**matrix(char *file_name, int width);

int			is_correct_name(char *name);
int			ft_validate(char *file_name, t_map *map);
void		flood_fill(t_player *player, int x, int y, char new);
int			monster_init(t_player *player);
void		monster_step(t_player *player);
#endif
