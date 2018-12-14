#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    std::map<string,int> dMap; //counting degrees here
    std::map<int,vector<string>> delta; //list of vertices with degree=key
    //dMap.count(6) == 0  <==> pas encore dans le dictionnaire
/*
    cout << dMap.count(6) << endl;
    dMap[6]=0;
    dMap.at(6)=687646;
    cout << dMap.at(6) << endl;
*/
    std::ifstream infile("conti.txt");
    string str;
    infile >> str;
    infile >> str;
    cout << str << endl;


    string a, b;
    while (infile >> a >> b)
    {
        //cout << a << " " << b << endl;
        if (dMap.count(a)==0) dMap[a]=0;
        if (dMap.count(b)==0) dMap[b]=0;
        dMap[a]=dMap[a]+1;
        dMap[b]=dMap[b]+1;
    }


    std::map<string, int>::iterator it = dMap.begin();
    while (it != dMap.end())
    {
        std::string vertex = it->first; //key
        int degree = it->second; //value
        if (delta.count(degree)==0) delta[degree]= vector<string>(1,vertex);
        else delta[degree].push_back(vertex);
        it++;
    }
    cout << "The first node with degree 2 is "<< delta[2].at(0) << endl;
    cout << "Node 1 "<< dMap["1"] << endl;
    cout << "Node 2 "<< dMap["2"] << endl;
    cout << "Thanks for using our program ! Glad it ended well." << endl;
    cout << "I hope you have a nice day." << endl;
    return 0;
}
