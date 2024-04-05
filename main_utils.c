/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:20:41 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/05 13:13:50 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move(t_data *data, int new_x, int new_y);

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

void	set_start_pos(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while(data->map[i][++j] != '\0')
		{
			if(data->map[i][j] == 'P')
			{
				data->start_x = j;
				data->start_y = i;
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
	if (keysym == ESC)
		exit_program(data);
	else if (keysym == W || keysym == UP)
		move(data, data->start_x, data->start_y - 1);
	else if (keysym == A || keysym == LEFT)
		move(data, data->start_x - 1, data->start_y);
	else if (keysym == S || keysym == DOWN)
		move(data, data->start_x, data->start_y + 1);
	else if (keysym == D || keysym == RIGHT)
		move(data, data->start_x + 1, data->start_y);
	return (0);
}

void	move(t_data *data, int new_x, int new_y)
{
	if (data->map[new_y][new_x] != '1')
	{
		data->map[data->start_y][data->start_x] = '0';
		data->start_x = new_x;
		data->start_y = new_y;
		data->map[data->start_y][data->start_x] = 'P';
		print_map(data);
	}
}
