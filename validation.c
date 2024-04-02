/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:58:02 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/02 19:06:19 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Input validation rules:
	- exactly one argument
	- the argument should be name of file ending at ?.ber

	- should have only chars [01CEP\n]
	- should have only 1 'E', 1 'P' and at least 1 'C'

	- should be rectagle means every sentense same lenth
	- should have at least 3 lines, and at least 3 chars len per line

	- should be only "1" at each side (up, down, left, right)

	- should not end with \n\0, but only with \n
	- should not have 2 continuous \n
	- should not start with \n
 */

#include "so_long.h"

static char	**clean_map_file(char **map, int fd, char *err_msg);
static char	**validate_map(char **map, int fd);

// returns NULL if error, map otherwise
// map: a NULL terminated array of strings-lines of the map
char	**get_map(int argc, char **argv)
{
	char	**map;
	int		fd;
	int		i;

	if (!check_args(argc, argv))
		return (clean_map_file(NULL, -1, "Error\nWrong Args\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (!check_nl(&i, fd) || i < 3)
		return (clean_map_file(NULL, fd, "Error\nRemove new lines\n"));
	if (close(fd) == -1)
		return (NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = malloc((i + 1) * sizeof(char *));
	if (!map)
		return (clean_map_file(map, fd, ""));
	i = 0;
	map[i] = get_next_line(fd);
	while (map[i])
		map[++i] = get_next_line(fd);
	return (validate_map(map, fd));
}

// returns NULL if error, map otherwise
// map: a NULL terminated array of strings-lines of the map
static char	**validate_map(char **map, int fd)
{
	if (!check_borders(map))
		return (clean_map_file(map, fd, "Error\nCheck walls\n"));
	if (!check_rectagle(map))
		return (clean_map_file(map, fd, "Error\nShould be rectagle\n"));
	if (!check_chars(map))
		return (clean_map_file(map, fd, "Error\nCheck characters\n"));
	if (close(fd) == -1)
		return (clean_map_file(map, -1, ""));
	return (map);
}

static char	**clean_map_file(char **map, int fd, char *err_msg)
{
	int	i;

	i = 0;
	while (err_msg[i] != '\0')
		write(1, &err_msg[i++], 1);
	if (fd > 0)
		close(fd);
	if (!map)
		return (NULL);
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	return (NULL);
}
