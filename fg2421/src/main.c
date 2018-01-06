#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <hidapi.h>


int main(int argc, char* argv[]) {
	hid_device *handle = NULL;

	if (argc < 2)
		return -1;
	int num = strtol(argv[1], NULL, 10);

	// Open the device using the VID, PID,
	// and optionally the Serial number.
	handle = hid_open(0x056d, 0x2, NULL);
	if (!handle)
		return -1;

	// 02 20 => equivalent to SIGNAL button
	// 02 ?? => power button
	// 09 ** => very slow

	// some commands before 17 0E erased model name and serial number :/

	// this basically emulates a single press of the "SIGNAL" button, I gave up bruteforcing commands after it screwed up my s/n
	const uint8_t cmd[] = { 0x02, 0x20, 0x00 };
	for (int i = 0; i < num; ++i) {
		if (i != 0)
			sleep(3);
		hid_write(handle, cmd, sizeof(cmd));
	}

	return 0;
}
