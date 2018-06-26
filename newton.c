/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:49:52 by akulaiev          #+#    #+#             */
/*   Updated: 2018/06/11 14:49:54 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	check_new(t_scale *s, float tmp)
{
	while (tmp > 0.000001 && ++s->iter < s->num_iter)
	{
		s->old_re = s->new_re;
		s->old_im = s->new_im;
		tmp = (s->new_re * s->new_re + s->new_im * s->new_im) *
		(s->new_re * s->new_re + s->new_im * s->new_im);
		s->new_re = (2 * s->new_re * tmp + s->new_re *
		s->new_re - s->new_im * s->new_im) / (3 * tmp);
		s->new_im = (2 * s->new_im * (tmp - s->old_re)) / (3 * tmp);
		tmp = (s->new_re - s->old_re) * (s->new_re - s->old_re) +
		(s->new_im - s->old_im) * (s->new_im - s->old_im);
	}
}

void	*set_newton(void *win)
{
	t_scale			s;
	t_data			w;
	float			tmp;

	w = *((t_fract*)win)->window;
	s.y = ((t_fract*)win)->current_y;
	s.i = -1;
	while (++s.y < w.wl && ++s.i < w.lines_per_th)
	{
		s.x = -1;
		while (++s.x < w.ww)
		{
			tmp = 1;
			s.iter = -1;
			s.num_iter = 150;
			s.new_re = (double)(s.x / (w.ww /
			(w.max_re - w.min_re)) + w.min_re) * w.enl + w.mr + 0.5;
			s.new_im = (double)(s.y / (w.wl /
			(w.max_im - w.min_im)) + w.min_im) * w.enl + w.md - 0.3;
			check_new(&s, tmp);
			s.col = colour_fract(((double)s.iter / (double)s.num_iter), &w);
			img_pixel_put(&w, s);
		}
	}
	pthread_exit(NULL);
}
