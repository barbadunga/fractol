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

void	anti_aliasing(void	*data)
{
	int *img;
	int	pixel;

	img = (int*)data;
	while (pixel < HEIGHT * WIDTH)
	{
		break;
	}
}

void	show_help(t_fctl *f)
{
	const int	pos = 2 * HEIGHT / 3;

	mlx_string_put(f->mlx, f->win, 5, HEIGHT - 25, 0xFFFFFF,
			"Press H to hide help");
	mlx_string_put(f->mlx, f->win, 5, pos + 10, WHITE,
			"Move on: arrows, mouse");
	mlx_string_put(f->mlx, f->win, 5, pos + 40, WHITE,
			"Zoom: mouse wheel, +/- keys");
	mlx_string_put(f->mlx, f->win, 5, pos + 70, WHITE, "lolchto");
}

void	show_info(t_fctl *f)
{
	char		*iter;
	char		*num;

	if (!(num = ft_itoa(f->img->view->max_iter)))
		terminate("error: allocation error", &f);
	if (!(iter = ft_strjoin("iterations: ", num)))
	{
		free(num);
		terminate("error: allocation error", &f);
	}
	mlx_string_put(f->mlx, f->win, WIDTH - 200, 5, 0xFFFFFF, iter);
	if (f->img->view->help)
		show_help(f);
	else
		mlx_string_put(f->mlx, f->win, 5, HEIGHT - 25, 0xFFFFFF,
				"Press H to show help");
	free(num);
	free(iter);
}

int 	render(t_fctl *f)
{
	if (run_kernel(f))
		terminate("error with OpenCL kernel", &f);
	anti_aliasing(f->img->data);
	if (f->img->view->help)
		fill((int*)(f->img->data), 1, 2 * HEIGHT / 3, 300, HEIGHT / 3, 0x0);
	mlx_put_image_to_window(f->mlx, f->win, f->img->img_ptr, 0, 0);
	show_info(f);
	return (1);
}
