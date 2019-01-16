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

int main(int argc, char *argv[]){
  imgdata idata;

  int x, y;
  int count = 0;
  int prev_state = 0;

  FILE *fp;	/* (1)ファイルポインタの宣言 */

  if (argc < 3) printf("使用法：cpbmp コピー元.bmp コピー先.bmp\n");
  else {
    if (readBMPfile(argv[1], &idata) > 0)
      printf("指定コピー元ファイル%sが見つかりません\n",argv[1]);
    else {}

  if ((fp = fopen("ans20-2.txt", "w")) == NULL) {
  	printf("file open error!!\n");
  	exit(EXIT_FAILURE);
  }
  fprintf(fp,"j14403\n");

  prev_state = (idata.source[RED][0][0] < WHITEVALUE);
  printf("prev_state = %d",prev_state);

  for (y = idata.height-1; y >= 0; y--){
    for (x = 0; x < idata.width; x++){
      if(prev_state != (idata.source[RED][y][x] < WHITEVALUE)){
        fprintf(fp,"(%d,%d)",prev_state,count);
        prev_state = (idata.source[RED][y][x] < WHITEVALUE);
        count = 0;
      }
      count++;
    }
  }
  fprintf(fp,"(%d,%d)",prev_state,count);
  fclose(fp);	/* (5)ファイルのクローズ */
  }

      if (writeBMPfile(argv[2], &idata) > 0)
	printf("コピー先ファイル%sに保存できませんでした\n",argv[2]);
}
