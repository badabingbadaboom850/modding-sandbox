// Palette-safe native conversion of the imagegen Pom Fu atlas.
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
static const int colors[16][3]={{0,0,0},{25,22,30},{50,46,55},{83,77,89},{68,40,28},{112,69,40},{170,114,67},{223,173,113},{248,248,248},{198,199,208},{138,141,154},{239,139,161},{167,75,106},{255,216,176},{222,225,235},{108,98,100}};
int main(int argc,char **argv) {
    if(argc!=7)return 1;
    int aw=atoi(argv[2]),ah=atoi(argv[3]),cell=atoi(argv[4]),size=atoi(argv[5]);
    unsigned char *atlas=malloc(aw*ah*4), *out=calloc(size*size,1);
    FILE *f=fopen(argv[1],"rb");if(!f||fread(atlas,1,aw*ah*4,f)!=(size_t)(aw*ah*4))return 2;fclose(f);
    int col=cell%3,row=cell/3,xmin=aw,ymin=ah,xmax=-1,ymax=-1;
    const int xs[4]={0,455,875,1280}, ys[5]={0,430,735,1040,1280};
    for(int y=ys[row]*ah/1280;y<ys[row+1]*ah/1280;y++)for(int x=xs[col]*aw/1280;x<xs[col+1]*aw/1280;x++)if(atlas[4*(y*aw+x)+3]>=230) {
        if(x<xmin)xmin=x;if(y<ymin)ymin=y;if(x>xmax)xmax=x;if(y>ymax)ymax=y;
    }
    if(xmax<0)return 3;
    int sw=xmax-xmin+1,sh=ymax-ymin+1,limit=size==64?60:size-3;
    double scale=(double)limit/sw;if((double)limit/sh<scale)scale=(double)limit/sh;
    int tw=sw*scale+0.5,th=sh*scale+0.5,left=(size-tw)/2,top=size-th-1;
    for(int y=0;y<th;y++)for(int x=0;x<tw;x++) {
        int ax=xmin+(2*x+1)*sw/(2*tw),ay=ymin+(2*y+1)*sh/(2*th);unsigned char *p=atlas+4*(ay*aw+ax);
        if(p[3]<230)continue;
        int best=1,dist=INT_MAX;
        for(int c=1;c<16;c++){int d=0;for(int q=0;q<3;q++){int v=p[q]-colors[c][q];d+=v*v;}if(d<dist){best=c;dist=d;}}
        out[(top+y)*size+left+x]=best;
    }
    f=fopen(argv[6],"wb");if(!f)return 4;fwrite(out,1,size*size,f);fclose(f);
    free(atlas);free(out);return 0;
}
