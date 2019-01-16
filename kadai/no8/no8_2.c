#include <stdio.h>
#include <stdio.h>
#include <math.h>

#include "def.h"
#include "var.h"

#define GMAX 256

void histFlat(imgdata idata, int color);

int main(int argc, char *argv[]){
  imgdata idata;
  int x,y;
  Uchar isum[3];

  if (argc < 3){
    printf("使用法：command in.bmp out.bmp\n");
  }else if(readBMPfile(argv[1], &idata) > 0){
    printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
  }else{
    /* Convert */
    histFlat(idata, RED);
    histFlat(idata, GREEN);
    histFlat(idata, BLUE);
  }

  /* Export */
  if (writeBMPfile(argv[2], &idata) > 0){
    printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
  }
}


void histFlat(imgdata idata,int color)
{
  int hist[256];
  int nmove[256][256];
  int cnt[256][256];
  int i, j;
  int k, k1, k2;
  int ss;
  Uchar gray;
  int mean;
  int x,y;

  mean = 256 * 256 / 256; // 平均画素数

  //　ヒストグラムの計算
  for(i = 0;i < 256;i++){
    for(j = 0;j < 256;j++){
      gray = idata.source[color][i][j];
      //printf("gray[%d][%d] = %d\n",i,j,gray);
      hist[gray]++;
    }
  }

  // 移動ピクセル数nmove(k1, k2)の計算
  for(k = 0;k < GMAX;k++){
    for(k1 = 0;k1 < GMAX;k1++){
      nmove[k][k1] = 0;
    }
    nmove[k][k] = hist[k];
  }
  for(k = 0;k < GMAX;k++){
    if(hist[k] > mean){
      ss = nmove[0][k];
      for(k1 = 0;k1 < k;k1++){
        if(ss > mean){
          nmove[k1][k+1] = ss - mean;
          nmove[k1][k] -= nmove[k1][k+1]; 
          hist[k] -= nmove[k1][k+1];
          hist[k+1] += nmove[k1][k+1];
          if(k != k1){
            for(k2 = k1+1;k2 < k;k2++){
              nmove[k2][k+1] = nmove[k2][k];
              hist[k+1] += nmove[k2][k+1];
              hist[k] -= nmove[k2][k+1];
              nmove[k2][k] = 0;
            }
            break;
          }
        }else{
          ss += nmove[k1+1][k];
        }
      }
    }else{
      ss = hist[k];
      for(k1 = k+1;k1 < GMAX;k1++){
        ss += hist[k1];
        if(ss > mean){
          nmove[k1][k] = mean - hist[k];
          hist[k] += nmove[k1][k];
          nmove[k1][k1] -= nmove[k1][k];
          hist[k1] -= nmove[k1][k];
          break;
        }else{
          nmove[k1][k] = hist[k1];
          hist[k] += nmove[k1][k];
          nmove[k1][k1] = 0;
          hist[k1] = 0;
        }
      }
    }
  }

  for (y = idata.height;y >= 0; y--){
    for (x = 0; x < idata.width; x++){
      gray = idata.source[color][y][x];
      for(k = 0;k < GMAX;k++){
        if(cnt[gray][k] < nmove[gray][k]) break;
      }
      idata.results[color][y][x] = k;
      cnt[gray][k] ++;
    }
  }
}
