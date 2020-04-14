#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;


struct item
{
	double weight; //weight of an item
	double profit; //profit for an item
	double profitToWeight; //an item's profit to weight ratio
};

struct Node
{
	int level; //what level of the tree a node is on
	double profit; //the sum of the profit of all the itmes included on the path to this node
	double bound; //highest possible profit for nodes that could be added
	double weight; //total weight of all included items for this node
	vector<int> contain; //list of the items that are included in this node
};

//comparator for the priority queue
struct compBound
{
	bool operator() (Node const& node1, Node const& node2)
	{
		return node1.bound < node2.bound;
	}
};

//this function sorts the items by profit to weight ratio in decreasing order using bubble sort
////item items[] - is an array of item structs
//int size - the number of items
void bSort(item items[], int size)
{
	for (int i=0; i<size-1; i++)
	{
		for (int j=0; j<size-1-i; j++)
		{
			if (items[j].profitToWeight < items[j+1].profitToWeight)
			{
				item temp = items[j]; //temp variable to allow swapping
				items[j] = items[j+1];
				items[j+1] = temp;
			}
		}
	}
}

//bound find the max possible proit for any node to serve as its bound
//Node v - the current node
//int numItems - the total number of items
//saint sackweight - the max weight of the knapsack
//item items[] - array of all the items
int bound(Node v, int numItems, int sackWeight, item items[])
{
	if (v.weight > sackWeight)
	{
		return 0;
	}
	double profitBound = v.profit; //running total the max possible profit (bound)
	int nLevel = v.level+1; //keep track of which level currently on
	int totalWeight = v.weight; //running total of the weight of included items

	while ((nLevel < numItems) && (totalWeight + items[nLevel].weight <= sackWeight))
	{
		totalWeight += items[nLevel].weight;
		profitBound += items[nLevel].profit;
		nLevel++;
	}

	if (nLevel < numItems)
	{
		profitBound += (sackWeight - totalWeight) * items[nLevel].profitToWeight;
	}

	return profitBound;
}

//runs the  best first branch and bound 0/1 knapsack algorithm
//int sackweight - the max weight of the knapsack
//item items[] - an array of all the items
//int numItems - the total number of items
//string filename - the filename for output
int knapsack01(int sackWeight, item items[], int numItems, string fileName)
{
	int numLeaves = 0; //total nodes visited
	int numNodes = 1; //total leaf nodes visited 
	vector<int> bestList; //list of the items included in the optimal solution

	priority_queue<Node, vector<Node>, compBound> q; //queue of nodes to search
	Node curr, next; //curr - the node currently worked on, next - the next node either with or without the next item

	curr.level = -1;
	curr.profit = curr.weight = 0;
	curr.bound = bound(curr, numItems, sackWeight, items);
	q.push(curr);

	int maxProfit = 0;
	while (!q.empty())
	{
		curr = q.top();
		q.pop();

		if (curr.bound <= maxProfit)
		{
			numLeaves++;
			continue;
		}

		//include item
		next.level = curr.level+1;
		next.weight = curr.weight + items[next.level].weight;
		next.profit = curr.profit + items[next.level].profit;

		if (next.weight <= sackWeight && next.profit > maxProfit)
		{
			maxProfit = next.profit;
		}
		next.contain = curr.contain;
		next.bound = bound(next, numItems, sackWeight, items);
		
		if (next.bound >= maxProfit)
		{
			next.contain.push_back(next.level);
			q.push(next);
			if (next.profit == maxProfit)
			{
				bestList = next.contain;
			}
			next.contain.pop_back();
		}
		else
		{
			numLeaves++;
		}
		numNodes++;

		//exclude item
		next.weight = curr.weight;
		next.profit = curr.profit;
		next.bound = bound(next, numItems, sackWeight, items);
		
		if (next.bound >= maxProfit)
		{
			q.push(next);
		}
		else
		{
			numLeaves++;
		}
		numNodes++;
	}
	
	ofstream outFile;
	outFile.open(fileName);


	outFile <<numItems << "," << maxProfit << ","<< bestList.size() << endl;

	outFile << numNodes << "," << numLeaves << endl;

	for (int w=0; w<bestList.size(); w++)
	{
		outFile << items[bestList[w]].weight << "," << items[bestList[w]].profit << endl;
	}

	return maxProfit;
}

int main(int argc, char *argv[])
{
	ifstream inputFile(argv[1]); //input filename
	string fileName  = argv[2]; //output filename

	string toBeSplit; //the next line of read in vaules that need to be split into the correct parts
	inputFile >> toBeSplit;

	size_t comma = toBeSplit.find(","); //location in string where the , is
	string totalItems = toBeSplit.substr(0, comma); //total number of items as a string
	string totalWeight = toBeSplit.substr(comma+1); //max allowed weight as a string
	int numItems = stoi(totalItems); //total numnber of items as an int
	int sackWeight = stoi(totalWeight); //max allowed weight as an int
	
	item items[numItems]; //array of all the items

	for (int i=0; i<numItems; i++)
	{
		item nItem; //a new item to be added
		inputFile >> toBeSplit;
		comma = toBeSplit.find(",");
		nItem.weight = stod(toBeSplit.substr(0, comma));
		nItem.profit = stod(toBeSplit.substr(comma+1));
		nItem.profitToWeight = (nItem.profit)/(nItem.weight);
		items[i] = nItem;
	}
	bSort(items, numItems);
	knapsack01(sackWeight, items, numItems, fileName);
	
	return 0;
}
