#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

typedef struct edge_t{

    int v;//  neighbour vector
    int weight;//  weight of that path
}edge;


void add_edge(vector<vector<edge>> &graph, int first, int second, int weight){

    edge temp;

    temp.v = second;
    temp.weight = weight;

    graph[first].push_back(temp);

    temp.v = first;

    graph[second].push_back(temp);
}


void list_edges(vector<vector<edge>> graph){

    if(!graph.empty()){

        for(int i = 0; i < graph.size(); i++)
        {
            cout << "node " << i << " has links to: ";
            if(!graph[i].empty())
            {
                for(int j = 0; j < graph[i].size(); j++)
                {
                    cout << graph[i][j].v << "(" << graph[i][j].weight << ") ";
                }
                cout << endl;
            }else
            {
                cout<< " no other nodes" << endl;
            }

        }
    }else{

        std::cout<<std::endl<<"Graph is empty!"<<std::endl<<std::endl;
    }
}

void load(vector<vector<edge > > &graph){

    graph.clear();

    int case_nodes;
    int case_links;

    int first, second, weight;

    cin >> case_nodes >> case_links;

    //cout << endl << endl << "loading case with " << case_nodes << " nodes and " << case_links << " links" << endl;

    graph.resize(case_nodes);

    for(int i = 0; i < case_links; i++)
    {
        cin >> first >> second >> weight;

        add_edge(graph, first, second, weight);
    }
}


bool comparison(const edge &a, const edge &b)
{//  this is used to satisfy the heap functions parameter format
  return (a.weight > b.weight);
}

void print_mst(vector<vector<edge>> graph){

    int INF = 10000;
    vector<edge> min_heap;
    int src = 0;

    vector<int> key(graph.size(), INF);
    vector<int> parent(graph.size(), -1);
    vector<bool> inMST(graph.size(), false);
    
    edge temp;
    temp.v = src; temp.weight = 0;

    min_heap.push_back(temp);
    
    key[src] = 0;

	/* Looping till priority queue becomes empty */
	while (!min_heap.empty()){

		//create the heap
		std::make_heap(min_heap.begin(), min_heap.end(), comparison);// all new entries get sorted with make_heap()

	    // The first vertex in pair is the minimum weight
	    // vertex, extract it from the heap.
	    // vertex label is stored in destination (it
	    // is done this way to keep the vertices
	    // sorted by weight (weight is key)

  	    int u = min_heap[0].v;
	    min_heap.erase(min_heap.begin()); // we erase the first element (pop)

        inMST[u] = true; // Include vertex in MST

    // Traverse all adjacent of u
        for (auto x : graph[u]){
      // Get vertex label and weight of current adjacent of u.
        int v = x.v;
        int weight = x.weight;

      // If v is not in MST and weight of (u,v) is smaller
      // than current key of v
        if (inMST[v] == false && key[v] > weight){
            // Updating key of v
            edge temp;
            key[v] = weight;
            temp.v = v;
            temp.weight = key[v];
            min_heap.push_back(temp);
            parent[v] = u;
            }
        }
	}

    int longest_distance = 0;
	
    for(int i = 1; i < graph.size(); ++i)
    {
        if(key[i] > longest_distance)
        {
            longest_distance = key[i];
        }
    }

    cout << longest_distance << endl;

    for (int i = 1; i < graph.size(); ++i)
    {
	    // printf("%d - %d - with weight %d \n", parent[i], i, key[i]);
        cout << "(" << parent[i] << ", " << i << ", " << key[i] << ") ";
    }
    cout<<endl;

}

int main(){

    //the representation of the graph is a vector
    //each element of this vector represents a node in the graph
    // it, in turn, is a vector of connections to other nodes, along with the weights of those connections
    vector<vector<edge>> graph;

    int num_cases;
    cin >> num_cases;

    //cout << "handling " << num_cases << " case(s)" << endl;

    for(int i = 0; i < num_cases; i++)
    {
        load(graph);
        //list_edges(graph);
        print_mst(graph);
    }


}