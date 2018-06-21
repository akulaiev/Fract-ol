#include "fractol.h"
#include <stdio.h>

void	check_point_la(t_scale *s, t_data *w)
{
	while ((++s->iter < s->num_iter &&
	(s->new_re * s->new_re + s->new_im * s->new_im < 4)))
	{
		s->old_re = s->new_re - (s->new_re * s->new_re) + (s->new_im * s->new_im);
		s->old_im = s->new_im - (2 * s->new_re * s->new_im);
		s->new_re =  w->c_re * s->old_re - w->c_im * s->old_im;
		s->new_im =  w->c_re * s->old_im + w->c_im * s->old_re;
	}
}

void			*set_lambda(void *win)
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
			w.c_re = (w.min_re + s.x * w.re_f) / (w.enl * 0.5) + (w.mr + 2);
			w.c_im = (w.max_im - s.y * w.im_f) / (w.enl * 0.5) - (w.md + 0.39);
			s.new_re = 0.5;
			s.new_im = 0;
			check_point_la(&s, &w);
			s.col = colour_fract(((double)s.iter / (double)s.num_iter), &w);
			img_pixel_put(&w, s);
		}
	}
	pthread_exit(NULL);
}
