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
# define NUM_TH 19

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "./minilibx_macos/mlx.h"
# include "./libft/libft.h"
# include <string.h>
# include <pthread.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct	s_data
{
	void	*mlx_p;
	void	*mlx_nw;
	void	*mlx_img;
	int		ww;
	int		wl;
	char	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		col;
	double	mr;
	double	md;
	double	enl;
	int		c_r;
	int		c_g;
	int		c_b;
	int		fn;
	double	c_re;
	double	c_im;
	int		mh;
	int		lines_per_th;
	int		current_y;
}				t_data;

typedef struct	s_scale
{
	int		x;
	int		y;
	double	new_re;
	double	new_im;
	double	old_re;
	double	old_im;
	int		iter;
	int		num_iter;
	int		col;
}				t_scale;

void			print_menu(t_data *win, char *input, int err);
int				check_input(t_data *win, char *i);
void			*set_julia(void *win);
void			params_init(t_data *win);
int				key_react(int keycode, void *param);
int				mouse_react(int button, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);
void			pic_scale(int keycode, void *param);
void			pic_move(int keycode, void *param);
void			change_col_channels(int keycode, void *param);
int				colour_fract(double i, t_data *win);
void			open_fract(t_data *win);
void			open_window(t_data *win, char *fract_name);
void			img_pixel_put(t_data *win, t_scale scl);
void			deal_with_threads(t_data *win);
void			*set_mandelbrot(void *win);
void			check_point(t_scale *scl, t_data *w);
void			menu_frame(t_data *win);
void			menu_content(t_data *win);
void			*set_biomorph(void *win);
void			check_point_bio(t_scale *s, t_data *w);
void			*set_newton(void *win);
void			check_new(t_scale *s, float tmp);
void			*set_lambda(void *win);
void			check_point_la(t_scale *s, t_data *w);
void			*set_spider(void *win);
void			*set_burning_ship(void *win);
void			check_point_ship(t_scale *s, t_data *w);
#endif