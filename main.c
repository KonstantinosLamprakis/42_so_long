/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:31:49 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/05 10:45:01 by klamprak         ###   ########.fr       */
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

static int get_map_len(char **map);

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

int	main(int argc, char **argv)
{
	t_data	data;
	void	*img;
	int		img_width;
	int		img_height;
	char	**map;
	int		i;
	int		j;

	map = get_map(argc, argv);
	if (!map)
		exit(1);
	i = -1;
	while (map[++i])
		printf("%s\n", map[i]);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, ft_strlen(map[0]) * IMG_SIZE, get_map_len(map) * IMG_SIZE, "Game of Life");
	if (!data.win)
		return (free(data.mlx), 1);
	mlx_key_hook(data.win, on_keypress, &data);
	mlx_hook(data.win, ON_DESTROY, 0, exit_program, &data);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while(map[i][++j] != '\0')
		{
			img = mlx_xpm_file_to_image(data.mlx, "xpm/bg.xpm", &img_width, &img_height);
			mlx_put_image_to_window(data.mlx, data.win, img, j * IMG_SIZE, i * IMG_SIZE);
			if (map[i][j] == '1')
			{
				img = mlx_xpm_file_to_image(data.mlx, "xpm/wall.xpm", &img_width, &img_height);
				mlx_put_image_to_window(data.mlx, data.win, img, j * IMG_SIZE, i * IMG_SIZE);
			}
			else if(map[i][j] == 'P')
			{
				img = mlx_xpm_file_to_image(data.mlx, "xpm/start.xpm", &img_width, &img_height);
				mlx_put_image_to_window(data.mlx, data.win, img, j * IMG_SIZE, i * IMG_SIZE);
			}
			else if(map[i][j] == 'E')
			{
				img = mlx_xpm_file_to_image(data.mlx, "xpm/end.xpm", &img_width, &img_height);
				mlx_put_image_to_window(data.mlx, data.win, img, j * IMG_SIZE, i * IMG_SIZE);
			}
			else if(map[i][j] == 'C')
			{
				img = mlx_xpm_file_to_image(data.mlx, "xpm/gym1.xpm", &img_width, &img_height);
				mlx_put_image_to_window(data.mlx, data.win, img, j * IMG_SIZE, i * IMG_SIZE);
			}
		}
	}
	mlx_loop(data.mlx);
	return (0);
}

static int get_map_len(char **map)
{
	int	i;

	i = 0;
	while(map[i])
		i++;
	return (i);
}

// --------------------

// -- Image with just a color dot
// void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_img	img;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
// 	img.img = mlx_new_image(mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
// 	my_mlx_pixel_put(&img, 50, 50, 0x00FF0000);
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	mlx_loop(mlx);
// }
