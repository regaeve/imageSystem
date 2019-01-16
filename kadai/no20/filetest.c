#include<stdlib.h>
#include<stdio.h>

int main(void){
FILE *fp;	/* (1)ファイルポインタの宣言 */

if ((fp = fopen("ans20-1.txt", "w")) == NULL) {
  printf("file open error!!\n");
  exit(EXIT_FAILURE);
}
fprintf(fp,"test");
fclose(fp);
return 0;
}
