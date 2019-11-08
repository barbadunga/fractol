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

void    set_default_view(t_param *p)
{
    p->radius = 1.0;
    p->center[0] = -0.5;
    p->center[1] = 0;
    p->click_pos[0] = 0;
    p->click_pos[1] = 0;
    p->is_click = 0;
    p->zoom = 0;
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
    if (!(img->params = (t_param*)malloc(sizeof(t_param))))
        return (NULL);
    set_default_view(img->params);
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
//	if (run_kernel(mlx))
//	    terminate("error: kernel setup\n");
//    single_thread(mlx->data, mlx->img->params);
    render(mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
