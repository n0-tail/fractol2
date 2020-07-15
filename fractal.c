/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:42:30 by anikkane          #+#    #+#             */
/*   Updated: 2020/07/15 14:21:12 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char		*fractal_check(char *str)
{
	if (ft_strcmp("mandelbrot", str) == 0)
		return ("mandelbrot");
	if (ft_strcmp("julia", str) == 0)
		return ("julia");
	if (ft_strcmp("mandelbar", str) == 0)
		return ("mandelbar");
	end("wrong fractal name, usage ./fractol fractalname");
	end("possible names: mandelbrot, mandelbar, julia");
	exit(0);
}

t_fractal	*init(void *mlx_ptr, char *str)
{
	t_fractal	*f_data;

	if (!(f_data = (t_fractal*)malloc(sizeof(t_fractal))))
		exit(1);
	f_data->name = fractal_check(str);
	f_data->win = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, f_data->name);
	f_data->mlx = mlx_ptr;
	if (!(f_data->image = mlx_new_image(f_data->mlx, WIDTH, HEIGHT)))
		exit(1);
	set_data(f_data);
	f_data->data_addr = mlx_get_data_addr(
			f_data->image,
			&(f_data->bits_per_pixel),
			&(f_data->size_line),
			&(f_data->endian));
	if (ft_strcmp(f_data->name, "julia") == 0)
		mlx_hook(f_data->win, 6, (1L << 6), julia_motion, f_data);
	mlx_mouse_hook(f_data->win, zoom, f_data);
	mlx_key_hook(f_data->win, keypressed, f_data);
	return (f_data);
}

int			iterate_mandelbrot(t_fractal *f_data)
{
	int			iteration;
	t_complex	z;

	iteration = 0;
	z = init_complex(f_data->c.re, f_data->c.im);
	while ((z.re * z.re) + z.im * z.im <= 4
			&& iteration < f_data->max_iteration)
	{
		z = init_complex(
				z.re * z.re - z.im * z.im + f_data->c.re,
				2.0 * z.re * z.im + f_data->c.im);
		iteration++;
	}
	return (iteration);
}

int			iterate_julia(t_fractal *f_data)
{
	int			iteration;
	t_complex	z;

	iteration = 0;
	z = init_complex(f_data->c.re, f_data->c.im);
	while ((z.re * z.re) + z.im * z.im <= 4
			&& iteration < f_data->max_iteration)
	{
		z = init_complex(
				z.re * z.re - z.im * z.im + f_data->k.re,
				2.0 * z.re * z.im + f_data->k.im);
		iteration++;
	}
	return (iteration);
}

int			iterate_mandelbar(t_fractal *f_data)
{
	int			iteration;
	t_complex	z;

	iteration = 0;
	z = init_complex(f_data->c.re, f_data->c.im);
	while (z.re * z.re + z.im * z.im <= 4
			&& iteration < f_data->max_iteration)
	{
		z = init_complex(
				z.re * z.re - z.im * z.im + f_data->c.re,
				-2.0 * z.re * z.im + f_data->c.im);
		iteration++;
	}
	return (iteration);
}
