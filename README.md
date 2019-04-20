Multi-layer router implemented using SoukUp Algorithm

Mini-project 2

Made by: Habiba Bassem Gamal (900151007)



After building the cpp file, the command line prompts on what you need to input. 
These are the prompts in order of their output. 


>> Please enter cost of via

>> Please enter the x-dimension of the plane

>>Please enter the y-dimension of the plane


>>If no path available, do you want to swap source and target and try again?
If yes enter 1, if no enter 0


>>Do you want to do DFS in more than one layer and thus flood less?
If yes enter 1, if no enter 0


>>Enter x coordinate of source

>>Enter y coordinate of source

>>Enter z coordinate of source

>>Enter x coordinate of target

>>Enter y coordinate of target

>>Enter z coordinate of target 


Then the grids are outputted, followed by the route cost (if there is a route) and elapsed CPU time. 

The first outputted grid is M1, followed by M2 then M3. 

In the outputted grids, the cells of a particular route are labelled with the same number. 

Any negative coordinate in x, y, or z of either the source or the target coordinates results in the program terminating. 

Assumptions: 
1) The grids are initially empty

2) There are only 3 available metal layers (M1: horizontal, M2: vertical, M3: horizontal)

3) The x-coordinate range from 0 to x-1 & the y-coordinate range from 0 to y-1

4) The z-coordinate is either 1, 2 or 3
