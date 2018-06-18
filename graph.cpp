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
  tempDataFileName = "graph.txt";     //this will store all of the point external file. Change the name if necessary
  gnuplotPipe = popen("gnuplot","w");
  if (gnuplotPipe) {
      fprintf(gnuplotPipe,"set terminal svg \n");
      fprintf(gnuplotPipe,"set output 'plot.svg' \n");
      fprintf(gnuplotPipe,"plot \"%s\" lt rgb \"blue\" \n",tempDataFileName); //change the color of the points here
      fflush(gnuplotPipe);
      tempDataFile = fopen(tempDataFileName,"w");
      for (i=0; i <= dataSize; i++) {
          x = xData[i];
          y = yData[i];
          fprintf(tempDataFile,"%lf %lf\n",x,y);
      }
      fprintf(gnuplotPipe,"set out \n");
      fclose(tempDataFile);
  } else {
      printf("gnuplot not found...");
  }
}
