#include <iostream>
#include <string>
#include <bits/stdc++.h> 
using namespace std;

typedef struct multi_graph
{
	int V;
	vector<char> color;
	vector<int> red_ind;
	vector<int> blue_ind;
	// vector<vector<int> > adj;
	vector<int> adj;
} graph;

// void addEdge(graph *G, int u, int v){
 
//     G->adj[u].push_back(v); 
//     G->adj[v].push_back(u); 
// }

void addEdge(vector<int> adj[], int u, int v){
 
    adj[u].push_back(v); 
    adj[v].push_back(u); 
}

// void prngraph(graph *G){

//     for (int v=0; v<G->V; ++v){
    
//         cout << "\n" << G->color[v] << " " << v << " -> "; 
        
//         for(int i=0; i<G->adj[v].size(); ++i){
//         	cout << G->adj[v][i];
//         	if (i!=G->adj[v].size()-1) cout << ", ";
//         }
//         // cout << endl; 
//     } 
// }

void prngraph(vector<int> adj[], vector<string> color, int V){

    for (int v=0; v<V; ++v){
    
        cout << "\n" << "[" << color[v] << "] " << v << " -> "; 
        
        for(int i=0; i<adj[v].size(); ++i){
        	cout << adj[v][i];
        	if (i!=adj[v].size()-1) cout << ", ";
        }
        // cout << endl; 
    } 
}

void prnsubgraphs(vector<int> adj[], vector<string> color, vector<int> ind, int V){

	for (int v=0; v<V; ++v){
    
        cout << "\n" << "[" << color[ind[v]] << "] " << ind[v] << " -> "; 
        
        for(int i=0; i<adj[v].size(); ++i){
        	cout << adj[v][i];
        	if (i!=adj[v].size()-1) cout << ", ";
        }
        // cout << endl; 
    } 
}

void getcolgraph(vector<int> adj[], vector<int> sub[], vector<string> color, int V, string c){

	int subgraph_count = 0;

	for (int v=0; v<V; ++v){

		if(color[v]==c){
    
	        // cout << "\n" << "[" << color[v] << "] " << v << " -> "; 
	        
	        for(int i=0; i<adj[v].size(); ++i){
	        	if(color[adj[v][i]]==c) sub[subgraph_count].push_back(adj[v][i]);
	        	// cout << adj[v][i];
	        	// if (i!=adj[v].size()-1) cout << ", ";
	        }
	        subgraph_count++;
	    }
    }
}

void DFSCycle(vector<int> adj[], int u, int p, int color[], int mark[], int par[], int& cyclenumber){
   
	if (color[u] == 2) {
		return;
	}

	if (color[u] == 1) {
		cyclenumber++;
		int cur = p;
		mark[cur] = cyclenumber;
		while (cur != u) {
			cur = par[cur];
			mark[cur] = cyclenumber;
		}
		
		return;
	}

	par[u] = p;
	color[u] = 1;
	for (int i=0; i<adj[u].size(); ++i){
		int v = adj[u][i];
		if (v == par[u]){
			continue;
		}
		
		DFSCycle(adj, v, u, color, mark, par, cyclenumber);
	}
	
	color[u] = 2;
}

void printCycles(vector<int> cycles[], int edges, int mark[], int& cyclenumber){
   
	for (int i = 1; i <= edges; i++){
		if (mark[i] != 0)
			cycles[mark[i]].push_back(i);
	}

	for (int i = 1; i <= cyclenumber; i++){
		cout << "Cycle " << i << ": ";
		for (int j=0; j<cycles[i].size(); ++j)
			cout << cycles[i][j] << " ";
		cout << endl;
	}
}

int main(){

	int n;
	// I have read the graph inputs through main as I didn't use a separate data-type.
	cin >> n;
	vector<string> cols(n);
	vector<int> adj[n];
	vector<int> red_ind;
	vector<int> blue_ind;
	// graph *G = (graph *)malloc(sizeof(graph));
	// G->V = n;
	// for(int i=0; i<n; ++i){
	// 	G->adj.push_back(i);
	// }
	
	// for(int i=0; i<n; ++i){

	// 	cin >> color;
	// 	G->color.push_back(color);

	// }
	for(int i=0; i<n; ++i) cin >> cols[i];
	for(int i=0; i<n; ++i){
		if (cols[i]=="r") red_ind.push_back(i);
		else blue_ind.push_back(i);
	}

	int e1, e2;

	int edges = 0;
	
	while(1){		
		cin >> e1;
		if(e1==-1) break;
		cin >> e2;
		addEdge(adj, e1, e2);
		edges++;
	}

	cout << "+++ Original graph (G)" << endl;
	prngraph(adj, cols, n);
	cout << "\n";
	
	vector<int> GR[red_ind.size()];
	vector<int> GB[blue_ind.size()];
	
	cout << "\n+++ Red subgraph (GR)" << endl;
	getcolgraph(adj, GR, cols, n, "r");
	prnsubgraphs(GR, cols, red_ind, red_ind.size());
	cout << "\n";
	cout << "\n+++ Blue subgraph (GB)" << endl;
	getcolgraph(adj, GB, cols, n, "b");
	prnsubgraphs(GB, cols, blue_ind, blue_ind.size());
	cout << "\n";

	int color[n]; 
    int par[n]; 
  
    int mark[n]; 
  
    int cyclenumber = 0; 
    vector<int> cycles[n];

    // DFSCycle(adj, 1, 0, color, mark, par, cyclenumber); 
    // printCycles(cycles, edges, mark, cyclenumber);

	return 0;
}