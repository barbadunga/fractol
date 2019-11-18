kernel void mandelbrot(__global int *data, int size_x, int size_y, double x, double y, double radius, int max_iter)
{
    int         idx = get_global_id(0);
    double2     z, c;
    double      r2;
    int         color = 0;
    double      tmp;
    double2     min, max;

    c.x = x + radius * ((double)(idx % size_x) - size_x / 2.0) / (size_y / 2.0);
    c.y = y - radius * ((double)(idx / size_y) - size_y / 2.0) / (size_y / 2.0);
    z.xy = (double2)(0.0, 0.0);
    double  otr = 0.01 * radius;
    if ((c.x >= x - otr && c.x <= x + otr) && (c.y <= y + otr && c.y >= y - otr))
    {
        data[idx] = 0xFF0000;
        return ;
    }
    if ((c.x >= x - radius && c.x <= x + radius) && (c.y <= y + radius && c.y >= y - radius)) // only radius
    for (int i = 0; i < max_iter; i++)
    {
        r2 = z.x * z.x + z.y * z.y;
        if (r2 > 4)
        {
            double t = (double)i / (double)max_iter;
            int red = (int)(9 * (1 - t) * pow(t, 3) * 255);
            int green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
            int blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
            color = red << 16 | green << 8 | blue;
            break;
        }
        tmp = z.x;
        z.x = z.x * z.x - z.y * z.y + c.x;
        z.y = 2 * tmp * z.y + c.y;
    }
    data[idx] = color;
}
