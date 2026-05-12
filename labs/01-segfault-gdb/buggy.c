/*
 * Ava Info Conseils
 *
 * Author: Antonin Do Souto
 * Contact: antonindosouto@gmail.com
 *
 * Copyright (c) 2026 Antonin Do Souto
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <stddef.h>

typedef struct
{
	int id;
	const char *name;
	int battery_percent;
} DeviceStatus;

static DeviceStatus *find_device(DeviceStatus devices[], size_t count, int id)
{
	for (size_t i = 0; i < count; ++i)
	{
		if (devices[i].id == id)
			return &devices[i];
	}

	return NULL;
}

static void print_device_report(DeviceStatus *device)
{
	printf("Device name: %s\n", device->name);
	printf("Device ID: %d\n", device->id);
	printf("Battery: %d%%\n", device->battery_percent);
}

int main(void)
{
	DeviceStatus devices[] = {
		{1, "temperature-sensor", 87},
		{2, "door-sensor", 64},
		{3, "humidity-sensor", 92},
	};

	size_t device_count = sizeof(devices) / sizeof(devices[0]);
	int requested_id = 42;

	printf("Looking for device with id %d...\n", requested_id);

	DeviceStatus *device = find_device(devices, device_count, requested_id);

	print_device_report(device);

	return 0;
}
