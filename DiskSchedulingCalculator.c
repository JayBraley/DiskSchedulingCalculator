#include <stdio.h>
#include "utils.h"
#include "distanceCalcs.h"

int main()
{
    int requests[] = {1515, 1212, 1296, 3800, 544, 618, 356, 2523, 5965, 4681};
    int initialPos = 4250;
    int prevPos = 5300;
    int direction = -1;
    int diskSize = 7400;
    int requestSize = sizeof(requests) / sizeof(requests[0]);

    direction = determineDirection(prevPos, initialPos);

    int totalDistance = fcfsDist(initialPos, requests, requestSize);
    printf("\nTotal FCFS distance: %d cylinders\n", totalDistance);
    totalDistance = 0;

    totalDistance = sstfDist(initialPos, requests, requestSize);
    printf("\nTotal SSTF distance: %d cylinders\n", totalDistance);
    totalDistance = 0;

    totalDistance = scanDist(initialPos, requests, requestSize, diskSize, direction);
    printf("\nTotal SCAN distance: %d cylinders\n", totalDistance);
    totalDistance = 0;

    totalDistance = lookDist(initialPos, requests, requestSize, direction);
    printf("\nTotal LOOK distance: %d cylinders\n", totalDistance);
    totalDistance = 0;


    return 0;
}