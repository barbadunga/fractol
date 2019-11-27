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
	mlx_put_image_to_window(f->mlx, f->win, f->img->img_ptr, 0, 0);
	if (f->img->view->help)
	{
		mlx_string_put(f->mlx, f->win, 5, HEIGHT - 25, 0xFFFFFF,
				"Press \'H\' to hide help");
		fill(f->img->data, 0, 2 * HEIGHT / 3, 100, 100, 0xFFFFFF);
	}
	else
		mlx_string_put(f->mlx, f->win, 5, HEIGHT - 25, 0xFFFFFF,
				"Press \'H\' to show help");
	return (1);
}