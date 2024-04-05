/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:20:41 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/05 11:23:55 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	print_map(t_data *data)
{
	int	i;
	int	j;
	void	*img;
	int		img_width;
	int		img_height;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while(data->map[i][++j] != '\0')
		{
			img = mlx_xpm_file_to_image(data->mlx, "xpm/bg.xpm", &img_width, &img_height);
			mlx_put_image_to_window(data->mlx, data->win, img, j * IMG_SIZE, i * IMG_SIZE);
			if (data->map[i][j] == '1')
			{
				img = mlx_xpm_file_to_image(data->mlx, "xpm/wall.xpm", &img_width, &img_height);
				mlx_put_image_to_window(data->mlx, data->win, img, j * IMG_SIZE, i * IMG_SIZE);
			}
			else if(data->map[i][j] == 'P')
			{
				img = mlx_xpm_file_to_image(data->mlx, "xpm/start.xpm", &img_width, &img_height);
				mlx_put_image_to_window(data->mlx, data->win, img, j * IMG_SIZE, i * IMG_SIZE);
			}
			else if(data->map[i][j] == 'E')
			{
				img = mlx_xpm_file_to_image(data->mlx, "xpm/end.xpm", &img_width, &img_height);
				mlx_put_image_to_window(data->mlx, data->win, img, j * IMG_SIZE, i * IMG_SIZE);
			}
			else if(data->map[i][j] == 'C')
			{
				img = mlx_xpm_file_to_image(data->mlx, "xpm/gym1.xpm", &img_width, &img_height);
				mlx_put_image_to_window(data->mlx, data->win, img, j * IMG_SIZE, i * IMG_SIZE);
			}
		}
	}
}

int	get_map_len(char **map)
{
	int	i;

	i = 0;
	while(map[i])
		i++;
	return (i);
}

void	get_start_pos(int *x, int *y, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while(map[i][++j] != '\0')
		{
			if(map[i][j] == 'P')
			{
				*x = j;
				*y = i;
				return ;
			}
		}
	}
}

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
	int	x;
	int	y;

	get_start_pos(&x, &y, data->map);
	if (keysym == ESC)
		exit_program(data);
	else if (keysym == W || keysym == UP)
	{
		if (y > 0 && data->map[y - 1][x] != '1')
		{
			data->map[y][x] = '0';
			data->map[y - 1][x] = 'P';
			print_map(data);
			printf("Pressed key: UP\n");
		}
	}
	else if (keysym == A || keysym == LEFT)
	{
		printf("Pressed key: LEFT\n");
	}
	else if (keysym == S || keysym == DOWN)
	{
		printf("Pressed key: DOWN\n");
	}
	else if (keysym == D || keysym == RIGHT)
	{
		printf("Pressed key: RIGHT\n");
	}
	return (0);
}
