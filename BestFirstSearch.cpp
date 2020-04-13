#include <iostream>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

int numLeaves = 0;
int numNodes = 0;

struct item
{
	double weight;
	double profit;
	double profitToWeight;
};

struct Node
{
	int level;
	double profit;
	double bound;
	double weight;
};

void bSort(item items[], int size)
{
	for (int i=0; i<size-1; i++)
	{
		for (int j=0; j<size-1-i; j++)
		{
			if (items[j].profitToWeight < items[j+1].profitToWeight)
			{
				item temp = items[j];
				items[j] = items[j+1];
				items[j+1] = temp;
			}
		}
	}
}

int bound(Node v, int numItems, int sackWeight, item items[])
{
	if (v.weight >= sackWeight)
	{
		return 0;
	}
	double profitBound = v.profit;
	int nLevel = v.level+1;
	int totalWeight = v.weight;

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

int knapsack01(int sackWeight, item items[], int numItems)
{
	queue<Node> q;
	Node curr, next;

	curr.level = -1;
	curr.profit = curr.weight = 0;
	q.push(curr);

	int maxProfit = 0;
	while (!q.empty())
	{
		curr = q.front();
		q.pop();

		if (curr.level == -1)
		{
			next.level = 0;
		}
		if (curr.level == numItems-1)
		{
			numLeaves++;
			continue;
		}

		next.level = curr.level+1;
		next.weight = curr.weight + items[next.level].weight;
		next.profit = curr.profit + items[next.level].profit;

		if (next.weight <= sackWeight && next.profit > maxProfit)
		{
			maxProfit = next.profit;
		}

		next.bound = bound(next, numItems, sackWeight, items);
		
		if (next.bound > maxProfit)
		{
			q.push(next);
		}

		next.weight = curr.weight;
		next.profit = curr.profit;
		next.bound = bound(next, numItems, sackWeight, items);
		if (next.bound > maxProfit)
		{
			q.push(next);
		}
	}
	return maxProfit;
}

int main(int argc, char *argv[])
{
	ifstream inputFile(argv[1]);
	ofstream outFile;
	outFile.open(argv[2]);

	string toBeSplit;
	inputFile >> toBeSplit;

	size_t comma = toBeSplit.find(",");
	string totalItems = toBeSplit.substr(0, comma);
	string totalWeight = toBeSplit.substr(comma+1);
	int numItems = stoi(totalItems);
	int sackWeight = stoi(totalWeight);
	
	outFile << numItems << ",";

	item items[numItems];

	for (int i=0; i<numItems; i++)
	{
		item nItem;
		inputFile >> toBeSplit;
		comma = toBeSplit.find(",");
		nItem.weight = stod(toBeSplit.substr(0, comma));
		nItem.profit = stod(toBeSplit.substr(comma+1));
		nItem.profitToWeight = (nItem.profit)/(nItem.weight);
		cout << nItem.profitToWeight << endl;
		items[i] = nItem;
	}
	bSort(items, numItems);
	int optProfit = knapsack01(sackWeight, items, numItems);
	outFile << optProfit << "," << endl;
	outFile << numLeaves << endl;

	outFile.close();
	return 0;
}
