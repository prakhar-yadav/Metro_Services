#include<bits/stdc++.h>
#include<string>
#include <climits>
using namespace std;
int minKey(int key[], bool mstSet[],int V)
{
int min = INT_MAX, min_index;

for (int v = 0; v < V; v++)
    if (mstSet[v] == false && key[v] < min)
        min = key[v], min_index = v;

return min_index;
}
int printMST(int parent[], int n, int **graph,string s[])
{
for (int i = 1; i < n; i++)
{
    /*
    if(parent[i]>i)
    {
        cout<<"Path of Metro  --> "<<s[i]<<"-----"<<s[parent[i]]<<".      Cost ->"<<graph[i][parent[i]]<<endl;
    }
    else
    {

    }*/
     cout<<"Path of Metro  --> "<<s[parent[i]]<<"-----"<<s[i]<<".      Cost ->"<<graph[i][parent[i]]<<endl;
}
}
void primMST(int **graph,int V,string s[])
{
    int parent[V];
    int key[V];
    bool mstSet[V];
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < V-1; count++)
    {
        int u = minKey(key, mstSet,V);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
        if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
        {
            parent[v] = u, key[v] = graph[u][v];
        }
    }
    printMST(parent, V, graph,s);
}
int main()
{
    int V,E;
    cout<<"  Enter total number of stations : ";
    cin>>V;
    cout<<"\n  Enter total no. of connections : ";
    cin>>E;
    cout<<endl;
    string s[V];
    cout<<"Enter name of stations : ";
    for(int i=0;i<V;i++)
    {
        cout<<endl<<i<<"  -->  ";
        fflush(stdin);
        getline(cin,s[i]);
    }
    int **graph=new int*[V];
    for(int i=0;i<V;i++)
    {
        graph[i]=new int[V];
        for(int j=0;j<V;j++)
        {
            graph[i][j]=0;
        }
    }

  for(int i=0;i<E;i++)
  {
      cout<<"\n  Enter 1st terminal, 2nd terminal, cost between 1st and 2nd terminal :";
      int f,s,w;
      cin>>f>>s>>w;
      graph[f][s]=w;
      graph[s][f]=w;
  }
    cout<<endl<<endl;
    primMST(graph,V,s);

    /*
    int k=1;
    do
    {
        int s;
        cout<<"\n 1. Insert Edge \n2. Delete  Edge \n 3. Exit ";
        cin>>s;
        if(s==1)
        {

        }
        else if(s==2)
        {

        }
        else if(s==3)
        {
            k=0;
        }
    }while(k==1)
    */
    return 0;
}
