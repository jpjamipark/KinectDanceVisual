#include <k4a/k4a.h>
#include <stdio.h>
#include <stdlib.h>

int main() 
{
	uint32_t count = k4a_device_get_installed_count();
	printf("%d\n", count);

	// Open the first plugged in Kinect device
	k4a_device_t device = NULL;
	if (K4A_FAILED(k4a_device_open(K4A_DEVICE_DEFAULT, &device)))
	{
		printf("Failed to open k4a device!\n");
		return 1;
	}

	size_t serial_size = 0;
	k4a_device_get_serialnum(device, NULL, &serial_size);
	char* serial = (char*)(malloc(serial_size));
	k4a_device_get_serialnum(device, serial, &serial_size);
	printf("Opened device %s\n", serial);
	free(serial);

	k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
	config.camera_fps = K4A_FRAMES_PER_SECOND_5;
	config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
	config.color_resolution = K4A_COLOR_RESOLUTION_720P;

	k4a_device_start_cameras(device, &config);
	k4a_device_stop_cameras(device);

	k4a_device_close(device);

	return 0;
}
