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

double2     cdel(double2 z1, double2 z2)
{
    double  del;

    del = z2.x * z2.x + z2.y * z2.y;
    z1 = cmul(z1, (double2)(z2.x, -z2.y));
    return (z1 / del);
}

double2     cpow(double2 z, int power)
{
    double2 res;

    res = z;
    for (int i = 0; i < power - 1; i++)
        res = cmul(res, z);
    return (res);
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

kernel void ship(__global int *data, int2 size, double2 center, double radius, int max_iter, double2 c, double3 pal)
{
    int     idx = get_global_id(0);
    double  index, r2, tmp;
    double2 z;
    int     color = 0x0;

    c = transform(idx, center, radius, size);
    z = (double2)(0, 0);
    for (int i = 0; i < max_iter; i++)
    {
        r2 = cmod(z);
        if (r2 > 4)
        {
            index = i - log(log(r2)) + 4;
            color = colorize(pal, index);
            break;
        }
        tmp = z.x * z.x - z.y * z.y + c.x;
        double r = z.x * z.y;
        r *= r < 0 ? -1.0 : 1.0;
        z.y = 2 * r - c.y;
        z.x = tmp;
    }
    data[idx] = color;
}

kernel void phoenix(__global int *data, int2 size, double2 center, double radius, int max_iter, double2 c, double3 pal)
{
    int         idx = get_global_id(0);
    double2     z, prev, tmp;
    double      r2, index;
    int         color = 0x0;

    z = transform(idx, center, radius, size);
    prev = 0;
    for (int i = 0; i < max_iter; i++)
    {
        r2 = cmod(z);
        if (r2 > 4)
        {
            index = i - log(log(r2)) + 4;
            color = colorize(pal, index);
            break;
        }
        tmp = z;
        // z.x = z.x * z.x - z.y * z.x + c.x + c.y * prev.y;
        // z.y = 2 * tmp.x * z.y + c.y * prev.x;
        z.x = z.x * z.x - z.y * z.y + c.x + c.y * prev.x + c.y * prev.y;
        z.y = 2 * tmp.x * z.y + c.x;
        prev = tmp;
    }
    data[idx] = color;
}

kernel void newton(__global int *data, int2 size, double2 center, double radius, int max_iter, double2 c, double3 pal)
{
    int     idx = get_global_id(0);
    double  index,tol;
    double2 z, der, p;
    int     color = 0x0, reason;
    double2 roots[3] = {double2(1.0, 0.0),
                        double2(-0.5, 0.8660254037844386),
                        double2(-0.5 -0.8660254037844386)};
    int     colors[3] = {0xFF,
                         0x00FF,
                         0x0000FF};

    z = transform(idx, center, radius, size);
    tol = 0.001;
    reason = 0;
    der = (double2)(1.0, 0.0);
    for (int i = 0; i < max_iter; i++)
    {
        der = 3 * cmul(z, z);
        p = cpow(z, 3) - (double2)(1, 0);
        z = z - cdel(p, z);
        for (int j = 0; j < 3; j++)
        {
            double2 diff = cadd(z, -roots[j]);

            if (diff.x < tol && diff.y < tol)
            {
                color = colors[j];
                reason = 1;
                break;
            }
        }
        if (reason == 1)
            break;
    }
    data[idx] = color;
}

kernel void cubic(__global int *data, int2 size, double2 center, double radius, int max_iter, double2 c_j, double3 pal)
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
        z = cpow(z, 3);
        z = cadd(z, c);
    }
    data[idx] = color;
}

kernel void quartic(__global int *data, int2 size, double2 center, double radius, int max_iter, double2 c_j, double3 pal)
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
        z = cpow(z, 4);
        z = cadd(z, c);
    }
    data[idx] = color;
}

kernel void foo(__global int *data, int2 size, double2 center, double radius, int max_iter, double2 c_j, double3 pal)
{
    int         idx = get_global_id(0);
    double2     z, c, del;
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
        del = cadd(z, c);
        del = cpow(del, 3);
        z = cdel((double2)(1.0, 0.0), del);
    }
    data[idx] = color;
}
