/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:42:40 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/08 00:42:33 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
// Custom declarations
# include "./mlx/mlx.h"
# define BUFFER_SIZE 42
// im_s : image size(its square)
# define IMG_S 60
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define ON_DESTROY 17

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

// t_img: one image per map element
// map[][]: a NULL terminated array of strings-lines of the map
// eaten_col: how many collectives the player eated
// num_col: total number of collectives
// start_x; column of starting point 'P'
// start_y; row of starting point 'P'
// end_x; column of ending point 'E'
// end_y; row of ending point 'E'
// num_moves: how many moves player did
// player1: player before collect all the collectives
// player2: player after collect all the collectives
// gate1, gate2 same as players but for gate
typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	int		num_moves;
	int		num_col;
	int		eaten_col;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	t_img	*i_bg;
	t_img	*i_player1;
	t_img	*i_player2;
	t_img	*i_col[4];
	t_img	*i_gate1;
	t_img	*i_gate2;
	t_img	*i_wall;
}			t_data;

// Declarations of get_next_line
char	*get_next_line(int fd);
void	put_buffer(char buffer[BUFFER_SIZE], int num_bytes, char **mem_str);
char	*get_whole_str(char **mem_str);
// Declarations of get_next_line_utils
int		ft_strlen(char *str);
char	*get_first_line(char **mem_str);
// Declarations of validation_utils.c
int		check_nl(int *num_lines, int fd);
int		check_borders(char **map);
int		check_rectagle(char **map);
int		check_chars(char **map);
int		check_args(int argc, char **argv);
// Declarations of validation.c
char	**get_map(int argc, char **argv);
int		check_paths(char **map);
// Declarations of main_utils.c
void	print_map(t_data *data);
void	game_init(t_data *data);
void	imgs_init(t_data *d);
int		exit_program(t_data *data);
// Declarations of main_utils2.c
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
int		on_keypress(int keysym, t_data *data);
// Declarations of main.c
int		get_map_len(char **map);
// Declarations of check_paths.c
int		check_paths(char **map);
#endif
