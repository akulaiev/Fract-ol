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

void	set_julia(t_data *win)
{
	int		x;
	int		y;
	double	min_scale_width;
	double	max_scale_width;
	double	min_scale_len;
	double	max_scale_len;

	double	x_scale;
	double	y_scale;

	double	new_re;
	double	new_im;
	double	old_re;
	double	old_im;

	int		iter;
	int		num_iter;

	double	c_re;
	double	c_im;	

	c_re = -0.7;
  	c_im = 0.27015;

	min_scale_width = -2.5;
	max_scale_width = 1;
	min_scale_len = -1;
	max_scale_len = 1;

	x_scale = (max_scale_width - min_scale_width) / (win->win_width - 0);
	y_scale = (max_scale_len - min_scale_len) / (win->win_length - 0);

	x = 0;
	while (x < win->win_width)
	{
		y = 0;
		while (y < win->win_length)
		{
			iter = 0;
			num_iter = 113;
			new_re = x * x_scale;
			new_im = y * y_scale;
			while (iter < num_iter)
			{
				old_re = new_re;
				old_im = new_im;
				new_re = (old_re * old_re) - (old_im * old_im) + c_re;
				new_im = (2 * old_re * old_im) + c_im;
				if (new_re * new_re + new_im * new_im > 4)
					break;
				iter++;
			}
			if (iter == num_iter)
				mlx_pixel_put(win->mlx_p, win->mlx_nw, x, y, 0xed0488);
			else
				mlx_pixel_put(win->mlx_p, win->mlx_nw, x, y, 0x333333);
			y++;
		}
		x++;
	}

	// For each pixel (x, y) on the screen, do:
	// {
	//     zx = scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5, 1))
	//        // zx represents the real part of z
	//     zy = scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
	//        // zy represents the imaginary part of z 

	//     iteration = 0
	//     max_iteration = 1000
	  
	//     while (zx*zx + zy*zy < 4  AND  iteration < max_iteration) 
	//     {
	//         xtemp = zx*zx - zy*zy
	//         zy = 2*zx*zy  + cy 
	//         zx = xtemp + cx
	    
	//         iteration = iteration + 1 
	//     }
	  
	//     if (iteration == max_iteration)
	//         return black;
	//     else
	//         return iteration;
	// }

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
