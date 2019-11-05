//
// Created by Morna Shagga on 2019-11-05.
//

#include "fractol.h"
#include <stdio.h>

typedef struct s_complex
{
    double	re;
    double	im;
}				t_complex;

t_complex init_complex(double r, double i)
{
    t_complex	c;

    c.re = r;
    c.im = i;
    return (c);
}

int		V(double n)
{
    int color;

    color = n * 0xFFFFFF / 50;
    return (color);
}

double  module(t_complex z)
{
    double  re;
    double  im;

    re = z.re * z.re - z.im * z.im;
    im = 2 * z.re * z.im;
    return (sqrt(re * re + im * im));
}

void	single_thread(void *data)
{
    t_complex	min = {-2.0, -1.5},
            max,
            scale, c, z;
    int			max_iter = 100;
    double		r2;
    int			color;

    max.re = 1.0;
    max.im = min.im + (max.re - min.re) * HEIGHT / WIDTH;
    scale.re = (max.re - min.re) / (WIDTH - 1);
    scale.im = (max.im - min.im) / (HEIGHT - 1);
    printf("%f %f\n", scale.re, scale.im);
    for (int pixel = 0; pixel < HEIGHT * WIDTH; pixel++)
    {
        c.re = min.re + pixel % WIDTH * scale.re;
        c.im = max.im - pixel / HEIGHT * scale.im;
        z = init_complex(0, 0);
        int i = -1;
        color = 0;
        while (++i < max_iter)
        {
            r2 = z.re * z.re + z.im * z.im;
            if (r2 > 1e10)
            {
//				color = V(log(r2));
              color = V(i);
//                color = V(i + 1 - log(log(module(z))) / log(2));
                break;
            }
            z = init_complex(z.re * z.re - z.im * z.im + c.re, 2 * z.im * z.re + c.im);
        }
        ((int*)data)[pixel] = color;
    }
}