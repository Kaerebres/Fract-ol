#include "cuda_call.h"
#include <stdlib.h>
#include <cuda.h>
#include <math.h>
#include <stdio.h>
#include "fractol.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C"
#endif

static void	handleerrorm(cudaError_t err, const char *file, int line)
{
	if (err != cudaSuccess)
	{
		exit(EXIT_FAILURE);
	}
}

__global__ void kernelm(double c0, double c1, double zoom, char *dev_img, double img_x, double img_y, int iter_max)
{
	double 	x = threadIdx.x+blockIdx.x*blockDim.x;
	double 	y = threadIdx.y+blockIdx.y*blockDim.y;
	double	zr;
	double	zi;
	int		i;
	double	tmp;
	int		pixel;
	int mapping[16][3];

	mapping[0][0] = 66;
	mapping[0][1] = 30;
	mapping[0][2] = 15;
	mapping[1][0] = 25;
	mapping[1][1] = 7;
	mapping[1][2] = 26;
	mapping[2][0] = 9;
	mapping[2][1] = 1;
	mapping[2][2] = 47;
    mapping[3][0] = 4;
	mapping[3][1] = 4;
	mapping[3][2] = 73;
	mapping[4][0] = 0;
	mapping[4][1] = 7;
	mapping[4][2] = 100;
	mapping[5][0] = 12;
	mapping[5][1] = 44;
	mapping[5][2] = 138;
 	mapping[6][0] = 24;
	mapping[6][1] = 82;
	mapping[6][2] = 177;
	mapping[7][0] = 57;
	mapping[7][1] = 125;
	mapping[7][2] = 209;
    mapping[8][0] = 134;
	mapping[8][1] = 181;
	mapping[8][2] = 229;
    mapping[9][0] = 211;
	mapping[9][1] = 234;
	mapping[9][2] = 248;
    mapping[10][0] = 241;
	mapping[10][1] = 233;
	mapping[10][2] = 191;
	mapping[11][0] = 248;
	mapping[11][1] = 201;
	mapping[11][2] = 95;
	mapping[12][0] = 255;
	mapping[12][1] = 170;
	mapping[12][2] = 0;
	mapping[13][0] = 204;
	mapping[13][1] = 128;
	mapping[13][2] = 0;
	mapping[14][0] = 153;
	mapping[14][1] = 87;
	mapping[14][2] = 0;
	mapping[15][0] = 106;
	mapping[15][1] = 52;
	mapping[15][2] = 3;
	if (x > LEN + 1)
		return ;
	if (y > LEN + 1)
		return ;
	pixel = x * 4 + (y * LEN * 4) * 2;
	zr = 0;
	zi = 0;
	i = 0;
	c0 = x / zoom + img_x;
	c1 = y / zoom + img_y;

	while (sqrtf(zr * zr + zi * zi) < 4 && i < iter_max)
	{
		tmp = zr;
		zr = zr * zr - zi * zi + c0;
		zi = 2 * zi * tmp + c1;
		i++;
		if (i == iter_max)
		{
			dev_img[pixel] = 0;
			dev_img[pixel + 1] = 0;
			dev_img[pixel + 2] = 0;
			dev_img[pixel + 3] = 0;
			break ;
		}
		else
		{
			dev_img[pixel] = mapping[i % 16][0];
			dev_img[pixel + 1] = mapping[i % 16][1];
			dev_img[pixel + 2] = mapping[i % 16][2];
			dev_img[pixel + 3] = 0;
		}
	}
}

#include <stdio.h>
#ifdef __cplusplus
extern "C"
#endif

char	*callcuda_mand(t_data *data, double x, double y)
{
	char 	*dev_img = NULL;
	double	c[2];
	double	zoo;
	double	img_x;
	double	img_y;

	img_x = data->x1;
	img_y = data->y1;
	c[0] = (x + (LEN / 2)) / (LEN / 2);
	c[1] = (y + (LEN / 2)) / (LEN / 2);

	HANDLE_ERRORM(cudaMalloc((void**)&dev_img, (LEN * LEN * 4 * 2 + 1)));
	dim3	blocks((LEN)/ 32, (LEN) / 32);
	dim3	threads(32, 32);
	zoo = data->zoom;
	kernelm<<<blocks,threads>>>(c[0], c[1], zoo, dev_img, img_x, img_y, data->iter_max);
	cudaDeviceSynchronize();
	HANDLE_ERRORM(cudaMemcpy(data->img_str, dev_img, LEN * LEN * 4 * 2 + 1, cudaMemcpyDeviceToHost));
	cudaFree(dev_img);
	return (data->img_str);
}