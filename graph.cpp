// Requires gnuplot in order to plot graphs
// Currently only able to plot functions, working on a way to graph a set of tuples

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

void plotResults(double* xData, double* yData, int dataSize);

int main() {
  int i = 0;
  int nIntervals = 100;
  double intervalSize = 1.0;
  double stepSize = intervalSize/nIntervals;

  double* xData = (double*) malloc((nIntervals+1)*sizeof(double));
  double* yData = (double*) malloc((nIntervals+1)*sizeof(double));

  xData[0] = 0.0;
  double x0 = 0.0;
  for (i = 0; i < nIntervals; i++) {
      x0 = xData[i];
      xData[i+1] = x0 + stepSize;
  }

  for (i = 0; i <= nIntervals; i++) {
      x0 = xData[i];
      yData[i] = pow(x0,2.0);
  }

  plotResults(xData,yData,nIntervals);
  return 0;

}

void plotResults(double* xData, double* yData, int dataSize) {
  FILE *gnuplotPipe,*tempDataFile;
  char *tempDataFileName;
  double x,y;
  int i;
  tempDataFileName = "graph";
  gnuplotPipe = popen("gnuplot","w");
  if (gnuplotPipe) {
      fprintf(gnuplotPipe,"plot \"%s\" with lines\n",tempDataFileName);
      fflush(gnuplotPipe);
      tempDataFile = fopen(tempDataFileName,"w");
      for (i=0; i <= dataSize; i++) {
          x = xData[i];
          y = yData[i];
          fprintf(tempDataFile,"%lf %lf\n",x,y);
      }
      fclose(tempDataFile);
      printf("press enter to continue...");
      getchar();
      remove(tempDataFileName);
      fprintf(gnuplotPipe,"exit \n");
  } else {
      printf("gnuplot not found...");
  }
}
