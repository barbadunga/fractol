/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlexandrSergeev <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 21:39:20 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2019/11/11 21:39:20 by AlexandrSergeev  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int 	render(t_fctl *f)
{
	if (run_kernel(f))
		terminate("error with OpenCL kernel", &f);
	if (f->img->view->help)
	{
		fill((int*)(f->img->data), WIDTH / 2 - WIDTH / 5,
				HEIGHT / 2 - HEIGHT / 5, WIDTH / 3, HEIGHT / 3, 0x0FFFFFF);
		mlx_put_image_to_window(f->mlx, f->win, f->img->img_ptr, 0, 0);
		mlx_string_put(f->mlx, f->win, 5, HEIGHT - 25, 0xFFFFFF,
				"Press H to hide help");
	}
	else
	{
		mlx_put_image_to_window(f->mlx, f->win, f->img->img_ptr, 0, 0);
		mlx_string_put(f->mlx, f->win, 5, HEIGHT - 25, 0xFFFFFF,
				"Press H to show help");
	}
	return (1);
}