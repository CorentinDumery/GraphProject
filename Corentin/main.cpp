#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

//linear in the size of input, and input is n+m

int n=0; //number of vertices
std::map<string,int> dMap; //counting degrees here
std::map<int,vector<string>> delta; //list of vertices with degree=key
std::map<string, vector<string>> neighborMap;
//dMap.count(6) == 0  <==> pas encore dans le dictionnaire


string popMinV(){ //Gets vertex with min degree and deletes it. if graph is empty, return "-1"

    bool testing = false;

    //pb : on dirait que je dégage les voisins du vertex aussi...

    for (int i=0;i<n+1;i++){
        if (delta.count(i)==0) {}
        else {if (delta.at(i).empty()) {}

            else {
                if (testing) cout << "Palier 1" << endl;
                string res = delta.at(i).back(); //we will delete this element
                delta.at(i).pop_back();
                for(auto const& neighbor: neighborMap[res]) { //for each neighbor, I need to delete res from neighbor list and decrease degree by one (both in dMap and delta)
                     if (testing) cout << "Palier 2" << endl;
                     vector<string> copy; //deleting res from neighborMap[neighbor]
                     for (auto const& neighborOfNeighbor:neighborMap[neighbor]){
                         if (neighborOfNeighbor != res) copy.push_back(neighborOfNeighbor);
                     }
                     neighborMap[neighbor]=copy;
                     //updating degree. First, I need to remove neighbor from its current delta division
                     if (testing) cout << "Palier 3" << endl;
                     vector<string> copy2;
                     for (auto const& truc : delta[dMap[neighbor]]){
                         if (truc != neighbor) copy2.push_back(truc);
                     }
                     if (testing) cout << "Palier 4" << endl;
                     delta[dMap[neighbor]]=copy2;
                     //then I need to put the said neighbor in a lower division :
                     delta[dMap[neighbor]-1].push_back(neighbor);
                     //finally, we can update its degree in dMap (it's useless but else we have false data stored in dMap and noone wants that)
                     dMap[neighbor]=dMap[neighbor]-1;
                }
                return res;

            }
         }
    }
    if (testing) cout << "Graph is empty" << endl;
    return "-1";
}

bool graphEmpty(){
    if (popMinV()=="-1") return false;
    else return true;
}

float rho(){ //TODO
    return 0.f;
}



int main(int argc, char *argv[])
{

    // INIT : computing dMap, neighborMap and initial delta

    std::ifstream infile("conti.txt");

    string str1,str2;
    infile >> str1 >> str2;
    cout << str1 << endl;

    string a, b;
    while (infile >> a >> b)
    {
        //cout << a << " " << b << endl;
        if (dMap.count(a)==0) {dMap[a]=0;n++;}
        if (dMap.count(b)==0) {dMap[b]=0;n++;}
        dMap[a]=dMap[a]+1;
        dMap[b]=dMap[b]+1;
        if (neighborMap.count(a)==0) neighborMap[a]=vector<string>(1,b);
        else neighborMap[a].push_back(b);
        if (neighborMap.count(b)==0) neighborMap[b]=vector<string>(1,a);
        else neighborMap[b].push_back(a);
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

    //end of INIT

    string test = popMinV();
    cout << test <<endl;
    while (test !="-1"){
        test = popMinV();
        cout << test <<endl;
    }


/*
    cout << "The first node with degree 2 is "<< delta[2].at(0) << endl;
    cout << "The first neighbor of node 1 is "<< neighborMap["1"].at(0) << endl; //attention il y a potentiellement des problèmes avec les str au début
    cout << "Node 1 "<< dMap["1"] << endl;
    cout << "Node 2 "<< dMap["2"] << endl;
    cout << "Thanks for using our program ! Glad it ended well." << endl;
    cout << "I hope you have a nice day." << endl;
*/
    return 0;
}
