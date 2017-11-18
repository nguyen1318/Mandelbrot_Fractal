#include <stdio.h>
#include <math.h>
#include <ncurses.h>

//Structures

//Struct representing complex numbers. a (real number), b (imaginary number).
typedef struct {
	long double a;
	long double b;
} complex_t;

//Struct representing the cartesian coordinate plane and the max width/height of
//the image.
typedef struct {
	float x_min, x_max;
	float y_min, y_max;
	int width, height;
} window_t;

//Struct representing the current point on the screen.
typedef struct {
	int x, y;
} screen_point;

//Prototypes
int is_in_set(complex_t z);
complex_t complex_multiply(complex_t a, complex_t b);
complex_t complex_add(complex_t a, complex_t b);
complex_t complex_sub(complex_t a, complex_t b);
float complex_magnitude(complex_t z);
complex_t scale(window_t s, screen_point p);

/*
 *Program prints fractals using Mandelbrot Sets.
 *
**/
int main(void){

	int i, j, k;
	int max_row, max_col;
	int close = 1;

	
	initscr();

	getmaxyx(stdscr, max_row, max_col);

	complex_t value;
	window_t s;
	screen_point p;
	s.x_min = -2;
	s.x_max = 1;
	s.y_min = -1;
	s.y_max = 1;
	s.width = max_col;
	s.height = max_row;

	start_color();
	init_pair(1, COLOR_RED, COLOR_RED);

	while(close){

		//Fractal is drawn here
		for(i = 0; i < max_row; i++){
			for(j = 0; j < max_col; j++){

				p.x = j;
				p.y = i;

				move(i, j);

				complex_t new_value = {0, 0};

				value = scale(s, p);

				for(k = 0; k < 200; k++){
					new_value = complex_add(complex_multiply(new_value, new_value), value);
				}

				if(!is_in_set(new_value)){
					wattron(stdscr, COLOR_PAIR(1));
					addch('X');
					wattroff(stdscr, COLOR_PAIR(1));
				} else {
					addch(' ');
				}
			}
		}

		//Switch statement used to pan and zoom.
		char c = getch();
		noecho();
		switch(c){
			case 'w':
				s.y_min = s.y_min + .5;
				s.y_max = s.y_max + .5;
				break;
			case 'a':
				s.x_min = s.x_min + .5;
				s.x_max = s.x_max + .5;
				break;
			case 's':
				s.y_min = s.y_min - .5;
				s.y_max = s.y_max - .5;
				break;
			case 'd':
				s.x_min = s.x_min - .5;
				s.x_max = s.x_max - .5;
				break;
			case 'q':
				s.x_min = s.x_min + .2;
				s.x_max = s.x_max - .2;
				s.y_min = s.y_min + .2;
				s.y_max = s.y_max - .2;
				break;
			case 'e':
				s.x_min = s.x_min - .2;
				s.x_max = s.x_max + .2;
				s.y_min = s.y_min - .2;
				s.y_max = s.y_max + .2;
				break;
			case ' ':
				close = 0;
				break;
			default:
				break;
		}

	}
	endwin();
	return 0;
}

/*
 *Function determines if the complex number is within the Mandelbrot set.
 *
 *complex_t z: Complex number that is to be determined
 *returns 1 if in set, 0 if not.
**/
int is_in_set(complex_t z){

	if(complex_magnitude(z) <= 2){
		return 1;
	} else {
		return 0;
	}
}

/*
 *Function that multiplies 2 complex numbers
 *
 *complex_t x: number to be multiplied.
 *complex_t y: number to be multiplied.
 *returns the product of x and y.
**/
complex_t complex_multiply(complex_t x, complex_t y){

	complex_t z;
	z.a = (x.a*y.a) - (x.b*y.b);
	z.b = (x.a*y.b) + (y.a*x.b);
	return z;
}

/*
 *Function that adds 2 complex numbers
 *
 *complex_t x: number to be added.
 *complex_t y: number to be added.
 *returns the sum of x and y.
**/
complex_t complex_add(complex_t x, complex_t y){

	complex_t z;
	z.a = x.a + y.a;
	z.b = x.b + y.b;
	return z;
}

/*
 *Function that subtracts 2 complex numbers
 *
 *complex_t x: number to be subtracted from.
 *complex_t y: number to be subtracted by.
 *returns the difference of x and y.
**/
complex_t complex_sub(complex_t x, complex_t y){

	complex_t z;
	z.a = x.a - y.a;
	z.a = x.b - y.b;
	return z;
}

/*
 *Function that finds the magnitude of a complex number.
 *
 *complex_t z: the complex number to find the magnitude of.
 *returns the magnitude of z.
 **/
float complex_magnitude(complex_t z){

	return sqrt((z.a * z.a) + (z.b * z.b));
}

/*
 *Function that scales the screen point into a cartesian coordinate point.
 *
 *window_t s: the cartesian coordinate plane.
 *screen_point p: the position of the current point on the screen.
 *returns the point converted into a cartesian coordinate point.
 **/
complex_t scale(window_t s, screen_point p){

	complex_t z;
	z.a = s.x_min + (s.x_max - s.x_min)*(p.x - 0)/(s.width - 0);
	z.b = s.y_min + (s.y_max - s.y_min)*(p.y - 0)/(s.height - 0);
	return z;
}
