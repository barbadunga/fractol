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

void	set_default_view(t_view *v, char *name)
{
	if (!ft_strcmp(name, "julia"))
	{
		v->center[0] = 0.0;
		v->center[1] = 0.0;
		v->radius = 2.0;
		v->constant[0] = -0.7;
		v->constant[1] = 0.27015;
	}
	else
	{
		v->radius = !ft_strcmp("ship", name) ? 2.0 : 1.5;
		v->center[0] = -0.5;
		v->center[1] = 0.0;
	}
	if (!ft_strcmp("phoenix", name))
	{
		v->constant[0] = 0.56667;
		v->constant[1] = -0.5;
	}
	v->max_iter = 1000;
	v->click[0] = -1;
	v->click[1] = -1;
	v->pressed = -1;
	v->rgb[0] = 0.0;
	v->rgb[1] = 0.6;
	v->rgb[2] = 1.0;
	v->help = 0;
}

char	*get_name(char	*input)
{
	const char	*names[] = {"mandelbrot", "julia", "ship",
							 		"quartic", "cubic", NULL};
	int			i;

	i = 0;
	input = ft_tolowercase(input);
	while (names[i])
	{
		if (!(ft_strcmp(names[i], input)))
			return (input);
		i++;
	}
	return (NULL);
}

int		init_fractol(t_fctl **fctl, char *name)
{
	(*fctl)->kernel = NULL;
	(*fctl)->img = NULL;
	if (!((*fctl)->mlx = mlx_init()))
		return (0);
	if (!((*fctl)->win = mlx_new_window((*fctl)->mlx, WIDTH, HEIGHT, "Fract'ol")))
		return (0);
	if (!((*fctl)->img = (t_img*)malloc(sizeof(t_img))))
		return (0);
	if (!((*fctl)->img->img_ptr = mlx_new_image((*fctl)->mlx, WIDTH, HEIGHT)))
		return (0);
	if (!((*fctl)->view = (t_view*)malloc(sizeof(t_view))))
		return (0);
	(*fctl)->img->data = mlx_get_data_addr((*fctl)->img->img_ptr,
			&(*fctl)->img->bpp, &(*fctl)->img->size_line, &(*fctl)->img->end);
	(*fctl)->name = name;
	set_default_view((*fctl)->view, (*fctl)->name);
	return (1);
}
