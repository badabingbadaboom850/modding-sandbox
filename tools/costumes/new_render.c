// Palette-safe conversion of six imagegen elemental atlases.
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
int main(int argc,char **argv) {
    if(argc!=8 && argc!=9)return 1;
    int isolate=argc==9 && atoi(argv[8])==1;
    int colors[16][3];
    FILE *pf=fopen(argv[7],"r");if(!pf)return 7;for(int i=0;i<16;i++)for(int j=0;j<3;j++)if(fscanf(pf,"%d",&colors[i][j])!=1)return 8;fclose(pf);
    int aw=atoi(argv[2]),ah=atoi(argv[3]),cell=atoi(argv[4]),size=atoi(argv[5]);
    unsigned char *atlas=malloc(aw*ah*4), *out=calloc(size*size,1);
    FILE *f=fopen(argv[1],"rb");if(!f||fread(atlas,1,aw*ah*4,f)!=(size_t)(aw*ah*4))return 2;fclose(f);
    int col=cell%3,row=cell/3,xmin=aw,ymin=ah,xmax=-1,ymax=-1;
    const int xs[4]={0,427,853,1280};
    // Detect transparent row gaps so generated silhouettes never lose their tops.
    int rows[4][2],nrows=0,last=-100;
    for(int y=0;y<ah;y++) {
        int occupied=0;for(int x=0;x<aw;x++)if(atlas[4*(y*aw+x)+3]>=230){occupied=1;break;}
        if(!occupied)continue;
        if(y-last>8){if(nrows==4)return 9;rows[nrows][0]=y;rows[nrows][1]=y;nrows++;}
        rows[nrows-1][1]=y;last=y;
    }
    if(nrows!=4)return 10;
    // Optional pose isolation: a neighboring pose can cross a column boundary.
    // Preserve default conversion; only explicitly selected cells use the largest
    // connected silhouette before determining bounds and scaling.
    int *labels=NULL, *queue=NULL, largest=0;
    if(isolate) {
        labels=calloc((size_t)aw*ah,sizeof(*labels));
        queue=malloc((size_t)aw*ah*sizeof(*queue));
        if(!labels || !queue)return 11;
        int next=0,best=0;
        int x0=xs[col]*aw/1280,x1=xs[col+1]*aw/1280;
        int y0=rows[row][0],y1=rows[row][1];
        for(int y=y0;y<=y1;y++)for(int x=x0;x<x1;x++) {
            int start=y*aw+x;
            if(labels[start] || atlas[4*start+3]<230)continue;
            int head=0,tail=1,id=++next;
            labels[start]=id;queue[0]=start;
            while(head<tail) {
                int pos=queue[head++],px=pos%aw,py=pos/aw;
                for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++) {
                    int nx=px+dx,ny=py+dy;
                    if(nx<x0 || nx>=x1 || ny<y0 || ny>y1)continue;
                    int np=ny*aw+nx;
                    if(!labels[np] && atlas[4*np+3]>=230) {
                        labels[np]=id;queue[tail++]=np;
                    }
                }
            }
            if(tail>best){best=tail;largest=id;}
        }
        if(!largest)return 12;
    }
    for(int y=rows[row][0];y<=rows[row][1];y++)for(int x=xs[col]*aw/1280;x<xs[col+1]*aw/1280;x++)if(atlas[4*(y*aw+x)+3]>=230) {
        if(isolate && labels[y*aw+x]!=largest)continue;
        if(x<xmin)xmin=x;if(y<ymin)ymin=y;if(x>xmax)xmax=x;if(y>ymax)ymax=y;
    }
    if(xmax<0)return 3;
    int sw=xmax-xmin+1,sh=ymax-ymin+1,limit=size==64?60:size-3;
    double scale=(double)limit/sw;if((double)limit/sh<scale)scale=(double)limit/sh;
    int tw=sw*scale+0.5,th=sh*scale+0.5,left=(size-tw)/2,top=size-th-1;
    for(int y=0;y<th;y++)for(int x=0;x<tw;x++) {
        int ax=xmin+(2*x+1)*sw/(2*tw),ay=ymin+(2*y+1)*sh/(2*th);unsigned char *p=atlas+4*(ay*aw+ax);
        if(p[3]<230 || (isolate && labels[ay*aw+ax]!=largest))continue;
        int best=1,dist=INT_MAX;
        for(int c=1;c<16;c++){int d=0;for(int q=0;q<3;q++){int v=p[q]-colors[c][q];d+=v*v;}if(d<dist){best=c;dist=d;}}
        out[(top+y)*size+left+x]=best;
    }
    f=fopen(argv[6],"wb");if(!f)return 4;fwrite(out,1,size*size,f);fclose(f);
    free(labels);free(queue);free(atlas);free(out);return 0;
}
