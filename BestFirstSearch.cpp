#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream inputFile(argv[1]);


	ofstream outFile;
	outFile.open(argv[2]);

	outFile.close();
	return 0;
}
