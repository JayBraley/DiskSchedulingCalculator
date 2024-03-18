#include <stdlib.h>
#include <limits.h>
#include "utils.h"

// Utility function for pre-sorting arrays
int compare(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

// Utility function for SSTF to find the shortest distance to a request from the current position.
int findMinDistance(int currentPos, int requests[], int requestSize, int processed[])
{
    int minDistance = INT_MAX;
    int index = -1;

    // Compare each request with the current position, and if it's
    // shorter than the last recorded minimum distance, save it as
    // the new minimum.
    for (int i = 0; i < requestSize; i++)
    {
        int distance = abs(currentPos - requests[i]);
        if (!processed[i] && distance < minDistance)
        {
            minDistance = distance;
            index = i;
        }
    }
    return index;
}

// Utility function for SCAN to check if we've reached a request position
void checkForRequest(int requestSize, int requests[], int processed[], int pos)
{
    // At each iteration check if we have reached a request
    for (int i = 0; i < requestSize; i++)
    {
        if (requests[i] == pos)
        {
            processed[i] = -1; // Mark off the request after reaching it.
            break;
        }
    }
}
// Utility function for SCAN to check if we've processed all requests.
int allRequestsProcessed(int processed[], int processedSize)
{
    for (int i = 0; i < processedSize; i++)
    {
        if (processed[i] != -1)
        {
            return -1;
        }
    }

    return 1;
}

// Determines a direction of travel to cylinder array based on a previous position.
int determineDirection(int prevPos, int currentPos)
{
    if (prevPos > currentPos)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

// Utility function to mark served requests and return the number of requests served
int serveRequests(int *requests, int *servedFlags, int requestSize, int currentPos, int direction, int *lastServedPos)
{
    int served = 0;
    int step = direction > 0 ? 1 : -1;

    // Serve requests and move head.
    for (int pos = currentPos; (direction > 0 ? pos < 7400 : pos >= 0); pos += step)
    {
        for (int i = 0; i < requestSize; i++)
        {
            if (requests[i] == pos && !servedFlags[i])
            {
                servedFlags[i] = 1;
                *lastServedPos = pos;
                served++;
                break;
            }
        }
    }
    return served;
}

// Utility function to check if there are any unserved requests in the current direction
int hasUnservedRequests(int *requests, int *servedFlags, int requestSize, int currentPos, int direction) {
    for (int i = 0; i < requestSize; i++) {
        if (!servedFlags[i] && ((direction > 0 && requests[i] > currentPos) || (direction < 0 && requests[i] < currentPos))) {
            return 1; // Found an unserved request in the current direction
        }
    }
    return 0; // No unserved requests in the current direction
}