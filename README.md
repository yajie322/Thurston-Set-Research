# Thurston-Set-Research

## Dependencies
GNU Library can be found here. 

http://mirrors.peers.community/mirrors/gnu/gsl/gsl-2.5.tar.gz

After the file is unzipped, open your terminal and change the directory to the unzipped folder, and run command "./configure && make && make install"

Gnuplot library can be installed through Homebrew. Homebrew can be installed by typing the follwing command in your terminal

> /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" 

After installing Homebrew, run the following command to install gnuplot.

> brew install gnuplot

## Compile & Run
To generate graph, adjust sign and parameters at the beginning of the main function.

Then run the following commands (order matters!!)

> g++ -Wall -I/usr/local/include -c KLplots.cpp
 
> g++ -L/usr/local/lib KLplots.o -lgsl -lgslcblas -lm

> ./a.out > FILENAME.png

FILENAME can be anything you wish to call the output graph. Finally you will find a png graph file in your working folder.
