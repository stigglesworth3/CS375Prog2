#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream inputFile(argv[1]);
	ofstream outFile;
	outFile.open(argv[2]);

	string toBeSplit;
	inputFile >> toBeSplit;

	size_t comma = toBeSplit.find(",");
	string totalItems = toBeSplit.substr(0, comma);
	string totalWeight =toBeSplit.substr(comma+1);
	int numItems = stoi(totalItems);
	int sackWeight = stoi(totalWeight);

	outFile.close();
	return 0;
}
