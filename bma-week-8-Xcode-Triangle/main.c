//
//  main.c
//  bma-week-8-TriAngles
//
//  Created by W. Mooncai on 10/23/12.
//  Copyright (c) 2012 W M. All rights reserved.
//


/*
 
 Crossfire Building Mobile Apps Homework Week 8 - Triangle Angle Calculator
 
 Homework: Write a Function
 • Program: The interior angles of a triangle must add up to 180 degrees.
 • Create a new C Command Line Tool named Triangle.
 • In main.c, write a function that takes the first two angles
 and returns the third.
 
 * OK, I did a little more...
 
 */

#include <stdio.h>
#include <stdlib.h>

#include "bma-week-8-Xcode-Triangle.h"

static const int ANGLE_TOTAL_DEGREES = 360;
static const int ARGS_QTY_NON_ANGLE = 1; // arg[0] = program name

/* ******************************** main() ********************************* */

int main(int argc, char *argv[])
{
    float result = 0.0;
    int status = -1;
    
    Polygon polygon;
    polygon.numAngles = ((argc - ARGS_QTY_NON_ANGLE) + 1);
    polygon.angleSum  = 0;
    polygon.maxDegs   = 0;
    
    float anglesList[(polygon.numAngles - 1)];
    
    printf("Welcome to the missing polygon angle oracle ~\nTell me your angles...\n\n");
    
    if (argc > 2) {
        
        if (parseArgs(&argc, argv, anglesList, &polygon) == EXIT_FAILURE) {
            status = EXIT_FAILURE;
        }
        
    } else if (argc == 1) {
                
        if (inputPolygon(&polygon) == EXIT_FAILURE) {
            status = EXIT_FAILURE;
        }
    } else {
        status = EXIT_FAILURE;
    }
    
    if (status != EXIT_FAILURE) result = inferAngle(anglesList, &polygon);
    
    if ( (status != EXIT_FAILURE) ) {
        status = displayResult(&result, &polygon);
    }
    
    if (status == EXIT_FAILURE) {
        displayUsage(&argc, argv);
        return EXIT_FAILURE;
    } else return EXIT_SUCCESS;
}

/* ***************************** inputPolygon() **************************** */

int inputPolygon(Polygon *p) {
    
    float angleDegrees = 0.0;
    // int count = 0;
    int status = 0;
    
    p->numAngles = 0;
    p->angleSum = 0.0;
    
    do {
        printf("\nEnter degrees for angle %d (enter '0' degrees when done): "
               , (p->numAngles));
        status = scanf("%f", &angleDegrees);
        
        if ( (status == 1) && (angleDegrees > 0.0) ) {
            
            p->angleSum += angleDegrees;
            p->numAngles ++;

            if (p->numAngles == 1) {
                
                printf("1 angle of %f degrees was entered.\n", p->angleSum);
                
            } else printf("%d angles totaling %f degrees were entered.\n"
                          , p->numAngles, p->angleSum);        }
        
    } while ( (angleDegrees > 0.0) );
    
    if ( (p->numAngles > 1) && (p->angleSum > 0.0)) {
        p->numAngles--;
        return EXIT_SUCCESS;
    } else return EXIT_FAILURE;
}

/* ****************************** parseArgs() ****************************** */

int parseArgs(int *argC, char *argV[], float angles[], Polygon *p)
{
    p->numAngles = 1;
    p->angleSum = 0.0;
    
    for (int angleCt = 0; angleCt < (*argC - ARGS_QTY_NON_ANGLE); angleCt++) {
        
        angles[angleCt] = atoi(argV[angleCt+1]);
        p->angleSum += angles[angleCt];
        p->numAngles++;
        
        if ( (angles[angleCt] == 0.0) && (p->numAngles  < 3) ) {
            return EXIT_FAILURE;
        }
        
        printf("Known input angle %d: %f\n", (angleCt + 1), angles[angleCt]);
    }
    
    return EXIT_SUCCESS;
}

/* ***************************** inferAngle() ****************************** */

float inferAngle(float angles[], Polygon *p)
{
    // http://en.wikipedia.org/wiki/Internal_angle
    
    p->maxDegs = 180 * ((p->numAngles) - 2);
    return (p->maxDegs - p->angleSum);
}

/* **************************** getPolygonName() *************************** */

char *getPolygonName(Polygon *p)
{
    // http://en.wikipedia.org/wiki/Polygon
    
    switch (p->numAngles) {
        case 3: return "triangle";
        case 4: return "square";
        case 5: return "pentagon";
        case 6: return "hexagon";
        case 7: return "heptagon";
        case 8: return "octagon";
        case 9: return "enneagon";
        case 10: return "decagon";
        case 11: return "hendecagon";
        case 12: return "dodecagon";
        case 13: return "tridecagon";
        case 14: return "tetradecagon";
        case 15: return "pentadecagon";
        case 16: return "hexadecagon";
        case 17: return "heptadecagon";
        case 18: return "octadecagon";
        case 19: return "ennedecagon";
        case 20: return "icosagon";
        case 30: return "triacontagon";
        case 100: return "hectogon";
        case 1000: return "chiliagon";
        default: return "polygon";
    }
}

/* ***************************** displayResult() *************************** */

int displayResult(float *rslt, Polygon *p) {
    
    char *polyName = getPolygonName(p);
    
    if (*rslt < 180) {
        
        printf("\n                  Result (inferred) Angle: %f\n", *rslt);
        printf("                 Total degrees in %s: %f\n"
               , polyName, p->maxDegs);
        printf("\nTotal sides (and angles) in your %s: %d\n"
               , polyName, p->numAngles);
        return EXIT_SUCCESS;
                
    } else {
        
        printf("\n* Error: The angles provided can not produce a %s.\n"
               , polyName);
        printf("The %d angles entered total %f degrees."
               , p->numAngles, p->angleSum);
        return EXIT_FAILURE;
    }
}

/* ***************************** displayUsage() **************************** */

void displayUsage(int *argC, char *argV[]) {
    
    if (*argC > 1) {
        printf("\n* Error: Here is what you input:\n\n");
        for (int i = 0; i < *argC; i++) {
            printf("%s ", argV[i]);
        }
    } else printf("\n* Error!");
    
    printf("\n\nUsage:\nbma-week-8-Xcode-Triangle ");
    printf("<[mandatory angle in degrees #1] [mandatory angle in degrees #2] ... [optional angle in degrees #n]>\n\n");
}
