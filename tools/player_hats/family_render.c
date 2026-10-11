// Native assembly of imagegen family accessories into existing indexed frames.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static const int colors[][3] = {
    {50,48,62}, {82,49,33}, {148,98,57}, {123,65,66},
    {255,199,148}, {255,139,198}, {200,65,139}, {255,255,255},
};
static const unsigned char indices[] = {8,6,5,4,2,10,11,14};
static const int directions[] = {0,1,2,0,0,1,1,2,2};

int main(int argc, char **argv)
{
    if (argc != 7) return 1;
    int w=atoi(argv[3]), h=32, aw=atoi(argv[5]), ah=atoi(argv[6]);
    unsigned char *src=malloc(w*h), *out=malloc(w*h), *atlas=malloc(aw*ah*4);
    FILE *f=fopen(argv[1], "rb");
    if (!f || fread(src,1,w*h,f)!=(size_t)(w*h)) return 2;
    fclose(f); memcpy(out,src,w*h);
    f=fopen(argv[4], "rb");
    if (!f || fread(atlas,1,aw*ah*4,f)!=(size_t)(aw*ah*4)) return 3;
    fclose(f);
    // Find the three isolated silhouettes rather than assuming equal columns.
    int boxes[3][4], count=0, active=0;
    for(int x=0;x<aw;x++) {
        int ymin=ah,ymax=-1;
        for(int y=0;y<ah;y++)if(atlas[4*(y*aw+x)+3]>=230) {
            if(y<ymin)ymin=y;if(y>ymax)ymax=y;
        }
        if(ymax<0){active=0;continue;}
        if(!active) {
            if(count==3)return 4;
            int *b=boxes[count++];b[0]=x;b[1]=ah;b[2]=x;b[3]=-1;active=1;
        }
        int *b=boxes[count-1];b[2]=x;
        if(ymin<b[1])b[1]=ymin;if(ymax>b[3])b[3]=ymax;
    }
    if(count!=3)return 4;
    for(int frame=0;frame<w/16;frame++) {
        int fx=frame*16,xmin=16,xmax=-1,ymin=32,ymax=-1;
        for(int y=0;y<32;y++)for(int x=0;x<16;x++) {
            int v=src[y*w+fx+x];
            if(v!=12&&v!=13)continue;
            if(ymin==32)ymin=y;
            if(y>ymin+7)continue;
            if(x<xmin)xmin=x;if(x>xmax)xmax=x;if(y>ymax)ymax=y;
        }
        if(xmax<0)return 5;
        // Remove only the native cap/band; keep the face and all body pixels.
        for(int y=ymin;y<=ymax;y++)for(int x=xmin;x<=xmax;x++) {
            int p=y*w+fx+x;
            if(src[p]==12||src[p]==13||src[p]==14)out[p]=5;
        }
        const int *b=boxes[directions[frame%9]];
        int tw=14,th=ymax-ymin+4,left=(xmin+xmax+1-tw)/2,top=ymin-3;
        if(left<0)left=0;if(left+tw>16)left=16-tw;
        for(int y=0;y<th;y++)for(int x=0;x<tw;x++) {
            int ax=b[0]+(2*x+1)*(b[2]-b[0]+1)/(2*tw);
            int ay=b[1]+(2*y+1)*(b[3]-b[1]+1)/(2*th);
            unsigned char *p=atlas+4*(ay*aw+ax);
            if(p[3]<230)continue;
            int best=0,dist=INT_MAX;
            for(int c=0;c<8;c++) {
                int n=0;for(int q=0;q<3;q++){int diff=p[q]-colors[c][q];n+=diff*diff;}
                if(n<dist){best=c;dist=n;}
            }
            out[(top+y)*w+fx+left+x]=indices[best];
        }
    }
    f=fopen(argv[2],"wb");if(!f)return 6;
    fwrite(out,1,w*h,f);fclose(f);free(src);free(out);free(atlas);return 0;
}
