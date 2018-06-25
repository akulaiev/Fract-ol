#include "fractol.h"
#include <stdio.h>

void	check_point_spi(t_scale *s, t_data *w)
{
	while ((++s->iter < s->num_iter &&
	(s->new_re * s->new_re + s->new_im * s->new_im < 4)))
	{
		s->old_re = s->new_re;
		s->old_im = s->new_im;
		s->new_re = (s->old_re * s->old_re) - (s->old_im * s->old_im) + w->c_re;
		s->new_im = 2 * s->old_re * s->old_im + w->c_im;
		w->c_re = w->c_re / 2 + s->new_re;
		w->c_im = w->c_im / 2 + s->new_im;
	}
}

void			*set_spider(void *win)
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
			(w.max_re - w.min_re)) + w.min_re) * w.enl + w.mr - 0.1;
			w.c_im = (double)(s.y / (w.wl /
			(w.max_im - w.min_im)) + w.min_im) * w.enl + w.md - 0.3;
			s.new_re = w.c_re;
			s.new_im = w.c_im;
			check_point_spi(&s, &w);
			s.col = colour_fract(((double)s.iter / (double)s.num_iter), &w);
			img_pixel_put(&w, s);
		}
	}
	pthread_exit(NULL);
}
