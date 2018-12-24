#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <unordered_set>
#include <memory>
#include <cstdlib>
#include <climits>

using namespace std;

/* ONE PASS :

    do{
        inFile>>x;
    }while(!(('0'<=x[0])&&(x[0]<='9')));

    inFile>>a;
    inFile>>b;
    if (printing) cout<<"Reading edge "<<a<<' '<<b<<endl;

    while(inFile>>a>>b){
        if (printing) cout<<"Reading edge "<<a<<' '<<b<<endl;
    }

*/

/*
int findMinDeg(map<int,vector<string>> dict){
// find minimum degree in current graph
    int minDeg=INT_MAX;
    for(map<int,vector<string>>::iterator pt=dict.begin();pt!=dict.end();pt++){
        if(minDeg> pt->first)
            minDeg=pt->first;
    }
    return minDeg;
}
*/
/*
bool hasNode(vector<string> ll, string obj){
// determine if obj is in ll
    for(vector<string>::iterator pt=ll.begin();pt!=ll.end();pt++){
        if (*pt==obj)
            return true;
    }
    return false;
}
*/
/*
int findCurrDeg(map<int, vector<string>> dict, string tarNode){
// find current degree of tarNode
    int deg=0;
    map<int, vector<string>>::iterator pt=dict.begin();
    while((deg==0)&&(pt!=dict.end())){
        if(hasNode(pt->second,tarNode)){
            deg=pt->first;
            break;
        }
        pt++;
    }
    return deg;
}
*/
/*
vector<string> updateDictEntry(vector<string> ll, string key){
// remove key from ll
    vector<string>::iterator pt=ll.begin();
    while((*pt)!=key){
        pt++;
    }
    ll.erase(pt);
    return ll;
}
*/


void myCopy(bool tab1[],bool tab2[],int n){ //copies tab2 into tab1 for n elements
    for (int i=0;i<n;i++) tab1[i]=tab2[i];
}

int main()
{
    // read graph info from file
    // establish degree map

    string fileName = "chicago.txt";

    bool printing = false; //Do you want me to print EVERYTHING for you ?

    float epsilon = 1000.5;

    ifstream inFile;
    inFile.open(fileName);


    string x;
    do{
        inFile>>x;
    }while(!(('0'<=x[0])&&(x[0]<='9')));

    //First, I want to know the number of edges and the maxId so that I can initialize my tabs with the right size.
    //This takes a whole pass, but we won't need to resize our tabs thanks to that.

    int numberOfEdges = 0;
    int maxId = 0; //hypothesis: the nodes' names are positive numbers

    int a,b;
    inFile>>a;
    maxId = a;
    inFile>>b;
    if (b>maxId) maxId=b;
    numberOfEdges +=1;
    if (printing) cout<<"Edge "<<a<<' '<<b<<endl;

    while(inFile>>a>>b){
        if (printing) cout<<"Edge "<<a<<' '<<b<<endl;
        if (a>maxId) maxId = a;
        if (b>maxId) maxId = b;
        numberOfEdges += 1;
    }

    maxId += 1; //the last element should be included in the tabs

    //Initializing tabs. I'll need another pass.

    int degree[maxId];
    bool isIn[maxId];

    for (int i=0;i<maxId;i++){
        degree[i]=0;
        isIn[i]=true;
    }

    inFile.close(); //maybe there's a better way to do that
    inFile.open(fileName);

    do{
        inFile>>x;
    }while(!(('0'<=x[0])&&(x[0]<='9')));

    inFile>>a;
    inFile>>b;
    if (printing) cout<<"Reading edge "<<a<<' '<<b<<endl;

    while(inFile>>a>>b){
        if (printing) cout<<"Reading edge "<<a<<' '<<b<<endl;
        degree[a]+=1;
        degree[b]+=1;
    }


    //Now we can begin the Streaming Algorithm for Densest Subgraph

    int nEdges=numberOfEdges; //number of edges left
    int nVertices=maxId; //number of vertices left

    float currentDensity = nEdges/nVertices;


    bool answer[maxId];
    myCopy(answer,isIn,maxId ); //copies tab2 into tab1 for n elements
    float bestDensity = currentDensity;

    while (numberOfEdges>0){
        for (int i=0;i<maxId;i++){

            if (isIn[i] && degree[i]<=2*(1+epsilon)*currentDensity){

                //removing this node, doing a pass to find its neighbors and decrease their degree
                isIn[i]=false;
                nVertices -= 1;

                do{
                    inFile>>x;
                }while(!(('0'<=x[0])&&(x[0]<='9')));

                inFile>>a;
                inFile>>b;
                if (printing) cout<<"Reading edge "<<a<<' '<<b<<endl;

                if (a==i && isIn[b]) {degree[b] -= 1; nEdges-=1;}
                if (b==i && isIn[a]) {degree[a] -= 1; nEdges-=1;}

                while(inFile>>a>>b){
                    if (printing) cout<<"Reading edge "<<a<<' '<<b<<endl;
                    if (a==i && isIn[b]) {degree[b] -= 1; nEdges-=1;}
                    if (b==i && isIn[a]) {degree[a] -= 1; nEdges-=1;}
                }
            }
        }

        if (nVertices == 0) break;
        currentDensity = nEdges/nVertices;
        if (currentDensity>bestDensity) {
            cout<<"I found a better graph"<<endl;
            bestDensity = currentDensity;
            myCopy(answer,isIn,maxId);
        }

        cout<<"Nodes left after this round : "<<nVertices<<endl;
        cout<<"Edges left after this round : "<<nEdges<<endl;

    }


    for (int i=0;i<maxId;i++){
        if (answer[i]) cout << "Node "<<i<<" is included"<<endl;
    }
    cout << "Final density "<<bestDensity<<endl;










/*




    nodes={a,b};
    degDictTmp[a]=1;
    degDictTmp[b]=1;

    // count simultaneously the degree of each node
    int numNode=2;
    while(inFile>>a>>b){
        cout<<a<<' '<<b<<endl;
        if (!degDictTmp.count(a)){
            degDictTmp[a]=1;
            numNode+=1;
        }
        else
            degDictTmp[a]+=1;
        if (!degDictTmp.count(b)){
            degDictTmp[b]=1;
            numNode+=1;
        }
        else
            degDictTmp[b]+=1;
        if(!nodes.count(a))
            nodes.insert(a);
        if(!nodes.count(b))
            nodes.insert(b);
    }

    cout<<"------------"<<endl;
    // estalish degDict with degDictTmp
    for(int i=1;i<=numNode;++i)
        degDict[i]=vector<string>();

    auto pt=degDictTmp.begin();
    while(pt!=degDictTmp.end()){
        degDict[pt->second].push_back(pt->first);
        cout<<pt->first<<' '<<pt->second<<endl;
        pt++;
    }

    cout<<"-------------"<<endl;


    cout<<nodes.size()<<endl;
    cout<<degDict.size()<<endl;
    for(auto pt=degDict.begin();pt!=degDict.end();pt++){
        cout<<pt->first<<' '<<pt->second.size()<<endl;
    }

*/

    cout<<"Reached ending safely."<<endl;
    return 0;
}
