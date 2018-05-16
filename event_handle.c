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
		exit(0);
	if (keycode == 69 || keycode == 24 || keycode == 78 || keycode == 27)
		pic_scale(keycode, param);
	if (keycode <= 126 && keycode >= 123)
		pic_move(keycode, param);
	if (keycode == 15 || keycode == 5 || keycode == 11 || keycode == 0)
		change_col_channels(keycode, param);
	return (0);
}

int		mouse_react(int button, int x, int y, void *param)
{
	if (button == 5 || button == 4)
	{
		// ((t_data*)param)->move_right = (double) x / ((t_data*)param)->win_width / 2;
		// ((t_data*)param)->move_down = (double) y / ((t_data*)param)->win_length / 2;
		((t_data*)param)->move_right = 
		((t_data*)param)->move_down = 
		pic_scale(button, param);
	}
	return (0);
	//https://docs.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/samples/jj635759(v=vs.85)
	//http://lodev.org/cgtutor/juliamandelbrot.html
}

void	pic_scale(int keycode, void *param)
{
	mlx_clear_window(((t_data*)param)->mlx_p, ((t_data*)param)->mlx_nw);
	if (keycode == 69 || keycode == 24 || keycode == 5)
		((t_data*)param)->enlarge += 1;
	if ((keycode == 78 || keycode == 27 || keycode == 4) && ((t_data*)param)->enlarge > 1)
		((t_data*)param)->enlarge -= 1;
	open_fract(((t_data*)param));
}

void	pic_move(int keycode, void *param)
{
	mlx_clear_window(((t_data*)param)->mlx_p, ((t_data*)param)->mlx_nw);
	if (keycode == 126)
		((t_data*)param)->move_down += 0.1;
	if (keycode == 125)
		((t_data*)param)->move_down -= 0.1;
	if (keycode == 124)
		((t_data*)param)->move_right -= 0.1;
	if (keycode == 123)
		((t_data*)param)->move_right += 0.1;
	open_fract(((t_data*)param));
}

void	change_col_channels(int keycode, void *param)
{
	mlx_clear_window(((t_data*)param)->mlx_p, ((t_data*)param)->mlx_nw);
	if (keycode == 15)
		((t_data*)param)->c_r += 1;
	if (keycode == 5)
		((t_data*)param)->c_g += 1;
	if (keycode == 11)
		((t_data*)param)->c_b += 1;
	if (keycode == 0)
	{
		((t_data*)param)->c_r += 5;
		((t_data*)param)->c_g += 5;
		((t_data*)param)->c_b += 5;
	}
	open_fract(((t_data*)param));
}