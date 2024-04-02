/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:31:49 by klamprak          #+#    #+#             */
/*   Updated: 2024/04/02 12:51:42 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: remove stdio.h from .h
// TODO: remove wildcard from makefile
// TODO: check fd for error after open-close-read

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
#include "../MLX42/include/MLX42/MLX42.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int32_t	main(void)
{

	// MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "421Balls", true);
	if (!mlx)
		ft_error();

	/* Do stuff */

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
