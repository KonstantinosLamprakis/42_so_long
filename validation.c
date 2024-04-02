/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:58:02 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/02 06:59:58 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// returns 0 if error, 1 otherwise
// errors:
// not 1 arg or less that 3 lines
// multiple \n in the row
// file opening problem
// file not ending in ?.der
int	validate_input(int argc, char **argv)
{
	char	**map;
	int		fd;
	int		i;

	if (argc != 2)
		return (0);
	i = 0;
	while (argv[1][i] != '\0')
		i++;
	if (--i < 4)
		return (0);
	fd = argv[1][i] != 'r' || argv[1][i - 1] != 'e' || argv[1][i - 2] != 'b';
	if (fd || argv[1][i - 3] != '.')
		return (0);
	i = get_lines(argv[1]);
	if (i < 3)
		return (0);
	map = malloc(i + 1 * sizeof(char *));
	if (!map)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		free(map);
		return (0);
	}
	i = 0;
	map[i] = get_next_line(fd);
	while (map[i])
		map[++i] = get_next_line(fd);
	if (close(fd) == -1)
	{
		// free_map
		return (0);
	}
}

// returns 0 if error, otherwise number of lines
// errors:
// file open-close-read
// multiple \n in the row
// last sentense ending in \n before \0
// filename: the name of the file contain the map
int	get_num_lines(char *filename)
{
	int		fd;
	int		i;
	char	buffer[BUFFER_SIZE];
	int		num_bytes;
	int		result;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	result = 0;
	while (42)
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (num_bytes == -1 || num_bytes == 0)
			break;
		else if (num_bytes < BUFFER_SIZE)
			break;
		i = -1;
		while (++i < BUFFER_SIZE)
		{
			if (buffer[i] == '\n')
				if (buffer[i + 1] == '\n' || buffer[i + 1] == '\0')
				{
					num_bytes = -1;
					break;
				}
				else
					result++;
		}
	}
	if(close(fd) == -1 || num_bytes == -1)
		return (0);
	return (result + 1);
}

// returns 0 if error, 1 otherwise
// map: list of lines of the map
// each line terminated by \0
// the map_str last element is NULL
// errors:
// use char other than "01CEP"
// more-less than 1 exit-start point, less than 1 collective element
// not possible path to exit
// not rectable(same strlen all lines), not surrouned by walls
int	validate_map(char **map_str)
{
	int	is_e;
	int	is_p;
	int	is_c;


}

// returns 1 if first-last line is only 1
// returns 0 otherwise
int	check_first_last_line(char **map_str)
{
	int	i;
	int	end;

	if (!map_str || !(*map_str))
		return (0);
	i = 0;
	while (map_str[0][i] != '\0')
		if (map_str[0][i++] != '1')
			return (0);
	end = 0;
	while (map_str[end + 1])
		end++;
	i = 0;
	while (map_str[end][i] != '\0')
		if (map_str[end][i++] != '1')
			return (end);
	return (1);
}

// returns 1 if sides have only 1
// returns 0 otherwise
int	check_left_right(char **map_str)
{
	int	i;
	int	len;

	if (!map_str || !(*map_str))
		return (0);
	len = ft_strlen(map_str[0]) - 1;
	i = -1;
	while (map_str[++i])
		if (map_str[i][0] != '1' || map_str[i][len] != '1')
			return (0);
	return (1);
}

// returns length if all line have same lenth, means its rectagle
// returns 0 otherwise, also returns 0 if length less than 3
int	check_length(char **map_str)
{
	int	i;
	int	temp;

	if (!map_str || !(*map_str))
		return (0);
	i = 0;
	temp = ft_strlen(map_str[i]);
	if (temp < 3)
		return (0);
	while (map_str[++i])
		if (temp != ft_strlen(map_str[i]))
			return (0);
	return (ft_strlen(map_str[0]));
}
