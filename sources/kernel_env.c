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

t_kernel    *init_kernel()
{
    t_kernel        *kernel;
    int             ret;
    cl_uint         ret_num_platforms;
    cl_uint         ret_num_device;

    if (!(kernel = (t_kernel*)malloc(sizeof(t_kernel))))
        return (NULL);
    kernel->buffer = NULL;
    kernel->core = NULL;
    kernel->ctx = NULL;
    kernel->queue = NULL;
    kernel->prog = NULL;
    if (clGetPlatformIDs(1, &kernel->platform, &ret_num_platforms))
    	return (NULL);
    if (clGetDeviceIDs(kernel->platform, CL_DEVICE_TYPE_GPU, 1, &kernel->device,
    		&ret_num_device))
		return (NULL);
    kernel->ctx = clCreateContext(0, 1, &kernel->device, NULL, NULL, &ret);
    if (ret != CL_SUCCESS)
        return (NULL);
    kernel->queue = clCreateCommandQueue(kernel->ctx, kernel->device, 0, &ret);
    if (ret != CL_SUCCESS)
        return (NULL);
    return (kernel);
}

int load_kernel(t_kernel *kernel, char *name)
{
    char    *source;
    size_t  len;
    int     ret;

    if (!(source = read_kernel("./sources/fractals.cl")))
        return (1);
    len = ft_strlen(source);
    kernel->prog = clCreateProgramWithSource(kernel->ctx, 1,
    		(const char **)&source, &len, &ret);
	ft_strdel(&source);
    if (ret != CL_SUCCESS)
        return (1);
    if (clBuildProgram(kernel->prog, 1, &kernel->device, NULL, NULL, NULL))
    {
        get_build_log(kernel->prog, kernel->device, ret);
        return (1);
    }
    kernel->core = clCreateKernel(kernel->prog, name, &ret); // segfault
    if (ret != CL_SUCCESS)
        return (1);
    return (0);
}

int set_args_kernel(t_kernel *krnl)
{
    int         ret;
	const int	size[2] = {WIDTH, HEIGHT};

    krnl->buffer = clCreateBuffer(krnl->ctx, CL_MEM_WRITE_ONLY, sizeof(int) * HEIGHT * WIDTH, NULL, &ret);
    if (ret != CL_SUCCESS)
        return (1);
    if ((ret = clSetKernelArg(krnl->core, 0, sizeof(cl_mem), &krnl->buffer)))
    	return (1);
	if ((ret = clSetKernelArg(krnl->core, 1, sizeof(cl_int2), &size)))
		return (1);
    return (0);
}

int	run_kernel(t_fctl *fctl)
{
	static const size_t	global_work_size = HEIGHT * WIDTH;
	const t_view		*v = fctl->img->view;
	const t_kernel		*krnl = fctl->kernel;

	if (clSetKernelArg(krnl->core, 2, sizeof(cl_double2), &(v->center)))
		return (1);
	if (clSetKernelArg(krnl->core, 3, sizeof(double), &(v->radius)))
		return (1);
	if (clSetKernelArg(krnl->core, 4, sizeof(int), &(v->max_iter)))
		return (1);
	if (clSetKernelArg(krnl->core, 5, sizeof(cl_double2), &(v->cnst)))
		return (1);
	if (clEnqueueNDRangeKernel(krnl->queue, krnl->core, 1, NULL, &global_work_size, NULL, 0, NULL, NULL)) // segfault
		return (1);
	clFinish(krnl->queue);
	if (clEnqueueReadBuffer(krnl->queue, krnl->buffer, CL_TRUE, 0, sizeof(int) * HEIGHT * WIDTH, fctl->img->data, 0, NULL, NULL))
		return (1);
	clFinish(krnl->queue);
	return (0);
}

int new_kernel(t_fctl *fctl)
{
	t_kernel	*kernel;

    if (!(kernel = init_kernel()))
		return (1);
    if (load_kernel(kernel, fctl->name) || set_args_kernel(kernel))
		return (1);
    fctl->kernel = kernel;
    return (0);
}