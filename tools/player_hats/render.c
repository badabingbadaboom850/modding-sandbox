// Native indexed-sprite accessory compiler. Keeps the original body pixels.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
static const int colors[8][3] = {{50,48,62},{121,81,61},{84,56,39},{235,95,110},{170,35,75},{255,195,90},{200,140,40},{255,255,255}};
static const int boxes[6][4] = {{150,230,375,420},{650,225,885,421},{1190,225,1390,420},{108,660,417,880},{615,660,925,880},{1120,665,1435,890}};
int main(int argc, char **argv)
{
    if (argc != 9) return 1;
    int w=atoi(argv[3]),h=atoi(argv[4]),fw=atoi(argv[5]),fh=atoi(argv[6]),kind=atoi(argv[7]),style=atoi(argv[8]);
    FILE *f=fopen(argv[1],"rb"); unsigned char *src=malloc(w*h),*out=malloc(w*h),*atlas=malloc(1536*1024*4);
    if (!f || fread(src,1,w*h,f)!=(size_t)(w*h)) return 2; fclose(f); memcpy(out,src,w*h);
    f=fopen("graphics/player_hats/accessory-reference.rgba","rb");if(!f || fread(atlas,1,1536*1024*4,f)!=1536*1024*4) return 3;fclose(f);
    const int maps[4][8]={{8,5,6,10,11,12,13,14},{9,13,8,11,5,6,1,10},{9,7,6,12,14,2,1,4},{15,7,5,9,7,9,7,14}};
    int battle=kind==1||kind==2;
    int gold1=kind==0?12:kind==1?6:kind==2?2:14,gold2=kind==0?13:kind==3?9:1;
    for(int fy=0;fy<h;fy+=fh)for(int fx=0;fx<w;fx+=fw)
    {
        int xmin=fw,ymin=fh,xmax=-1,ymax=-1;
        // The cap is the highest yellow component. Ignore yellow on bikes/rods.
        for(int y=0;y<fh;y++)for(int x=0;x<fw;x++)if(src[(fy+y)*w+fx+x]==gold1||src[(fy+y)*w+fx+x]==gold2)
        {if(ymin==fh)ymin=y;if(y>ymin+(battle?18:7))continue;if(x<xmin)xmin=x;if(x>xmax)xmax=x;if(y>ymax)ymax=y;}
        if(xmax<0)continue;
        int direction=0,skin=0,sx=0,scx=0;
        int skinindex=kind==0?2:kind==1?4:11;
        for(int y=ymax+1;y<fh&&y<ymax+6;y++)for(int x=xmin;x<=xmax;x++)if(src[(fy+y)*w+fx+x]==skinindex){skin++;sx+=x;scx++;}
        if(!skin)direction=1;else if(scx && sx/scx < (xmin+xmax)/2-1)direction=2;
        if(kind==2)direction=2;
        if(kind==3)direction=fx/fw==0?0:fx/fw==1?1:2;
        const int *box=boxes[(style-1)*3+direction];
        int tw=xmax-xmin+1+(style==2?(battle?8:4):0),th=ymax-ymin+1+(battle?3:2);
        if(tw>fw)tw=fw;
        int left=(xmin+xmax+1-tw)/2,top=ymin-1;
        if(left<0)left=0;if(left+tw>fw)left=fw-tw;if(top<0)top=0;
        // Expose brown hair underneath the bow, including the original cap band.
        if(style==1)for(int y=ymin;y<=ymax;y++)for(int x=xmin;x<=xmax;x++)
        {int p=(fy+y)*w+fx+x;if(src[p]==gold1||src[p]==gold2||src[p]==maps[kind][7])out[p]=maps[kind][1];}
        for(int y=0;y<th&&top+y<fh;y++)for(int x=0;x<tw;x++)
        {
            int ax=box[0]+(2*x+1)*(box[2]-box[0])/(2*tw),ay=box[1]+(2*y+1)*(box[3]-box[1])/(2*th);
            unsigned char *p=atlas+4*(ay*1536+ax);if(p[3]<230)continue;
            int best=0,dist=INT_MAX;for(int c=0;c<8;c++){int d=0;for(int q=0;q<3;q++){int a=p[q]-colors[c][q];d+=a*a;}if(d<dist){best=c;dist=d;}}
            out[(fy+top+y)*w+fx+left+x]=maps[kind][best];
        }
    }
    f=fopen(argv[2],"wb");if(!f)return 4;fwrite(out,1,w*h,f);fclose(f);return 0;
}
