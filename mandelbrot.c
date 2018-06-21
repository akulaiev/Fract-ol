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
			w.c_re = (w.min_re + s.x * w.re_f) / w.enl + w.mr;
			w.c_im = (w.max_im - s.y * w.im_f) / w.enl - (w.md + 0.2);
			s.new_re = w.c_re;
			s.new_im = w.c_im;
			check_point(&s, &w);
			s.col = colour_fract(((double)s.iter / (double)s.num_iter), &w);
			img_pixel_put(&w, s);
		}
	}
	pthread_exit(NULL);
}
