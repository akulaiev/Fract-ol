/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 20:40:38 by akulaiev          #+#    #+#             */
/*   Updated: 2018/06/08 20:40:40 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	menu_content(t_data *win)
{
	mlx_string_put(win->mlx_p, win->mlx_nw, 155, 15, 0x1041a5, "Menu");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15, 35, 0x1041a5, "'esc' - quit");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	75, 0x1041a5, "'+'/mouse wheel - zoom in");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	95, 0x1041a5, "'-'/mouse wheel - zoom out");
	mlx_string_put(win->mlx_p, win->mlx_nw,
	15, 135, 0x1041a5, "arrows - move fract");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	155, 0x1041a5, "'c' - center and redraw fract");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	195, 0x1041a5, "'q' - enable changing Julia");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	215, 0x1041a5, "params with mouse");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	235, 0x1041a5, "'e' - disable changing Julia");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	255, 0x1041a5, "params with mouse");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	295, 0x1041a5, "'a' - change colours");
}

void	menu_frame(t_data *win)
{
	t_scale	menu;

	menu.x = -1;
	while (++menu.x < 350)
	{
		menu.y = -1;
		while (++menu.y < 950)
		{
			if (menu.x <= 10 || menu.y <= 10 || menu.x >= 340 || menu.y >= 940)
				menu.col = 0x001d59;
			else
				menu.col = 0x75a2ff;
			img_pixel_put(win, menu);
		}
	}
	mlx_put_image_to_window(win->mlx_p, win->mlx_nw, win->mlx_img, 0, 0);
	menu_content(win);
}

int		check_input(t_data *win, char *i)
{
	if ((!ft_strcmp("Julia", i) || !ft_strcmp("1", i)) && (win->fn = 1))
		open_window(win, "Julia");
	if ((!ft_strcmp("Mandelbrot", i) || !ft_strcmp("2", i)) && (win->fn = 2))
		open_window(win, "Mandelbrot");
	if ((!ft_strcmp("Newton", i) || !ft_strcmp("3", i)) && (win->fn = 3))
		open_window(win, "Newton");
	if ((!ft_strcmp("Biomorph", i) || !ft_strcmp("4", i)) && (win->fn = 4))
		open_window(win, "Biomorph");
	if ((!ft_strcmp("Lambda", i) || !ft_strcmp("5", i)) && (win->fn = 5))
		open_window(win, "Lambda");
	if ((!ft_strcmp("Spider", i) || !ft_strcmp("6", i)) && (win->fn = 6))
		open_window(win, "Spider");
	if (!ft_strcmp("exit", i))
		exit(0);
	else
		return (1);
	return (0);
}

void	print_menu(t_data *win, char *input, int err)
{
	char	*name;

	name = NULL;
	if (input)
		err = check_input(win, input);
	if (err == 1)
		write(2, "usage: ./fractol [fract name]\n", 30);
	write(1, "available fractals:\n", 20);
	write(1, "-> 1. Julia\n", 12);
	write(1, "-> 2. Mandelbrot\n", 17);
	write(1, "-> 3. Newton\n", 13);
	write(1, "-> 4. Biomorph\n", 15);
	write(1, "-> 5. Lambda\n", 13);
	write(1, "-> 6. Spider\n", 13);
	write(1, "type 'exit' to 'exit properly'\n", 31);
	while (get_next_line(0, &name))
	{
		if ((check_input(win, name)))
			print_menu(win, name, 1);
	}
}

int		main(int argc, char **argv)
{
	t_data	win;

	if (argc != 2)
		print_menu(&win, NULL, 1);
	else
		print_menu(&win, argv[1], 0);
	return (0);
}
