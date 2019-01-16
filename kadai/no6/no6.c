#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "var.h"
#include <math.h>

int main(int argc, char *argv[])
{
  imgdata idata;
  double c;
  int x, y;

  // 例題プログラム
  // 　BMPファイルをコピーするプログラム
  int lut[256] = {0};
  int i;
  for (i=0;i<=256;i++){
    lut[i]=255 * sqrt((double)i/255);
  }

  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {
    /* 例題：コピーするプログラム */
      for (y = 0; y < idata.height; y++){
	for (x = 0; x < idata.width; x++){
	  idata.results[RED][y][x]
	    = lut[idata.source[RED][y][x]];
    idata.results[BLUE][y][x]
	    = lut[idata.source[BLUE][y][x]];
    idata.results[GREEN][y][x]
	    = lut[idata.source[GREEN][y][x]];
	}
      }
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
    }
  }
}
