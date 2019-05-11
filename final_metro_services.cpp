#include <bits/stdc++.h>

const int n=9;
using namespace std;


void func1(int arr[n][n])
{
    ofstream file;
    file.open("graph1.dot",ios::trunc);
    if(file)
    {
        file << "strict graph G {" << endl;
        file << "   node [margin=0 fontcolor=black fontsize=20 width=0.7 shape=circle style=filled]" << endl;
        file << "   edge [dir = none constraint=false]" << endl;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i!=j && arr[i][j]!=0)
                    file << "   " << i << " -- " << j << "[label=\"" << arr[i][j] << "\"]" << ";" << endl;
            }
        }
        file << "}" << endl;
    }
    file.close();
    system("circo -Tpng graph1.dot -o demo1.png");
    system("demo1.png");
}

void func2(int arr[n][n])
{
    ofstream file;
    file.open("graph2.dot",ios::trunc);
    if(file)
    {
        file << "strict graph G {" << endl;
        file << "   node [margin=0 fontcolor=black fontsize=20 width=0.7 shape=circle style=filled]" << endl;
        file << "   edge [dir = none constraint=false]" << endl;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i!=j && arr[i][j]!=0)
                    file << "   " << i << " -- " << j << "[label=\"" << arr[i][j] << "\"]" << ";" << endl;
            }
        }
        file << "}" << endl;
    }
    file.close();
    system("sfdp -Tpng graph2.dot -o demo2.png");
    system("demo2.png");
}

void func3(int arr[n][n])
{
    ofstream file;
    file.open("graph3.dot",ios::trunc);
    if(file)
    {
        file << "strict graph G {" << endl;
        file << "   node [margin=0 fontcolor=black fontsize=20 width=0.7 shape=circle style=filled]" << endl;
        file << "   edge [dir = none constraint=false]" << endl;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i!=j && arr[i][j]!=0)
                    file << "   " << i << " -- " << j << "[label=\"" << arr[i][j] << "\"]" << ";" << endl;
            }
        }
        file << "}" << endl;
    }
    file.close();
    system("sfdp -Tpng graph3.dot -o demo3.png");
    system("demo3.png");
}



/*
structure of nodes used in binomial heap 
 start= starting vertex
 endv= end vertex
 data= weight of edge connecting start and endv vertices
 cp= child pointer
 rp= right pointer
 lp= left pointer 
 
 */

struct node{
    int start,endv,data,order;
    node *cp,*rp,*lp;
};

struct pack{
    node *head,*minptr;
};

node* newnode(int start,int endv,int data)
{
    node *ptr=new node;
    ptr->data=data; ptr->start=start; ptr->endv=endv;
    ptr->order=0;
    ptr->cp=ptr->rp=ptr->lp=NULL;
    return ptr;
}

// enterData() function enter nodes into binomial heap

//minptr is a pointer of min node with min wts

pack* enterData(int start,int endv,int data,node *head,node *minptr)
{
    pack *p=new pack;
    node *newptr=newnode(start,endv,data);
    if(head==NULL){

        head=newptr;
        head->rp=head; head->lp=head;
        minptr=head;
    }
    else{
        if(head->rp==head)
            head->lp=newptr;
        newptr->lp=head;
        (head->rp)->lp=newptr;
        node *temp=head->rp;
        head->rp=newptr;
        newptr->rp=temp;
        if(data<minptr->data)
            minptr=newptr;
    }
    p->head=head;
    p->minptr=minptr;
    return p;
}



void add2(node *plug, node *socket)
{
    if(socket->cp==NULL)
    {
        socket->cp=plug;
        socket->order=1;
        plug->lp=plug;
        plug->rp=plug;
    }
    else
    {
        node *tempc=(socket->cp)->rp;
        (socket->cp)->rp=plug;
        plug->rp=tempc;
        tempc->lp=plug;
        plug->lp=socket->cp;
        (socket->order)++;
    }
}


node* add(node *temp2,node *head)
{
    if(head->data<temp2->data)
    {
        (temp2->lp)->rp=temp2->rp;
        (temp2->rp)->lp=temp2->lp;
        add2(temp2,head);
    }
    else
    {
        (head->lp)->rp=head->rp;
        (head->rp)->lp=head->lp;
         add2(head,temp2);
         head=temp2;
    }
    return head;
}

//merge two heap to make a binomial heap after extraction of minptr

node* merge(node *head,int nodenum)
{
    int maxsize=(log(nodenum)/log(2))+1;
    node *arr[maxsize];
    for(int i=0;i<maxsize;i++)
        arr[i]=NULL;

    while(1)
    {
        int order=head->order;
        if(arr[order]==NULL){
            arr[order]=head; head=head->rp;
        }
        else
        {
            if(head==arr[order])
                return head;

            head=add(arr[order],head);
            arr[order]=NULL;
        }

    }
}

//ectracting minptr
node* deletemin(node *head,node *minptr,int nodenum)
{

    if(head->rp==head)
    {
        return NULL;
    }
    if(head==minptr)
        head=head->rp;
    if(minptr->cp==NULL)
    {
            (minptr->lp)->rp=minptr->rp;
            (minptr->rp)->lp=minptr->lp;

     }
    else{

             node *temp=(minptr->cp)->lp;
             (minptr->lp)->rp=minptr->cp;
             (minptr->cp)->lp=minptr->lp;
             (minptr->rp)->lp=temp;
             temp->rp=minptr->rp;
         }
                           node *t=head;
                            while(1)
                            {
                                cout<<t->data<<"->"<<t->order<<" ";
                                t=t->rp;
                                if(t==head)
                                    break;
                            }

    head=merge(head,nodenum);
    return head;


}

//setting new minptr after extraction
node* setmin(node *head,node *minptr)
{
    if(head==NULL)
        return NULL;
    minptr->data=INT_MAX;
    node *htemp=head;
    while(1)
    {
        if(htemp->data<minptr->data)
        {
            minptr=htemp;
        }
        htemp=htemp->rp;
        if(head==htemp)
            return minptr;
    }
}


// function to find mst using binomial heap
void find_mst(int arr[n][n],int mst[n][n])
{
    pack *p;
    node *head=NULL, *minptr=NULL;
    int nodenum=0;

    int vertex[n];
    for(int i=0;i<n;i++)
        vertex[i]=0;

    vertex[0]=1;
    int counter=1,current_vrtx=0;


    while(1)
    {

        for(int i=0;i<n;i++)
        {
            if(arr[current_vrtx][i]!=0 && vertex[i]==0)
            {
                //add vertex

                 nodenum++;
                 p=enterData(current_vrtx,i,arr[current_vrtx][i],head,minptr);
                 head=p->head; minptr=p->minptr;
            }
        }
        cout<<"\n"; node *t=head;
                            while(1)
                            {
                                cout<<t->data<<"->"<<t->order<<" ";
                                t=t->rp;
                                if(t==head)
                                    break;
                            }

                            cout<<"\n";

          if(vertex[minptr->endv]==1)
          {
              while(1)
              {
                  nodenum--;
                  head=deletemin(head,minptr,nodenum);
                  minptr=setmin(head,minptr);
                  if(vertex[minptr->endv]==0)
                    break;
              }
          }
           cout<<minptr->start<<"---------->"<<minptr->endv<<"---------->"<<minptr->data<<"\n";
           mst[minptr->start][minptr->endv]=minptr->data;
           mst[minptr->endv][minptr->start]=minptr->data;
           counter++;
            if(counter==n)
            break;
            vertex[minptr->endv]=1;
            current_vrtx=minptr->endv;

            nodenum--;
            head=deletemin(head,minptr,nodenum);
            minptr=setmin(head,minptr);
                           t=head;
                           while(1)
                            {
                                cout<<t->data<<"->"<<t->order<<" ";
                                t=t->rp;
                                if(t==head)
                                    break;
                            }

                            cout<<"\n";
        cout<<"counter="<<counter<<"\n";
    }



}






int main()
{


    int arr[n][n];

   // cout<<"enter budget required to connect each stations:\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>arr[i][j];
        }
    }

    func1(arr);

    int mst[n][n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            mst[i][j]=0;
        }
    }
    find_mst(arr,mst);
    
    
    func2(mst);
    cout<<"\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<mst[i][j]<<" ";
        }
        cout<<"\n";
    }
//mst 2-d array contains mst


// continue from here...........

    int finalnet[n][n];int vertex[n]; int vrtx=0;
    for(int i=0;i<n;i++)
    {
        int count=0;
        for(int j=0;j<n;j++)
        {
            if(mst[i][j]!=0)
                count++;
        }
        if(count==1)
            vertex[vrtx++]=i;

    }
    int temp[n][n];

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            temp[i][j]=0;
        }
    }


    for(int i=0;i<vrtx;i++)
    {
        for(int j=0;j<vrtx;j++)
        {
            temp[vertex[i]][vertex[j]]=arr[vertex[i]][vertex[j]];
        }
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            finalnet[i][j]=mst[i][j]+temp[i][j];
        }
    }

    cout<<"\n";
    
    
    //final graph after adding alternates path for each metro stations
    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
           cout<<finalnet[i][j]<<" ";
        }
        cout<<"\n";
    }
    
    func3(finalnet);





}
