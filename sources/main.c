/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:25:18 by mshagga           #+#    #+#             */
/*   Updated: 2019/09/18 18:25:52 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_param *init_params()
{
    t_param *p;

    if (!(p = (t_param*)malloc(sizeof(p))))
        return (NULL);
    p->top[0] = -2.0;
    p->bot[0] = 1.0;
    p->bot[1] = -1.0;
    p->top[1] = p->bot[1] + (p->bot[0] - p->top[0]) * HEIGHT / WIDTH;
    p->scale[0] = (p->bot[0] - p->top[0]) / (WIDTH - 1);
    p->scale[1] = (p->top[1] - p->bot[1]) / (HEIGHT - 1);
    p->radius = 1.0;
    p->center[0] = -0.5;
    p->center[1] = 0;
    p->move[0] = 0.0;
    p->move[1] = 0.0;
    return (p);
}

// If fail allocation free all memory
t_mlx	*init()
{
	t_mlx	*mlx;
	t_img	*img;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (NULL);
	if (!(img = (t_img*)malloc(sizeof(t_img))))
		return (NULL);
	if (!(mlx->mlx = mlx_init()))
		return (NULL);
	if (!(mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "fract'ol")))
		return (NULL);
	if (!(img->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT)))
		return (NULL);
    if (!(img->params = init_params()))
        return (NULL);
	mlx->data = mlx_get_data_addr(img->img, &img->bpp, &img->size_line, &img->end);
	mlx->img = img;
	return (mlx);
}

int		main(void)
{
	t_mlx       *mlx; // allocated

	if (!(mlx = init()))
		exit(1);
	event_handler(mlx);
//	if (run_kernel(mlx->data))
//	    terminate("error: kernel setup\n");
    render(mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
