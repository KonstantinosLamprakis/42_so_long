/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:20:41 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/05 14:50:26 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move(t_data *data, int new_x, int new_y);

void	print_map(t_data *d)
{
	int		i;
	int		j;

	i = -1;
	while (d->map[++i])
	{
		j = -1;
		while (d->map[i][++j] != '\0')
		{
			mlx_put_image_to_window(d->mlx, d->win, d->i_bg, j * IMG_S, i * IMG_S);
			if (d->map[i][j] == '1')
				mlx_put_image_to_window(d->mlx, d->win, d->i_wall, j * IMG_S, i * IMG_S);
			else if (d->map[i][j] == 'P' && d->eaten_col != d->num_col)
				mlx_put_image_to_window(d->mlx, d->win, d->i_player1, j * IMG_S, i * IMG_S);
			else if (d->map[i][j] == 'P' && d->eaten_col == d->num_col)
				mlx_put_image_to_window(d->mlx, d->win, d->i_player2, j * IMG_S, i * IMG_S);
			else if (d->map[i][j] == 'E' && d->eaten_col != d->num_col)
				mlx_put_image_to_window(d->mlx, d->win, d->i_gate1, j * IMG_S, i * IMG_S);
			else if (d->map[i][j] == 'E' && d->eaten_col == d->num_col)
				mlx_put_image_to_window(d->mlx, d->win, d->i_gate2, j * IMG_S, i * IMG_S);
			else if (d->map[i][j] == 'C')
				mlx_put_image_to_window(d->mlx, d->win, d->i_col[j % 4], j * IMG_S, i * IMG_S);
		}
	}
}

int	get_map_len(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	game_init(t_data *data)
{
	int	i;
	int	j;

	data->num_col = 0;
	data->num_moves = 0;
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j] != '\0')
		{
			if (data->map[i][j] == 'P')
			{
				data->start_x = j;
				data->start_y = i;
			}
			else if (data->map[i][j] == 'E')
			{
				data->end_x = j;
				data->end_y = i;
			}
			else if (data->map[i][j] == 'C')
				data->num_col += 1;
		}
	}
}

void	imgs_init(t_data *d)
{
	int	w;
	int	h;

	d->i_gate1 = mlx_xpm_file_to_image(d->mlx, "xpms/gate1.xpm", &w, &h);
	d->i_gate2 = mlx_xpm_file_to_image(d->mlx, "xpms/gate2.xpm", &w, &h);
	d->i_player1 = mlx_xpm_file_to_image(d->mlx, "xpms/player1.xpm", &w, &h);
	d->i_player2 = mlx_xpm_file_to_image(d->mlx, "xpms/player2.xpm", &w, &h);
	d->i_col[0] = mlx_xpm_file_to_image(d->mlx, "xpms/gym1.xpm", &w, &h);
	d->i_col[1] = mlx_xpm_file_to_image(d->mlx, "xpms/gym2.xpm", &w, &h);
	d->i_col[2] = mlx_xpm_file_to_image(d->mlx, "xpms/gym3.xpm", &w, &h);
	d->i_col[3] = mlx_xpm_file_to_image(d->mlx, "xpms/gym4.xpm", &w, &h);
	d->i_wall = mlx_xpm_file_to_image(d->mlx, "xpms/wall.xpm", &w, &h);
	d->i_bg = mlx_xpm_file_to_image(d->mlx, "xpms/bg.xpm", &w, &h);
}

int	exit_program(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	exit(0);
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

static void	move(t_data *data, int new_x, int new_y)
{
	if (data->map[new_y][new_x] == 'C')
		data->eaten_col += 1;
	if (data->map[new_y][new_x] == 'E')
	{
		if (data->eaten_col < data->num_col)
			return ;
		else
		{
			printf("WIN\n");
			exit(1);
		}
	}
	if (data->map[new_y][new_x] != '1')
	{
		data->num_moves += 1;
		data->map[data->start_y][data->start_x] = '0';
		data->start_x = new_x;
		data->start_y = new_y;
		data->map[data->start_y][data->start_x] = 'P';
		printf("moves: %d\ncolected: %d/%d\n", data->num_moves, data->eaten_col, data->num_col);
		print_map(data);
	}
}
