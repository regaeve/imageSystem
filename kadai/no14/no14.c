#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "var.h"
#include <math.h>

#define FILTER_X 3
#define FILTER_Y 3

int is_in_image(int height,int width,int i,int j,int y,int x){
  return y+i >= 0 && y+i < width && x+j >= 0 && x+j < height;
}

int is_cross(int i,int j){
  if(i == 0 && j == -1)return 1;
  if(i == 0 && j == 1) return 1;
  if(i == -1 && j == 0)return 1;
  if(i == 1 && j == 0)return 1;
  return 0;
}

int calc_filter(imgdata idata,int color,int y,int x){
  int num = 0;
  int i,j;

  for(i = -1;i < FILTER_Y-1;i++){
    for(j = -1;j < FILTER_X-1;j++){
      if(is_in_image(idata.height,idata.width,i,j,y,x)){
        if(is_cross(i,j)){
          num -= idata.source[color][y+i][x+j];
        }
        if(i == 0 && j == 0){
          num += 5*idata.source[color][y][x];
        }
      }
    }
  }

  if(num > 255){
    return 255;
  }
  if(num < 0){
    return 0;
  }else{
    return num;
  }

}

int main(int argc, char *argv[])
{
  imgdata idata;
  int x, y;
  // 例題プログラム
  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {

    for (y = 0; y < idata.height; y++){
      for (x = 0; x < idata.width; x++){
        //show_filter(filter);
        idata.results[RED][y][x] = calc_filter(idata,RED,y,x);
        //show_filter(filter);
        idata.results[BLUE][y][x] = calc_filter(idata,BLUE,y,x);
        //show_filter(filter);
        idata.results[GREEN][y][x] = calc_filter(idata,GREEN,y,x);
      }
    }
  }
}
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
}
