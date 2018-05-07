/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 11:33:33 by akulaiev          #+#    #+#             */
/*   Updated: 2018/05/07 11:33:35 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "./libft/libft.h"
# include <string.h>

typedef struct	s_data
{
	void	*mlx_p;
	void	*mlx_nw;
	int		win_width;
	int		win_length;
	int		x;
	int		y;
	int		col;
}				t_data;

int		my_err(int errn);
void	open_window(t_data *win, char *fract_name);
int		key_react(int keycode, void *param);

#endif