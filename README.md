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
1. Squer dimension 
2. Empty cell's position
3. Cell's possition with Camera in it
4. Cell's id number, desired to make empty 
5. Number of cars
6. Each car's id number and spaces it takes
7. when done enter `-1`.

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

## Question :

* Given the relation between each two city, calculate shortest path from a given starting point to a given ending point.
* Print the path alongside with path's length. 
* Cities' path is two sided, meaning if the path's length from `a` to `b` is `18`, path's length is the same from `b` to `a`.

## Query :
1. Number of the relations between each two cities.
2. Separate cities' name by a space and then enter the length between these two.

Example:

    8
    a b 7
    c b 2
    d c 4
    e d 1
    a e 1
    a d 6
    a c 4
    b d 3


* Given the starting and ending points it is abled to print all possible paths alongside the path's length.
<img src="guide/task2A.png" width="800">

## Algorithm's used in task2A: Dijkstra
* Our starting point in dijkstra is the starting point and we find all shortest path from the starting point to all other points.
* We save the length in an array including shortest path from starting point to all others and print our desired one at last.
* We save the path in a array with vector type and recursively print the path from end to start.


# Task2-B

