#include <stdio.h>
#define NV 7 // 0�� �ȽἭ vertex�� 6�������� 1�� ���ߴ�.

typedef struct {
	int prev; // ������ ��ģ vertex ��ȣ
	int dist; // start vertex-> ���������� �Ÿ�
	int done;// �ִܰŸ��� ã�Ҵ°�
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

//dtable���� dist�� ���� ª��, done = 0�� vertex�� ã�Ƽ� �� ��ȣ ��ȯ,
// ���� ��� vertex���� done =1 �̸� -1�� ��ȯ.

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
	// start vertex���� ���� �� �� �ִ� vertex�鿡 ���ؼ� dtable�� �����Ѵ�.
	
	dtable[start_vertex].done = 1;
	for (int i = 0; i < NV; i++) {
		if (graph[start_vertex][i] != -1) {
			dtable[i].dist = graph[start_vertex][i];
			dtable[i].prev = start_vertex;
		}
	}

	
	//detable���� ���� ª�� �Ÿ��� ���� vertex�̸鼭, done = 0�� vertex�� ã�´�.

	while (1) {

		int v = find_shortext_path_vertex(dtable);
		if (v == -1) {
			break;
		}
		dtable[v].done = 1;
		//v�� ���ؼ� ���ŵǴ� ��ΰ� �� ª�� vertex���� ã�Ƽ� �ش� dtable�� ����.
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