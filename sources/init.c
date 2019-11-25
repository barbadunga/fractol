/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:16:49 by mshagga           #+#    #+#             */
/*   Updated: 2019/11/21 14:16:49 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	set_default_view(t_view *v, char name)
{
	if (name == 'j')
	{
		v->center[0] = 0.0;
		v->center[1] = 0.0;
		v->radius = 2.0;
		v->cnst[0] = -0.7;
		v->cnst[1] = 0.27015;
	}
	else
	{
		v->radius = 1.5;
		v->center[0] = -0.5;
		v->center[1] = 0.0;
	}
	v->max_iter = 50;
	v->click[0] = -1;
	v->click[1]= -1;
	v->pressed = -1;
	v->angle = 2.346;
}

int		init_fractol(t_fctl **fctl, char *type)
{
	(*fctl)->kernel = NULL;
	(*fctl)->img = NULL;
	if (!((*fctl)->mlx = mlx_init()))
		return (0);
	if (!((*fctl)->win = mlx_new_window((*fctl)->mlx, WIDTH, HEIGHT, type)))
		return (0);
	if (!((*fctl)->img = (t_img*)malloc(sizeof(t_img))))
		return (0);
	if (!((*fctl)->img->img_ptr = mlx_new_image((*fctl)->mlx, WIDTH, HEIGHT)))
		return (0);
	if (!((*fctl)->img->view = (t_view*)malloc(sizeof(t_view))))
		return (0);
	(*fctl)->img->data = mlx_get_data_addr((*fctl)->img->img_ptr, &(*fctl)->img->bpp,
			&(*fctl)->img->size_line, &(*fctl)->img->end);
	(*fctl)->name = type;
	set_default_view((*fctl)->img->view, (*fctl)->name[0]);
	return (1);
}