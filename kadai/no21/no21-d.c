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
  int min_d = 99999999;
  int min_x = 0;
  int min_y = 0;
  int d;

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
    //printf("h = %d,W = %d\n",idata.height,idata.width);
    for(i=0;i<idata.height;i++){
      for(j=0;j<idata.width;j++){
        d = 0;
        if(is_in_image(idata.height,idata.width,i,j,tdata.height,tdata.width)){
          for(k=0;k<tdata.height;k++){
            for(l=0;l<tdata.width;l++){
                d += abs(idata.results[RED][i+k][j+l] - tdata.results[RED][k][l]);
                //XOR nazeka umakuiku
            }
          }
        }else{
          d = tdata.height * tdata.width;
        }
        if (min_d > d){
          min_d = d;
          min_y = i;
          min_x = j;
          //printf("d = %d,y = %d,x = %d\n",d,i,j);
        }
      }
    }
    for(i=0;i<tdata.height;i++){
      for(j=0;j<tdata.width;j++){
        tdata.results[RED][i][j] =
        tdata.results[BLUE][i][j] =
        tdata.results[GREEN][i][j] = idata.source[RED][min_y+i][min_x+j];
      }
    }
  }
  if(writeBMPfile(argv[3],&tdata)>0)printf("can not write bmp file!!\n");
}
