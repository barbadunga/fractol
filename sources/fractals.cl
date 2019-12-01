int         colorize(double3 rgb, double index)
{
    char3 c;

   c.x = (char)(cos(0.015 * index + 3.0 + rgb.x) * 127.5 + 127.5);
   c.y = (char)(cos(0.015 * index + 3.0 + rgb.y) * 127.5 + 127.5);
   c.z = (char)(cos(0.015 * index + 3.0 + rgb.z) * 127.5 + 127.5);
   return ((unsigned char)c.x << 16 | (unsigned char)c.y << 8 | (unsigned char)c.z);
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

kernel void mandelbrot(__global int *data, int2 size, double2 center, double radius, int max_iter, double2 c_j, double3 pal)
{
    int         idx = get_global_id(0);
    double2     z, c;
    double      r2, index;
    int         color = 0x0;

    c = transform(idx, center, radius, size);
    z.xy = (double2)(0.0, 0.0);
    for (int i = 0; i < max_iter; i++)
    {
        r2 = cmod(z);
        if (r2 > 4)
        {
            index = i - log(log(r2)) + 4;
            color = colorize(pal, index);
            break;
        }
        z = cmul(z, z);
        z = cadd(z, c);
    }
    data[idx] = color;
}

kernel void julia(__global int *data, int2 size, double2 center, double radius, int max_iter, double2 c, double3 pal)
{
    int     idx = get_global_id(0);
    double  index, r2;
    double2 z;
    int     color = 0x0;
    char3        rgb;

    z = transform(idx, center, radius, size);
    for (int i = 0; i < max_iter; i++)
    {
        z = cmul(z, z);
        z = cadd(z, c);
        r2 = cmod(z);
        if (r2 > 4)
        {
            index = i - log(log(r2)) + 4;
            color = colorize(pal, index);
            break;
        }
    }
    data[idx] = color;
}
