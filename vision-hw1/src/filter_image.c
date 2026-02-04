#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

image image_of_ones(int h,int w,int c){
    image im = make_image(w,h,c);
    for (int i = 0; i < im.h*im.w*im.c; i++)
    {

        im.data[i] = 1.0f;
    }
    return  im;
}

void l1_normalize(image im)
{
    float normalize=0;
    

    for (int i = 0; i < im.c*im.h*im.w; i++)
    {
        normalize += im.data[i];
    }
    if (normalize==0)
        return;
    for (int i = 0; i < im.h; i++)
    {
        for (int j = 0; j < im.w; j++)
        {
           for (int z = 0; z < im.c; z++)
           {
            set_pixel(im,i,j,z,(float)1/normalize);  
           }
           
        }
        
    }
    
}

image make_box_filter(int w)
{
    image im =image_of_ones(w,w,1);
    l1_normalize(im);
    return im;
}

image convolve_image(image im, image filter, int preserve)
{
    // cross correlação discreta pode ser expressa
    // g(x,y) = h⊗f = ∑h(u,v)f(i+u,j+v), seja h(u,v) o kernel que se deseja aplicar e f(x,y) o pixel da imagem original
    // g(x,y) é o pixel aplicado a mascara(kernel)
    // get_pixel está usando a estragédia clamp
    // também é necessário centralizar o centro do kernel com o pixel selecionado, então é preciso pegar as coordenadas
    // do centro do kernel e assim aplicar a cross correlation

    assert(im.c == filter.c || filter.c == 1);

    int out_c = preserve ? im.c : 1;

    image out = make_image(im.w, im.h, out_c);

    int fh = filter.h / 2;
    int fw = filter.w / 2;

    for (int i = 0; i < im.w; i++)
    {
        for (int j = 0; j < im.h; j++)
        {
            for (int z = 0; z < im.c; z++)
            {
                float sum = 0.0f;

                for (int a = 0; a < filter.w; a++)
                {
                    for (int b = 0; b < filter.h; b++)
                    {
                        int fc = (filter.c == 1) ? 0 : z;

                        float im_val = get_pixel(
                            im,
                            i + a - fh,
                            j + b - fw,
                            z
                        );

                        float f_val = get_pixel(filter, a, b, fc);

                        sum += im_val * f_val;
                    }
                }

                if (preserve)
                {
                    set_pixel(out, i, j, z, sum);
                }
                else
                {
                    float prev = get_pixel(out, i, j, 0);
                    set_pixel(out, i, j, 0, prev + sum);
                }
            }
        }
    }

    return out;
}


image make_highpass_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_sharpen_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_emboss_filter()
{
    // TODO
    return make_image(1,1,1);
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

image make_gaussian_filter(float sigma)
{
    // TODO
    return make_image(1,1,1);
}

image add_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image sub_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image make_gx_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_gy_filter()
{
    // TODO
    return make_image(1,1,1);
}

void feature_normalize(image im)
{
    // TODO
}

image *sobel_image(image im)
{
    // TODO
    return calloc(2, sizeof(image));
}

image colorize_sobel(image im)
{
    // TODO
    return make_image(1,1,1);
}
