/* 
    Duota N daiktų, kurių svoriai s1, s2, ... sN. Programa turi suskirstyti daiktus į 2 grupes taip, 
    kad grupių svoriai būtų, kiek įmanoma, vienodesni. Vartotojas nurodo failą, iš kurio programa įveda daiktų svorius. 

    Armantas Pikšrys PS3 1 pogrupis. 2.2 užd.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

#define maxChar 255

vector<float> selectPartition(vector<float> startWeights, int index, float target);
vector<float> selectOtherPartition(vector<float> startWeights, vector<float> groupOne);
void printResult(vector<float> startWeights, vector<float> groupOne, vector<float> groupTwo);
void saveToFile(vector<float> startWeights, vector<float> groupOne, vector<float> groupTwo);
float vectorSum(vector<float> branch);
float absDifference(float a, float b);

int main()
{
    vector<float> startWeights;
    vector<float> otherStartWeights;
    vector<float> groupOne;
    vector<float> groupTwo;
    vector<float> groupThree;
    float target;

    //Open and read data file
    char fileName[maxChar];
    ifstream dataFile;

    while(true)
    {
        cout << "Enter the data file name: ";
        cin.getline(fileName, maxChar);
        cout << endl;

        dataFile.open(fileName);

        if(dataFile.fail())
            cout << "Couldn't open the file! Try again.\n" << endl;
        else
            break;
    }

    float element;
    while(dataFile >> element)
        startWeights.push_back(element);

    dataFile.close();

    //Execute the partition selection algorithm
    target =  vectorSum(startWeights) / 3;
    
    groupOne = selectPartition(startWeights, 0, target);
    otherStartWeights = selectOtherPartition(startWeights, groupOne);
    groupTwo = selectPartition(otherStartWeights, 0, target);
    groupThree = selectOtherPartition(otherStartWeights, groupTwo);

    //Print all of the weights and partitions
    printResult(startWeights, groupOne, groupTwo);

    //Print third group
    cout << "Third group: [ ";

    for(int i = 0; i < groupThree.size(); i++)
        cout << fixed << setprecision(2) << groupThree[i] << " ";

    cout << "] \t Third group weight is " << fixed << setprecision(2) << vectorSum(groupThree) << endl;

    //Save to file
    saveToFile(startWeights, groupOne, groupTwo);
   
    return 0;
}

//Function that returns a partition vector which is the closest to the target
vector<float> selectPartition(vector<float> startWeights, int index, float target)
{
    if(index >= startWeights.size())
        return vector<float>();

    vector<float> branch1 = selectPartition(startWeights, index + 1, target - startWeights[index]);
    branch1.push_back(startWeights[index]);

    vector<float> branch2 = selectPartition(startWeights, index + 1, target);

    float sumBranch1 = vectorSum(branch1);
    float sumBranch2 = vectorSum(branch2);

    if(absDifference(sumBranch1, target) < absDifference(sumBranch2, target))
        return branch1;
    else
        return branch2;
}

//Function that returns a partition vector that doesnt include objects of the other partition group
vector<float> selectOtherPartition(vector<float> startWeights, vector<float> groupOne)
{
    vector<float> groupTwo = startWeights;
    vector<float>::iterator iterate;

    for(int i = 0; i < groupOne.size(); i++)
    {
        for(int j = 0; j < groupTwo.size(); j++)
        {
            if(groupOne[i] == groupTwo[j])
            {
                iterate = groupTwo.begin();

                for(int k = 0; k < j; k++)
                    iterate++;

                groupTwo.erase(iterate);

                break;
            }
        }
    }

    return groupTwo;
}

//Calculates the sum of elements in a vector of type float
float vectorSum(vector<float> branch)
{
    float sum = 0;

    for(int i = 0; i < branch.size(); i++)
        sum += branch[i];

    return sum;
}

//Calculates the positive difference between two floats
float absDifference(float a, float b) 
{
	return a > b ? a - b : b - a;
}

//Prints the start weight group and then two partitions closest to the targert weight
void printResult(vector<float> startWeights, vector<float> groupOne, vector<float> groupTwo)
{
    //Print all of the weights read from the data file
    cout << "All weights: [ ";

    for(int i = 0; i < startWeights.size(); i++)
        cout << fixed << setprecision(2) << startWeights[i] << " ";

    cout << "] \t Target weight is " << fixed << setprecision(2) << vectorSum(startWeights) / 3 << endl;

    //Print first group
    cout << "First group: [ ";

    for(int i = 0; i < groupOne.size(); i++)
        cout << fixed << setprecision(2) << groupOne[i] << " ";

    cout << "] \t First group weight is " << fixed << setprecision(2) << vectorSum(groupOne) << endl;

    //Print second group
    cout << "Second group: [ ";

    for(int i = 0; i < groupTwo.size(); i++)
        cout << fixed << setprecision(2) << groupTwo[i] << " ";

    cout << "] \t Second group weight is " << fixed << setprecision(2) << vectorSum(groupTwo) << endl;

    return;
}

//Save the result to a file
void saveToFile(vector<float> startWeights, vector<float> groupOne, vector<float> groupTwo)
{
    ofstream resFile;
    resFile.open("result.txt");

    //Print all of the weights read from the data file
    resFile << "All weights: [ ";

    for(int i = 0; i < startWeights.size(); i++)
        resFile << fixed << setprecision(2) << startWeights[i] << " ";

    resFile << "] \t Target weight is " << fixed << setprecision(2) << vectorSum(startWeights) / 2 << endl;

    //Print first group
    resFile << "First group: [ ";

    for(int i = 0; i < groupOne.size(); i++)
        resFile << fixed << setprecision(2) << groupOne[i] << " ";

    resFile << "] \t First group weight is " << fixed << setprecision(2) << vectorSum(groupOne) << endl;

    //Print second group
    resFile << "Second group: [ ";

    for(int i = 0; i < groupTwo.size(); i++)
        resFile << fixed << setprecision(2) << groupTwo[i] << " ";

    resFile << "] \t Second group weight is " << fixed << setprecision(2) << vectorSum(groupTwo) << endl;
    
    cout<<"\nSuccessfully saved the result to a file"<<endl;
    resFile.close();

    return;
}