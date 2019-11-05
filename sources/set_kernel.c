/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_kernel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlexandrSergeev <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 00:35:52 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2019/11/04 00:35:52 by AlexandrSergeev  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char *load_kernel(char *filename)
{
	int		fd;
	char	*kernel;
	t_vec	*vec;
	char	buf[1];

	fd = open(filename, O_RDONLY);
	if (!(vec = ft_vec_init(1, sizeof(char))))
		return (NULL);
	if (fd < 0 && read(fd, NULL, 0) < 0)
		return (NULL);
	while ((read(fd, buf, 1)) > 0)
		if (!ft_vec_add(&vec, buf))
			return (NULL);
	ft_vec_add(&vec, "\0");
	if (!(ft_vec_resize(&vec)))
	{
		ft_vec_del(&vec);
		return (NULL);
	}
	kernel = vec->data;
	ft_vec_del(&vec);
	return (kernel);
}

int		run_kernel(t_mlx *mlx)
{
	cl_program			program[1];
	cl_kernel			kernel[1];
	cl_command_queue	cmd_queue;
	cl_context			context;
	cl_device_id		cpu = NULL, device = NULL;
	cl_int				err = 0;
	size_t				returned_size = 0;
	size_t 				buffer_size;
	char				*prog_src;

	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_CPU, 1, &cpu, NULL);
	if (err != CL_SUCCESS)
		return (-1);
	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_CPU, 1, &cpu, NULL);
	if (err != CL_SUCCESS)
		device = cpu;
	context = clCreateContext(0, 1, &device, NULL, NULL, &err);

	prog_src = load_kernel("fractals.cl");
	void *ptr = clCreateBuffer();
//	Check for success request

	return (1);
}