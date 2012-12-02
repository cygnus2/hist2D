#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
  extern double **allocatedouble2d(int,int);
  extern void deallocatedouble2d(double **,int,int);

  FILE *inpfile;
  int i,j;
  double dummy1,dummy2;
  int d1,d2,d3;

  int ITER=200000;
  int MAX,MIN,NL;
  double **pA,**pB;
  int MA,MB;
  double sumA,sumB;

  MAX = (4*4*800)/2;
  MIN = -MAX;
  NL  = 2*MAX + 1;

  pA=allocatedouble2d(NL,NL);
  pB=allocatedouble2d(NL,NL);

  inpfile = fopen("multi.dat","r");
  for(i=0;i<ITER;i++){
   fscanf(inpfile,"%d %d %d %lf %lf %d %d",&d1,&d2,&d3,&dummy1,&dummy2,&MA,&MB);
   pA[MA-MIN][MB-MIN]++;
   pB[MA-MIN][MB-MIN]++;
  }
  fclose(inpfile); 

  sumA=sumB=0.0;
  for(i=0;i<NL;i++){
  for(j=0;j<NL;j++){
   sumA += pA[i][j];
   sumB += pB[i][j];
  } }
 

  for(i=0;i<NL;i++){
  for(j=0;j<NL;j++){
   pA[i][j] /= ((double)sumA); 
   pB[i][j] /= ((double)sumB);
   printf("%d %d %2.4le %2.4le\n",i,j,pA[i][j],pB[i][j]);
  }
  printf("\n");
  }
  
  deallocatedouble2d(pA,NL,NL);
  deallocatedouble2d(pB,NL,NL);

  return 0;
  }

double **allocatedouble2d(int row, int col)
{
  int i,j;
  double **mat;
  mat = (double **)malloc(row*sizeof(double*));
  if(mat==NULL) {printf("Out of memory\n"); exit(0);}

  for(i=0;i<row;i++){
   mat[i]=(double *)malloc(col*sizeof(double));
   if(mat[i]==NULL)  {printf("Out of memory\n"); exit(0);}
  }

 for(i=0;i<row;i++)
 for(j=0;j<col;j++)
  mat[i][j]=0.0;

 return mat;

}

void deallocatedouble2d(double **mat, int row, int col)
{
  int i;
  for(i=0;i<row;i++)
   free(mat[i]);

 free(mat);
}
