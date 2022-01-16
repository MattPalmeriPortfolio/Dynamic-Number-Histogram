# Dynamic-Number-Histogram

Contents
---------------------
* File Contents
* Introduction
* Algorithm
* Requirements

## File Contents
	
	Dynamic_Number_Histogram.cpp (program file containing code)

## Introduction
Book practice project from Problem Solving With C++ Chapter 9. Project 8.
Program calculates and creates a histogram with a dynamic number of inputs. Demonstrates ability to use multiple functions and math to create visuals in c++.
Written using Microsoft Visual Studio. 

## Algorithm

	1. Take input from a randomly generated file, because its more fun that way.
		1a. use fstream, push_back with vector (capacity initialized to 300), input separated by space so ezpz; sentinel value -1
	2. Create a 2D dynamic array equal to [size of vector][2]; store the # in [x][0], and the frequency in [x][1]
		2a. Use a for loop, iterating through each index known to contain a value; if that value matches one of the stored values, ++frequency; else, add it to array and ++marker for array size
		2b. move all the elements to a new array, properly sized to fit the entries.
	3. Quicksort the array:
		3a. use a double swap function to swap the frequency together with the values
	4. Output

## Requirements
No requirements or modules needed for running this program.
