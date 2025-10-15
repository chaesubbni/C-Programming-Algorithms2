#include <stdio.h>
#include <stdlib.h>
#define NUM_VTX 6

// �׷���. ����Ǿ� �ִ� ���� ���� ���踣�� ǥ���ϴ� �ڷᱸ��. �׷����� ��) tree, ����ö �뼱��. 
// ��, ����(link) �� ������ ���� �� �׷���
// �׷��� G�� V, E�� ǥ��. V(node) ����. E(edge, link) ����, ��ũ.
// ��߿��� �������� �־����� ����� ȯ���ؾ��ϴ��� ¥���ϴ� ����.
// ������(undirect) �׷��� , (A,B) �� ǥ��-������ ���� ��������� ���� ����
// ����(direct) �׷���, <A,B>�� ǥ��- ������ ���� ���� �������θ� �� �� ����.
// ����ġ �׷��� - ������ ����̳� ����ġ�� �Ҵ�� �׷���. �� ���� ���� �Ÿ��� ����� ǥ���� �� ����.
// ���� ����. adjacent vertex. �������� ����Ǿ� ����
// ����. �ϳ��� ������ ����� �ٸ� ������ ��. ���� ���� �׷����� ���������� �������� ����. ��������, ��������
//�׷����� ���. �׷����� ���� s ���� ���� e ������ ���
// �ܼ� ���. ��� �߿��� �ݺ��Ǵ� ������ ���� ���
// ����Ŭ. ���� ������ ���� ������ ������ ���
// ���� �׷���. 
// Ʈ��. ���� �׷���. �׷����� Ư���� ���·μ� ����Ŭ�� ������ �ʴ� ���� �׷���.
// ���� �׷��� - - ��� ������ ���� ����Ǿ� �־�� �Ѵ�
// �׷��� ǥ�� ���. 2���� ��ķ� ǥ��. or ��������Ʈ. �� linked list�� ǥ��
// sll�� ǥ��
// DFS - ���� �켱 Ž�� - stack ���
// BFS - ���� �켱 Ž�� - que ���

// �迭�� �׷��� ����----------------------- ��� ���� edge�� ���� ��
/*
int graph[NUM_VTX][NUM_VTX]; // �۷ι� ������ �ڵ����� 0���� �ʱ�ȭ!!!!.

void addEdge(int v1, int v2) {
	graph[v1][v2] = 1;
	graph[v2][v1] = 1;
	return;
}

int isThereEdge(int v1, int v2) { // �� ������ ���� ����Ǿ� �ֳ�???
	return graph[v1][v2]; // �ش� �迭�� 1�̸� ��!!!, �ƴϸ� �ƴϿ�!!
}

*/

// ���� ����Ʈ�� ���� dege�� ���� ���� ��
// edge -undirected graph, directed graph, weighted graph.
// �׷��� Ž��: ��� vertex�� �湮�ϴ� ���, DFS- depth first search-stack, BFS-breadth first search-que.  Ư�� vertex���� �� �� �ִ� vertex���� ��� ã�� ���ؼ�. height(����Ʈ) linear(���Ͼ�)
struct node{
	int vtx;
	struct node* next;
};

struct node* graph[NUM_VTX];

int stack_dfs[NUM_VTX];
int top = -1;

void push(int _v) {
	if (top == NUM_VTX - 1) {
		return;
	}

	top++;
	stack_dfs[top] = _v;
	return;
}

int pop(void) {
	if (top == -1) {
		return -999;
	}

	int res = stack_dfs[top];
	top--;
	return res;
}

// BFS�� ���� que
int que_bfs[NUM_VTX];
int front = 0;
int rear = 0;

void enque(int _v) {
	if (front == (rear + 1) % NUM_VTX) {
		return;
	}
	que_bfs[rear] = _v;
	rear = (rear + 1)%NUM_VTX;
}

int deque(void) {
	if (front == rear) {
		return -999;
	}
	int res = que_bfs[front];
	front = (front + 1) % NUM_VTX;
	return res;
}



// stack�ȿ� v�� �̹� ������ 1, �ƴϸ� 0
int checkDuplication(int v) {
	if (top == -1) {
		return 0;
	}
	for (int i = 0; i <= top; i++) {
		if (stack_dfs[i] == v) {
			return 1;
		}
	}
	return 0;
}


// _v���� �����Ͽ�, DFS ����
void do_DFS(int _v) {
	// 1.stack_dfs: push, pop, checkduplication
	// 2. �湮�ߴ��� ���θ� ��Ÿ���� 1���� �迭(visited)
	int visited[NUM_VTX] = { 0 }; // ��δ� �湮���� �ʾ���.

	// ���� vertex�� stack�� �ִ´�.
	// �ݺ� -- ������ �� ������.
	// ���ÿ��� pop�Ѵ�. -- m
	// m�� �湮�ߴٰ� ǥ���ϰ�,
	// m�� ȭ�鿡 ���
	// for (m�� ����� ������ vertex�� ���ؼ� )
	//    if( stack �� ����, visited�� �ƴϸ� --> push)
	push(_v);
	while (1) {
		int m = pop();
		if (m == -999) {
			break;
		}
		if (visited[m] == 0) {
			visited[m] = 1;
			printf("%d vertex�� �湮���� \n", m);
		}
		struct node* _cur = graph[m];
		while (_cur != 0) {
			if (visited[_cur->vtx] == 0) {
				push(_cur->vtx);
			}
			_cur = _cur->next;
		}
	}
}

// spanning tree, ����Ʈ��. - ��� vertex���� ����� subgraph. ���� �Ǿ� �ֱ⸸ �ϸ� �ȴ�.
// minimum spanning tree, �ּҽ���Ʈ��.- �ּ����� edge������ ��� vertex�� �����ϴ� spanning tree. �ּ����� edge���� = vertex���� - 1, ���� weighted �׷������ �ϸ�, MST�� weight�� ���� �ּ�.
// MST�� ����.- �ּ� ������� ���ΰǼ�, �ּ� ������� ��Ʈ��ũ�� �Ǽ�
// MST �˰���. - Prim, Kruskal. -----------cycle�� �����Ǹ� �ȵȴ�.
//prim. --- 3������ ��귮�� �ʹ� ����. (node�� ���� ��)
//1. ���� vertex�� ���Ѵ�. 2. ���� vertex�� '����' �Ǿ��ٰ� ǥ���Ѵ�. 3. ���� vertex���� ������ vertex�� ����� edge�߿� ���� ���� weight�� ���� edge�� ã�´�.
//4. edge�� ����� ������ vertex�� ���ԵǾ��ٰ� ǥ���Ѵ�. 5. 3������ �ݺ��ϴµ�, N-1���� edge�� ���õ� ������. N�� vertex�� ����.

// kruskal Algorithm: Prim �˰��� ���ٴ� ����. (edge�� ���� ��)
// edge ����. (prim�� vertex�� ����)    ���̵��: ���� ���� weight�� ���� edge�� ã�Ƽ� ������� �߰�. �ٸ�, edge�߰��� ���ؼ� cycle�� �� ���� ��쿡�� �߰�.    ����: cycle�� ����°� ��� ����? (prim�� �������� �ذ�)                    
//1. ���� ���� weight�� ������ edge�� �����Ѵ�. v1 - edge - v2   2. (union-find)v1�� v2�� family���� �˻��ؼ�, family�� �ƴϸ� edge�� MST�� �߰��ϰ�, �ƴϸ� v1�� v2�� ��ȥ���Ѽ� family�� �����.
//3. 1������ �ݺ�, N-1���� edge�� ���õ� ������.
void do_BFS(int v) {
	int visited[NUM_VTX] = { 0 };
	enque(v);
	while (1) {
		int m = deque();
		if (m == -999) {
			break;
		}
		if (visited[m] != 1) {
			visited[m] = 1;
			printf("%d vertex�� �湮�Ͽ���\n", m);
		}
		else {
			printf("%d ---- �ߺ�\n",m);
		}
		struct node* _cur = graph[m];
		while (_cur != 0) {
			if (visited[_cur->vtx] == 0) {
				enque(_cur->vtx);
			}
			_cur = _cur->next;
		}
	}
}


void _addEdge(int v1, int v2) { // v1->v2. v2�� ���� ��带 �����.
	struct node* _v2 = (struct node*)malloc(sizeof(struct node));
	_v2->vtx = v2;
	_v2->next = 0;
	struct node* cur = graph[v1];

	if (cur == 0) {
		graph[v1] = _v2;
		return;
	}
	else {
		while (cur->next != 0) {
			cur = cur->next;
		}
		cur->next = _v2;
		return;
	}

}

int isThereEdge(int v1, int v2) {
	struct node* cur = graph[v1];
	while (cur != 0) {
		if (cur->vtx == v2) {
			return 1; // ã���� 1
		}
		else {
			cur = cur->next;
		}
	}
	return 0; // ��ã�Ƽ� 0
}



void addEdge(int v1, int v2) { // v1->v2, v2->v1
	
	_addEdge(v1, v2);
	_addEdge(v2, v1);
	return;

}

// Graph �˰����� ��: Dijkstra �˰���, �˴ܰ��ã�� �˰���
// - �׺���̼�, ���ӿ��� ���� �̵�
// - Dijstra algorithm(������� �߽����� ���ɿ��� �׸��鼭 ã�´�.) ->(��ȭ) ->  A*Algorithm(�������� ���ɿ��� �׸��� ã�´�.) - �׺���̼ǿ��� �̰� ����.
// Dijstra algorithm- Ư�� ��������� �ٸ� ��� ���������� �ִܰŸ�.
int main(void) {
	
	addEdge(0, 3);
	addEdge(0, 1);
	addEdge(0, 2);
	addEdge(1, 4);
	addEdge(2, 3);
	addEdge(2, 4);
	addEdge(3, 5);
	addEdge(4, 5);
	
	do_DFS(0); // 0�� vertex���� �����ؼ� DFS ���� - stack
	
	//do_BFS(0); // 0�� vertex���� �����ؼ� BFS ����

	//priintf("%d\n", isTherePath(1, 3)); // edge�� �ܹ���, path�� �� �����ؼ� �� �� �ִ���. �� �� �ִ�. ��, ���� �ִ�.
	// �̶� �׷��� Ž�� �˰���. DFS or BFS �� Ǭ��. ���� �߿���!!!!
	return 0;
}


