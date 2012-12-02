#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<gsl/gsl_histogram2d.h>

int main(){
  FILE *inpfile,*outfile;
  int i,j;
  double dummy1,dummy2;
  int d1,d2,d3;

  int ITER=200000;
  int MAX,MIN,NL;
  double bsize;
  int MA,MB;
  double sum;
  char bin_format[5]="%f";
  char range_format[5]="%f";

  MAX = (4*4*800)/4;
  MIN = -MAX;
//  NL  = 2*MAX + 1;
  NL  = 400;
  bsize = ((double)(MAX-MIN))/((double)NL);

  gsl_histogram2d *h = gsl_histogram2d_alloc(NL,NL);
  gsl_histogram2d_set_ranges_uniform (h,MIN,MAX,MIN,MAX);

  inpfile = fopen("multi.dat","r");
  for(i=0;i<ITER;i++){
   fscanf(inpfile,"%d %d %d %lf %lf %d %d",&d1,&d2,&d3,&dummy1,&dummy2,&MA,&MB);
   gsl_histogram2d_accumulate(h,MA,MB,1);
  }
  fclose(inpfile);
  sum=gsl_histogram2d_sum(h);
  gsl_histogram2d_scale(h,1.0/sum);

  outfile=fopen("histMAB.dat","w");
  gsl_histogram2d_fprintf(outfile,h,range_format,bin_format);
  fclose(outfile);

  gsl_histogram2d_free(h);
  return 0;

}
