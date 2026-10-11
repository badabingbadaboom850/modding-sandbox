// Compile imagegen three-cell accessory sheets to the existing native palette.
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main(int argc, char **argv)
{
    if(argc!=6)return 1;
    int w=atoi(argv[3]),h=atoi(argv[4]),pal[16][3];
    unsigned char *rgba=malloc(w*h*4),out[16*48]={0};
    FILE *f=fopen(argv[1],"rb");if(!f||fread(rgba,1,w*h*4,f)!=(size_t)(w*h*4))return 2;fclose(f);
    f=fopen(argv[5],"r");if(!f)return 3;for(int c=0;c<16;c++)for(int q=0;q<3;q++)if(fscanf(f,"%d",&pal[c][q])!=1)return 4;fclose(f);
    for(int frame=0;frame<3;frame++)
    {
        int start=frame*h/3,end=(frame+1)*h/3,xmin=w,ymin=h,xmax=-1,ymax=-1;
        for(int y=start;y<end;y++)for(int x=0;x<w;x++)if(rgba[4*(y*w+x)+3]>=220)
        {if(x<xmin)xmin=x;if(x>xmax)xmax=x;if(y<ymin)ymin=y;if(y>ymax)ymax=y;}
        if(xmax<0)return 5;
        int tw=frame==0?12:14,th=frame==0?12:15,left=(16-tw)/2,top=frame*16+(16-th)/2;
        for(int y=0;y<th;y++)for(int x=0;x<tw;x++)
        {
            int ax=xmin+(2*x+1)*(xmax-xmin+1)/(2*tw),ay=ymin+(2*y+1)*(ymax-ymin+1)/(2*th);
            unsigned char *p=rgba+4*(ay*w+ax);if(p[3]<220)continue;
            int best=1,distance=INT_MAX;
            for(int c=1;c<16;c++){int d=0;for(int q=0;q<3;q++){int delta=p[q]-pal[c][q];d+=delta*delta;}if(d<distance){distance=d;best=c;}}
            out[(top+y)*16+left+x]=best;
        }
    }
    f=fopen(argv[2],"wb");if(!f)return 6;fwrite(out,1,sizeof out,f);fclose(f);free(rgba);return 0;
}
