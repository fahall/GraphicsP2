#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<float> FileReader(string inputFile)
{
	vector<float> myHeightMap;
	vector<string> unconvertedHeightMap;
	ifstream heightMapFile(inputFile);

	if(!heightMapFile) //Always test the file open.
    {
                cout<<"Error opening output file"<<endl;
                system("pause");
                return;
    }

	while(!heightMapFile.eof())
    {
		string thisValue;
		while(heightMapFile >> thisValue)
		{
			myHeightMap.push_back(stof(thisValue));
		}
    }

	for(int i; i < myHeightMap.size(); i++)
	{
		if(i % int(myHeightMap[0]) == 0 || i == 3)
		{
		cout << endl;
		}
		cout << myHeightMap[i] << "\t";
	}

	return myHeightMap;
}

