#include <math.h>
#include "image.h"


float nn_interpolate(image im, float x, float y, int c)
{
   
    return   get_pixel(im, ceil(x), ceil(y), c);
}

image nn_resize(image im, int w, int h)
{
    image new_image = make_image(w, h, im.c);

    // System Equation   aX+b = Y to represent transformation  nxn -> mxm
    // the ideia is to find invariant that are the corns 
    // a*x1 +b = y1
    // a*x2 +b = y2
    //x1 belongs to image mxm, and y1 belongs to nxn image, These are just names
    //x2 belongs to image mxm, and y2 belongs to nxn image, These are just names
    // (x1,x2) are unique point (x,y) in image mxm and (y1,y2) are unique point (x,y) in image nxn
    float a,b, x1=-0.5,x2=h-0.5,y1=-0.5,y2=im.h-0.5;

    a= (y1-y2)/(x1-x2);
    b= y1 - x1*a;

    for (int k = 0; k < new_image.c; k++)
    {
        for (int i = 0; i < new_image.w; i++)
        {
            for (int j = 0; j < new_image.h; j++)
            {
                
                set_pixel(new_image,i,j,k,nn_interpolate(im,i*a+b,j*a+b,k));
        }
        
        }
    }
    
    return new_image;
}

float bilinear_interpolate(image im, float x, float y, int c)
{   
    // When we use images  the axis xy begins from:
    //  (0,0) ---------------------> x
    //       |
    //       |
    //       |
//           |
    //       |
    //      y|

    //     d3         d4
    // v1* * * * * * * * * * * * v2
    // *        *                *  
    // *        *                *  
    // *        *                *      d1
    // *        *                *
    // *        *                *
    // *        *                *
    // q1 * * * q  * * * * * * * q2
    // *                         *  
    // *                         *     d2
    // *                         *
    // *                         *
    // *                         *
    // v3 * * * * * * * * * * * *v4
    // v1 = (down_x,down_y)
    // v2 = (upper_x,down_y)
    // v3 = (down_x,upper_y)
    // v4 = (upper_x,upper_y)
    // d1 =  y - down_y
    // d2 =  upper_y - y
    // d3 = x - down_x
    // d4 = upper_x - x
    // q1 = v3*d1 +v1*d2
    // q2 = v4*d1 + v3*d2
    // q =  q1*d4+q2*d3
    float upper_x ,upper_y,down_x,down_y;
    float d1,d2,d3,d4;
    float v1,v2 ,v3,v4;
    float q1,q2,q;
    upper_x = ceil(x);
    upper_y = ceil(y);
    down_x = floor(x);
    down_y = floor(y);
    d1 =  y - down_y;
    d2 =  upper_y - y;
    d3 =  x - down_x;
    d4 = upper_x - x;
    v1 = get_pixel(im,down_x,down_y,c);
    v2 = get_pixel(im,upper_x,down_y,c);
    v3 = get_pixel(im,down_x,upper_y,c);
    v4 = get_pixel(im,upper_x,upper_y,c);
    q1 = v3*d1 +v1*d2;
    q2 = v4*d1 + v2*d2;
    q =  q1*d4+q2*d3;

    return q;
}

image bilinear_resize(image im, int w, int h)
{
    image new_image =make_image(w, h, im.c);
    
    // System Equation   aX+b = Y to represent transformation  nxn -> mxm
    // the ideia is to find invariant that are the corns 
    // a*x1 +b = y1
    // a*x2 +b = y2
    //x1 belongs to image mxm, and y1 belongs to nxn image, These are just names
    //x2 belongs to image mxm, and y2 belongs to nxn image, These are just names
    // (x1,x2) are unique point (x,y) in image mxm and (y1,y2) are unique point (x,y) in image nxn
    float a,b, x1=-0.5,x2=h-0.5,y1=-0.5,y2=im.h-0.5;

    a= (y1-y2)/(x1-x2);
    b= y1 - x1*a;

    for (int k = 0; k < new_image.c; k++)
    {
        for (int i = 0; i < new_image.w; i++)
        {
            for (int j = 0; j < new_image.h; j++)
            {
                
                set_pixel(new_image,i,j,k,bilinear_interpolate(im,i*a+b,j*a+b,k));
        }
        
        }
    }
    return new_image;
}

