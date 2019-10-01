#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>


extern sf::RenderWindow* window;

void start();
void draw();
void end();
void selectionSort();
void insertionSort();
void shellSort();
void bubbleSort();
void radixSort();
void cocktailSort();
void mergeSort(int beginIndex, int endIndex);
void merge(int arr1BeginIndex, int arr1EndIndex, int arr2BeginIndex, int arr2EndIndex);
void quickSort(int lowIndex, int highIndex);
int partition(int lowIndex, int highIndex);

void sortAnimation();
void shuffle();

/*
 *	Below functions all require to
 *	be added into "Source.cpp"
 *	so that they can be called.
 *	This is only required if they
 *	have an implimentation.
*/

void mousePressed();
void keyPressed(sf::Keyboard::Key keyCode);
void keyReleased(sf::Keyboard::Key keyCode);

