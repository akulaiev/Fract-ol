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

void	fract_scale(t_data *win, t_scale *scl)
{
	scl->c_re = -0.7;
	scl->c_im = 0.27015;
	scl->min_scale_width = -2.5;
	scl->max_scale_width = 1;
	scl->min_scale_len = -1;
	scl->max_scale_len = 1;
	scl->x_scale = scl->x_scale = (scl->max_scale_width - scl->min_scale_width) / (win->win_width);
	scl->y_scale = (scl->max_scale_len - scl->min_scale_len) / (win->win_length);
}

void	set_julia(t_data *win)
{
	t_scale	scl;

	scl.x = -1;
	fract_scale(win, &scl);
	while (++scl.x < win->win_width)
	{
		scl.y = -1;
		while (++scl.y < win->win_length)
		{
			scl.iter = -1;
			scl.num_iter = 150;
			scl.new_re = (scl.x - win->win_width / 2) * scl.x_scale;
			scl.new_im = (scl.y - win->win_length / 2) * scl.y_scale;
			while ((++scl.iter < scl.num_iter && (scl.new_re * scl.new_re + scl.new_im * scl.new_im < 4)))
			{
				scl.old_re = scl.new_re;
				scl.old_im = scl.new_im;
				scl.new_re = (scl.old_re * scl.old_re) - (scl.old_im * scl.old_im) + scl.c_re;
				scl.new_im = (2 * scl.old_re * scl.old_im) + scl.c_im;
			}
			if (scl.iter == scl.num_iter)
				mlx_pixel_put(win->mlx_p, win->mlx_nw, scl.x, scl.y, scl.iter % 256 + 255 + 255 * (scl.iter < scl.num_iter));
			else
				mlx_pixel_put(win->mlx_p, win->mlx_nw, scl.x, scl.y, 0xc8daf7);
		}
	}

	// https://ru.wikipedia.org/wiki/HSV_(цветовая_модель)
	// http://grafika.me/node/55
	// http://lodev.org/cgtutor/juliamandelbrot.html
}

void	open_window(t_data *win, char *fract_name)
{
	win->win_width = 950;
	win->win_length = 950;
	win->mlx_p = mlx_init();
	win->mlx_nw = mlx_new_window(win->mlx_p, win->win_width, win->win_length, fract_name);
	mlx_hook(win->mlx_nw, 2, 5, key_react, (void*)&win);
		set_julia(win);
	mlx_loop(win->mlx_p);
}

int		my_err(int errn)
{
	if (errn == 1)
	{
		write(2, "usage: ./fractol [fract name]\n", 30);
		write(2, "available fractals:\n", 20);
		write(2, "-> Mandelbrot\n", 14);
		write(2, "-> Julia\n", 9);
	}
	return (errn);
}

int		main(int argc, char **argv)
{
	t_data	win;

	if (argc < 2)
		return (my_err(1));
	else
	{
		open_window(&win, argv[1]);
	
	}
	return (0);
}
