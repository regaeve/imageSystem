#include <stdio.h>
#include <stdlib.h>

#include "../def.h"
#include "../var.h"
#include <math.h>

int calc_vias(int num){
  if(num > 50){
    return 255;
  }else{
    return 0;
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
        idata.results[RED][y][x] = calc_vias(idata.source[RED][y][x]);
        //show_filter(filter);
        idata.results[BLUE][y][x] = calc_vias(idata.source[BLUE][y][x]);
        //show_filter(filter);
        idata.results[GREEN][y][x] = calc_vias(idata.source[GREEN][y][x]);
      }
    }
  }
}
      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
}
