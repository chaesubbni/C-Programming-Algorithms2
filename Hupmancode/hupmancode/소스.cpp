// 허프만 코드: 압축. 무손실 압축. 이진트리 이용.. min heap 이용
// 이진 트리 = 허프만 트리.
// 제일 적은 빈도수를 계속 한 부모로 묶는다.
#include <stdio.h>
#include <stdlib.h>
#define pque_SZ 100
struct node {
	char c; // 허프만 코드를 할당받을 문자.
	int freq; // 문자의 출현 빈도수
	struct node* left;
	struct node* right;
};

// minheap 우선 순위 큐, 빈도수가 적을수록 우선순위가 높다.

struct node* pque[pque_SZ + 1];
int idx = 0;

// huffmancode
char code[30] = { 0 };
int code_idx = -1; //코드를 추가해야 하는 위치. 왼쪽 내려갈때는 0, 오른쪽 내려갈때는 1

struct node* createnode(char _c, int _freq) {
	struct node* _new = (struct node*)malloc(sizeof(struct node));
	_new->c = _c;
	_new->freq = _freq;
	_new->left = _new->right = 0;
	return _new;
}

void enque(struct node* _new) {
	if (idx > pque_SZ) {
		return;
	}

	idx++;
	pque[idx] = _new;
	int _cur_idx = idx;
	int parent_idx = idx / 2;
	while (_cur_idx > 1) {
		if (pque[_cur_idx]->freq > pque[parent_idx]->freq) {
			break;
		}
		else {
			struct node* temp = pque[_cur_idx];
			pque[_cur_idx] = pque[parent_idx];
			pque[parent_idx] = temp;
			_cur_idx = _cur_idx/2;
			parent_idx = parent_idx / 2;
		}
	}

}

struct node* deque(void) {
	if (idx == 0) {
		return 0;
	}
	struct node* res = pque[1];
	pque[1] = pque[idx];
	idx--;

	int _cur_idx = 1;
	int _child_idx = _cur_idx * 2;

	while (1) {

		if (_child_idx > idx) {
			break;
		}
		if (_child_idx + 1 <= idx) {
			if (pque[_child_idx]->freq > pque[_child_idx + 1]->freq) {
				_child_idx = _child_idx + 1;
			}
		}

		if (pque[_cur_idx]->freq < pque[_child_idx]->freq) {
			break;
		}
		else {
			struct node* flag = pque[_cur_idx];
			pque[_cur_idx] = pque[_child_idx];
			pque[_child_idx] = flag;
			_cur_idx = _child_idx;
			_child_idx = _cur_idx * 2;
		}

	}
	return res;
}


// min_heap에 담긴 노드 정보들을 이용해서 huffman tree 만들고, 마지막에 root node에 대한 주소를 반환
struct node* huffmantree(void) {
	// 1. 2개를 꺼낸다. 
	//단 1개만 있으면, 반환하고 끝.
	// 2개 있으면 이진트리를 만들어서 다시 enque
	while (1) {
		struct node* _first = deque();
		struct node* _second = deque();

		if (_second == 0) { // _first가 root node라는 뜻.
			return _first;
		}

		struct node* combined = createnode(0, _first->freq + _second->freq);
		combined->left = _first;
		combined->right = _second;

		enque(combined);

	}	
	
}

void madehuffmancode(struct node* _node) {
	if (_node == 0) {
		return;
	}

	code_idx++;
	code[code_idx] = '0';
	madehuffmancode(_node->left);
	code[code_idx] = 0; // 내가 넣은거 지운다.
	code_idx--;
	
	
	if (_node->c != 0) {
		printf("%c---->%s\n", _node->c, code);
	}
	
		
	code_idx++;
	code[code_idx] = '1';
	madehuffmancode(_node->right);
	code[code_idx] = 0; // 내가 넣은거 지운다.
	code_idx--;
}




int main(void) {
	enque(createnode('c', 6));
	enque(createnode('a', 3));
	enque(createnode('z', 100));
	enque(createnode('b', 4));
 /*
	while (1) {
		struct node* temp = deque();
		if (temp == 0) {
			break;
		}
		printf("%c   %d\n", temp->c, temp->freq);
	}
	//  ------------- 여기까지 min_heap 구현.
*/
	struct node* temp = huffmantree();
	printf("%d\n", temp->freq);
	madehuffmancode(temp);
	return 0;
}