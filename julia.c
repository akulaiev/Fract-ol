/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:53:01 by akulaiev          #+#    #+#             */
/*   Updated: 2018/05/31 12:53:06 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void			*set_julia(void *win)
{
	t_scale			scl;
	t_data			*w;
	int				i;

	w = (t_data*)win;
	scl.y = w->current_y;
	i = -1;
	while (++scl.y < w->win_length && ++i < w->lines_per_th)
	{
		scl.x = -1;
		while (++scl.x < w->win_width)
		{
			scl.iter = -1;
			scl.num_iter = 150;
			scl.new_re = 1.5 * (scl.x - w->win_width / 2) / (0.5 * w->enlarge * w->win_width) + w->move_right;
			scl.new_im = (scl.y - w->win_length / 2) / (0.5 * w->enlarge * w->win_length) + w->move_down;
			while ((++scl.iter < scl.num_iter && (scl.new_re * scl.new_re + scl.new_im * scl.new_im < 4)))
			{
				scl.old_re = scl.new_re;
				scl.old_im = scl.new_im;
				scl.new_re = (scl.old_re * scl.old_re) - (scl.old_im * scl.old_im) + w->c_re;
				scl.new_im = (2 * scl.old_re * scl.old_im) + w->c_im;
			}
			scl.col = colour_fract(((double)scl.iter / (double)scl.num_iter), win);
			img_pixel_put(win, scl);
		}
	}
	pthread_exit(NULL);
	// return (0);
}
