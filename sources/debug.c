/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:53:53 by mshagga           #+#    #+#             */
/*   Updated: 2019/11/21 15:53:53 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

cl_device_id	get_device_info(cl_platform_id id, cl_device_info value_name)
{
	cl_device_id	*devices;
	cl_uint			device_count;
	char			*name;
	size_t			name_len;
	int				i;

	clGetDeviceIDs(id, value_name, 0, NULL, &device_count);
	i = 0;
	if (!(devices = (cl_device_id*)malloc(sizeof(cl_device_id) * device_count)))
		return (0);
	clGetDeviceIDs(id, value_name, device_count, devices, NULL);
	ft_putendl("Available devices:");
	while (i < (int)device_count)
	{
		clGetDeviceInfo(devices[i], CL_DEVICE_NAME, 0, NULL, &name_len);
		if (!(name = (char*)malloc(name_len)))
			return (0);
		clGetDeviceInfo(devices[i], CL_DEVICE_NAME, name_len, name, NULL);
		ft_putstr("Name: ");
		ft_putendl(name);
		free(name);
		i++;
	}
	return (*devices);
}

void			print_device_info(cl_device_id id)
{
	char	*name;
	size_t	name_len;

	clGetDeviceInfo(id, CL_DEVICE_NAME, 0, NULL, &name_len);
	if (!(name = (char*)malloc(name_len)))
		return ;
	clGetDeviceInfo(id, CL_DEVICE_NAME, name_len, name, NULL);
	ft_putstr("Device: ");
	ft_putendl(name);
}

void			get_build_log(cl_program prog, cl_device_id id, cl_int errno)
{
	char	*build;
	char	*build_log;
	size_t	log_size;
	int		ret;

	clGetProgramBuildInfo(prog, id, CL_PROGRAM_BUILD_STATUS,
			sizeof(cl_build_status), &build, NULL);
	ft_putstr("Error ");
	ft_putnbr(errno);
	ft_putchar('\n');
	ret = clGetProgramBuildInfo(prog, id, CL_PROGRAM_BUILD_LOG, 0, NULL,
			&log_size);
	ft_putstr("Build status: ");
	ft_putnbr(ret);
	ft_putchar('\n');
	if (!(build_log = (char*)malloc(log_size)))
		return ;
	clGetProgramBuildInfo(prog, id, CL_PROGRAM_BUILD_LOG, log_size, build_log,
			NULL);
	build_log[log_size] = '\0';
	ft_putstr("Build log: ");
	ft_putendl(build_log);
	free(build_log);
}
