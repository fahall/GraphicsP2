#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<float> FileReader(string inputFile)
{
	cout << "Reading Selected Mars File...";
	vector<float> myHeightMap;
	ifstream heightMapFile(inputFile);

	if(!heightMapFile) //Always test the file open.
    {
                cout<<"Error opening input file"<<endl;
                system("pause");
                return myHeightMap;
    }

	while(!heightMapFile.eof())
    {
		string thisValue;
		while(heightMapFile >> thisValue)
		{
			myHeightMap.push_back(stof(thisValue));
		}
    }
	/**************************Debugging test for file reader. 
	for(int i = myHeightMap.size()-1; i < myHeightMap.size(); i++)
	{
		if(i % int(myHeightMap[0]) == 0 || i == 3)
		{
		cout << endl;
		}
		cout << myHeightMap[i] << "\t";
	}
	//*/

	cout << "COMPLETED" << endl;
	return myHeightMap;
}

