/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:10:42 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/05 17:43:22 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move(t_data *data, int new_x, int new_y);
static void	positive_itoa(long n, char **result, int i, int sign);

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	long	l_num;
	int		sign;

	l_num = n;
	sign = 0;
	result = NULL;
	i = 0;
	if (l_num < 0)
	{
		l_num = -l_num;
		sign = 1;
	}
	positive_itoa(l_num, &result, i, sign);
	return (result);
}

static void	positive_itoa(long n, char **result, int i, int sign)
{
	long	div;
	long	temp_num;
	int		digits;

	temp_num = n;
	div = 1;
	digits = 1;
	while (temp_num / 10 != 0)
	{
		temp_num /= 10;
		div *= 10;
		digits++;
	}
	*result = malloc((digits + 1 + sign) * sizeof(char));
	if (!(*result))
		return ;
	if (sign == 1)
		(*result)[i++] = '-';
	while (div >= 1)
	{
		(*result)[i++] = '0' + (n / div);
		n %= div;
		div /= 10;
	}
	(*result)[i++] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[j + i] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

// called whenever the user press a key
// is a hook function
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

// move the player 1 position and updates the values
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
			write(1, "YOU WIN!\n", 9);
			exit_program(data);
		}
	}
	if (data->map[new_y][new_x] != '1')
	{
		data->num_moves += 1;
		data->map[data->start_y][data->start_x] = '0';
		data->start_x = new_x;
		data->start_y = new_y;
		data->map[data->start_y][data->start_x] = 'P';
		print_map(data);
	}
}
