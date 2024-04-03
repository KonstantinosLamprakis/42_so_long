/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:31:49 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/03 18:22:16 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO:
// remove stdio.h from .h
// remove wildcard from makefile
// check fd for error after open-close-read
	// - on error: free mem, exit with "Error\n" followed by custom error msg
	// - should have valid path from P to E
// check for leaks also in get_next_line
// add assets to git

// cc -Wall -Werror -Wextra *.c *.h && ./a.out map.ber

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

int	on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	// mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

int	exit_program(t_data *data)
{
	(void) data;
	exit(1);
}

int	on_keypress(int keysym, t_data *data)
{
	(void) data;
	if (keysym == ESC)
		exit_program(data);
	else if (keysym == W || keysym == UP)
		printf("Pressed key: UP\n");
	else if (keysym == A || keysym == LEFT)
		printf("Pressed key: LEFT\n");
	else if (keysym == S || keysym == DOWN)
		printf("Pressed key: DOWN\n");
	else if (keysym == D || keysym == RIGHT)
		printf("Pressed key: RIGHT\n");
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, 600, 400, "hi :)");
	if (!data.win)
		return (free(data.mlx), 1);
	mlx_key_hook(data.win, on_keypress, &data);
	mlx_hook(data.win, ON_DESTROY, 0, exit_program, &data);
	mlx_loop(data.mlx);
	return (0);
}

// --------------------

// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;

// 	mlx = mlx_init();
// 	if (!mlx)
// 		exit(1);
// 	mlx_win = mlx_new_window(mlx, 1920, 1080, "The Game of Life");
// 	mlx_loop(mlx);
// }

// int	main(int argc, char **argv)
// {
// 	char	**map;
// 	int		i;

// 	map = get_map(argc, argv);
// 	if (!map)
// 		exit(1);
// 	i = -1;
// 	while (map[++i])
// 		printf("%s\n", map[i]);
// }
