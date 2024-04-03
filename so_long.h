/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:42:40 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/03 18:19:45 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
// Custom declarations
# include "./mlx/mlx.h"
# define BUFFER_SIZE 42
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

typedef struct s_data
{
	void	*mlx;
	void	*win;
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
#endif
