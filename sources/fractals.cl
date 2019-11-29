int     colorize(int i, int max)
{
    double  t;

    t = (double)i / max;
    int red = (int)(9 * (1 - t) * pow(t, 3) * 255);
    int green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
    int blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
    return (red << 16 | green << 8 | blue);
}

int         coloring(double t)
{
    int red = (int)(9 * (1 - t) * pow(t, 3) * 255);
    int green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
    int blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
    return (red << 16 | green << 8 | blue);
}

double2     transform(int idx, double2 c, double r, int2 s)
{
    double2 complex;

    complex.x = c.x + r * ((double)(idx % s.x) - s.x / 2.0) / (s.y /2.0);
    complex.y = c.y - r * ((double)(idx / s.y) - s.y / 2.0) / (s.y /2.0);
    return (complex);
}

double      cmod(double2 z)
{
    return (z.x * z.x + z.y * z.y);
}

double2     cmul(double2 z1, double2 z2)
{
    double2 z;

    z.x = z1.x * z2.x - z1.y * z2.y;
    z.y = z1.x * z2.y + z2.x * z1.y;
    return (z);
}

double2     cadd(double2 z1, double2 z2)
{
    return ((double2)(z1.x + z2.x, z1.y + z2.y));
}

kernel void mandelbrot(__global int *data, int2 size, double2 center, double radius, int max_iter, double2 c_j)
{
    int         idx = get_global_id(0);
    double2     z, c;
    double      r2;
    int         color = 0x0;

    c = transform(idx, center, radius, size);
    z.xy = (double2)(0.0, 0.0);
    for (int i = 0; i < max_iter; i++)
    {
        r2 = cmod(z);
        if (r2 > 10000)
        {
            color = colorize(i, max_iter);
            break;
        }
        z = cmul(z, z);
        z = cadd(z, c);
    }
    data[idx] = color;
}

kernel void julia(__global int *data, int2 size, double2 center, double radius, int max_iter, double2 c)
{
    int     idx = get_global_id(0);
    double2 z;
    double  r2;
    int     color = 0x0;

    z = transform(idx, center, radius, size);
    for (int i = 0; i < max_iter; i++)
    {
        z = cmul(z, z);
        z = cadd(z, c);
        r2 = cmod(z);
        if (r2 > 4)
        {
            color = colorize(i, max_iter);
            break;
        }
    }
    data[idx] = color;
}
