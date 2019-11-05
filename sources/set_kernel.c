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
//    Clean all struct with OpenCL destroy methods
    free(*kernel);
    *kernel = NULL;
}

t_kernel    *init_kernel()
{
    printf("INIT KERNEL\n");
    t_kernel        *kernel;
    cl_device_id    device;
    int             ret;

    if (!(kernel = (t_kernel*)malloc(sizeof(kernel))))
        return (NULL);
    ret = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (ret != CL_SUCCESS)
        return (NULL);
    kernel->ctx = clCreateContext(0, 1, &device, NULL, NULL, &ret);
    if (ret != CL_SUCCESS)
        return (NULL);
    kernel->queue = clCreateCommandQueue(kernel->ctx, device, 0, &ret);
    if (ret != CL_SUCCESS)
        return (NULL);
    return (0);
}

int load_kernel(t_kernel *kernel)
{
    printf("LOAD KERNEL\n");
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
    return (0);
}

int compile_kernel(t_kernel *kernel)
{
    printf("COMPILE KERNEL");
    int ret;

    ret = clBuildProgram(kernel->prog, 0, NULL, NULL, NULL, NULL);
    if (ret != CL_SUCCESS)
        return (1);
    kernel->core = clCreateKernel(kernel->prog, "mandelbrot", &ret);
    if (ret != CL_SUCCESS)
        return (1);
    return (0);
}

int set_args_kernel(t_kernel *kernel)
{
    printf("SET ARGS\n");
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

    if ((kernel = init_kernel())) {
        printf("DROP INIT\n");
        return (1);
    }
    if (load_kernel(kernel)) {
        printf("DROP LOAD\n");
        return (1);
    }
    if (compile_kernel(kernel)) {
        printf("DROP COMPILE\n");
        return (1);
    }
    if (set_args_kernel(kernel)) {
        printf("DROP SET ARGS\n");
        return (1);
    }
    global_work_size = HEIGHT * WIDTH;
    printf("RUN KERNEL\n");
    ret = clEnqueueNDRangeKernel(kernel->queue, kernel->core, 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
    clFinish(kernel->queue);
    clEnqueueReadBuffer(kernel->queue, kernel->buffer, CL_TRUE, 0, HEIGHT * WIDTH, data, 0, NULL, NULL);
    clFinish(kernel->queue);
    clReleaseCommandQueue(kernel->queue);
    clReleaseContext(kernel->ctx);
    return (1);
}