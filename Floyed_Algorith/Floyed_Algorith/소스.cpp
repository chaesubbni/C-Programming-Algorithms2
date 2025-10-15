
// Dijkstra 알고리즘 - 한계: 출발점 지정, 나머지 모든 지점까지 최단.
// Floyd 알고리즘 = 모든 점 사이의 최단 경로.

// k는 거쳐가는 것.

#include <stdio.h>
#define NV 4

int graph[NV][NV];

int floyd_graph[NV][NV];

void addEdge(int v1, int v2, int weight) {
	graph[v1][v2] = weight;
	graph[v2][v1] = weight;
}

void initFloydgraph(void) {
	for (int i = 0; i < NV; i++) {
		for (int j = 0; j < NV; j++) {
			if (i == j) {
				floyd_graph[i][j] = 0;
			}
			else if (graph[i][j] > 0) {
				floyd_graph[i][j] = graph[i][j];
			}
			else {
				floyd_graph[i][j] = 9999;
			}
		}
	}
}

int main(void) {
	
	addEdge(0, 1, 1);
	addEdge(0, 3, 1);
	addEdge(1, 2, 1);

	initFloydgraph();
	// floyd 알고리즘 돌리기
	for (int k = 0; k < NV; k++) { // 모든 중간노드
		// 모든 vertex쌍에 대해서
		for (int i = 0; i < NV; i++) {
			for (int j = 0; j < NV; j++) {
				if (floyd_graph[i][j] > floyd_graph[i][k] + floyd_graph[k][j]) {
					floyd_graph[i][j] = floyd_graph[i][k] + floyd_graph[k][j];
				}
			}
		}
	}
	
	for (int i = 0; i < NV; i++) {
		for (int j = 0; j < NV; j++) {
			printf("%d    ", floyd_graph[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < NV; i++) {
		for (int j = 0; j < NV; j++) {
			printf("%d    ", graph[i][j]);
		}
		printf("\n");
	}

	return 0;
}