kernel void mandelbrot(__global int *data, int h, int w)
{
	int idx = get_global_id(0);
	int iterations = 100;
	int i = 0;
	float2 min = (-2.0f, -1.5f);
    float2 max = (1.0f, 0.0f);
    int color = 0xFFFFFF;
    max.y = min.y + (max.x - min.x) * h/w;

    float2 factor = ((max.x-min.x)/w-1, (max.y-min.y)/h-1);

	float2 z = (0.0, 0.0);
    float2 c = (min.x + idx % w * factor.x, max.y - idx / h * factor.y);
	for (i = 0; i < iterations; i++) {
		if (z.x*z.x + z.y*z.y > 4){
		    color = 0xFFFFFF;
		    break;
		}
		float oldx = z.x;
		z.x = z.x*z.x - z.y*z.y + c.x;
		z.y = 2*oldx*z.y + c.y;
	}
	double t = (double)i / (double)iterations;
    int red = (int)(9 * (1 - t) * pow(t, 3) * 255);
    int green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
    int blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
    color = red;
	data[idx] = color;
}
