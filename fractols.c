/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractols.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 15:00:43 by akulaiev          #+#    #+#             */
/*   Updated: 2018/05/14 15:00:45 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

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
			scl.col = colour_fract(((double)scl.iter / (double)scl.num_iter), win);
			mlx_pixel_put(win->mlx_p, win->mlx_nw, scl.x, scl.y, scl.col);
		}
	}
}