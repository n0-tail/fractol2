/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:26:10 by anikkane          #+#    #+#             */
/*   Updated: 2020/07/15 14:41:00 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			julia_motion(int x, int y, t_fractal *f_data)
{
	if (x > 150 && x < 450 && y > 150 && y < 450)
	{
		f_data->k = init_complex(((double)x / WIDTH - 0.05),
				((double)(HEIGHT - y) / HEIGHT - 0.05));
		pthread(f_data);
	}
	return (0);
}

int		keypressed(int keycode)
{
	if (keycode == MAIN_PAD_ESC)
		exit(0);
	return (0);
}

double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int		zoom(int button, int x, int y, t_fractal *f_data)
{
	t_complex	mouse;
	double		interpolation;
	double		zoom;

	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		mouse = init_complex(
				(double)x / (WIDTH / (f_data->max.re - f_data->min.re))
				+ f_data->min.re,
				(double)y / (HEIGHT / (f_data->max.im - f_data->min.im))
				* -1 + f_data->max.im);
		if (button == MOUSE_SCROLL_UP)
			zoom = 0.90;
		else
			zoom = 1.1;
		interpolation = 1.0 / zoom;
		f_data->min.re = interpolate(mouse.re, f_data->min.re, interpolation);
		f_data->min.im = interpolate(mouse.im, f_data->min.im, interpolation);
		f_data->max.re = interpolate(mouse.re, f_data->max.re, interpolation);
		f_data->max.im = interpolate(mouse.im, f_data->max.im, interpolation);
		f_data->max_iteration += 1;
		pthread(f_data);
	}
	return (0);
}