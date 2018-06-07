/*C++*/
#include <stdio.h> /* printf */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <vector>
#include <iostream>
#include "Graphset.h" 
main(){
  int nd;
  double x[1000],y[1000];
  int i,j,l,pos,ef,xs=50,ys=350;
  int ix,iy,x1,y1,x2,y2;
  FILE *fpw1;
  char *NUMBER="%d",*POINT="%d %d",*LINE="%d %d %d %d";
  char ch[100];
  char file[50];
  
  printf("Input filename ?\n");
  scanf("%s",file); //ÉtÉ@ÉCÉãñºì¸óÕ

  gint(400,400); /*èâä˙âª*/
  line(50,50,50,360,0);//
  line(40,350,350,350,0);

  symbol(330,350,"x",0,1,1);
  symbol(40,60,"y",0,1,1);

  
  fpw1=fopen(file,"r");

  ef=0;
  fgets(ch,sizeof(ch),fpw1);
  while(ef==0){
    while (ch[0] == '#'){
      pos=ftell(fpw1); 
      printf("%s",ch);
      fgets(ch,sizeof(ch),fpw1);
    }
    fseek(fpw1,pos,SEEK_SET);
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
      fgets(ch,sizeof(ch),fpw1);
      fgets(ch,sizeof(ch),fpw1);
      if(ch[0]=='#' & ch[1]=='E' & ch[2]=='N' & ch[3]=='D'){ef=1;}
  }
  printf("%s",ch);
  fclose(fpw1);
  

  //---------------â¡ïM-------------------------
  /*
  double X;
  double Y;

  //x,y
  for(int i=0; i<nd; i++){
    X += x[i];
    Y += y[i];
  }
  X/=nd;
  Y/=nd;

  //
  double Sxy, Sxx, Syy;
  for(int i=0; i<nd; i++){
    Sxy += (x[i]-X)*(y[i]-Y);
    Sxx += pow((x[i]-X),2);
    Syy += pow((y[i]-Y),2);
  }

  //
  double theta = atan(2*Sxy/(Sxx-Syy))/2;


  if(theta*Sxy>0){
    theta = theta + M_PI/2;
  }

  double p = X*cos(theta) + Y*sin(theta);

  double Y0=p/sin(theta);						//X=0
  double Y300=(p-300*cos(theta))/sin(theta);  //X=300
  //line(xs+0,ys-Y2,xs+300,ys-Y3,2);
  line(xs+0,ys-Y0,xs+300,ys-Y300,2);
  */


  const int theta_max = 180;//360->180
  const int rho_max = 300;
  long count[rho_max*2][theta_max];



  for(int rho=0; rho<rho_max*2; rho++){
  	for(int theta=0; theta<theta_max; theta++){//count
  		count[rho][theta]=0;
    }
  }

  for(int i=0; i<nd; i++){
  	for(int theta=0; theta<theta_max; theta++){
      double theta_rad = (double)theta * M_PI/180.0;
	  //printf("%f ", theta_rad);
		
	    int rho = (int)(x[i]*cos(theta_rad)+y[i]*sin(theta_rad) + rho_max);
		  if(rho>=rho_max*2-1)continue;
		//printf("%d  ", rho)
	    count[rho][theta]++;
		
  	}
  }
  

  int count_max =0;
  
  
  int rho_ans = 0 - rho_max;
  int theta_ans = 0;

  int count_max2 = -1;
  int rho_ans2 = -1;
  int theta_ans2 = -1;
  
  
  for(int rho=0; rho<rho_max*2; rho++){
    for(int theta=0; theta<theta_max; theta++){
      if (count_max < count[rho][theta]){
	  	  if(abs(rho-rho_ans) > 25 && abs(theta-theta_ans) > 25){
	  		 count_max2=count_max;
	  		 rho_ans2 = rho_ans;
         theta_ans2 = theta_ans;
			  }
	      count_max = count[rho][theta];
	      rho_ans = rho - rho_max; // rho_max
	      theta_ans = theta;
	    }
  	  else if(count_max2 < count[rho][theta]){
  	  	if(abs(rho-rho_ans) > 25 && abs(theta-theta_ans) > 25){
  	  	count_max2=count[rho][theta];
  	  	rho_ans2 = rho-rho_max;
          theta_ans2 = theta;
  	    }
	    }
    }
  }

	
  double Y0=rho_ans/sin(theta_ans*M_PI/180);						//X=0
  double Y300=(rho_ans-300*cos(theta_ans*M_PI/180.0))/sin(theta_ans*M_PI/180.0);  //X=300
  line(xs+0,ys-Y0,xs+300,ys-Y300,2);

  if(rho_ans2 != -1 && theta_ans2 != -1 && count_max2 > 18){
    double Y0_2=rho_ans2/sin(theta_ans2 * M_PI / 180);						//X=0
    double Y300_2=(rho_ans2-300*cos(theta_ans2 * M_PI / 180.0))/sin(theta_ans2 * M_PI / 180.0);
    //line(xs+0,ys-Y2,xs+300,ys-Y3,2);
  
    line(xs+0,ys-Y0_2,xs+300,ys-Y300_2,4);
  }
  //printf("%d %d ", theta_ans, rho_ans);
  //printf("%d %d ", theta_ans2, rho_ans2);
  //printf("%d %d ", Y0_2, ys-Y300_2);
	
 
  
  save_bmpj("Graph.bmp"); 
  gend(); 
  return EXIT_SUCCESS;
}
/*
DataPoint/Point10.dat
DataPoint/Point11.dat
DataPoint/Point12.dat
DataPoint/Point13.dat
DataPoint/Point20.dat
DataPoint/Point21.dat
DataPoint/Point22.dat

DataPoint/Pointm0.dat
DataPoint/Pointm1.dat
DataPoint/Pointm2.dat

DataPoint/Point10n.dat
DataPoint/Point11n.dat
DataPoint/Point12n.dat
DataPoint/Pointm0n.dat
DataPoint/Pointm1n.dat
maxa = max(i, maxa);
*/

/* main */

