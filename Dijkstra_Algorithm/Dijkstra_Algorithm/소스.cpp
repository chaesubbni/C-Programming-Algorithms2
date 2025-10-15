#include <stdio.h>
#define NV 7 // 0은 안써서 vertex가 6개이지만 1을 더했다.

typedef struct {
	int prev; // 직전에 거친 vertex 번호
	int dist; // start vertex-> 목적지까지 거리
	int done;// 최단거리를 찾았는가
}DijkstraElement;



void addEdge(int graph[][NV], int v1, int v2, int weight) {
	graph[v1][v2] = weight;
	graph[v2][v1] = weight;
	return;
}

void initDTable(DijkstraElement dtable[]) {
	for (int i = 0; i < NV; i++) {
		dtable[i].prev = -1;
		dtable[i].dist = 9999;
		dtable[i].done = 0;
	}
	return;
}

//dtable에서 dist가 가장 짧고, done = 0인 vertex를 찾아서 그 번호 반환,
// 만약 모든 vertex들의 done =1 이면 -1을 반환.

int find_shortext_path_vertex(DijkstraElement dtable[]) {

	int vertex_idx = -1;
	int vertex_dist = 9999;

	for (int i = 0; i < NV; i++) {
		if (dtable[i].done == 0 && dtable[i].dist < vertex_dist) {
			vertex_dist = dtable[i].dist;
			vertex_idx = i;
		}
	}

	return vertex_idx;
}

void showDtable(DijkstraElement dtable[]) {
	
	for (int i = 1; i < NV; i++) {
		printf("%5d ", i);
	}
	printf("---vertex---\n");

	for (int i = 1; i < NV; i++) {
		printf("%5d ", dtable[i].prev);
	}
	printf("------prev---\n");

	for (int i = 1; i < NV; i++) {
		printf("%5d ", dtable[i].dist);
	}
	printf("-----dist------\n");

	for (int i = 1; i < NV; i++) {
		printf("%5d ", dtable[i].done);
	}
	printf("----done--\n");


}

void printgraph(int graph[][NV]) {
	for (int i = 0; i < NV; i++) {
		for (int j = 0; j < NV; j++) {
			printf("%d ", graph[i][j]);
		}
		printf("%\n");
	}
}

void initgraph(int graph[][NV]) {
	for (int i = 0; i < NV; i++) {
		for (int j = 0; j < NV; j++) {
			graph[i][j] = -1;
		}
	}
}







int main(void) {
	DijkstraElement dtable[NV];
	int graph[NV][NV];
	initgraph(graph);
	addEdge(graph, 1, 2, 3);
	addEdge(graph, 1, 4, 15);
	addEdge(graph, 2, 4, 2);
	addEdge(graph, 2, 3, 30);
	addEdge(graph, 4, 5, 1);
	addEdge(graph, 3, 5, 3);
	addEdge(graph, 3, 6, 4);
	addEdge(graph, 5, 6, 20);

	

	initDTable(dtable);

	int start_vertex = 1;
	// start vertex에서 직접 갈 수 있는 vertex들에 대해서 dtable을 갱신한다.
	
	dtable[start_vertex].done = 1;
	for (int i = 0; i < NV; i++) {
		if (graph[start_vertex][i] != -1) {
			dtable[i].dist = graph[start_vertex][i];
			dtable[i].prev = start_vertex;
		}
	}

	
	//detable에서 가장 짧은 거리를 가진 vertex이면서, done = 0인 vertex를 찾는다.

	while (1) {

		int v = find_shortext_path_vertex(dtable);
		if (v == -1) {
			break;
		}
		dtable[v].done = 1;
		//v를 통해서 갱신되는 경로가 더 짧은 vertex들을 찾아서 해당 dtable을 갱신.
		for (int i = 0; i < NV; i++) {
			if (dtable[i].done==0 && graph[v][i] != -1 && (dtable[v].dist + graph[v][i] < dtable[i].dist)) {
				dtable[i].dist = dtable[v].dist + graph[v][i];
				dtable[i].prev = v;
			}
		}


	}


	showDtable(dtable);

	return 0;
}