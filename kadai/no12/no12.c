#include <stdio.h>
#include <stdlib.h>

#include "../def.h"
#include "../var.h"
#include <math.h>

#define FILTER_X 3
#define FILTER_Y 3

int is_in_image(int height,int width,int i,int j,int y,int x){
  return y+i >= 0 && y+i < width && x+j >= 0 && x+j < height;
}

int calc_filter(imgdata idata,int color,int y,int x,int n){
  int delta_x = 0;
  int delta_y = 0;
  int i,j;
  int result = 0;

  for(i = -1;i < FILTER_Y-1;i++){
    for(j = -1;j < FILTER_X-1;j++){
      if(is_in_image(idata.height,idata.width,i,j,y,x)){
        if(i == 0){
          delta_x += (j*2)*idata.source[color][y+i][x+j];
        }else{
          delta_x += j*idata.source[color][y+i][x+j];
        }
        if(j == 0){
          delta_y += (i*2)*idata.source[color][y+i][x+j];
        }else{
          delta_y += i*idata.source[color][y+i][x+j];
        }
      }
    }
  }
result = pow(pow((double)delta_x,2.0)+pow((double)delta_y,2.0),0.5);

if(result > 255){
    return 255;
}else{
    return result;
}
}

int main(int argc, char *argv[])
{
  imgdata idata;
  int x, y;
  int n = 5;
  // 例題プログラム
  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {

    for (y = 0; y < idata.height; y++){
      for (x = 0; x < idata.width; x++){
        //show_filter(filter);
        idata.results[RED][y][x] = calc_filter(idata,RED,y,x,n);
        //show_filter(filter);
        idata.results[BLUE][y][x] = calc_filter(idata,BLUE,y,x,n);
        //show_filter(filter);
        idata.results[GREEN][y][x] = calc_filter(idata,GREEN,y,x,n);
      }
    }
  }
}
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
}
