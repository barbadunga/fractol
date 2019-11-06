kernel void mandelbrot(__global int *data, int h, int w)
{
    double2 min, max;
    double2  z, c;
    double2 scale;
    uint    max_iter = 100;

    min = (double2)(-2.0, -1.5);
    max.x = 1.0;
    max.y = min.y + (max.x - min.x) * h / w;
    scale.x = (max.x - min.x) / (w - 1);
    scale.y = (max.y - min.y) / (h - 1);
    int idx = get_global_id(0);
    c.x = min.x + idx % w * scale.x;
    c.y = max.y - idx / h * scale.y;
    z = (0.0, 0.0);
    for (int i = 0; i < max_iter; i++)
    {
        uint r2 = z.x * z.x + z.y * z.y;
        if (r2 > 1e10)
        {
            data[idx] = i * 255 / max_iter;
            return ;
        }
        z = (z.x * z.x - z.y * z.y + c.x, 2 * z.y * z.x + c.y);
    }
    data[idx] = 0;
}
