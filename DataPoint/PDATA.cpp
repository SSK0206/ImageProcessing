/* May 6, 1999
Making Points Data 

*/

#include <stdio.h> /* printf */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <conio.h>
#include <math.h>
#include <dos.h>
#include "Random.h"

#include "gint.fx"   /* �O���t�B�b�N�X�������֐� gint,gend */
#include "gcls.fx"    /* �O���t�B�b�N�X���� */
#include "line.fx"     /* ���֐� */
#include "pset.fx"     /* �_�֐� */
#include "paint.fx"    /* �h���֐� */
#include "symbol.fx"   /* ������g��֐� */
//#include "gwait.fx"    /* �O���t�B�b�N�X��~ */

main()
{
    int nd;
    double r,dl,px,py,a,b,x,y;
	float sg;
    int i,j,k,l,pos,ef;
	int ix,iy,x1,y1,x2,y2;
	FILE *fpw1;
	char *NUMBER="%d",*POINT="%d %d",*LINE="%d %d %d %d";
	char ch[100];
    char file[50]="C:\\BC\\ENSHU\\POINT.DAT";

    printf("Input coordinates start(x1,y1)-end(x2,y2): input x1 y1 x2 y2 \n");
	scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
	printf("Sigma for scattering data? \n");
	scanf("%e",&sg);
    px=x2-x1;
	py=y2-y1;
	r=sqrt(px*px+py*py);
	nd=r/1.5;

	fpw1=fopen(file,"w");
	printf("#Line data: Number=%d sigma=%.1f \n",nd,sg);
	fprintf(fpw1,"#Line data: Number=%d sigma=%.1f \n",nd,sg);

	if(px==0){
		a=0;
		b=0;
		printf("#(%d,%d)-(%d,%d) y=%.2fx+%.2f\n",x1,y1,x2,y2,a,b);
		printf("%d\n%d %d %d %d\n",nd,x1,y1,x2,y2);
		fprintf(fpw1,"#(%d,%d)-(%d,%d) y=%.2fx+%.2f\n",x1,y1,x2,y2,a,b);
		fprintf(fpw1,"%d\n%d %d %d %d\n",nd,x1,y1,x2,y2);
		dl=py/nd;
		y=y1;
		for(i=0;i<nd;i++){
    		px=x1+gauss()*sg;
			py=y+gauss()*sg;
			ix=px+0.5;
			iy=py+0.5;
			fprintf(fpw1,"%d %d\n",ix,iy);
			y+=dl;
		}
	}
   	else
	{
		a=py/px;
		b=y1-a*x1;
		printf("#(%d,%d)-(%d,%d) y=%.2fx+%.2f\n",x1,y1,x2,y2,a,b);
		printf("%d\n%d %d %d %d\n",nd,x1,y1,x2,y2);
		fprintf(fpw1,"#(%d,%d)-(%d,%d) y=%.2fx+%.2f\n",x1,y1,x2,y2,a,b);
		fprintf(fpw1,"%d\n%d %d %d %d\n",nd,x1,y1,x2,y2);
		dl=px/nd;
		x=x1;
		for(i=0;i<nd;i++){
    		px=x+gauss()*sg;
			py=x*a+b+gauss()*sg;
			ix=px+0.5;
			iy=py+0.5;
			fprintf(fpw1,"%d %d\n",ix,iy);
			x+=dl;
		}
    }
	fprintf(fpw1,"#END\n");
	fclose(fpw1);

    gint(400,400); /* �O���t�B�b�N�X������(400x300dot) */
     line(50,50,50,360,0);
     line(40,350,350,350,0);
	fpw1=fopen(file,"r");
	fgets(ch,sizeof(ch),fpw1);
		while (ch[0] == '#'||ch[1] == '#'){
			pos=ftell(fpw1); /*���݂̃t�@�C�����R�[�h�̈ʒu���L��*/
			printf("%s",ch);
			fgets(ch,sizeof(ch),fpw1);
    	}
		fseek(fpw1,pos,SEEK_SET); /*�O�i�œǂݍ��݂������������ǂ��ăZ�b�g*/
		fscanf(fpw1,NUMBER,&nd);
		fscanf(fpw1,LINE,&x1,&y1,&x2,&y2);
		line(x1+50,350-y1,x2+50,350-y2,5);
    		for(i=0;i<nd;i++){
				fscanf(fpw1,POINT,&ix,&iy);
				pset(ix+50,350-iy,1);
			}
	fclose(fpw1);


  gend(); /* �O���t�B�b�N�X�I�� �����Ńv���O�����ێ�*/

  return EXIT_SUCCESS;
}
 /* main */


/** �I��� **/
