/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:48:45 by mshagga           #+#    #+#             */
/*   Updated: 2019/11/21 16:48:45 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

typedef struct	s_complex
{
	double		re;
	double		im;
}				t_complex;

t_complex	init_complex(double re, double im)
{
	t_complex c;

	c.re = re;
	c.im = im;
	return c;
}

void	single_thread(void *data, t_view *v)
{
	t_complex	c, z;
	double		r2;
	int			color;

	for (int pixel = 0; pixel < HEIGHT * WIDTH; pixel++)
	{
		c.re = v->center[0] + v->radius * ((double)(pixel % WIDTH) - WIDTH / 2.0) / (HEIGHT / 2.0);
		c.im = v->center[1] - v->radius * ((double)(pixel / HEIGHT) - HEIGHT / 2.0) / (HEIGHT / 2.0);
		z = init_complex(0, 0);
		int i = -1;
		color = 0;
		while (++i < v->max_iter)
		{
			r2 = z.re * z.re + z.im * z.im;
			if (r2 > 1e10)
			{
				double t = (double)i / (double)v->max_iter;
				int red = (int)(9 * (1 - t) * pow(t, 3) * 255);
				int green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
				int blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
				color = red << 16 | green << 8 | blue;
				break;
			}
			z = init_complex(z.re * z.re - z.im * z.im + c.re, 2 * z.im * z.re + c.im);
		}
		((int*)data)[pixel] = color;
	}
}