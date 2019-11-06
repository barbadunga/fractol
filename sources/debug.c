//
// Created by Morna Shagga on 2019-11-06.
//

#include "fractol.h"
#include <stdio.h>

void    get_platform_info(cl_platform_id id)
{
    cl_int  ret = 0;
    char    *value = NULL;
    size_t  value_len = 0;
    int    info[3] = {CL_PLATFORM_NAME, CL_PLATFORM_VENDOR, CL_PLATFORM_VERSION};

    printf("*Platform info*\n______________\n");
    for (int i = 0; i < 3; i++) {
        char    *prefix;
        if (i == 0)
            prefix = "Name:";
        if (i == 1)
            prefix = "Vendor:";
        if (i == 2)
            prefix = "Version: ";
        ret = clGetPlatformInfo(id, info[i], 0, NULL, &value_len);
        value = (char *) malloc(value_len);
        ret = clGetPlatformInfo(id, info[i], value_len, value, &value_len);
        printf("%s %s\n", prefix, value);
        free(value);
    }
    printf("______________\n");
}

cl_device_id    get_device_info(cl_platform_id id, cl_device_info value_name)
{
    cl_device_id    *devices;
    cl_uint         device_count;
    char            *name;
    size_t          name_len;
    cl_uint         ret = 0;

    ret = clGetDeviceIDs(id, value_name, 0, NULL, &device_count);
    devices = (cl_device_id*)malloc(sizeof(cl_device_id) * device_count);
    ret = clGetDeviceIDs(id, value_name, device_count, devices, NULL);
    printf("Available devices:\n");
    for (int i = 0; i < (int)device_count; i++)
    {
        clGetDeviceInfo(devices[i], CL_DEVICE_NAME, 0, NULL, &name_len);
        name = (char*)malloc(name_len);
        clGetDeviceInfo(devices[i], CL_DEVICE_NAME, name_len, name, NULL);
        printf("Name: %s\n", name);
        free(name);
    }
    return (*devices);
}

void    print_device_info(cl_device_id id)
{
    char    *name;
    size_t  name_len;
    int     ret;

    ret = clGetDeviceInfo(id, CL_DEVICE_NAME, 0, NULL, &name_len);
    name = (char*)malloc(name_len);
    ret = clGetDeviceInfo(id, CL_DEVICE_NAME, name_len, name, NULL);
    printf("Device: %s\n", name);
}

void    get_build_log(cl_program prog, cl_device_id id, cl_int errno)
{
    char    *build = NULL;
    char    *build_log = NULL;
    size_t  log_size;
    int     ret = 0;

    ret = clGetProgramBuildInfo(prog, id, CL_PROGRAM_BUILD_STATUS, sizeof(cl_build_status), &build, NULL);
    printf("Error %d\n", errno);
    ret = clGetProgramBuildInfo(prog, id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
    printf("Build status: %d\n", ret);
    build_log = (char*)malloc(log_size);
    ret = clGetProgramBuildInfo(prog, id, CL_PROGRAM_BUILD_LOG, log_size, build_log, NULL);
    build_log[log_size] = '\0';
    printf("Build log: %s", build_log);

}