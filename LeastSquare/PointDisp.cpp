/*C++で数式処理、グラフィック表示などを行うためのヘッダ等の定義*/
#include <stdio.h> /* printf */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <conio.h>
#include <math.h>
#include <dos.h>
#include "Graphset.h" /*グラフィクスのためのファイル準備*/
main(){
  int nd;
  double x[1000],y[1000];
  int i,j,l,pos,ef,xs=50,ys=350;
  int ix,iy,x1,y1,x2,y2;
  FILE *fpw1;
  char *NUMBER="%d",*POINT="%d %d",*LINE="%d %d %d %d";
  char ch[100];
  char file[50];
  /*点座標データが入っているファイル名の入力*/
  printf("Input filename ?\n");
  scanf("%s",file); //ファイル名を入力

  gint(400,400); /*グラフィックスを初期化*/
  line(50,50,50,360,0);//軸
  line(40,350,350,350,0);

  symbol(330,350,"x",0,1,1);
  symbol(40,60,"y",0,1,1);

  /*点座標データの読み込み*/
  fpw1=fopen(file,"r");//ファイルを開く

  ef=0;
  fgets(ch,sizeof(ch),fpw1);
  while(ef==0){
    while (ch[0] == '#'){
      pos=ftell(fpw1); /*現在のファイルレコードの位置を記録*/
      printf("%s",ch);
      fgets(ch,sizeof(ch),fpw1);
    }
    fseek(fpw1,pos,SEEK_SET);/*前段で読みすぎた分をもどしてセット*/
    fscanf(fpw1,NUMBER,&nd);
    fscanf(fpw1,LINE,&x1,&y1,&x2,&y2);
    line(x1+xs,ys-y1,x2+xs,ys-y2,5);
    for(i=0;i<nd;i++){
      fscanf(fpw1,POINT,&ix,&iy);
      printf("%d:%d %d\n",i,ix,iy);
      pset(ix+xs,ys-iy,1);
      x[i]=ix;
      y[i]=iy;
    }
      fgets(ch,sizeof(ch),fpw1);/*データ型の変更のためのダミー*/
      fgets(ch,sizeof(ch),fpw1);/*データ終了の判定*/
      if(ch[0]=='#' & ch[1]=='E' & ch[2]=='N' & ch[3]=='D'){ef=1;}
  }
  printf("%s",ch);
  fclose(fpw1);
  /*点座標のデータ読み込み*/

  ////////////////加筆/////////////////////
  double X;
  double Y;

  //x,y平均
  for(int i=0; i<nd; i++){
    X += x[i];
    Y += y[i];
  }
  X/=nd;
  Y/=nd;
  
  //共分散、分散
  double Sxy, Sxx, Syy;
  for(int i=0; i<nd; i++){
    Sxy += (x[i]-X)*(y[i]-Y);
    Sxx += pow((x[i]-X),2);
    Syy += pow((y[i]-Y),2);
  }

  //θ変数
  double theta = atan(2*Sxy/(Sxx-Syy))/2;


  if(theta*Sxy>0){
    theta = theta + M_PI/2;
  }

  double p = X*cos(theta) + Y*sin(theta);
  
  double Y0=p/sin(theta);						//X=0
  double Y300=(p-300*cos(theta))/sin(theta);  //X=300
  //line(xs+0,ys-Y2,xs+300,ys-Y3,2);
  line(xs+0,ys-Y0,xs+300,ys-Y300,2);

  /*保存*/
  save_bmpj("Graph.bmp"); //
  gend(); /* グラフィックス終了*/
  return EXIT_SUCCESS;
}
/* main */
/**終わり**/
