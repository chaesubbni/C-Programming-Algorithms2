// mimimum spanning tree
// edge �ּ� = vertex - 1
// weight �ּ�.
// Kruskal �˰��� = weight�� ���� edge���� cycle���� �ʰԲ� �����Ѵ�.
// prim �˰��� = vertex���� ����.
//prim

#include <stdio.h>

#define NV 5

void addEdge(int graph[][NV], int v1, int v2, int weight) {
	graph[v1][v2] = weight; // >0 ��ΰ� �ְ�, 0�̸� weight�� ����.
	graph[v2][v1] = weight;
}

void perform_MST_Prim(int graph[][NV], int sVertex) {
	// visited array ����.
	int visited[NV] = { 0 };
	visited[sVertex] = 1; // start vertex�� BST�� ���� �Ǿ��ٰ� ǥ��.
    
	// ã�ƾ� �Ǵ� edge ���� = NV - 1
	for (int i = 0; i < NV - 1; i++) {
		// visited --> non-visited ã��, ���� ���� weight�� ���� ���� ã�´�.
		int minDist = 99999;
		int visited_vertex = -1;
		int nonvisited_vertex = -1;
		
		for (int j = 0; j < NV; j++) {
			// visited �� ã�´�.
			if (visited[j] == 1) {
				for (int k = 0; k < NV; k++) {
					if (visited[k] == 0) { // �湮���� ���� �ֵ� �߿���... j-->k
						if (graph[j][k] > 0 && graph[j][k] < minDist) { // graph[j][k] > 0 --> j���� k�� ���� ��ΰ� �ִٴ� ��.
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
	// NV - 1 ���� ��ŭ�� edge ã��
	for (int cnt = 0; cnt < NV - 1; cnt++) {
		// weight�� ���� ���� edge�� ã�Ƽ�, MST�� ����.

		int v1 = -1;
		int v2 = -1;
		int minDist = 9999;
		for (int i = 0; i < NV; i++) { // ��� edge�鿡 ���ؼ� �˻�
			for (int j = i + 1; j < NV; j++) {
				// ��ΰ� �ְ�, ���� family�� �ƴϰ�, ���ݱ��� �˷��� minDist���� ©�� edge��
				if (graph[i][j] > 0 && family[i] != family[j] && minDist > graph[i][j]) {
					minDist = graph[i][j];
					v1 = i;
					v2 = j;
				}
			}
		}
		// ���� ª�� edge�� ã�����Ƿ�...
		printf("%d --- %d\n", v1, v2);
		//��ȥ�� ����. v1, v2������ ��ȥ
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
	//perform_MST_Prim(graph, 0); // graph�� ���ؼ�, wtart vertex = 0�� �Ͽ� MST�� Prim �˰������� ã�´�.
    // MST by Kruskal
	perform_MST_Kruskal(graph);
	return 0;
}
