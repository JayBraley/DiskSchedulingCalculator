#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "distanceCalcs.h"

int fcfsDist(int currentPos, int requests[], int requestSize)
{
    int totalDistance = 0;

    for (int i = 0; i < requestSize; i++)
    {
        totalDistance += abs(currentPos - requests[i]);
        currentPos = requests[i];
    }

    return totalDistance;
}


int sstfDist(int currentPos, int requests[], int requestSize)
{
    int totalDistance = 0;
    // Dynamically allocate the processed array
    int* processed = (int*)malloc(requestSize * sizeof(int));

    // Check if malloc succeeded
    if (processed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1; // or exit, or handle the error as appropriate
    }

    // Reset processed array
    for (int i = 0; i < requestSize; i++)
    {
        processed[i] = 0;
    }

    for (int i = 0; i < requestSize; i++)
    {
        int nextIndex = findMinDistance(currentPos, requests, requestSize, processed);
        if (nextIndex != -1)
        {
            totalDistance += abs(currentPos - requests[nextIndex]);
            currentPos = requests[nextIndex];
            processed[nextIndex] = 1;
        }
    }

    // Release the allocated memory
    free(processed);
    return totalDistance;
}

int scanDist(int currentPos, int requests[], int requestSize, int diskSize, int direction)
{
    int totalDistance = 0;

    // Dynamically allocate the processed array
    int* processed = (int*)malloc(requestSize * sizeof(int));
    // Check if malloc succeeded
    if (processed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1; // or exit, or handle the error as appropriate
    }
    // Reset processed array
    for (int i = 0; i < requestSize; i++)
    {
        processed[i] = 0;
    }
    
    // Start at the current position then search to the beginning or end
    // of the disk for requests depending on which direction we are initially
    // travelling in.

    // Start travel towards 0.
    if (direction == -1)
    {
        for (int pos = currentPos; pos >= 0; pos--)
        {
            checkForRequest(requestSize, requests, processed, pos);

            totalDistance += 1;
            currentPos = pos;

            if (allRequestsProcessed(processed, requestSize) > 0)
            {
                return totalDistance;
            }
        }

        // Once we reach 0, change direction.
        direction = 1;
        for (int pos = currentPos+2; pos < diskSize; pos++)
        {
            checkForRequest(requestSize, requests, processed, pos);

            totalDistance += 1;
            currentPos = pos;

            if (allRequestsProcessed(processed, requestSize) > 0)
            {
                return totalDistance;
            }
        }
    }
    // Start travel towards the end of the disk.
    else
    {
        direction = 1;
        for (int pos = currentPos; pos < diskSize; pos++)
        {
            checkForRequest(requestSize, requests, processed, pos);

            totalDistance += 1;
            currentPos = pos;

            if (allRequestsProcessed(processed, requestSize) > 0)
            {
                return totalDistance;
            }
        }

        // Once we reach array end, change direction.
        direction = -1;
        for (int pos = currentPos-2; pos >= 0; pos--)
        {
            // At each iteration check if we have reached a request
            checkForRequest(requestSize, requests, processed, pos);

            totalDistance += 1;
            currentPos = pos;

            if (allRequestsProcessed(processed, requestSize) > 0)
            {
                return totalDistance;
            }
        }   
    }

    // Release the allocated memory
    free(processed);
    return totalDistance;
}

int lookDist(int currentPos, int requests[], int requestSize, int direction)
{
    int totalDistance = 0;
    int lastServedPos = currentPos;
    int remainingRequests = requestSize;
    int *servedFlags = (int*)calloc(requestSize, sizeof(int)); // Array to track served requests

    if (!servedFlags)
    {
        printf("Memory allocation failed\n");
        return -1;
    }

    while (hasUnservedRequests(requests, servedFlags, requestSize, lastServedPos, direction))
    {
        for (int pos = currentPos; direction > 0 ? pos < 7400 : pos >= 0; pos += direction) {
            for (int i = 0; i < requestSize; i++) {
                if (requests[i] == pos && !servedFlags[i]) {
                    servedFlags[i] = 1; // Mark the request as served
                    lastServedPos = pos;
                    break;
                }
            }
        }
        totalDistance += abs(lastServedPos - currentPos); // Update total distance
        currentPos = lastServedPos; // Update current position to last served position
        
        // Check if we need to reverse the direction
        if (!hasUnservedRequests(requests, servedFlags, requestSize, lastServedPos, direction)) {
            direction = -direction; // Reverse direction
        }
    }

    free(servedFlags);
    return totalDistance;
}