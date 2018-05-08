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
	scl->x_scale = (scl->max_scale_width - scl->min_scale_width) / (win->win_width);
	scl->y_scale = (scl->max_scale_len - scl->min_scale_len) / (win->win_length);
}

int		rainbow(int i)
{
	int		r;
	int		g;
	int		b;

	r = sin(0.1 * i + 4) * 25 + 127;
	g = sin(0.2 * i + 2) * 25 + 127;
	b = sin(0.3 * i + 1) * 25 + 127;
	return ((r << 16) + (g << 8) + b);
}	

void	set_julia(t_data *win)
{
	t_scale	scl;
	int		cont_ind;
	int		z_n;

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
			z_n = sqrt(scl.new_re * scl.new_re + scl.new_im * scl.new_im);
			cont_ind = scl.num_iter + 1 - (log(2) / z_n) / log (2);
			scl.max_col = rainbow(cont_ind);
			mlx_pixel_put(win->mlx_p, win->mlx_nw, scl.x, scl.y, (scl.iter * (scl.max_col / cont_ind)));
		}
	}
	//https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
	//http://www.paridebroggi.com/2015/05/fractal-continuous-coloring.html

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
