kernel void mandelbrot(__global int data, __global int h, __global int w)
{
    unsigned int x = get_global_id(0);
    unsigned int y = get_global_id(1);
    unsigned int i = 0;

    float a = -2.5+(((float)x)/size)*3.5;
    float b = -1.75+(((float)y)/size)*3.5;
    double2 z = (0.0, 0.0);
    int     i;
    for (i = 0; i < 100; i++) {
        if (z.x*z.x + z.y*z.y > 4) {
            break;
        }
        double tmp = z.x;
        z.x = z.x*z.x - z.y*z.y + a;
        z.y = 2*tmp*z.y + b;
    }
    buffer[x + y*w] = i*255 / 100;
}
