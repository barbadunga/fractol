kernel void mandelbrot(__global int *data, int2 size, double2 center, double radius, int max_iter, double2 c_j)
{
    int         idx = get_global_id(0);
    int         index;
    double2     z, c;
    double      r2;
    int         color = 0;
    double      tmp;

    c.x = center.x + radius * ((double)(idx % size.x) - size.x / 2.0) / (size.y / 2.0);
    c.y = center.y - radius * ((double)(idx / size.y) - size.y / 2.0) / (size.y / 2.0);
    z.xy = (double2)(0.0, 0.0);
    for (int i = 0; i < max_iter; i++)
    {
        r2 = z.x * z.x + z.y * z.y;
        if (r2 > 4)
        {
            index = i + 1 - log(log(sqrt(r2))) / log(2.0);
            /*
            double t = (double)index / (double)max_iter;
            int red = (int)(9 * (1 - t) * pow(t, 3) * 255);
            int green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
            int blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
            color = red << 16 | green << 8 | blue;
            */
            color = 255 * (double)index / max_iter;
            break;
        }
        tmp = z.x;
        z.x = z.x * z.x - z.y * z.y + c.x;
        z.y = 2 * tmp * z.y + c.y;
    }
    data[idx] = color;
}

kernel void julia(__global int *data, int2 size, double2 center, double radius, int max_iter, double2 c)
{
    int     idx = get_global_id(0);
    double2 z, old;
    double  r2;
    int     color = 0;

    z.x = center.x + radius * ((double)(idx % size.x) - size.x / 2.0) / (size.y / 2.0);
    z.y = center.y - radius * ((double)(idx / size.y) - size.y / 2.0) / (size.y / 2.0);
    for (int i = 0; i < max_iter; i++)
    {
        old = z;
        z.x = old.x * old.x - old.y * old.y + c.x;
        z.y = 2 * old.x * old.y + c.y;
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
    }
    data[idx] = color;
}
/*
kernel void newton(__global int *data, int2 size, double2 center, double radius, int max_iter, double2 c)
{
    int     idx = get_global_id(0);
    double2 z, r1, r2, r3;
    double  ro2, mod, maxMod = 0.0;
    double  to = 0.0001;
    int     color = 0;
    double  t1, t2, t3, to2;
    int     i = 0;

    z.x = center.x + radius * ((double)(idx % size.x) - size.x / 2.0) / (size.y / 2.0);
    z.y = center.y - radius * ((double)(idx / size.y) - size.y / 2.0) / (size.y / 2.0);
    r1 = (double2)(1, 0);
    r2 = (double2)(-0.5, 0.86602540378443882);
    r3 = (double2)(-0.5, -0.86602540378443882);
    to2 = to * to;
    while (i < max_iter)
    {
        t1 = z.x * z.x - 2 * z.x * r1.x + r1.y * r1.y;
        t2 = z.x * z.x - 2 * z.x * r2.x + r2.y * r2.y;
        t3 = z.x * z.x - 2 * z.x * r3.x + r3.y * r3.y;
        ro2 = z.x * z.x + z.y * z.y;
        if (t1 >= to2 || t2 >= to2 || t3 >= to2)
            break;
        if (ro2 >= 0)
        {
            double2 tmp = z;
            z.x = tmp.x * (tmp.x * tmp.x - tmp.y * tmp.y);
            z.y = tmp.y * (3 * tmp.x * tmp.x - 2 * tmp.x * tmp.y - tmp.y * tmp.y);
        }
        i++;
    }
    if (t1 < to)
        color = (255 - i * 15) << 16;
    else if (t2 < to)
        color = (255 - i * 15) << 8;
    else if (t3 < to)
        color = 255 - i * 15;
    data[idx] = color;
} */