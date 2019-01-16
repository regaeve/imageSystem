#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../def.h"
#include "../var.h"

#define SOURCE 0
#define RESULTS 1


int is_in_image(int height,int width,int i,int j,int y,int x){
  return y+i >= 0 && y+i < width && x+j >= 0 && x+j < height;
}
void eight_expansion(unsigned char data[2][256][256]){
  int i,j;
  int x,y;

  for(y = 0; y < 256; y++){
    for(x = 0; x < 256; x++){
      if(data[SOURCE][y][x] == BLACKVALUE){
  for(i = -1; i <= 1; i++){
    for(j = -1; j <= 1; j++){
      if(!(i==0 && j==0)){
        if(is_in_image(256,256,i,j,y,x)){
          data[RESULTS][y+i][x+j] = BLACKVALUE;
        }
      }
    }
  }
      }
    }
  }
  for(y = 0; y < 256; y++){
    for(x = 0; x < 256; x++){
      data[SOURCE][y][x] = data[RESULTS][y][x];

    }
  }
}

void four_expansion(unsigned char data[2][256][256]){
  int i,j;
  int x,y;

  for(y = 0; y < 256; y++){
    for(x = 0; x < 256; x++){
      if(data[SOURCE][y][x] == BLACKVALUE){
  for(i = -1; i <= 1; i++){
    for(j = -1; j <= 1; j++){
      if(i == 0 || j == 0){
        if(is_in_image(256,256,i,j,y,x)){
          data[RESULTS][y+i][x+j] = BLACKVALUE;
        }
      }
    }
  }
      }
    }
  }
  for(y = 0; y < 256; y++){
    for(x = 0; x < 256; x++){
      data[SOURCE][y][x] = data[RESULTS][y][x];

    }
  }
}

void four_comtraction(unsigned char data[2][256][256]){
  int i,j;
  int x,y;

  for(y = 0; y < 256; y++){
    for(x = 0; x < 256; x++){
      if(data[SOURCE][y][x] == WHITEVALUE){
  for(i = -1; i <= 1; i++){
    for(j = -1; j <= 1; j++){
      if(i == 0 || j == 0){
        if(is_in_image(256,256,i,j,y,x)){
          data[RESULTS][y+i][x+j] = WHITEVALUE;
        }
      }
    }
  }
      }
    }
  }
  for(y = 0; y < 256; y++){
    for(x = 0; x < 256; x++){
      data[SOURCE][y][x] = data[RESULTS][y][x];
    }
  }
}

void eight_comtraction(unsigned char data[2][256][256]){
  int i,j;
  int x,y;

  for(y = 0; y < 256; y++){
    for(x = 0; x < 256; x++){
      if(data[SOURCE][y][x] == WHITEVALUE){
  for(i = -1; i <= 1; i++){
    for(j = -1; j <= 1; j++){
      if(!(i==0 && j==0)){
        if(is_in_image(256,256,i,j,y,x)){
          data[RESULTS][y+i][x+j] = WHITEVALUE;
        }
      }
    }
  }
      }
    }
  }
  for(y = 0; y < 256; y++){
    for(x = 0; x < 256; x++){
      data[SOURCE][y][x] = data[RESULTS][y][x];
    }
  }
}

int main(int argc, char *argv[]){
  imgdata idata;
  unsigned char data[2][256][256] = {0};
  int x, y;

  // 例題プログラム
  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {}

    for (y = 0; y < idata.height; y++){
      for (x = 0; x < idata.width; x++){
        data[SOURCE][y][x] = idata.source[RED][y][x];
        data[RESULTS][y][x] = idata.source[RED][y][x];
      }
    }

    eight_expansion(data);
    eight_comtraction(data);
    eight_comtraction(data);
    eight_expansion(data);

    for (y = 0; y < idata.height; y++){
      for (x = 0; x < idata.width; x++){
        idata.results[RED][y][x] =
        idata.results[BLUE][y][x] =
        idata.results[GREEN][y][x] = data[RESULTS][y][x];
      }
    }
  }
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
}
