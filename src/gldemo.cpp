//
// Array Visualisation for CIS6007 WRIT1
//

#include <iostream>
#include <string>
#include <random>
#include "gl_stuff.h"
#include "Array2D.h"
#include <tbb/tbb.h>
#include <chrono>


using namespace std;
using namespace tbb;


#pragma region Function Prototypes

void initPattern(Array2D<int>& array); // Initialise grid with "alive" and "dead" cell patterns
void update(void); // Main update function - apply Game of Life rules here

#pragma endregion



//
// Example array
//

// This is the empty base array which will be replaced with the first generation through the cycle.
Array2D<int>						myArray = Array2D<int>(512, 512);


// Starting point for our program...
int main(int argc, char* argv[])
{
	// Initialise OpenGL window...
	gl_init(argc, argv, update, "CIS6007 WRIT1 - Game of Life Demo", true);

	// Initialise our Game of Life starting pattern...
	initPattern(myArray);

	// Start the main loop - this calls our update function (below) to update our game of life generations.
	// Note: We never return from glutMainLoop until we quit the application
	glutMainLoop();

	return 0;
}


// Initialise grid with "alive" and "dead" cell patterns
void initPattern(Array2D<int>& array) {

	// 1. First clear the array (set all cells to "dead" ie. 0)
	parallel_for(
		0,
		array.w * array.h,
		[&](int i) {

			int x = i % array.w;
			int y = i / array.h;
			array(x, y) = 0;
		}
	);

	// 2. Setup random number generator
	random_device						rd;
	mt19937								mt(rd());
	uniform_int_distribution<int>		iDist(0, 1);

#if 1

// Approach 1 - explicitly set each cell you want to be alive

	//glider gun
	array(2, 6) = 1;
	array(2, 7) = 1;
	array(3, 6) = 1;
	array(3, 7) = 1;
	array(12, 6) = 1;
	array(12, 7) = 1;
	array(12, 8) = 1;
	array(13, 5) = 1;
	array(13, 9) = 1;
	array(14, 4) = 1;
	array(14, 10) = 1;
	array(15, 4) = 1;
	array(15, 10) = 1;
	array(16, 7) = 1;
	array(17, 5) = 1;
	array(17, 9) = 1;
	array(18, 6) = 1;
	array(18, 7) = 1;
	array(18, 8) = 1;
	array(19, 7) = 1;
	array(22, 4) = 1;
	array(22, 5) = 1;
	array(22, 6) = 1;
	array(23, 4) = 1;
	array(23, 5) = 1;
	array(23, 6) = 1;
	array(24, 3) = 1;
	array(24, 7) = 1;
	array(26, 2) = 1;
	array(26, 3) = 1;
	array(26, 7) = 1;
	array(26, 8) = 1;
	array(36, 4) = 1;
	array(36, 5) = 1;
	array(37, 4) = 1;
	array(37, 5) = 1;

	//// single glider
	//array(2, 0) = 1;
	//array(2, 1) = 1;
	//array(2, 2) = 1;
	//array(1, 2) = 1;
	//array(0, 1) = 1; 

	//// lightweight spaceship
	//array(2, 3) = 1;
	//array(2, 4) = 1;
	//array(3, 3) = 1;
	//array(3, 4) = 1;
	//array(3, 5) = 1;
	//array(4, 2) = 1;
	//array(4, 4) = 1;
	//array(4, 5) = 1;
	//array(5, 2) = 1;
	//array(5, 3) = 1;
	//array(5, 4) = 1;
	//array(6, 3) = 1;

	//// beacon
	//array(1, 1) = 1;
	//array(2, 1) = 1;
	//array(1, 2) = 1;
	//array(2, 2) = 1;
	//array(3, 3) = 1;
	//array(4, 3) = 1;
	//array(3, 4) = 1;
	//array(4, 4) = 1;

	//// Pulsar
	//array(3, 5) = 1;
	//array(3, 6) = 1;
	//array(3, 7) = 1;
	//array(3, 11) = 1;
	//array(3, 12) = 1;
	//array(3, 13) = 1;
	//array(5, 3) = 1;
	//array(5, 8) = 1;
	//array(5, 10) = 1;
	//array(5, 15) = 1;
	//array(6, 3) = 1;
	//array(6, 8) = 1;
	//array(6, 10) = 1;
	//array(6, 15) = 1;
	//array(7, 3) = 1;
	//array(7, 8) = 1;
	//array(7, 10) = 1;
	//array(7, 15) = 1;
	//array(8, 5) = 1;
	//array(8, 6) = 1;
	//array(8, 7) = 1;
	//array(8, 11) = 1;
	//array(8, 12) = 1;
	//array(8, 13) = 1;
	//array(10, 5) = 1;
	//array(10, 6) = 1;
	//array(10, 7) = 1;
	//array(10, 11) = 1;
	//array(10, 12) = 1;
	//array(10, 13) = 1;
	//array(11, 3) = 1;
	//array(11, 8) = 1;
	//array(11, 10) = 1;
	//array(11, 15) = 1;
	//array(12, 3) = 1;
	//array(12, 8) = 1;
	//array(12, 10) = 1;
	//array(12, 15) = 1;
	//array(13, 3) = 1;
	//array(13, 8) = 1;
	//array(13, 10) = 1;
	//array(13, 15) = 1;
	//array(15, 5) = 1;
	//array(15, 6) = 1;
	//array(15, 7) = 1;
	//array(15, 11) = 1;
	//array(15, 12) = 1;
	//array(15, 13) = 1;


#else

	// Parallel for initialisation of cells...
	// NOTE: Uses 1D array approach, but can map single index to 2D coord if we know the width and height of the 2D array
	parallel_for(
		0,
		array.w * array.h,
		[&](int i) {

			int x = i % array.w;
			int y = i / array.h;

			// Example - checkerboard pattern
			if ((x & 0x01) == (y & 0x01))
				array(x, y) = 1;
		}
	);

#endif

}

int cellValue(int x, int y, int width, int height) {

	if (x >= 0 && y >= 0 && x < width && y < height) {

		return myArray(x, y);
	}

	else {
		return 0;
	}

}

int CountLiveCell (int x, int y) {
	int a = cellValue(x - 1, y - 1, myArray.w, myArray.h);
	int b = cellValue(x, y - 1, myArray.w, myArray.h);
	int c = cellValue(x + 1, y - 1, myArray.w, myArray.h);
	int d = cellValue(x - 1, y, myArray.w, myArray.h);
	int e = cellValue(x + 1, y, myArray.w, myArray.h);
	int f = cellValue(x - 1, y + 1, myArray.w, myArray.h);
	int g = cellValue(x, y + 1, myArray.w, myArray.h);
	int h = cellValue(x + 1, y + 1, myArray.w, myArray.h);

	return a + b + c + d + e + f + g + h;
}


// Main update function - apply Game of Life rules here
// Note: This is called by FreeGLUT's main event loop - YOU DON'T NEED TO CALL THIS - IT'S CALLED FOR YOU!!!
void update(void) {

	//This is the scond array. it will go through the conditions to then create the new array, then it will replace the first array for the next cycle
	Array2D<int>						myArrayB = Array2D<int>(512, 512);

	//first clearing the array (set all cells to "dead" ie. 0)
	parallel_for(
		0,
		myArrayB.w * myArrayB.h,
		[&](int i) {

			int x = i % myArrayB.w;
			int y = i / myArrayB.h;
			myArrayB(x, y) = 0;
		}
	);

	

	// This is the speed counter. it sets the speed of the movement or iterations between the generations. 
	/*static int count = 50;

	count--;

	if (count == 0) {*/

	tick_count t0 = tick_count::now();

		// Sequential Version
		/*for (int y = 0; y < myArray.h; y++) {
			for (int x = 0; x < myArray.w; x++) {

				int LiveCells = CountLiveCell(x, y);
				if (myArray(x, y) == 1) {
					if (LiveCells < 2) {
						myArrayB(x, y) = 0;
					}
					if (LiveCells == 2 || LiveCells == 3) {
						myArrayB(x, y) = 1;
					}
					if (LiveCells > 3) {
						myArrayB(x, y) = 0;
					}
				}
				else {
					if (LiveCells == 3) {
						myArrayB(x, y) = 1;
					}
				}
			}
		}*/

		parallel_for(
			blocked_range2d<int, int>(0,myArray.h,0,myArray.w),
			[&](const blocked_range2d<int>& r) {
				for (int y = r.rows().begin(); y!=r.rows().end(); y++) {
					for (int x = r.cols().begin(); x!=r.cols().end(); x++) {
						int LiveCells = CountLiveCell(x, y);
						if (myArray(x, y) == 1) {
							if (LiveCells < 2) {
								myArrayB(x, y) = 0;
							}
							if (LiveCells == 2 || LiveCells == 3) {
								myArrayB(x, y) = 1;
							}
							if (LiveCells > 3) {
								myArrayB(x, y) = 0;
							}
						}
						else {
							if (LiveCells == 3) {
								myArrayB(x, y) = 1;
							}
						}
					}
				}
			}
		);

		tick_count t1 = tick_count::now();
		// end of the timer then requests the system to print to the terminal 
		printf("time taken: %g seconds\n", (t1 - t0).seconds());


		myArray = myArrayB;

		/*count = 50;
	}*/


	// Redraw the screen to show latest generation
	renderLatestGeneration(myArray);
}
