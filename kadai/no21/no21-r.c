#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
  double near_r = 999999;
  int near_x = 0;
  int near_y = 0;
  double r;
  double f;
  double t;
  double ft;

  double lower ; //memo variable

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
    //finding pos
    for(i=idata.height-1;i>=0;i--){
      for(j=idata.width-1;j>=0;j--){
        //is in image
        if(is_in_image(idata.height,idata.width,i,j,tdata.height,tdata.width)){
          //init
          r = 0.0;
          f = 0.0;
          t = 0.0;
          ft = 0.0;
          //compare
          for(k=0;k<tdata.height;k++){
            for(l=0;l<tdata.width;l++){
                //calc
                ft += (idata.results[RED][i+k][j+l] * tdata.results[RED][k][l]);
                f += pow(idata.results[RED][i+k][j+l],2.0);
                t += pow(tdata.results[RED][k][l],2.0);
            }
          }

          lower = sqrt(f) * sqrt(t);
          // reject 0/0 = -nan
          r = ft / lower;
          if (fabs(1.0-near_r) > fabs(1.0-r)){
          //abs func is not return double type variable!!!,you should use fabs func!!!
          //it returns double type variable!!!!!!fuck!!!!
            near_r = r;
            near_y = i;
            near_x = j;
            printf("near_r = %lf,r = %lf\n",fabs(1.0-near_r),fabs(1.0-r));
            printf("r = %lf,y = %d,x = %d\n",r,i,j);
          }
        }
      }
    }
    //------------------encoding part ------------------------//
    for(i=0;i<tdata.height;i++){
      for(j=0;j<tdata.width;j++){
        tdata.results[RED][i][j] =
        tdata.results[BLUE][i][j] =
        tdata.results[GREEN][i][j] = idata.source[RED][near_y+i][near_x+j];
      }
    }
  }
  if(writeBMPfile(argv[3],&tdata)>0)printf("can not write bmp file!!\n");
}
