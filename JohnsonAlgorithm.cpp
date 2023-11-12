#include<iostream>
using namespace std;
#define INF 999
template <class t>
class algorithm
{
protected:
    int v,e;
    t graph[10][10],graph1[10][10];
    t **edges, *dist, *dis;
public:
    algorithm()
    {
        v=0;
        e=0;
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                graph1[i][j]=0;
        edges=new t*[20];
        for(int i=0;i<20;i++)
            edges[i]=new t [3];
        dist=new t[v+1];
        dis=new t[v];
        for(int i=0;i<v+1;i++)
            dist[i]=INF;
        dist[v]=0;
    }
    algorithm(int a,int b)
    {
        v=a;
        e=b;
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                graph1[i][j]=0;
        edges=new t*[20];
        for(int i=0;i<20;i++)
            edges[i]=new t [3];
        dist=new t[v+1];
        dis=new t[v];
        for(int i=0;i<v+1;i++)
            dist[i]=INF;
        dist[v]=0;
    }
    void read(int v)
    {
        for(int i=0;i<v;i++)
            for(int j=0;j<v;j++)
                cin>>graph[i][j];
    }
    int mindistance(t d[],int visit[]);
    void dijkstra(int src);
    void append(int a,int b,t c);
    void append1(int a,int b,t k);
    void reduce(int src,int des,t weight);
    void bellmanford();
    void johnson();
};
template <class t>
int algorithm<t>::mindistance(t d[],int visit[])
{
    int minimum=INF;
    int minVertex=0;
    for(int i=0;i<v;i++)
    {
        if(minimum>d[i] && visit[i]==0)
        {
            minimum=d[i];
            minVertex=i;
        }
    }
    return minVertex;
}
template <class t>
void algorithm<t>::dijkstra(int src)
{
    static int visit[10];
    for(int i=0;i<v;i++)
        visit[i]=0;
    t dist1[v];
    for(int i=0;i<v;i++)
        dist1[i]=INF;
    dist1[src]=0;
    for(int i=0;i<v;i++)
    {
        int curver=mindistance(dist1,visit);
        visit[curver]=1;
        for(int j=0;j<v;j++)
        {
            if((visit[j]==0)&&(dist1[j]>(dist1[curver]+graph1[curver][j])&&(graph[curver][j]!=0)))
               dist1[j]=dist1[curver]+graph1[curver][j];
        }
    }
    for(int ver=0;ver<v;ver++)
        cout<<"\nVertex "<<ver<<": "<<dist1[ver];
}
template <class t>
void algorithm<t>::append(int a,int b,t k)
{
    static int c=0;
    edges[c][0]=a;
    edges[c][1]=b;
    edges[c][2]=k;
    c++;
}
template <class t>
void algorithm<t>::append1(int a,int b,t k)
{
    static int d=e;
    edges[d][0]=a;
    edges[d][1]=b;
    edges[d][2]=k;
    d++;
}
template <class t>
void algorithm<t>::reduce(int src,int des,t weight)
{
    if((dist[src]!=INF)&&(dist[src]+weight<dist[des]))
        dist[des]=dist[src]+weight;
}
template <class t>
void algorithm<t>::bellmanford()
{
    for(int i=0;i<v;i++)
        append1(v,i,0);

    for(int k=0;k<v;k++)
    {
        for(int i=0;i<v+e;i++)
        {
            int src=edges[i][0];
            int des=edges[i][1];
            t weight=edges[i][2];
            reduce(src,des,weight);
        }
    }
    for(int i=0;i<v;i++)
        dis[i]=dist[i];
}
template <class t>
void algorithm<t>::johnson()
{
    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
            if(graph[i][j]!=0)
                append(i,j,graph[i][j]);
        }
    }

    bellmanford();
    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
            if(graph[i][j]!=0)
                graph1[i][j]=(graph[i][j]+dis[i]-dis[j]);
        }
    }
    cout<<"\n\nThe modified Graph is :\n";
    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
            cout<<graph1[i][j]<<" ";
        cout<<endl;
    }
    cout<<"_____________________________________________________";
    for(int src=0;src<v;src++)
    {
        cout<<"\n\nShortest Distance with vertex "<<src<<" as the source:\n";
        dijkstra(src);
        cout<<"\n_____________________________________________________";
    }
}
int main()
{
        int v,e,c;
        cout<<"Enter the number of vertices: ";
        cin>>v;
        try
        {
            if(v>10)
                throw 5;
            else
            {
                cout<<"Enter the number of edges: ";
                cin>>e;
                cout<<"_____________________________________________________";
                cout<<"\n1.Integer graph\n2.Float graph\n";
                cout<<"Enter your choice: ";
                cin>>c;
                switch(c)
                {
                    case 1:
                    {
                        algorithm<int> a(v,e);
                        cout<<"_____________________________________________________";
                        cout<<"\nEnter the cost matrix:\n";
                        a.read(v);
                        cout<<"_____________________________________________________";
                        a.johnson();
                        break;
                    }
                    case 2:
                    {
                        algorithm<float> b(v,e);
                        cout<<"_____________________________________________________";
                        cout<<"\nEnter the cost matrix:\n";
                        b.read(v);
                        cout<<"_____________________________________________________";
                        b.johnson();
                        break;
                    }

                }
            }
        }
        catch(int a)
        {
            cout<<"No of vertices cannot be greater than 10. Error.\n";
            cout<<"_____________________________________________________\n";
            main();
        }

        return 0;
}


