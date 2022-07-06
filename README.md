# Algorithm-design
Algorithm design's Project
Written by Mitra Omrani

This project contains 4 tasks, each is discussed individually :

# Task 1 :

## Question :
Given Car's possition, claim if it's possible to move cars in their directions such way that the desired possition is empty.
If it's possible print number of movements required and car's id number in order of moving.
If it's not possible  print "impossible".

## Query :
1.Squer dimension 

2.Empty cell's position

3.Cell's possition with Camera in it

4.Cell's id number, desired to make empty 

5.Number of cars

Each car's id number and spaces it takes

Example :

    4
    15
    8
    7
    1 1 2
    2 3 4
    3 5 9
    4 6 7
    5 10 11
    6 12 16
    7 13 14
    -1
 
As you may see in the diagram :

<img src="guide/2.png" width="300">

The resault would be : 

<img src="guide/3.png" width="300">
<img src="guide/1.png" width="700">

## Algorithm's used in task1: Backtracking 
* Strating from the empty possition we check all four neighbors and calculate each cars' move in those position.
* We use Depth first search for finding the answer.
* The answer  is retured when we empty the desired space.


# Task2-A





