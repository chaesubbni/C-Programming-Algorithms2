// ������ �ڵ�: ����. ���ս� ����. ����Ʈ�� �̿�.. min heap �̿�
// ���� Ʈ�� = ������ Ʈ��.
// ���� ���� �󵵼��� ��� �� �θ�� ���´�.
#include <stdio.h>
#include <stdlib.h>
#define pque_SZ 100
struct node {
	char c; // ������ �ڵ带 �Ҵ���� ����.
	int freq; // ������ ���� �󵵼�
	struct node* left;
	struct node* right;
};

// minheap �켱 ���� ť, �󵵼��� �������� �켱������ ����.

struct node* pque[pque_SZ + 1];
int idx = 0;

// huffmancode
char code[30] = { 0 };
int code_idx = -1; //�ڵ带 �߰��ؾ� �ϴ� ��ġ. ���� ���������� 0, ������ ���������� 1

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


// min_heap�� ��� ��� �������� �̿��ؼ� huffman tree �����, �������� root node�� ���� �ּҸ� ��ȯ
struct node* huffmantree(void) {
	// 1. 2���� ������. 
	//�� 1���� ������, ��ȯ�ϰ� ��.
	// 2�� ������ ����Ʈ���� ���� �ٽ� enque
	while (1) {
		struct node* _first = deque();
		struct node* _second = deque();

		if (_second == 0) { // _first�� root node��� ��.
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
	code[code_idx] = 0; // ���� ������ �����.
	code_idx--;
	
	
	if (_node->c != 0) {
		printf("%c---->%s\n", _node->c, code);
	}
	
		
	code_idx++;
	code[code_idx] = '1';
	madehuffmancode(_node->right);
	code[code_idx] = 0; // ���� ������ �����.
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
	//  ------------- ������� min_heap ����.
*/
	struct node* temp = huffmantree();
	printf("%d\n", temp->freq);
	madehuffmancode(temp);
	return 0;
}