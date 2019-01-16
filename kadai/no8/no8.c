#include <stdio.h>
#include <stdio.h>
#include <math.h>

#include "def.h"
#include "var.h"

#define GMAX 256 // GMAX+1

int main(int argc, char *argv[]){
  imgdata idata;
  int x,y;
  Uchar isum[3];

  int hist[256] = {0};
  int nmove[256][256] = {0};
  int cnt[256][256] = {0};
  int mean;
  int k, k1, k2;
  int ss;
  int i,j;
  Uchar gray;

  if (argc < 3){
    printf("使用法：command in.bmp out.bmp\n");
  }else if(readBMPfile(argv[1], &idata) > 0){
    printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
  }else{
    /* Convert */
    mean = 256; // 平均画素数

    // 0 set
    for(i = 0;i < 256;i++){
      for(j = 0;j < 256;j++){
        nmove[i][j] = 0;
        cnt[i][j] = 0;
      }
      hist[i] = 0;
    }

    //　ヒストグラムの計算
    for(i = 0;i < 256;i++){
      for(j = 0;j < 256;j++){
        gray = idata.source[RED][i][j];
        hist[gray]++;
      }
    }

    for(k = 0;k < GMAX;k++){
      for(k1 = 0;k1 < GMAX;k1++){
        nmove[k][k1] = 0;
      }
      nmove[k][k] = hist[k];
    }

    for(k = 0;k < GMAX;k++){
      if(hist[k] > mean){
        ss = nmove[0][k];
        for(k1 = 0;k1 <= k;k1++){
          if(ss > mean){
            nmove[k1][k+1] = ss - mean;
            nmove[k1][k] = nmove[k1][k] - nmove[k1][k+1];
            hist[k] = hist[k] - nmove[k1][k+1];
            hist[k+1] = hist[k+1] + nmove[k1][k+1];
            if(k != k1){
              for(k2 = k1+1;k2 <= k;k2++){
                nmove[k2][k+1] = nmove[k2][k];
                hist[k+1] = hist[k+1] + nmove[k2][k+1];
                hist[k] = hist[k] - nmove[k2][k+1];
                nmove[k2][k] = 0;
              }
            }
            break;
          }else{
            ss = ss + nmove[k1+1][k];
          }
        }
      }else{
        ss = hist[k];
        for(k1 = k+1;k1 < GMAX;k1++){
          ss = ss + hist[k1];
          if(ss > mean){
            nmove[k1][k] = mean - hist[k];
            hist[k] = hist[k] + nmove[k1][k];
            nmove[k1][k1] = nmove[k1][k1] - nmove[k1][k];
            hist[k1] = hist[k1] - nmove[k1][k];
            break;
          }else{
            nmove[k1][k] = hist[k1];
            hist[k] = hist[k] + nmove[k1][k];
            nmove[k1][k1] = 0;
            hist[k1] = 0;
          }
        }
      }
    }

    for (y = idata.height-1;y >= 0; y--){
      for (x = 0; x < idata.width; x++){
        gray = idata.source[RED][y][x];
        for(k = 0;k < GMAX;k++){
          if(cnt[gray][k] < nmove[gray][k]) break;
        }
        idata.results[RED][y][x] = k;
        idata.results[GREEN][y][x] = k;
        idata.results[BLUE][y][x]  = k;
        cnt[gray][k] = cnt[gray][k] + 1;
      }
    }
  }

  /* Export */
  if (writeBMPfile(argv[2], &idata) > 0){
    printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
  }
}
