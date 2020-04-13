#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct singleItem
{
	int weight;
	int profit;
	double profitToWeight;
};
typedef struct singleItem item;

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

	vector<item> items;

	for (int i=0; i<numItems; i++)
	{
		item nItem;
		inputFile >> toBeSplit;
		comma = toBeSplit.find(",");
		nItem.weight = stoi(toBeSplit.substr(0, comma));
		nItem.profit = stoi(toBeSplit.substr(comma+1));
		nItem.profitToWeight = (nItem.profit)/(nItem.weight);
		int inserted = 0;
		for (int j=0; j<items.size(); j++)
		{
			if (items[j].proftitToWeight < nItem.profitToWeight)
			{
				items.insert(j, nItem);
				inserted = 1;
				break;
			}
		}
		if (inserted == 0)
		{
			items.push_back(nItem);
		}
	}

	outFile.close();
	return 0;
}
//can i pull this?
