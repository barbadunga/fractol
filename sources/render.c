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

void	render(t_fctl *f)
{
	if (run_kernel(f))
		terminate("error with OpenCL kernel\n", &f);
//	single_thread(f->img->data, f->img->view);
//	mlx_clear_window(f->mlx, f->win);
	mlx_put_image_to_window(f->mlx, f->win, f->img->img_ptr, WIDTH - HEIGHT, 0);
}