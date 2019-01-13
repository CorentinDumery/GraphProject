# GraphProject

## Compiling

To run this project, simply type "make run" in your terminal once you are in the main repository.

It was coded in C++ by Dongrui LU and Corentin DUMERY. There is also a python file used for python's plotting library.



"You should also discuss whether the results are expected or not and if not motivate why you might have obtained different results than what you had expected. Any “interesting findings” will also be appreciated.""

## Part 1 : Greedy Algorithm

### Data Structures

[structures suivantes à modifier]

map<string,int> degDictTmp;
unordered_set<string> nodes;
map<int,            > degDict; // delta key,value=degree,nodes
unordered_set<string> edges; //edge information

According to cplusplus.com, unordered_set::insert has a constant complexity, and unordered_set::erase has the same complexity as long as you erase a constant number of elements.

According to cppreference.com, map::insert and map::operator[] have a logarithmic complexity. Ultimately, this could be improved by using a data structure which can be accessed in constant time, but the logarithmic factor has very little weight.

How to improve data structures : [ ... ]

### Description of the algorithm
- First, we have to read the input file.
- Then we need to establish the degree map : we will add, for each edge we find, 1 to the number of edges that each vertices composing this edge has.
- We now want to complete our degree dictionary. To do so, we read the degree map completed in the previous step and make a map with the number of neighbors as key and the nodes with that number of neighbors as value.
- We also need an output value which is initialized as the initial graph
- We can now begin iterating, for as long as our graph has at least one edge :
 - Let's find the vertex with the lowest degree (or one of them if there are multiple possibilities). This is easily achieved with our degree dictionary and the function findMinDeg.
 - Then, we remove this vertex from our graph structure. We find all of this vertex's neighbors, reduce their degree by 1, and update their own neighbors list.
 - If the resulting graph has a better density than the current output value, we replace our output value with this graph.



### Results - Running time
To test the results, the c++ program writes in a text file how much time it takes to process graphs with varying size. This text file is then read by a python program which plots the time taken depending on the size of the graph. From there, all we need to do is a linear regression and the quality of our program will be determined by the coefficient of determination r_squared. The closer r_squared is to 1, the better the implementation is.

[...]

### Results - Resulting subgraphs
[...] Report the density of the subgraphs you found as well the number of nodes in each of the
subgraphs.



## Part 2 : Streaming Algorithm

"While reading the file you can store some information in main memory, however, you can only use O(n log n) bits in main memory. In particular, for each node you can store in main memory only its (current) degree and not the edges incident to the node."

### Data Structures

In this section we will try to find the densest subgraph without using more than O(n log n) bits. This implies we cannot use the same data structures, in particular, the unordered_set we used to store the edges cannot be used anymore because of its size. Instead, we will have to read the input graph multiple times.

### Description of the algorithm
- We set an arbitrary value for epsilon.
- We read the graph once to determine its number of edges and nodes. (Without storing the edges because of the memory use constraint !)
- Just like in the previous section, we create an output value initialized as the initial graph.
- Again, for as long as our graph contains at least one edge :
 - We remove every node that has a degree lower than 2(1+epsilon)*density(G). For every removal, we read the graph so that we can decrease the degree of the node's former neighbors.
 - If the resulting graph has a better density than the current output value, we replace our output value with this graph.

### Results - Memory use

[graph or tab]

By incrementing a value everytime a new slot of memory is reserved, we can measure memory use. The results show that it is proportional to the number of nodes, but not to the input size which includes the number of edges. The constraint on memory use is satisfied.

### Results - Running time

[graph]



### Results - Running time and density for different epsilons

[tab]

There seems to be little difference in processing time. This is probably explained by the fact that the algorithm has to remove every node one by one and read the graph every time indepedently of the value of epsilon. Perhaps if we implemented a better way to remove the nodes, by doing only one pass per iteration to remove all the selected nodes at the same time, we would find a better running time with higher epsilon.
In general, density seems to decrease when epsilon increases. The value for epsilon = 0.4 can probably be explained by the fact that the number of nodes removed depends on the epsilon value, so based on that value the algorithm could "skip" the right solution and remove too many nodes.
In order to get consistent results on a given graph, it would probably be important to test different epsilon values. Furthermore, our approximation guarantee certifies that the densest subgraph's density is not greater than the value of 2(1+epsilon)*output_density found with this algorithm. For this reason, even if an epsilon gives us a terrible output (with a very low density), it will provide us with a good idea of the maximum density we can hope to find. In this case, the lowest value found is for epsilon = 0.2 and certifies that the densest subgraph's density is below 5.12 .
