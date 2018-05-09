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

int		colour_fract(double i)
{
	int		r;
	int		g;
	int		b;
	int		n3;
	int		n;
	int		nn;
	int		c;

	c = 256;
	n3 = c * c * c;
	n = (int)(i * (double)n3);
	b = n / (c * c);
	nn = n - b * c * c;
	r = nn / c;
	g = nn - r * c;

	r = (int)(9 * (1 - i) * i * i * i * 255);
	g = (int)(15 * (1 - i) * (1 - i) * i * i * 255);
	b =  (int)(8.5 * (1 - i) * (1 - i) * (1 - i) * i * 255);

	r = sin(0.1 * i + 4) * 125 + 127;
	g = sin(0.2 * i + 2) * 125 + 127;
	b = sin(0.3 * i + 1) * 125 + 127;
	return ((r << 16) + (g << 8) + b);
}	

void	set_julia(t_data *win)
{
	t_scale	scl;

	scl.c_re = -0.7;
	scl.c_im = 0.27015;
	scl.x = -1;
	while (++scl.x < win->win_width)
	{
		scl.y = -1;
		while (++scl.y < win->win_length)
		{
			scl.iter = -1;
			scl.num_iter = 150;
			scl.new_re = 1.5 * (scl.x - win->win_width / 2) / (0.5 * win->enlarge * win->win_width) + win->move_right;
      		scl.new_im = (scl.y - win->win_length / 2) / (0.5 * win->enlarge * win->win_length) + win->move_down;
			while ((++scl.iter < scl.num_iter && (scl.new_re * scl.new_re + scl.new_im * scl.new_im < 4)))
			{
				scl.old_re = scl.new_re;
				scl.old_im = scl.new_im;
				scl.new_re = (scl.old_re * scl.old_re) - (scl.old_im * scl.old_im) + scl.c_re;
				scl.new_im = (2 * scl.old_re * scl.old_im) + scl.c_im;
			}
			scl.z_n = sqrt(scl.new_re * scl.new_re + scl.new_im * scl.new_im);
			scl.cont_ind = scl.iter + 1 - (log(2) / scl.z_n) / log(2);
			scl.max_col += colour_fract(scl.cont_ind / (double)scl.num_iter);
			mlx_pixel_put(win->mlx_p, win->mlx_nw, scl.x, scl.y, (scl.iter * (scl.max_col / scl.cont_ind)));
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
	win->enlarge = 1;
	win->move_down = 0;
	win->move_right = 0;
	mlx_hook(win->mlx_nw, 2, 5, key_react, (void*)win);
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
