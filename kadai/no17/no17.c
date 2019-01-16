#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../def.h"
#include "../var.h"

#define FILTER_X 7
#define FILTER_Y 7

int is_in_image(int height,int width,int i,int j,int y,int x){
  return y+i >= 0 && y+i < width && x+j >= 0 && x+j < height;
}

int calc_filter_ave(imgdata idata,int color,int y,int x){
  int sum = 0;
  int div_count = 0;
  int i,j;

  for(i = -3;i <= 3;i++){
    for(j = -3;j <= 3;j++){
      if(is_in_image(idata.height,idata.width,i,j,y,x)){
        sum += idata.source[color][y+i][x+j];
        div_count++;
      }
    }
  }
  return sum / div_count;
}

double calc_filter_sigma(imgdata idata,int color,int y,int x,int ave){
    double num = 0.0;
    int i,j;
    int div_count = 0;

    for(i = -3;i <= 3;i++){
      for(j = -3;j <= 3;j++){
        if(is_in_image(idata.height,idata.width,i,j,y,x)){
          num += pow(idata.source[color][y+i][x+j] - ave,2.0);
          div_count++;
        }
      }
    }
  return num / div_count;
}

int calc_vias(int num,int vias){
  if(num >= vias){
    return 255;
  }else{
    return 0;
  }
}

int main(int argc, char *argv[]){
  imgdata idata;
  int x, y;
  int color=0;
  double sigma = 0.0;
  int vias = 0;
  int ave = 0;
  
  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {
      for (y = 0; y < idata.height; y++){
        vias = 0;
        for (x = 0; x < idata.width; x++){
          ave = calc_filter_ave(idata,color,y,x);
          sigma = calc_filter_sigma(idata,color,y,x,ave);
          if(sigma >= 1000){
            vias = calc_filter_ave(idata,color,y,x);
          }

          idata.results[color][y][x]
          =idata.results[color+1][y][x]
          =idata.results[color+2][y][x]
          = calc_vias(idata.source[color][y][x],vias);
        }
      }
    }
  }

      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);

}
