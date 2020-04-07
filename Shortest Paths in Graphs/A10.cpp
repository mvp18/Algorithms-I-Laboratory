#include <iostream>
#include <limits.h>
#include <bits/stdc++.h> 
using namespace std;

#define INF INT_MAX

typedef struct Graph
{
	int C;
	char **airline;
	int **ticket;
} graph;

graph* initGraph(int V){

	int i, j;
	
	graph* G = (graph *) malloc(sizeof(graph));
	G->C = V;

	G->airline = (char **)malloc(V*sizeof(char *));
	G->ticket = (int **)malloc(V*sizeof(int *));

	for(i=0; i<V; ++i){
		G->airline[i] = (char *)malloc(V*sizeof(char));
		G->ticket[i] = (int *)malloc(V*sizeof(int));
	}

	for(i=0; i<V; ++i){
		for(j=0; j<V; ++j){
			if(i==j){
				G->airline[i][j] = 's';
				G->ticket[i][j] = 0;
			}
			else{
				G->airline[i][j] = '-';
				G->ticket[i][j] = INF;
			}
		}
	}

	return G;
	}

void addEdge(graph *G, int v1, int v2, int price, char air){

	G->airline[v1][v2] = air;
	G->ticket[v1][v2] = price;
}

graph* readgraph(int V){

	graph* G = initGraph(V);
	int v1, v2, price;
	char air;
	while(1){
		cin >> v1;
		if(v1==-1) break;
		cin >> v2 >> price >> air;
		addEdge(G, v1, v2, price, air);
	}

	return G;
}

void prngraph(graph *G){

	int i, j;
	for(i=0; i<G->C; ++i){
		cout << i << " ->	";
		for(j=0; j<G->C; ++j){
			if((i!=j) && (G->airline[i][j]!='-'))
				cout << j << "(" << G->ticket[i][j] << ", " << G->airline[i][j] << ")	";
		}
		cout << "\n";
	}
	cout << "\n\n";
}

graph* getAIgraph(graph *G){

	int i, j;
	graph* H = initGraph(G->C);
	for(i=0; i<H->C; ++i){
		for(j=0; j<H->C; ++j){
			if((i!=j) && (G->airline[i][j]=='a')){
				H->airline[i][j] = G->airline[i][j];
				H->ticket[i][j] = G->ticket[i][j];
			}
		}
	}
	
	return H;
}

void print_ratechart(int **Cx, int V){

	cout << "     ";
	int i, j;
	for(i=0; i<V; ++i) cout << i << "     ";
	cout << "\n";
	for(i=0; i<V; ++i){
		cout << i << " -> ";
		for(j=0; j<V; ++j){
			if (Cx[i][j]==INF) cout << "----- ";
			else cout << Cx[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n\n";
}

int** APSP(graph *H){

	int i, j, k;
	int **C1 = (int **)malloc(H->C*sizeof(int *));
	for(i=0; i<H->C; ++i){
		C1[i] = (int *)malloc(H->C*sizeof(int));
	}

	for(i=0; i<H->C; ++i){
		for(j=0; j<H->C; ++j){
			C1[i][j] = H->ticket[i][j];
		}
	}

	for(k=0; k<H->C; ++k){
		for(i=0; i<H->C; ++i){
			for(j=0; j<H->C; ++j){
				if((C1[i][k]!=INF) && (C1[k][j]!=INF)){
					if(C1[i][k] + C1[k][j] < C1[i][j]) C1[i][j] = C1[i][k] + C1[k][j];
				}
			}
		}
	}
	
	print_ratechart(C1, H->C);

	return C1;
}

void APSPone(graph *G, int **C1){

	int i, j, k, l;
	int **C2 = (int **)malloc(G->C*sizeof(int *));
	for(i=0; i<G->C; ++i){
		C2[i] = (int *)malloc(G->C*sizeof(int));
	}

	for(i=0; i<G->C; ++i){
		for(j=0; j<G->C; ++j){
			if (C1[i][j]==INF){
				int min_kl = INF;
				int new_cost;
				for(k=0; k<G->C; ++k){
					for(l=0; l<G->C; ++l){
						if((G->airline[k][l]=='n') && (C1[i][k]!=INF) && (C1[l][j]!=INF)){
							new_cost = C1[i][k]+G->ticket[k][l]+C1[l][j];
							if (new_cost<min_kl) min_kl = new_cost;
						}
					}
				}
				
				C2[i][j] = min_kl;
			}
			else C2[i][j] = C1[i][j];

		}
	}

	print_ratechart(C2, G->C);
}

void APSPany(graph *G, int **C1){

	int i, j, k;
	int **C3 = (int **)malloc(G->C*sizeof(int *));
	int **C4 = (int **)malloc(G->C*sizeof(int *));
	for(i=0; i<G->C; ++i){
		C3[i] = (int *)malloc(G->C*sizeof(int));
		C4[i] = (int *)malloc(G->C*sizeof(int));
	}

	for(i=0; i<G->C; ++i){
		for(j=0; j<G->C; ++j){
			C4[i][j] = G->ticket[i][j];
		}
	}

	for(k=0; k<G->C; ++k){
		for(i=0; i<G->C; ++i){
			for(j=0; j<G->C; ++j){
				if((C4[i][k]!=INF) && (C4[k][j]!=INF)){
					if(C4[i][k] + C4[k][j] < C4[i][j]) C4[i][j] = C4[i][k] + C4[k][j];
				}
			}
		}
	}

	for(i=0; i<G->C; ++i){
		for(j=0; j<G->C; ++j){
			if (C1[i][j]==INF) C3[i][j] = C4[i][j];
			else C3[i][j] = C1[i][j];
		}
	}

	print_ratechart(C3, G->C);
}

int main(){

	int n;
	cin >> n;
	graph* G = readgraph(n);
	cout << "+++ Original graph\n";
	prngraph(G);
	graph* H = getAIgraph(G);
	cout << "+++ AI subgraph\n";
	prngraph(H);
	cout << "+++ Cheapest AI prices\n";
	int** C1 = APSP(H);
	cout << "+++ Cheapest prices with at most one non-AI leg\n";
	APSPone(G, C1);
	cout << "+++ Cheapest prices with any number of non-AI legs\n";
	APSPany(G, C1);
	return 0;
}