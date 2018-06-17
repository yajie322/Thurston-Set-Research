// Requires gnuplot in order to plot graphs
// Once the plot as been created, you will need to save the graph as a separate file.
// Unfortunately, I could not make the code do this by default

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>

void plotResults(double* xData, double* yData, int dataSize);

int main() {
  int i = 0;
  int nIntervals = 100000;        //edit this to be the number of total points

  double* xData = (double*) malloc((nIntervals+1)*sizeof(double));
  double* yData = (double*) malloc((nIntervals+1)*sizeof(double));


  for (i = 0; i < nIntervals; i++) {
      xData[i] = rand() % 10000;   //edit this to be the x-coordinates of the points

  }

  for (i = 0; i <= nIntervals; i++) {
      yData[i] = rand() % 10000;   //edit this to be the y-coordinates of the points
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
      fprintf(gnuplotPipe,"plot \"%s\" \n",tempDataFileName);
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
