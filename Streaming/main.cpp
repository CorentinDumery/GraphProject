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

int memoryCount=0;


void myCopy(bool tab1[],bool tab2[],int n){ //copies tab2 into tab1 for n elements
    for (int i=0;i<n;i++) tab1[i]=tab2[i];
}

void printTab(int tab[],int size,string name){
    for (int i=0;i<size;i++){
         cout << name <<"["<<i<<"] = "<<tab[i]<<endl;
    }
}

int main()
{
    clock_t begin = clock();

    string fileName = "chicago.txt";
    //fileName = "contiguous.txt";
    //fileName = "astro.txt";
    fileName = "hamster.txt";
    fileName = "power.txt";
    fileName = "facebook.txt";


    float epsilon = 0.1;


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
    memoryCount +=2*sizeof(int);

    int a,b;
    string str = x;
    a = stoi(x);
    maxId = a;
    inFile>>b;
    if (b>maxId) maxId=b;
    numberOfEdges +=1;

    while(inFile>>a>>b){

        if (a>maxId) maxId = a;
        if (b>maxId) maxId = b;
        numberOfEdges += 1;
    }

    maxId += 1; //the last element should be included in the tabs

    cout << "maxId is "<<maxId<<endl;
    //Initializing tabs. I'll need another pass.

    int degree[maxId];
    bool isIn[maxId];
    memoryCount +=maxId*(sizeof(int)+sizeof(bool));

    for (int i=0;i<maxId;i++){
        degree[i]=0;
        isIn[i]=true;
    }

    inFile.close();
    inFile.open(fileName);

    do{
        inFile>>x;
    }while(!(('0'<=x[0])&&(x[0]<='9')));

    str = x;
    a = stoi(x);
    inFile>>b;

    cout<<"First edge read is "<<a<<" "<<b<<endl;

    degree[a]+=1;
    degree[b]+=1;


    while(inFile>>a>>b){
        degree[a]+=1;
        degree[b]+=1;
    }
    cout<<"Last edge read is "<<a<<" "<<b<<endl;

    //Now we can begin the Streaming Algorithm for Densest Subgraph

    int nEdges=numberOfEdges; //number of edges left
    cout << "Initial n of edges"<<nEdges<<endl;

    int nVertices=maxId; //number of vertices left

    cout << "Initial n of vertices"<<nVertices<<endl;


    float currentDensity = (float) nEdges /(float) nVertices;
    cout << "Initial d "<<currentDensity<<endl;


    bool answer[maxId];
    memoryCount +=maxId*sizeof(bool);
    myCopy(answer,isIn,maxId ); //copies tab2 into tab1 for n elements
    float bestDensity = currentDensity;
    cout << "Initial density "<<bestDensity<<endl;

    while (numberOfEdges>0){
        for (int i=0;i<maxId;i++){

            if (isIn[i] && degree[i]<=2*(1+epsilon)*currentDensity){
                cout << "I'm removing node "<<i<<endl;
                //removing this node, doing a pass to find its neighbors and decrease their degree
                isIn[i]=false;
                nVertices -= 1;

                inFile.close();
                inFile.open(fileName);

                do{
                    inFile>>x;
                }while(!(('0'<=x[0])&&(x[0]<='9')));

                str = x;
                a = stoi(x);

                inFile>>b;

                if (a==i && isIn[b]) {degree[b] = degree[b]-1; degree[a]=degree[a]-1; nEdges-=1;}
                if (b==i && isIn[a]) {degree[b] = degree[b]-1; degree[a]=degree[a]-1; nEdges-=1;}

                while(inFile>>a>>b){
                    if (i==3 && (a==3 || b==3)) cout<<"Found "<<a<<" "<<b<<endl;
                    if (a==i && isIn[b]) {degree[b] = degree[b]-1; degree[a]=degree[a]-1; nEdges-=1;}
                    if (b==i && isIn[a]) {degree[b] = degree[b]-1; degree[a]=degree[a]-1; nEdges-=1;}
                }
            }
        }

        if (nVertices == 0) break;
        currentDensity = (float) nEdges/(float) nVertices;
        if (currentDensity>bestDensity) {

            bestDensity = currentDensity;
            myCopy(answer,isIn,maxId);
            cout<<"I found a better graph with density "<<bestDensity<<endl;
        }

        /*
        cout<<"Nodes left after this round : "<<nVertices<<endl;
        cout<<"Edges left after this round : "<<nEdges<<endl;
        //*/
    }

    printTab(degree,maxId,"final degree");
    for (int i=0;i<maxId;i++){
        if (answer[i]) cout << "Node "<<i<<" is included"<<endl;
    }
    cout << "Final density "<<bestDensity<<endl;

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"This task took me "<<elapsed_secs<<" s"<<endl;
    cout<<"Number of nodes = "<<(maxId-1)<<endl;
    cout<<"And the input size was : maxId+numberOfEdges = "<<(maxId-1)+numberOfEdges<<endl;
    cout<<"Memory used to store graph and answer : "<<memoryCount<<" bytes"<< endl;

    cout<<sizeof(bool)<< endl;



    cout<<"Reached ending safely."<<endl;
    return 0;
}
