/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:20:41 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/05 18:08:05 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_stats(t_data *d);
static void	place_img(t_data *d, t_img *img, int x, int y);

// prints the map in every new move of the player
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
			place_img(d, d->i_bg, j * IMG_S, i * IMG_S);
			if (d->map[i][j] == '1')
				place_img(d, d->i_wall, j * IMG_S, i * IMG_S);
			else if (d->map[i][j] == 'P' && d->eaten_col != d->num_col)
				place_img(d, d->i_player1, j * IMG_S, i * IMG_S);
			else if (d->map[i][j] == 'P' && d->eaten_col == d->num_col)
				place_img(d, d->i_player2, j * IMG_S, i * IMG_S);
			else if (d->map[i][j] == 'E' && d->eaten_col != d->num_col)
				place_img(d, d->i_gate1, j * IMG_S, i * IMG_S);
			else if (d->map[i][j] == 'E' && d->eaten_col == d->num_col)
				place_img(d, d->i_gate2, j * IMG_S, i * IMG_S);
			else if (d->map[i][j] == 'C')
				place_img(d, d->i_col[j % 4], j * IMG_S, i * IMG_S);
		}
	}
	print_stats(d);
}

// just puts an image on position [x, y]
static void	place_img(t_data *d, t_img *img, int x, int y)
{
	mlx_put_image_to_window(d->mlx, d->win, img, x, y);
}

static void	print_stats(t_data *d)
{
	char	*temp1;
	char	*temp2;
	char	*str1;
	char	*str2;
	int		i;

	temp1 = ft_itoa(d->num_moves);
	str1 = ft_strjoin("Moves: ", temp1);
	free(temp1);
	temp1 = ft_itoa(d->eaten_col);
	str2 = ft_strjoin("Collectived: ", temp1);
	free(temp1);
	temp2 = ft_strjoin(str2, " \\ ");
	free(str2);
	temp1 = ft_itoa(d->num_col);
	str2 = ft_strjoin(temp2, temp1);
	free(temp1);
	free(temp2);
	i = (ft_strlen(d->map[0]) * IMG_S / 2);
	mlx_string_put(d->mlx, d->win, i, 25, 0x00FFFFFF, str1);
	mlx_string_put(d->mlx, d->win, i, 50, 0x00FFFFFF, str2);
	free(str1);
	free(str2);
}

// initialize position of starting point, ending point, number of collectives
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

// initialize all the images
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
	if (!d->i_gate1 || !d->i_gate2 || !d->i_player1 || !d->i_player2)
		exit_program(d);
	if (!d->i_col[0] || !d->i_col[1] || !d->i_col[2] || !d->i_col[3])
		exit_program(d);
	if (!d->i_wall || !d->i_bg)
		exit_program(d);
}
