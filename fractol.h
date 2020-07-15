/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:25:19 by anikkane          #+#    #+#             */
/*   Updated: 2020/07/15 14:31:26 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "stdio.h"
# include <fcntl.h>
# include "math.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include "pthread.h"
# include "keys.h"

# define WIDTH			600
# define HEIGHT			600

# define THREAD_NUMBER	6
# define THREAD_WIDTH	100

typedef struct		s_complex
{
	double			re;
	double			im;
}					t_complex;

typedef	struct		s_color
{
	int8_t			channel[4];
}					t_color;

typedef struct		s_fractal
{
	t_complex		min;
	t_complex		max;
	t_complex		factor;
	t_complex		c;
	t_complex		k;
	int				x;
	int				y;
	void			*win;
	void			*mlx;
	void			*image;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				start_line;
	int				finish_line;
	int				mouse;
	int				endian;
	int				fractol_nbr;
	int				max_iteration;
	char			*name;
}					t_fractal;

int					end(char *reason);
t_fractal			*init(void *mlx_ptr, char *str);
t_color				get_color(int iteration, t_fractal *f_data);
void				draw_fractal_part(t_fractal *f_data);
void				put_pixel(t_fractal *f_data, int x, int y, t_color color);
void				set_data(t_fractal *f_data);
t_complex			init_complex(double re, double im);
int					iterate_mandelbrot(t_fractal *f_data);
int					iterate_julia(t_fractal *f_data);
int					iterate_mandelbar(t_fractal *f_data);
char				*fractal_check(char *str);
void				pthread(t_fractal *f_data);
int					zoom(int button, int x, int y, t_fractal *f_data);
double				interpolate(double start, double end, double interpolation);
int					julia_motion(int x, int y, t_fractal *f_data);
int					keypressed(int keycode);

#endif
