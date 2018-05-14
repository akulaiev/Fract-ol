/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   c_reated: 2018/05/07 11:46:53 by akulaiev          #+#    #+#             */
/*   Updated: 2018/05/07 11:46:55 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>



int		colour_fract(double i, t_data *win)
{
	int		r;
	int		g;
	int		b;

	r = (int)(win->c_r * (1 - i) * i * i * i * 255);
	g = (int)(win->c_g * (1 - i) * (1 - i) * i * i * 255);
	b = (int)(win->c_b * (1 - i) * (1 - i) * (1 - i) * i * 255);
	return ((r << 16) + (g << 8) + b);
}	

void	open_window(t_data *win, char *fract_name)
{
	// void	*mlx_mw;

	// mlx_mw = mlx_new_window(win->mlx_p, 350, 350, "Menu:");

	win->win_width = 950;
	win->win_length = 950;
	win->mlx_p = mlx_init();
	win->mlx_nw = mlx_new_window(win->mlx_p, win->win_width, win->win_length, fract_name);
	win->enlarge = 1;
	win->move_down = 0;
	win->move_right = 0;
	win->c_r = 9;
	win->c_g = 9;
	win->c_b = 9;
	mlx_hook(win->mlx_nw, 2, 5, key_react, (void*)win);
	set_julia(win);
	mlx_loop(win->mlx_p);
}

int		print_menu(int errn, t_data *win)
{
	char	*name;

	if (errn == 1)
		write(2, "usage: ./fractol [fract name]\n", 30);
	write(2, "available fractals:\n", 20);
	write(2, "-> 1. Mandelbrot\n", 17);
	write(2, "-> 2. Julia\n", 12);
	while (get_next_line(0, &name))
	{
		if (!ft_strcmp("Julia", name) || !ft_strcmp("2", name))
			open_window(win, "Julia");
		else
			print_menu(1, win);
	}
	return (errn);
}

int		main(int argc, char **argv)
{
	t_data	win;

	if (argc != 2)
		print_menu(0, &win);
	else
	{
		if (!ft_strcmp("Julia", argv[1]))
			open_window(&win, argv[1]);
		else
			print_menu(1, &win);
	}
	return (0);
}
