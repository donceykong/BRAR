// Created by Doncey Albin

#include <stdio.h>

const int points = 100000;
float x[points];
float z[points];

int i = 0;
void plotData(float xpos, float zpos) {
    // Example data, you can replace this with your data
    x[i] = xpos;
    z[i] = zpos;

    // Create a pipe to run a process
    FILE *pipe = popen("gnuplot -persistent", "w");

    if (pipe == NULL) {
        printf("Error opening pipe.\n");
        return;
    }

    fprintf(pipe, "set terminal png\n");     // Set your desired terminal type here.
    fprintf(pipe, "set output 'plot.png'\n"); // Set your output file name here.
    fprintf(pipe, "plot '-' using 1:2 with linespoints\n");
    for (int j = 0; j < i; j++) {
        fprintf(pipe, "%lf %lf\n", x[j], z[j]);
    }

    fprintf(pipe, "e\n"); // End of data

    // Close the pipe
    pclose(pipe);

    i++;
}