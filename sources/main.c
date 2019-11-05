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
#include <stdio.h>

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
	run_kernel(mlx->data);
//    single_thread(mlx->data);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	mlx_loop(mlx->mlx);
	return (0);
}
