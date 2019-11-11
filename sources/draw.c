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

void        render(t_mlx *mlx)
{
//    single_thread(mlx->data, mlx->img->params);
	run_kernel(mlx); // check return
    mlx_clear_window(mlx->mlx, mlx->win);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
}

t_complex   init_complex(double r, double i)
{
    t_complex	c;

    c.re = r;
    c.im = i;
    return (c);
}

void	single_thread(void *data, t_param *p)
{
    t_complex	c, z;
    double		r2;
    int			color;
	const int	max_iter = 50;

    for (int pixel = 0; pixel < HEIGHT * WIDTH; pixel++)
    {
        c.re = p->center[0] + p->radius * ((pixel % WIDTH) - WIDTH / 2.0) / (HEIGHT / 2.0);
        c.im = p->center[1] + p->radius * ((pixel / HEIGHT) - HEIGHT / 2.0) / (HEIGHT / 2.0);
        z = init_complex(0, 0);
        int i = -1;
        color = 0;
        while (++i < max_iter)
        {
            r2 = z.re * z.re + z.im * z.im;
            if (r2 > 1e10)
            {
                double t = (double)i / (double)max_iter;
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
