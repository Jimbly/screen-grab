#include <stdio.h>

#include "grabber-base.h"
#include "grabber-xgetimage.h"

int main(int argc, char **argv) {
	volatile bool stop;
	CGrabberXGetImage g(NULL, stop, false);
	g.Setup();
	g.Run();

	printf("Done.\n");
	return 0;
}
