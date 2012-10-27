//
//  triAngles.h
//  bma-week-8-Xcode-TriAngles
//
//  Created by Wally on 10/25/12.
//  Copyright (c) 2012 W M. All rights reserved.
//

#ifndef bma_week_8_Xcode_TriAngles_triAngles_h
#define bma_week_8_Xcode_TriAngles_triAngles_h

typedef struct {
    int numAngles;
    float maxDegs;
    float angleSum;
} Polygon;

int parseArgs(int *argC, char *argV[], float angles[], Polygon *p);

float inferAngle(float angles[], Polygon *p);

int inputPolygon(Polygon *p);

char *getPolygonName(Polygon *p);

int displayResult(float *rslt, Polygon *p);

void displayUsage(int *argC, char *argV[]);

#endif
