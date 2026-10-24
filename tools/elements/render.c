// Palette-safe conversion of six imagegen elemental atlases.
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
int main(int argc,char **argv) {
    if(argc!=8)return 1;
    int colors[16][3];
    FILE *pf=fopen(argv[7],"r");if(!pf)return 7;for(int i=0;i<16;i++)for(int j=0;j<3;j++)if(fscanf(pf,"%d",&colors[i][j])!=1)return 8;fclose(pf);
    int aw=atoi(argv[2]),ah=atoi(argv[3]),cell=atoi(argv[4]),size=atoi(argv[5]);
    unsigned char *atlas=malloc(aw*ah*4), *out=calloc(size*size,1);
    FILE *f=fopen(argv[1],"rb");if(!f||fread(atlas,1,aw*ah*4,f)!=(size_t)(aw*ah*4))return 2;fclose(f);
    int col=cell%3,row=cell/3,xmin=aw,ymin=ah,xmax=-1,ymax=-1;
    const int xs[4]={0,455,875,1280};
    // Detect transparent row gaps so generated silhouettes never lose their tops.
    int rows[4][2],nrows=0,last=-100;
    for(int y=0;y<ah;y++) {
        int occupied=0;for(int x=0;x<aw;x++)if(atlas[4*(y*aw+x)+3]>=230){occupied=1;break;}
        if(!occupied)continue;
        if(y-last>8){if(nrows==4)return 9;rows[nrows][0]=y;rows[nrows][1]=y;nrows++;}
        rows[nrows-1][1]=y;last=y;
    }
    if(nrows!=4)return 10;
    for(int y=rows[row][0];y<=rows[row][1];y++)for(int x=xs[col]*aw/1280;x<xs[col+1]*aw/1280;x++)if(atlas[4*(y*aw+x)+3]>=230) {
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
