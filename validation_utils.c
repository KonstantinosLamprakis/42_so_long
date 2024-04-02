/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:28:42 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/02 18:53:58 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// returns 0 on error, 1 otherwise
// errors:
// - exactly one argument
// - the argument should be name of file ending at ?.ber
int	check_args(int argc, char **argv)
{
	int	i;
	int	flag;

	if (argc != 2)
		return (0);
	i = 0;
	while (argv[1][i] != '\0')
		i++;
	if (--i < 4)
		return (0);
	flag = argv[1][i] != 'r' || argv[1][i - 1] != 'e';
	if (flag || argv[1][i - 3] != '.' || argv[1][i - 2] != 'b')
		return (0);
	return (1);
}

// returns 0 on error, 1 otherwise
// errors:
// - should have only chars [01CEP], we already removed \n
// - should have only 1 'E', 1 'P' and at least 1 'C'
// map: a NULL terminated array of strings-lines of the map
int	check_chars(char **map)
{
	int	is_p;
	int	is_e;
	int	is_c;
	int	j;

	is_p = 0;
	is_e = 0;
	is_c = 0;
	while (*map)
	{
		j = -1;
		while ((*map)[++j] != '\0')
		{
			if (((*map)[j] == 'P' && is_p) || ((*map)[j] == 'E' && is_e))
				return (0);
			is_p += (*map)[j] == 'P';
			is_e += (*map)[j] == 'E';
			is_c += (*map)[j] == 'C';
			if ((*map)[j] != 'P' && (*map)[j] != 'E' && (*map)[j] != 'C')
				if ((*map)[j] != '0' && (*map)[j] != '1')
					return (0);
		}
		map++;
	}
	return ((is_c != 0) && is_p && is_e);
}

// returns 0 on error, 1 otherwise
// errors:
// - should be rectagle means every sentense same lenth
// - should have at least 3 lines, and at least 3 chars len per line
// map: a NULL terminated array of strings-lines of the map
int	check_rectagle(char **map)
{
	int	i;
	int	temp;

	if (!map || !(*map))
		return (0);
	i = 0;
	temp = ft_strlen(map[i]);
	if (temp < 3)
		return (0);
	while (map[++i])
		if (temp != ft_strlen(map[i]))
			return (0);
	if (i < 3)
		return (0);
	return (ft_strlen(map[0]));
}

// returns 0 on error, 1 otherwise
// errors:
// - should be only 1 at each side (up, down, left, right)
// map: a NULL terminated array of strings-lines of the map
int	check_borders(char **map)
{
	int	i;
	int	last;
	int	len;

	i = 0;
	while (map[0][i] != '\0')
		if (map[0][i++] != '1')
			return (0);
	last = 0;
	while (map[last + 1])
		last++;
	i = 0;
	while (map[last][i] != '\0')
		if (map[last][i++] != '1')
			return (0);
	len = ft_strlen(map[0]) - 1;
	i = -1;
	while (map[++i])
		if (map[i][0] != '1' || map[i][len] != '1')
			return (0);
	return (1);
}

// returns 0 on error,  otherwise number of lines
// fd = file descriptor
// num_lines = variable to be updated
// errors:
// - should not end with \n\0, but only with \n
// - should not have 2 continuous \n
// - should not start with \n
// - read() returned -1
int	check_nl(int *num_lines, int fd)
{
	int		is_first;
	int		i;
	char	buf[42];
	int		num_bytes;

	num_bytes = read(fd, buf, 42);
	is_first = 1;
	*num_lines = 0;
	while (num_bytes > 0)
	{
		if (is_first && buf[0] == '\n')
			return (0);
		is_first = 0;
		i = -1;
		while (++i < num_bytes)
		{
			*num_lines += buf[i] == '\n';
			if (buf[i] == '\n' && (buf[i + 1] == '\n' || buf[i + 1] == '\0'))
				return (0);
		}
		num_bytes = read(fd, buf, 42);
	}
	if (num_bytes == -1)
		return (0);
	return (++(*num_lines));
}
