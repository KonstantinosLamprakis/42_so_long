/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:31:49 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/03 08:59:16 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO:
// remove stdio.h from .h
// remove wildcard from makefile
// check fd for error after open-close-read
	// - on error: free mem, exit with "Error\n" followed by custom error msg
	// - should have valid path from P to E
// check for leaks also in get_next_line
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

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hellota world!");
	mlx_loop(mlx);
}

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
