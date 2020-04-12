#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream inputFile(argv[1]);

	string toBeSplit;
	inputFile >> toBeSplit;

	ofstream outFile;
	outFile.open(argv[2]);

	outFile << toBeSplit << endl;

	outFile.close();
	return 0;
}
