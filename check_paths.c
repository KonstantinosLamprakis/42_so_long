/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 00:22:15 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/11 15:12:53 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	flood(int x, int y, char **map);
static char	**copy_map(char **map, int len_x, int len_y);
static void	get_path(char **map, int *flag);

// checks if all collectives, exit and starting point are accesible
// returns 1 if they are accessible, 0 if there are invalid, no possible route
int	check_paths(char **map)
{
	char	**map_fill;
	int		i;
	int		not_valid;

	not_valid = 0;
	map_fill = copy_map(map, ft_strlen(map[0]), get_map_len(map));
	if (!map_fill)
		return (0);
	get_path(map_fill, &not_valid);
	i = get_map_len(map);
	while (--i >= 0)
		free (map_fill[i]);
	free(map_fill);
	if (not_valid)
		write(1, "Not accesible all collectives and/or exit\n", 43);
	return (!not_valid);
}

static void	get_path(char **map, int *flag)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = -1;
	x = 0;
	y = 0;
	while (map[++i] && !x && !y)
	{
		j = -1;
		while (map[i][++j] != '\0' && !x && !y)
			if (map[i][j] == 'P')
				y = j;
	}
	x = i - 1;
	*flag = !flood(x, y, map);
	i = -1;
	while (map[++i] && !(*flag))
	{
		j = -1;
		while (map[i][++j])
			*flag += (map[i][j] == 'C' || map[i][j] == 'P');
	}
}

static char	**copy_map(char **map, int len_x, int len_y)
{
	char	**result;
	int		i;
	int		j;

	result = malloc((len_y + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = -1;
	while (map[++i])
	{
		result[i] = malloc((len_x + 1) * sizeof(char));
		if (!result[i])
		{
			while (--i >= 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		j = -1;
		while (map[i][++j] != '\0')
			result[i][j] = map[i][j];
		result[i][j] = '\0';
	}
	result[i] = NULL;
	return (result);
}

// returns 1 if find exit accessible, 0 otherwise
static int	flood(int x, int y, char **map)
{
	int	is_e;

	is_e = 0;
	if (!map)
		return (0);
	if (x < 0 || y < 0 || x > get_map_len(map) - 1 || y > ft_strlen(map[0]) - 1)
		return (0);
	if (map[x][y] != '1' && map[x][y] != 'E')
	{
		map[x][y] = '1';
		is_e += flood(x + 1, y, map);
		is_e += flood(x - 1, y, map);
		is_e += flood(x, y + 1, map);
		is_e += flood(x, y - 1, map);
	}
	is_e += map[x][y] == 'E';
	return (is_e);
}
