/*C++�Ő��������A�O���t�B�b�N�\���Ȃǂ��s�����߂̃w�b�_���̒�`*/
#include <stdio.h> /* printf */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <conio.h>
#include <math.h>
#include <dos.h>
#include "Graphset.h" /*�O���t�B�N�X�̂��߂̃t�@�C������*/
main(){
  int nd;
  double x[1000],y[1000];
  int i,j,l,pos,ef,xs=50,ys=350;
  int ix,iy,x1,y1,x2,y2;
  FILE *fpw1;
  char *NUMBER="%d",*POINT="%d %d",*LINE="%d %d %d %d";
  char ch[100];
  char file[50];
  /*�_���W�f�[�^�������Ă���t�@�C�����̓���*/
  printf("Input filename ?\n");
  scanf("%s",file); //�t�@�C���������

  gint(400,400); /*�O���t�B�b�N�X��������*/
  line(50,50,50,360,0);//��
  line(40,350,350,350,0);

  symbol(330,350,"x",0,1,1);
  symbol(40,60,"y",0,1,1);

  /*�_���W�f�[�^�̓ǂݍ���*/
  fpw1=fopen(file,"r");//�t�@�C�����J��

  ef=0;
  fgets(ch,sizeof(ch),fpw1);
  while(ef==0){
    while (ch[0] == '#'){
      pos=ftell(fpw1); /*���݂̃t�@�C�����R�[�h�̈ʒu���L�^*/
      printf("%s",ch);
      fgets(ch,sizeof(ch),fpw1);
    }
    fseek(fpw1,pos,SEEK_SET);/*�O�i�œǂ݂������������ǂ��ăZ�b�g*/
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
      fgets(ch,sizeof(ch),fpw1);/*�f�[�^�^�̕ύX�̂��߂̃_�~�[*/
      fgets(ch,sizeof(ch),fpw1);/*�f�[�^�I���̔���*/
      if(ch[0]=='#' & ch[1]=='E' & ch[2]=='N' & ch[3]=='D'){ef=1;}
  }
  printf("%s",ch);
  fclose(fpw1);
  /*�_���W�̃f�[�^�ǂݍ���*/

  ////////////////���M/////////////////////
  double X;
  double Y;

  //x,y����
  for(int i=0; i<nd; i++){
    X += x[i];
    Y += y[i];
  }
  X/=nd;
  Y/=nd;
  
  //�����U�A���U
  double Sxy, Sxx, Syy;
  for(int i=0; i<nd; i++){
    Sxy += (x[i]-X)*(y[i]-Y);
    Sxx += pow((x[i]-X),2);
    Syy += pow((y[i]-Y),2);
  }

  //�ƕϐ�
  double theta = atan(2*Sxy/(Sxx-Syy))/2;


  if(theta*Sxy>0){
    theta = theta + M_PI/2;
  }

  double p = X*cos(theta) + Y*sin(theta);
  
  double Y0=p/sin(theta);						//X=0
  double Y300=(p-300*cos(theta))/sin(theta);  //X=300
  //line(xs+0,ys-Y2,xs+300,ys-Y3,2);
  line(xs+0,ys-Y0,xs+300,ys-Y300,2);

  /*�ۑ�*/
  save_bmpj("Graph.bmp"); //
  gend(); /* �O���t�B�b�N�X�I��*/
  return EXIT_SUCCESS;
}
/* main */
/**�I���**/
