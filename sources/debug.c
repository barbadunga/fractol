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

void    get_platform_info(cl_platform_id id)
{
    char    *value = NULL;
    size_t  value_len = 0;
    int    info[3] = {CL_PLATFORM_NAME, CL_PLATFORM_VENDOR, CL_PLATFORM_VERSION};

    ft_putendl("*Platform info*\n______________");
    for (int i = 0; i < 3; i++) {
        char    *prefix;
        if (i == 0)
            prefix = "Name: ";
        if (i == 1)
            prefix = "Vendor: ";
        if (i == 2)
            prefix = "Version: ";
        clGetPlatformInfo(id, info[i], 0, NULL, &value_len);
        value = (char *) malloc(value_len);
        clGetPlatformInfo(id, info[i], value_len, value, &value_len);
        ft_putstr(prefix);
        ft_putendl(value);
        free(value);
    }
    ft_putendl("______________");
}

cl_device_id    get_device_info(cl_platform_id id, cl_device_info value_name)
{
    cl_device_id    *devices;
    cl_uint         device_count;
    char            *name;
    size_t          name_len;

    clGetDeviceIDs(id, value_name, 0, NULL, &device_count);
    devices = (cl_device_id*)malloc(sizeof(cl_device_id) * device_count);
    clGetDeviceIDs(id, value_name, device_count, devices, NULL);
    ft_putendl("Available devices:");
    for (int i = 0; i < (int)device_count; i++)
    {
        clGetDeviceInfo(devices[i], CL_DEVICE_NAME, 0, NULL, &name_len);
        name = (char*)malloc(name_len);
        clGetDeviceInfo(devices[i], CL_DEVICE_NAME, name_len, name, NULL);
        ft_putstr("Name: ");
        ft_putendl(name);
        free(name);
    }
    return (*devices);
}

void    print_device_info(cl_device_id id)
{
    char    *name;
    size_t  name_len;

    clGetDeviceInfo(id, CL_DEVICE_NAME, 0, NULL, &name_len);
    name = (char*)malloc(name_len);
    clGetDeviceInfo(id, CL_DEVICE_NAME, name_len, name, NULL);
    ft_putstr("Device: ");
    ft_putendl(name);
}

void    get_build_log(cl_program prog, cl_device_id id, cl_int errno)
{
    char    *build = NULL;
    char    *build_log = NULL;
    size_t  log_size;
    int     ret = 0;

    clGetProgramBuildInfo(prog, id, CL_PROGRAM_BUILD_STATUS, sizeof(cl_build_status), &build, NULL);
    ft_putstr("Error ");
    ft_putnbr(errno);
    ft_putchar('\n');
    ret = clGetProgramBuildInfo(prog, id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	ft_putstr("Build status: ");
	ft_putnbr(ret);
	ft_putchar('\n');
    build_log = (char*)malloc(log_size);
    clGetProgramBuildInfo(prog, id, CL_PROGRAM_BUILD_LOG, log_size, build_log, NULL);
    build_log[log_size] = '\0';
	ft_putstr("Build log: ");
	ft_putendl(build_log);
	free(build_log);
}