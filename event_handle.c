/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 12:40:02 by akulaiev          #+#    #+#             */
/*   Updated: 2018/05/07 12:40:03 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int		key_react(int keycode, void *param)
{
	if (keycode == 53)
	{
		// system("leaks fractol");
		exit(0);
	}
	if (keycode == 8)
	{
		params_init(param);
		open_fract(param);
	}
	if (keycode == 12 && (((t_data*)param)->mh = 1))
		mlx_hook(((t_data*)param)->mlx_nw, 6, (1L << 13), &mouse_move, param);
	if (keycode == 14)
	{
		((t_data*)param)->mh = 0;
		mlx_clear_window(((t_data*)param)->mlx_p, ((t_data*)param)->mlx_nw);
		((t_data*)param)->c_re = -0.7;
		((t_data*)param)->c_im = 0.27015;
		open_fract(((t_data*)param));
	}
	if (keycode == 69 || keycode == 24 || keycode == 78 || keycode == 27)
		pic_scale(keycode, param);
	if (keycode <= 126 && keycode >= 123)
		pic_move(keycode, param);
	if (keycode == 0)
		change_col_channels(keycode, param);
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_data	*p;

	if (((t_data*)param)->mh == 1)
	{
		p = (t_data*)param;
		mlx_clear_window(p->mlx_p, p->mlx_nw);
		p = (t_data*)param;
		p->c_re = (float)x / p->ww;
		p->c_im = (float)y / p->wl;
		open_fract(p);
	}
	return (0);
}

int		mouse_react(int button, int x, int y, void *param)
{
	t_data	*p;

	p = (t_data*)param;
	if (button == 4 || button == 5)
	{
		// p->mr = (x - p->ww / 2) / (0.5 * p->enl * p->ww) + p->mr;
		// p->md = (y - p->wl / 2) / (0.5 * p->enl * p->wl) + p->md;
		
		p->mr = (x + x - p->ww) / (p->ww * p->enl) + p->mr;
		p->md = (y + y - p->wl) / (p->wl * p->enl) + p->md;
	}
	pic_scale(button, p);
	return (0);
}
