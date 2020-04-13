#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct item
{
	double weight;
	double profit;
	double profitToWeight;
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

	outFile.close();
	return 0;
}
