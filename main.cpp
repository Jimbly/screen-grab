#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <time.h>

#include "grabber.h"

long long now() {
	long long ms; // Milliseconds
	struct timespec spec;
	clock_gettime(CLOCK_MONOTONIC, &spec);
	ms = spec.tv_sec * 1000 + (long long)(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
	return ms;
}

void pressCross() {
	system("emuclient --config PS3_KB.xml --event \"cross(1)\"");
	usleep(100000);
	system("emuclient --config PS3_KB.xml --event \"cross(0)\"");
}

int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);

	CGrabber g;

	if (!"test_key") {
		printf("waiting...\n");
		usleep(10000000);
		printf("sending key.\n");
		g.sendKey(XK_s);
		return 0;
	}

	if (!"test_pixel_readl") {
		while (true) {
			int x, y;
			g.getMousePos(x, y);
			unsigned int px = g.sample(x, y);
			printf("\r%4d,%4d: %02x%02x%02x    ", x, y, (px>>16)&0xff, (px>>8)&0xff, (px>>0)&0xff);
			usleep(100000); // 1000000 = 1sec
		}
	}

	if (!"test_gimx") {
		pressCross();
		return 0;
	}

	if ("doge_lightning") {
#define THRESHOLD 100
#define PX 5
#define TEST_MODE 0
		int stable_ticks = 0;
		int lastx=0, lasty=0;
		int last_px[PX];
		int pi = 0;
		int last_flash = 0;
		int frame_count = 0;
		int frame_time = now();
		int flash_count = 0;
		float fps = 0;
		while (true) {
			int x, y;
			g.getMousePos(x, y);
			if (x == lastx && y == lasty) {
				++stable_ticks;
			} else {
				stable_ticks = 0;
			}
			lastx = x;
			lasty = y;
#if TEST_MODE
			bool stable = true; //(stable_ticks > 1);
#else
			bool stable = (stable_ticks > 100);
#endif
			unsigned int px = g.sample(x, y);
			int intensity = ((px>>16)&0xff) + ((px>>8)&0xff) + ((px>>0)&0xff);
			last_px[pi] = intensity;
			pi = (pi + 1) % PX;
			bool flash = false;
			int compare = last_px[pi];
			int delta = intensity - compare;
			if (stable) {
#if TEST_MODE
				if (last_flash >= 5)
#else
				if (last_flash > 100)
#endif
				{
					// consider flashes
					if (delta > THRESHOLD) {
						flash = true;
						last_flash = 0;
					}
				} else {
					last_flash++;
				}
			} else {
				last_flash = 0;
			}
			++frame_count;
			long long now_time = now();
			if (now_time > frame_time + 1000) {
				float dt = now_time - frame_time;
				fps = frame_count / dt * 1000;
				frame_time = now_time;
				frame_count = 0;
			//}
			printf(
#if TEST_MODE
				"\n"
#else
				"\r"
#endif
				"FPS: %1.1f, %c %4d,%4d: %02x%02x%02x delta: %6d %s %3d flashes   ",
				fps, stable ? 'S' : 'u',
				x, y, (px>>16)&0xff, (px>>8)&0xff, (px>>0)&0xff,
				delta, flash ? "FLASH" : "     ", flash_count);
			}
#if TEST_MODE
			usleep(200000); // 100fps, 1000000 = 1sec
#else
			if (flash) {
				++flash_count;
				pressCross();
			}
			usleep(16000); // 60fps, 1000000 = 1sec
#endif
		}
	}

	printf("Done.\n");
	return 0;
}
