
#include "fractol.h"
#include <stdio.h>

void	check_point_bio(t_scale *s, t_data *w)
{
	s->col = 0;

	while ((++s->iter < s->num_iter && (s->new_re < 80 ||
	s->new_im < 80 || s->old_re < 80 || s->old_im < 80)))
	{
		s->old_re = s->new_re;
		s->old_im = s->new_im;
		s->new_re = (s->old_re * s->old_re * s->old_re) - (3 * s->old_im * s->old_im * s->old_re) + w->c_re;
		s->new_im = (3 * s->old_re * s->old_re * s->old_im) - (s->old_im * s->old_im * s->old_im) + w->c_im;
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

void			*set_biomorph(void *win)
{
	t_scale			s;
	t_data			*w;
	int				i;

	w = (t_data*)win;
	s.y = w->current_y;
	i = -1;
	w->c_re = 1.07;
	w->c_im = 0.0001;
	while (++s.y < w->wl && ++i < w->lines_per_th)
	{
		s.x = -1;
		while (++s.x < w->ww)
		{
			s.iter = -1;
			s.num_iter = 150;
			s.new_re = 4 * (s.x - w->ww / 2) / (0.5 * w->enl * w->ww) + w->mr;
			s.new_im = 3 * (s.y - w->wl / 2) / (0.5 * w->enl * w->wl) + w->md;
			check_point_bio(&s, w);
			img_pixel_put(win, s);
		}
	}
	pthread_exit(NULL);
}