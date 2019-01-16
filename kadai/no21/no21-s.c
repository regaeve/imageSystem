#include <stdio.h>
#include <stdlib.h>

#include "def550.h"
#include "var.h"

int is_in_image(int height,int width,int i,int j,int y,int x){
  return y+i >= 0 && y+i < width && x+j >= 0 && x+j < height;
}

int main(int argc, char *argv[])
{
  imgdata idata,tdata;
  int i,j;
  int k,l;
  int max_s = 0;
  int max_x = 0;
  int max_y = 0;
  int s;

  if (readBMPfile(argv[1], &idata) > 0)printf("file not found name:%s\n",argv[1]);
  else if (readBMPfile(argv[2], &tdata) > 0)printf("file not found name:%s\n",argv[2]);
  //---------------prev work------------------
  else {
    for(i=0;i<idata.height;i++){
      for(j=0;j<idata.width;j++){
        if(idata.source[RED][i][j] == 255 &&
           idata.source[BLUE][i][j] == 255 &&
           idata.source[GREEN][i][j] == 255){
          idata.results[RED][i][j] =
          idata.results[BLUE][i][j] =
          idata.results[GREEN][i][j] = 0;
        }else{
          idata.results[RED][i][j] =
          idata.results[BLUE][i][j] =
          idata.results[GREEN][i][j] = 1;
        }
        //
        //printf("%d,%d\n",i,j);
      }
    }

    for(i=0;i<tdata.height;i++){
      for(j=0;j<tdata.width;j++){
        if(tdata.source[RED][i][j] == 255 &&
          tdata.source[BLUE][i][j] == 255 &&
          tdata.source[GREEN][i][j] == 255){
          tdata.results[RED][i][j] =
          tdata.results[BLUE][i][j] =
          tdata.results[GREEN][i][j] = 0;
        }else{
          tdata.results[RED][i][j] =
          tdata.results[BLUE][i][j] =
          tdata.results[GREEN][i][j] = 1;
        }
        //printf("%d,%d\n",i,j);
      }
    }

//-------------------main part ---------------------------//
    printf("h = %d,W = %d\n",tdata.height,tdata.width);
    for(i=idata.height-1;i>=0;i--){
      for(j=idata.width-1;j>=0;j--){
        s = 0;
        if(is_in_image(idata.height,idata.width,i,j,tdata.height,tdata.width)){
          for(k=0;k<tdata.height;k++){
            for(l=0;l<tdata.width;l++){
                s += idata.results[RED][i+k][j+l] * tdata.results[RED][k][l];
            }
          }
        }else{
          s = 0;
        }
        if (max_s < s){
          max_s = s;
          max_y = i;
          max_x = j;
          printf("s = %d,y = %d,x = %d\n",s,i,j);
        }
      }
    }
    for(i=0;i<tdata.height;i++){
      for(j=0;j<tdata.width;j++){
        tdata.results[RED][i][j] =
        tdata.results[BLUE][i][j] =
        tdata.results[GREEN][i][j] = idata.source[RED][max_y+i][max_x+j];
      }
    }
  }
  if(writeBMPfile(argv[3],&tdata)>0)printf("can not write bmp file!!\n");
}
