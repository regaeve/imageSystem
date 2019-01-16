#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../def.h"
#include "../var.h"

#define FILTER_X 3
#define FILTER_Y 3

int is_in_image(int height,int width,int i,int j,int y,int x){
  return y+i >= 0 && y+i < width && x+j >= 0 && x+j < height;
}

void make_histgram(imgdata idata,int histgram[255],int color){
  int x,y;
  int delta;

  delta = 0;
  for (y = 1; y < idata.height-1; y++){
    for (x = 1; x < idata.width-1; x++){
      int delta_x = 0;
      int delta_y = 0;
      int i,j;

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

      delta = pow(pow((double)delta_x,2.0)+pow((double)delta_y,2.0),0.5);
      delta = abs(delta);

      if(delta > 30){
        histgram[idata.source[RED][y][x]] += delta;
      }
    }
  }
}

int find_peak(int histgram[255],int color){
  int peak_index = 0;
  int i;

  for(i = 0;i < 255;i++){
    if(histgram[peak_index] < histgram[i])
    peak_index = i;
  }
  return peak_index;
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
  int histgram[255] ={0};
  int x, y;
  int vias = 0;

  // 例題プログラム
  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {}

    make_histgram(idata,histgram,RED);
    vias = find_peak(histgram,RED);


    for (y = 0; y < idata.height; y++){
      for (x = 0; x < idata.width; x++){
        idata.results[RED][y][x] =
        idata.results[BLUE][y][x] =
        idata.results[GREEN][y][x] = calc_vias(idata.source[RED][y][x],vias);
      }
    }
  }
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
}
