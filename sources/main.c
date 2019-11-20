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

char 	*ft_lower_case(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		*ptr = ft_tolower(*ptr);
		ptr++;
	}
	return (str);
}

void    set_default_view(t_param *p)
{
	if (!ft_strcmp("julia", p->name))
	{
		p->radius = 2.0;
		p->center[0] = 0.0;
		p->center[1] = 0.0;
	}
	else
	{
		p->radius = 1.5;
		p->center[0] = -0.5;
		p->center[1] = 0;
	}
    p->click_pos[0] = 0;
    p->click_pos[1] = 0;
    p->is_click = 0;
    p->max_iter = 100;
}

t_mngr	*init(t_mngr **mngr, char *name)
{
	t_mngr	*m;
	t_img	*img;

	if (!((*mngr) = (t_mngr*)malloc(sizeof(t_mngr))))
		return (NULL);
	m = *mngr;
	if (!(img = (t_img*)malloc(sizeof(t_img))))
		return (NULL);
	if (!(m->mlx = mlx_init()))
		return (NULL);
	if (!(m->win = mlx_new_window(m->mlx, WIDTH, HEIGHT, "fract'ol")))
		return (NULL);
	if (!(img->img_ptr = mlx_new_image(m->mlx, WIDTH, HEIGHT)))
		return (NULL);
    if (!(img->params = (t_param*)malloc(sizeof(t_param))))
        return (NULL);
    img->params->name = ft_lower_case(name);
    printf("%p\n", m->mlx);
    set_default_view(img->params);
	m->data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->end);
	m->img = img;
	m->kernel = NULL;
	return (m);
}

int		main(int argc, char	**argv)
{
	t_mngr       *mngr; // allocated

	if (argc < 2)
		terminate("usage: ./fractol [name]\n\nAvailable fractals:\nMandelbrot\n", NULL);
	if (!(init(&mngr, argv[1])))
		terminate("error: can't init\n", mngr);
	event_handler(mngr);
	if (new_kernel(mngr))
	    terminate("error: kernel setup\n", mngr);
    render(mngr);
	mlx_loop(mngr->mlx);
	return (0);
}
