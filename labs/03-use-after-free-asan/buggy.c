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
	int device_id;
	char device_name[32];
	int packets_received;
} DeviceSession;

static DeviceSession *open_device_session(int device_id, const char *device_name)
{
	DeviceSession *session = malloc(sizeof(DeviceSession));
	if (session == NULL)
		return NULL;

	session->device_id = device_id;
	session->packets_received = 12;

	snprintf(session->device_name, sizeof(session->device_name), "%s", device_name);

	return session;
}

static void close_device_session(DeviceSession *session)
{
	free(session);
}

static void print_session_summary(const DeviceSession *session)
{
	printf("Device ID: %d\n", session->device_id);
	printf("Device name: %s\n", session->device_name);
	printf("Packets received: %d\n", session->packets_received);
}

int main(void)
{
	printf("Opening device session...\n");

	DeviceSession *session = open_device_session(101, "sensor-gateway-01");
	if (session == NULL)
	{
		fprintf(stderr, "Error: failed to open device session.\n");
		return 1;
	}

	printf("Session opened for %s\n", session->device_name);

	printf("Closing device session...\n");
	close_device_session(session);

	printf("Printing session summary after close...\n");
	print_session_summary(session);

	return 0;
}
