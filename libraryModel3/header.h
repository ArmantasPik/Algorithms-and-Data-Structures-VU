#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "BST.h"
#include "vector.h"

#define maxChar 255
#define maxBookSize 10000
#define maxActiveClients 10000

void readFileAndValidate(FILE *inputFile, int *modelTime, int *numberOfBooks, float *clientProbability, float *bookProbability);
void initializeAndFill(vector *bookVectorArranged, vector *bookVectorNotArranged, binarySearchTree *bookBST, int numberOfBooks, int arranged[], int notArranged[]);
int bookSearchModelInVector(vector bookVector, int bookArray[], int modelTime, int numberOfBooks, float clientProbability, float bookProbability);
int bookSearchModelInBST(binarySearchTree *bookBST, int bookArray[], int modelTime, int numberOfBooks, float clientProbability, float bookProbability);
void shuffle(int *array, int n);
int cmpfunction(const void * a, const void * b);

#endif