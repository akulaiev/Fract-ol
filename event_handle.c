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
	return (0);
}

void	pic_scale(int keycode, void *param)
{
	mlx_clear_window(((t_data*)param)->mlx_p, ((t_data*)param)->mlx_nw);
	if (keycode == 69 || keycode == 24)
		((t_data*)param)->enlarge += 1;
	if (keycode == 78 || keycode == 27)
		((t_data*)param)->enlarge -= 1;
	set_julia(((t_data*)param));
}