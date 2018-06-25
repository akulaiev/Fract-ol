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
	t_data			w;
	int				i;

	w = *((t_fract*)win)->window;
	s.y = ((t_fract*)win)->current_y;
	i = -1;
	while (++s.y < w.wl && ++i < w.lines_per_th)
	{
		
		s.x = -1;
		while (++s.x < w.ww)
		{
			s.iter = -1;
			s.num_iter = 150;
			w.c_re = (double)(s.x / (w.ww /
			(w.max_re - w.min_re)) + w.min_re) * w.enl + w.mr;
			w.c_im = (double)(s.y / (w.wl /
			(w.max_im - w.min_im)) + w.min_im) * w.enl + w.md - 0.3;
			s.new_re = w.c_re;
			s.new_im = w.c_im;
			check_point(&s, &w);
			s.col = colour_fract(((double)s.iter / (double)s.num_iter), &w);
			img_pixel_put(&w, s);
		}
	}
	pthread_exit(NULL);
}
