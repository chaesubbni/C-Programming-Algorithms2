#include <stdio.h>
#include <stdlib.h>
#define NUM_VTX 6

// 그래프. 연결되어 있는 객제 간의 관계르르 표현하는 자료구조. 그래프의 예) tree, 지하철 노선도. 
// 즉, 연결(link) 가 있으면 전부 다 그래프
// 그래프 G는 V, E로 표시. V(node) 정점. E(edge, link) 간선, 링크.
// 출발역과 도착역을 넣었을때 어디어디에 환승해야하는지 짜야하는 과제.
// 무방향(undirect) 그래프 , (A,B) 로 표시-간선을 통해 양방향으로 갈수 있음
// 방향(direct) 그래프, <A,B>로 표시- 간선을 통해 한쪽 방향으로만 갈 수 있음.
// 가중치 그래프 - 간선에 비용이나 가중치가 할당된 그래프. 즉 연결 선에 거리나 비용을 표시할 수 있음.
// 인접 정점. adjacent vertex. 간선으로 연결되어 있음
// 차수. 하나의 정점에 연결된 다른 정점의 수. 만약 방향 그래프면 진입차수와 진출차수 구분. 들어오는지, 나가는지
//그래프의 경로. 그래프의 정점 s 부터 정점 e 까지의 경로
// 단순 경로. 경로 중에서 반복되는 간선이 없는 경로
// 사이클. 시작 정점과 종료 정점이 동일한 경로
// 연결 그래프. 
// 트리. 연결 그래프. 그래프의 특수한 형태로서 사이클을 가지지 않는 연결 그래프.
// 완전 그래프 - - 모든 정점이 서로 연결되어 있어야 한다
// 그래프 표현 방법. 2차원 행렬로 표현. or 인접리스트. 즉 linked list로 표현
// sll로 표현
// DFS - 깊이 우선 탐색 - stack 사용
// BFS - 넓이 우선 탐색 - que 사용

// 배열로 그래프 구현----------------------- 노드 간의 edge가 많을 때
/*
int graph[NUM_VTX][NUM_VTX]; // 글로벌 변수는 자동으로 0으로 초기화!!!!.

void addEdge(int v1, int v2) {
	graph[v1][v2] = 1;
	graph[v2][v1] = 1;
	return;
}

int isThereEdge(int v1, int v2) { // 두 정점이 서로 연결되어 있나???
	return graph[v1][v2]; // 해당 배열이 1이면 넵!!!, 아니면 아니용!!
}

*/

// 연결 리스트로 구현 dege가 별로 없을 때
// edge -undirected graph, directed graph, weighted graph.
// 그래프 탐색: 모든 vertex를 방문하는 방법, DFS- depth first search-stack, BFS-breadth first search-que.  특정 vertex에서 갈 수 있는 vertex들을 모두 찾기 위해서. height(하이트) linear(리니얼)
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

// BFS를 위한 que
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



// stack안에 v가 이미 있으면 1, 아니면 0
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


// _v에서 시작하여, DFS 시행
void do_DFS(int _v) {
	// 1.stack_dfs: push, pop, checkduplication
	// 2. 방문했는지 여부를 나타내는 1차원 배열(visited)
	int visited[NUM_VTX] = { 0 }; // 모두다 방문하지 않았음.

	// 시작 vertex를 stack에 넣는다.
	// 반복 -- 스택이 빌 때까지.
	// 스택에서 pop한다. -- m
	// m을 방문했다고 표시하고,
	// m을 화면에 출력
	// for (m에 연결된 각각의 vertex에 대해서 )
	//    if( stack 에 없고, visited가 아니면 --> push)
	push(_v);
	while (1) {
		int m = pop();
		if (m == -999) {
			break;
		}
		if (visited[m] == 0) {
			visited[m] = 1;
			printf("%d vertex를 방문했음 \n", m);
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

// spanning tree, 신장트리. - 모든 vertex들이 연결된 subgraph. 연결 되어 있기만 하면 된다.
// minimum spanning tree, 최소신장트리.- 최소한의 edge개수로 모든 vertex를 연결하는 spanning tree. 최소한의 edge개수 = vertex개수 - 1, 만약 weighted 그래프라고 하면, MST는 weight의 합이 최소.
// MST의 응용.- 최소 비용으로 도로건설, 최소 비용으로 네트워크망 건설
// MST 알고리즘. - Prim, Kruskal. -----------cycle이 생성되면 안된다.
//prim. --- 3번에서 계산량이 너무 많다. (node가 많을 때)
//1. 시작 vertex를 정한다. 2. 시작 vertex를 '포함' 되었다고 표시한다. 3. 포함 vertex에서 불포함 vertex로 연결된 edge중에 가장 작은 weight를 갖는 edge를 찾는다.
//4. edge로 연결된 불포함 vertex를 포함되었다고 표시한다. 5. 3번으로 반복하는데, N-1개의 edge가 선택될 때까지. N은 vertex의 개수.

// kruskal Algorithm: Prim 알고리즘 보다는 빠름. (edge가 많을 때)
// edge 기준. (prim는 vertex가 기준)    아이디어: 가장 작은 weight를 갖는 edge를 찾아서 순서대로 추가. 다만, edge추가로 인해서 cycle이 안 생길 경우에만 추가.    난점: cycle이 생기는걸 어떻게 알쥐? (prim은 포함으로 해결)                    
//1. 가장 작은 weight를 가지는 edge를 선택한다. v1 - edge - v2   2. (union-find)v1과 v2가 family인지 검사해서, family가 아니면 edge를 MST에 추가하고, 아니면 v1과 v2를 결혼시켜서 family로 만든다.
//3. 1번으로 반복, N-1개의 edge가 선택될 때까지.
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
			printf("%d vertex를 방문하였음\n", m);
		}
		else {
			printf("%d ---- 중복\n",m);
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


void _addEdge(int v1, int v2) { // v1->v2. v2로 가는 노드를 만든다.
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
			return 1; // 찾으면 1
		}
		else {
			cur = cur->next;
		}
	}
	return 0; // 못찾아서 0
}



void addEdge(int v1, int v2) { // v1->v2, v2->v1
	
	_addEdge(v1, v2);
	_addEdge(v2, v1);
	return;

}

// Graph 알고리즘의 꽃: Dijkstra 알고리즘, 죄단경로찾기 알고리즘
// - 네비게이션, 게임에서 유닛 이동
// - Dijstra algorithm(출발지를 중심으로 동심원을 그리면서 찾는다.) ->(진화) ->  A*Algorithm(목적지로 동심원을 그리며 찾는다.) - 네비게이션에서 이걸 쓴다.
// Dijstra algorithm- 특정 출발점에서 다른 모든 지점까지의 최단거리.
int main(void) {
	
	addEdge(0, 3);
	addEdge(0, 1);
	addEdge(0, 2);
	addEdge(1, 4);
	addEdge(2, 3);
	addEdge(2, 4);
	addEdge(3, 5);
	addEdge(4, 5);
	
	do_DFS(0); // 0번 vertex부터 시작해서 DFS 시행 - stack
	
	//do_BFS(0); // 0번 vertex부터 시작해서 BFS 시행

	//priintf("%d\n", isTherePath(1, 3)); // edge는 단번에, path는 쭉 연결해서 갈 수 있는지. 갈 수 있다. 즉, 길이 있다.
	// 이때 그래프 탐색 알고리즘. DFS or BFS 로 푼다. 완전 중요해!!!!
	return 0;
}


