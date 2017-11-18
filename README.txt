Author: Tony Nguyen

How to compile:
	- Compile and link to math library and ncurses library
	- use "gcc -Wall mandelbrot.c -o mandelbrot -lm -lncurses

This program displays a mandelbrot fractal in color in which you can move and zoom in on.
Once the program is running, using "./mandelbrot", the fractal will appear.
	- W = pan image up
	- A = pan image to the left
	- S = pan image down
	- D = pan image to the right
	- Q = zoom in on the image
	- E = zoome out on the image
	
To exit, hit the space bar or use Ctrl+C.