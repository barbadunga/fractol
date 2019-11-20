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

void	render(t_mngr *mngr)
{
	if (run_kernel(mngr))
	{
		destroy_kernel(mngr->kernel);
		terminate("error with OpenCL kernel\n", mngr);
	}
	mlx_clear_window(mngr->mlx, mngr->win);
	mlx_put_image_to_window(mngr->mlx, mngr->win, mngr->img->img_ptr, WIDTH - HEIGHT, 0);
}