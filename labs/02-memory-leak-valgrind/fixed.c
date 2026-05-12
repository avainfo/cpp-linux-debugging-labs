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
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int id;
	char name[32];
	double temperature_celsius;
	int battery_percent;
} DeviceReading;

static DeviceReading *load_device_readings(size_t *out_count)
{
	size_t count = 3;

	DeviceReading *readings = malloc(count * sizeof(DeviceReading));
	if (readings == NULL)
	{
		return NULL;
	}

	readings[0].id = 1;
	strncpy(readings[0].name, "temperature-sensor", sizeof(readings[0].name));
	readings[0].temperature_celsius = 22.5;
	readings[0].battery_percent = 87;

	readings[1].id = 2;
	strncpy(readings[1].name, "door-sensor", sizeof(readings[1].name));
	readings[1].temperature_celsius = 19.0;
	readings[1].battery_percent = 64;

	readings[2].id = 3;
	strncpy(readings[2].name, "humidity-sensor", sizeof(readings[2].name));
	readings[2].temperature_celsius = 24.1;
	readings[2].battery_percent = 92;

	*out_count = count;

	return readings;
}

static void print_device_readings(const DeviceReading readings[], size_t count)
{
	printf("Device readings:\n");

	for (size_t i = 0; i < count; ++i)
	{
		printf("- %s: %.2f°C, battery %d%%\n",
			   readings[i].name,
			   readings[i].temperature_celsius,
			   readings[i].battery_percent);
	}
}

int main(void)
{
	size_t reading_count = 0;

	printf("Loading device readings...\n\n");

	DeviceReading *readings = load_device_readings(&reading_count);
	if (readings == NULL)
	{
		fprintf(stderr, "Error: failed to load device readings.\n");
		return 1;
	}

	print_device_readings(readings, reading_count);

	free(readings);
	printf("\nReport completed.\n");

	return 0;
}
