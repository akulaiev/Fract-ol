/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biomorph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:26:08 by akulaiev          #+#    #+#             */
/*   Updated: 2018/06/26 16:26:10 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	check_point_bio(t_scale *s, t_data *w)
{
	s->col = 0;
	while ((++s->iter < s->num_iter && (s->new_re < 80 ||
	s->new_im < 80 || s->old_re < 80 || s->old_im < 80)))
	{
		s->old_re = s->new_re;
		s->old_im = s->new_im;
		s->new_re = (s->old_re * s->old_re * s->old_re) -
		(3 * s->old_im * s->old_im * s->old_re) + w->c_re;
		s->new_im = (3 * s->old_re * s->old_re * s->old_im) -
		(s->old_im * s->old_im * s->old_im) + w->c_im;
		s->new_re = fabs(s->new_re);
		s->new_im = fabs(s->new_im);
		if ((s->new_re) < 80 && (s->new_im) < 80)
			s->col = 0x00ffe1;
		if ((s->new_re) >= 80 && (s->new_im) < 80)
			s->col = 0xff0000;
		if ((s->new_re) < 80 && (s->new_im) >= 80)
			s->col = 0x00ff00;
	}
	if (s->col)
		s->col /= colour_fract(((double)s->iter / (double)s->num_iter), w);
	else
		s->col = colour_fract(((double)s->iter / (double)s->num_iter), w);
}

void	*set_biomorph(void *win)
{
	t_scale			s;
	t_data			w;
	int				i;

	w = *((t_fract*)win)->window;
	s.y = ((t_fract*)win)->current_y;
	i = -1;
	w.c_re = 1.07;
	w.c_im = 0.0001;
	while (++s.y < w.wl && ++i < w.lines_per_th)
	{
		s.x = -1;
		while (++s.x < w.ww)
		{
			s.iter = -1;
			s.num_iter = 150;
			s.new_re = (double)(s.x / (w.ww /
			(w.max_re - w.min_re)) + w.min_re) * (w.enl / 0.7) + w.mr + 0.5;
			s.new_im = (double)(s.y / (w.wl /
			(w.max_im - w.min_im)) + w.min_im) * (w.enl / 0.7) + w.md - 0.5;
			check_point_bio(&s, &w);
			img_pixel_put(&w, s);
		}
	}
	pthread_exit(NULL);
}
