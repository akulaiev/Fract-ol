/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 19:12:15 by akulaiev          #+#    #+#             */
/*   Updated: 2018/06/08 19:12:16 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void			*set_mandelbrot(void *win)
{
	t_scale			s;
	t_data			*w;
	int				i;

	w = (t_data*)win;
	s.y = w->current_y;
	i = -1;
	while (++s.y < w->wl && ++i < w->lines_per_th)
	{
		s.x = -1;
		while (++s.x < w->ww)
		{
			s.iter = -1;
			s.num_iter = 150;
			w->c_re = 1.5 * (s.x - w->ww / 1.5) /
			(0.5 * w->enl * w->ww) + w->mr;
			w->c_im = (s.y - w->wl / 2) / (0.5 * w->enl * w->wl) + w->md;
			s.new_re = w->c_re;
			s.new_im = w->c_im;
			check_point(&s, w);
			s.col = colour_fract(((double)s.iter / (double)s.num_iter), win);
			img_pixel_put(win, s);
		}
	}
	pthread_exit(NULL);
}
