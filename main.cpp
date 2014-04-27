#include <stdio.h>
#include <unistd.h>

#include "grabber.h"

int main(int argc, char **argv) {
	CGrabber g;
	while (true) {
		int x, y;
		g.getMousePos(x, y);
		unsigned int px = g.sample(x, y);
		printf("\r%4d,%4d: %02x%02x%02x    ", x, y, (px>>16)&0xff, (px>>8)&0xff, (px>>0)&0xff);
		usleep(1000); // 10000 = 1sec
	}

	printf("Done.\n");
	return 0;
}
