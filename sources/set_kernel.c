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
#include <stdio.h>

void        destroy_kernel(t_kernel **kernel)
{
//    Clean all struct with OpenCL release methods
    free(*kernel);
    *kernel = NULL;
}

t_kernel    *init_kernel()
{
    t_kernel        *kernel;
    int             ret;
    cl_uint         ret_num_platforms;
    cl_uint         ret_num_device;

    if (!(kernel = (t_kernel*)malloc(sizeof(kernel))))
        return (NULL);
    kernel->ctx = NULL;
    kernel->prog = NULL;
    ret = clGetPlatformIDs(1, &kernel->platform, &ret_num_platforms);
    get_platform_info(kernel->platform); // DELETE
    if (ret != CL_SUCCESS)
        return (NULL);
//    get_device_info(kernel->platform, CL_DEVICE_TYPE_ALL); // DELETE
    ret = clGetDeviceIDs(kernel->platform, CL_DEVICE_TYPE_GPU, 1, &kernel->device, &ret_num_device);
    print_device_info(kernel->device); // DELETE
    if (ret != CL_SUCCESS)
        return (NULL);
    kernel->ctx = clCreateContext(0, 1, &kernel->device, NULL, NULL, &ret);
    if (ret != CL_SUCCESS)
        return (NULL);
    kernel->queue = clCreateCommandQueue(kernel->ctx, kernel->device, 0, &ret);
    if (ret != CL_SUCCESS)
        return (NULL);
    return (kernel);
}

int load_kernel(t_kernel *kernel)
{
    char    *source;
    size_t  len;
    int     ret;

    if (!(source = read_kernel("./sources/fractals.cl")))
        return (1);
    len = ft_strlen(source);
    kernel->prog = clCreateProgramWithSource(kernel->ctx, 1, (const char **)&source, &len, &ret);
    if (ret != CL_SUCCESS)
        return (1);
    ft_strdel(&source);
    ret = clBuildProgram(kernel->prog, 1, &kernel->device, NULL, NULL, NULL);
    if (ret != CL_SUCCESS) {
        get_build_log(kernel->prog, kernel->device, ret);
        return (1);
    }
    kernel->core = clCreateKernel(kernel->prog, "mandelbrot", &ret);
    if (ret != CL_SUCCESS) {
        printf("Create Kernel: %d\n", ret);
        return (1);
    }
    return (0);
}

int set_args_kernel(t_kernel *kernel)
{
//    printf("SET ARGS\n");
    int     ret;
    int     height;
    int     width;

    kernel->buffer = clCreateBuffer(kernel->ctx, CL_MEM_WRITE_ONLY, HEIGHT * WIDTH, NULL, &ret);
    if (ret != CL_SUCCESS)
        return (1);
    ret = clSetKernelArg(kernel->core, 0, sizeof(cl_mem), &kernel->buffer);
    if (ret != CL_SUCCESS)
        return (1);
    height = HEIGHT;
    ret = clSetKernelArg(kernel->core, 1, sizeof(cl_int), &height);
    if (ret != CL_SUCCESS)
        return (1);
    width = WIDTH;
    ret = clSetKernelArg(kernel->core, 1, sizeof(cl_int), &width);
    if (ret != CL_SUCCESS)
        return (1);
    return (0);
}

int run_kernel(void *data) {
    t_kernel *kernel;
    int ret;
    size_t global_work_size;

    if (!(kernel = init_kernel()))
        return (1);
    if (load_kernel(kernel))
        return (1);
    if (set_args_kernel(kernel))
        return (1);
    global_work_size = HEIGHT * WIDTH;
    ret = clEnqueueNDRangeKernel(kernel->queue, kernel->core, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    if (ret != CL_SUCCESS)
        return (1);
    clFinish(kernel->queue);
    clEnqueueReadBuffer(kernel->queue, kernel->buffer, CL_TRUE, 0, HEIGHT * WIDTH, data, 0, NULL, NULL);
    clFinish(kernel->queue);
    clReleaseCommandQueue(kernel->queue);
    clReleaseContext(kernel->ctx);
    return (0);
}