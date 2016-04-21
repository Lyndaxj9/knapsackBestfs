ABOUT
-----

* Author - Omowumi L. Ademola

CS375 Programming Assignment 2
Program to solve the knapsack problem using Best-First-Search.

INSTRUCTIONS
------------
* Compile the program with the command:
Prompt> make BestFirstSearch

* Run the program with the command:
Prompt> BestFirstSearch <input.txt> <output.txt>

DATA STRUCTURES
---------------

The main data structures used were array, vector and structs.

* Arrays were used to store an array of structs as well as 0/1
used to indicate whether or not the item was in the solution.
* A vector was used as a queue for the next item so that std::sort
could be used on it
* Structs were used for nodes that had general information about
the item as well a statenodes that had held information once the
algorithm started.

ANALYSIS
--------

This method (Best-First-Search) is works well because instead of
having to go through (2^n) - 1 nodes solutions to find the final
solution it gets cut down to a bit more or less than half.
This is due to the pruning that takes place with comparison to
bound, best and capacity.
