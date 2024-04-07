/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:31:49 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/08 01:25:24 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cc -Wall -Werror -Wextra *.c *.h && ./a.out map.ber
// norminette get_next_line_utils.c get_next_line.c so_long.h main.c
// main_utils.c validation.c validation_utils.c main_utils2.c check_paths.c

/*
	Input validation rules:
		- exactly one argument
		- the argument should be name of file ending at ?.ber
		- should have only chars [01CEP\n]
		- should have only 1 'E', 1 'P' and at least 1 'C'
		- should be rectagle means every sentense same lenth
		- should be only 1 at each side (up, down, left, right)
		- should have at least 3 lines, and at least 3 chars len per line
		- should not end with \n\0, but only with \n
		- should not have 2 continuous \n
		- on error: free mem, exit with "Error\n" followed by custom error msg

	Notes:
		- I changed get_next_line to return each line without \n but with \0
		- protect mlx_init(): use "env -i <your-executable>" to test it
			- crashes on empty shell environments
*/

#include "so_long.h"

static void	destroy_map(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	data.map = get_map(argc, argv);
	if (!data.map)
		exit(1);
	if (!check_paths(data.map))
		exit(1);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, ft_strlen(data.map[0]) * IMG_S, \
	get_map_len(data.map) * IMG_S, "Game of Life");
	if (!data.win)
		return (free(data.mlx), 1);
	game_init(&data);
	imgs_init(&data);
	mlx_key_hook(data.win, on_keypress, &data);
	mlx_hook(data.win, ON_DESTROY, 0, exit_program, &data);
	print_map(&data);
	mlx_loop(data.mlx);
	return (0);
}

// returns the length of the map, basically the number of rows
int	get_map_len(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

// free everything
int	exit_program(t_data *data)
{
	if (data->i_gate1)
		mlx_destroy_image(data->mlx, data->i_gate1);
	if (data->i_gate2)
		mlx_destroy_image(data->mlx, data->i_gate2);
	if (data->i_player1)
		mlx_destroy_image(data->mlx, data->i_player1);
	if (data->i_player2)
		mlx_destroy_image(data->mlx, data->i_player2);
	if (data->i_wall)
		mlx_destroy_image(data->mlx, data->i_wall);
	if (data->i_bg)
		mlx_destroy_image(data->mlx, data->i_bg);
	if (data->i_col[0])
		mlx_destroy_image(data->mlx, data->i_col[0]);
	if (data->i_col[1])
		mlx_destroy_image(data->mlx, data->i_col[1]);
	if (data->i_col[2])
		mlx_destroy_image(data->mlx, data->i_col[2]);
	if (data->i_col[3])
		mlx_destroy_image(data->mlx, data->i_col[3]);
	mlx_destroy_window(data->mlx, data->win);
	destroy_map(data);
	exit(0);
}

static void	destroy_map(t_data *data)
{
	int	i;

	i = -1;
	while (data->map[++i])
		free(data->map[i]);
	free(data->map);
}
