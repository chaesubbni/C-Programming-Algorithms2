// mimimum spanning tree
// edge 최소 = vertex - 1
// weight 최소.
// Kruskal 알고리즘 = weight가 작은 edge부터 cycle되지 않게끔 선택한다.
// prim 알고리즘 = vertex부터 시작.
//prim

#include <stdio.h>

#define NV 5

void addEdge(int graph[][NV], int v1, int v2, int weight) {
	graph[v1][v2] = weight; // >0 경로가 있고, 0이면 weight가 없다.
	graph[v2][v1] = weight;
}

void perform_MST_Prim(int graph[][NV], int sVertex) {
	// visited array 생성.
	int visited[NV] = { 0 };
	visited[sVertex] = 1; // start vertex는 BST에 포함 되었다고 표시.
    
	// 찾아야 되는 edge 개수 = NV - 1
	for (int i = 0; i < NV - 1; i++) {
		// visited --> non-visited 찾고, 가장 작은 weight를 갖는 것을 찾는다.
		int minDist = 99999;
		int visited_vertex = -1;
		int nonvisited_vertex = -1;
		
		for (int j = 0; j < NV; j++) {
			// visited 를 찾는다.
			if (visited[j] == 1) {
				for (int k = 0; k < NV; k++) {
					if (visited[k] == 0) { // 방문하지 않은 애들 중에서... j-->k
						if (graph[j][k] > 0 && graph[j][k] < minDist) { // graph[j][k] > 0 --> j에서 k로 가는 경로가 있다는 뜻.
							minDist = graph[j][k];
							visited_vertex = j;
							nonvisited_vertex = k;
						}
					}
				}
			}
		}
		printf("%d --- %d \n", visited_vertex, nonvisited_vertex);
		visited[nonvisited_vertex] = 1;
	}
}

void perform_MST_Kruskal(int graph[][NV]) {
	int family[NV] = { 0 , 1 , 2 , 3, 4 };
	// NV - 1 갯수 만큼의 edge 찾기
	for (int cnt = 0; cnt < NV - 1; cnt++) {
		// weight가 가장 작은 edge를 찾아서, MST에 포함.

		int v1 = -1;
		int v2 = -1;
		int minDist = 9999;
		for (int i = 0; i < NV; i++) { // 모든 edge들에 대해서 검사
			for (int j = i + 1; j < NV; j++) {
				// 경로가 있고, 같은 family가 아니고, 지금까지 알려진 minDist보다 짤은 edge면
				if (graph[i][j] > 0 && family[i] != family[j] && minDist > graph[i][j]) {
					minDist = graph[i][j];
					v1 = i;
					v2 = j;
				}
			}
		}
		// 가장 짧은 edge를 찾았으므로...
		printf("%d --- %d\n", v1, v2);
		//결혼식 거행. v1, v2가문의 결혼
		int old_family = family[v2];
		int new_family = family[v1];

		for (int k = 0; k < NV; k++) {
			if (family[k] == old_family) {
				family[k] = new_family;
			}
		}
	}
}


int main(void) {
	int graph[NV][NV] = { 0 };
	addEdge(graph, 0, 1, 100); // 0 -> 1 edge, weight = 100
	addEdge(graph, 0, 2, 10); // 0 -> 1 edge, weight = 100
	addEdge(graph, 1, 2, 40); // 0 -> 1 edge, weight = 100
	addEdge(graph, 1, 3, 50); // 0 -> 1 edge, weight = 100
	addEdge(graph, 2, 3, 1); // 0 -> 1 edge, weight = 100
	addEdge(graph, 3, 4, 10); // 0 -> 1 edge, weight = 100

	// MST by prim
	//perform_MST_Prim(graph, 0); // graph에 대해서, wtart vertex = 0로 하여 MST를 Prim 알고리즘으로 찾는다.
    // MST by Kruskal
	perform_MST_Kruskal(graph);
	return 0;
}
