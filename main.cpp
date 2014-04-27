#include <stdio.h>
#include <unistd.h>

#include "grabber.h"

int main(int argc, char **argv) {
	CGrabber g;
	while (true) {
		unsigned int px = g.sample(100, 100);
		printf("%02x%02x%02x\n", (px>>16)&0xff, (px>>8)&0xff, (px>>0)&0xff);
		sleep(1);
	}

	printf("Done.\n");
	return 0;
}
