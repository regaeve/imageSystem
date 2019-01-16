#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../def.h"
#include "../var.h"

void make_histgram(imgdata idata,int histgram[3][255],int color){
  int x,y;

  for (y = 0; y < idata.height; y++){
    for (x = 0; x < idata.width; x++){
      histgram[color][idata.source[color][y][x]]++;
    }
  }
}

int find_peak(int histgram[3][255],int color){
  int peak_index = 0;
  int i;

  for(i = 0;i <= 255;i++){
    if(histgram[color][peak_index] < histgram[color][i])
    peak_index = i;
  }
  return peak_index;
}

int find_second_peak(int peak_index,int histgram[3][255],int color){
  int second_peak_index = 0;
  int i;

  for(i = 0;i < 255;i++){
    if(abs(i - peak_index) >= 50){
      if(histgram[color][second_peak_index] < histgram[color][i])
      second_peak_index = i;
    }
  }
  return second_peak_index;
}

int find_vias(int peak_index,int second_peak_index,int histgram[3][255],int color){
  int vias_index;
  int i;
  int low_index;
  int high_index;

  /*a ho ku sa*/
  if(peak_index > second_peak_index){
    high_index = peak_index;
    low_index = second_peak_index;
  }else{
    high_index = second_peak_index;
    low_index = peak_index;
  }
  vias_index = low_index;

  for(i = low_index;i < high_index;i++){
    if(histgram[color][vias_index] > histgram[color][i])
      vias_index = i;
    }
  return vias_index;
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
  int histgram[3][255] ={0};
  int x, y;
  int i;
  int first_peak[3] = {0};
  int second_peak[3] = {0};
  int vias[3] = {0};

  // 例題プログラム
  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {
    for(i=0;i<3;i++){
      make_histgram(idata,histgram,i);
      first_peak[i] = find_peak(histgram,i);
      second_peak[i] = find_second_peak(first_peak[i],histgram,i);
      vias[i] = find_vias(first_peak[i],second_peak[i],histgram,i);
    }

    for (y = 0; y < idata.height; y++){
      for (x = 0; x < idata.width; x++){
        idata.results[RED][y][x] = calc_vias(idata.source[RED][y][x],vias[RED]);
        idata.results[BLUE][y][x] = calc_vias(idata.source[BLUE][y][x],vias[BLUE]);
        idata.results[GREEN][y][x] = calc_vias(idata.source[GREEN][y][x],vias[GREEN]);
      }
    }
  }
}
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
}
