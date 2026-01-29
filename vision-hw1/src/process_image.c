#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define modulo(x) ((x)>=(0) ? (x): (-x))
#define mod(x) ((x)>=(0) ? (x): (-x))
float get_pixel(image im, int x, int y, int c)
{
    if (x<0){
        x=0;
    }
    if (y<0){
        y=0;
    } 
    if (c<0){
        c=0;
    } 
    if(x>=im.w){
        x=im.w-1;
    }
    if(y>=im.h){
        y=im.h-1;
    }
    if(c>=im.c){
        c=im.c-1;

    }

    return  im.data[im.w*im.h*c + y*im.w +x];
}

void set_pixel(image im, int x, int y, int c, float v)
{

    if ( x<im.w && x>=0 && y>=0 && y<im.h && c>=0 && c<im.c){
        im.data[im.w*im.h*c + y*im.w +x]  = v;
    }
}


image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    memcpy ( &copy, &im, sizeof(im) );
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    float y_transform;
    for (int i = 0; i < im.w ; i++)
    {
      for (int j = 0; j < im.h; j++)
      {
        y_transform=0.299*get_pixel(im,i, j, 0) + 0.587*get_pixel(im,i, j, 1)+0.114*get_pixel(im,i, j, 2);
        set_pixel(gray, i, j, 0, y_transform);

    }
      
    }
    
    return gray;
}

void shift_image(image im, int c, float v)
{
   float pixelValue;

    for (int i = 0; i < im.w; i++)
    {
       for (int j = 0; j < im.h; j++)
       {
         pixelValue = get_pixel(im, i, j,c);
         set_pixel(im, i, j, c , v+pixelValue);
       }
       
    }
    
}



void clamp_image(image im)
{
    float pixelValueRed;
    float pixelValueGreen;
    float pixelValueBlue;

    for (int i = 0; i < im.w; i++)
    {
       for (int j = 0; j < im.h; j++)
       {
         pixelValueRed = get_pixel(im, i, j,0);
         if(pixelValueRed>1){
            pixelValueRed=1;
         }
         if(pixelValueRed<0){
            pixelValueRed=0;
         }
         pixelValueGreen = get_pixel(im, i, j,1);
         if(pixelValueGreen>1){
            pixelValueGreen=1;
         }
         if(pixelValueGreen<0){
            pixelValueGreen=0;
         }
         pixelValueBlue = get_pixel(im, i, j,2);
         if(pixelValueBlue>1){
            pixelValueBlue=1;
         }
         if(pixelValueBlue<0){
            pixelValueBlue=0;
         }
         

         set_pixel(im, i, j, 0 , pixelValueRed);
         set_pixel(im, i, j, 1 , pixelValueGreen);
         set_pixel(im, i, j, 2 , pixelValueBlue);
       }
       
    }
    
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
   
     for (int i = 0; i < im.w; i++)
    {
       for (int j = 0; j < im.h; j++)
       {
        float Value,min;
        float R = get_pixel(im, i, j,0);
        float G = get_pixel(im, i, j,1);
        float B = get_pixel(im, i, j,2);

        Value = three_way_max(R,G,B);
        min = three_way_min(R,G,B);
      
        float C = Value - min;
        float Saturation = Value==0?  0: (C / Value);
        float HueProjection,Hue;

        if (Value==R){
            HueProjection = (G-B)/C;
        }
        if(Value==G){
            HueProjection = ((B-R)/C) + 2;
        }
        if(Value==B){
            HueProjection = ((R-G)/C)  + 4;
        }
        if(C==0){
            HueProjection = 0;
        } 
        if(HueProjection<0){
            Hue = (HueProjection/6) + 1;
        }else{
            Hue = ((HueProjection)/6);
        }
        
        set_pixel(im, i, j, 0 , Hue);
        set_pixel(im, i, j, 1 , Saturation);
        set_pixel(im, i, j, 2 , Value);

       }
       
    }
}


void hsv_to_rgb(image im)
{
       for (int i = 0; i < im.w; i++)
       {
        for (int j = 0; j < im.h; j++)
        {
            float R=0,G=0,B=0,X,C,m,H_;
            float H = get_pixel(im, i, j,0);
            float S = get_pixel(im, i, j,1);
            float V = get_pixel(im, i, j,2);

            C = V*S;
            H_ = H*6;
            X = C*(1 - fabs( fmod(H_,2) - 1 ) );
            m = V - C;
            // printf("HUE EXEIBIDO: %f\n", H_);

            if (H_<1 && H_>=0){
                R = C;
                G = X;
                B = 0;
            }
            if(H_>=1 && H_<2){
                R = X;
                G = C;
                B = 0;
            }
            if (H_>=2 && H_<3)
            {
                R = 0;
                G = C;
                B = X;
            }
            if (H_>=3 && H_<4)
            {
                R = 0;
                G = X;
                B = C;
            }
            if (H_>=4 && H_<5)
            {
                R = X;
                G = 0;
                B = C;
            }
            if (H_>=5 && H_<6)
            {
                R = C;
                G = 0;
                B = X;
            }
                                   
            set_pixel(im, i, j, 0 , (R+m));
            set_pixel(im, i, j, 1 , (G+m));
            set_pixel(im, i, j, 2 , (B+m));
        }        
    }
}

void scale_image(image im, int c, float v){
    for (int i = 0; i < im.w; i++)
    {
       for (int j = 0; j < im.h; j++)
       {
        float S = get_pixel(im, i, j,c);
        set_pixel(im, i, j, c , v*S);

       }
       
    }
    
}