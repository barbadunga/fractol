/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:25:18 by mshagga           #+#    #+#             */
/*   Updated: 2019/12/06 16:58:31 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fctl		*fctl;
	char		*name;
	char		*usage;

	usage = "usage: ./fractol [name]\n\nAvailable fractals:\n -->"
" Mandelbrot\n --> Julia\n --> Ship\n --> Quartic\n --> Cubic\n --> Unnamed\n"
" --> Magnet\n --> Cactus\n --> Dragon";
	if (argc != 2)
		terminate((char*)usage, NULL);
	if (!(name = get_name(argv[1])))
		terminate((char*)usage, NULL);
	if (!(fctl = (t_fctl*)malloc(sizeof(t_fctl))))
		terminate("error: malloc failure", NULL);
	if (!init_fractol(&fctl, name))
		terminate("error: init failure", &fctl);
	if (new_kernel(fctl, CL_DEVICE_TYPE_GPU))
		terminate("error: OpenCL failure", &fctl);
	event_handler(fctl);
	mlx_loop(fctl->mlx);
	return (1);
}
