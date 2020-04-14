To run BestFirstSearch enter the following commands:
to complie: "make"
to run: "./BestFirstSearch *file name that contains input* *file name for what the output should be*"

input format:
total number of items, max sack weight (no spaces)
item 1 weight, item 1 profit (no spaces)
...
item k weight, item k profit (no spaces)

output format:
total number of items, optimal profit, number of items in optimal
number of nodes visited, number of leaf nodes visited
item 1 weight, item 1 profit
...
item k weight, item k profit

Data  structures:
a priority queue is used to store nodes as the search is happening 

Time Complexity:
worst case - O(nlogn), will happen if every node must be visted in order to find the optimal solution (n nodes), queueing and dequeueing a priority queue takes logn time
best case - O(log^2(n)), will happen if the first branch is the optimal and the bounds for the others are less than the optimal, queueing and dequeueing takes logn time
