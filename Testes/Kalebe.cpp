#include <iostream>

using namespace std;

struct Node{
	int iData;
	struct Node *next;
};

void insert(Node *head, int value) {
	Node *newNode = new Node;
	newNode -> next = head -> next;
	newNode -> iData = value;
	head -> next = newNode;
}

void insertOrdem(Node *head, int value){
	Node *max = head, *min = head;
	for(Node *tmp = head->next; tmp != head; tmp = tmp-> next) {
		if(tmp -> iData <= value && tmp->next->iData >= value) {
			insert(tmp, value);
			return;
		}
		if(tmp -> iData >= max -> iData)
			max = tmp;
		if(tmp -> next -> iData <= min -> iData)
			min = tmp;
	}
	if(value <= min -> next -> iData){
		insert(min, value);
		return;
	}
	insert(max, value);
}

bool verifyList(Node *head) {
	for(Node *tmp = head -> next; tmp != head; tmp = tmp -> next)
		if(tmp == nullptr)
			return false;
	return true;
}

void exibirLista(Node *head) {
    cout << "Lista: "; 
    while (head->next != nullptr)
    {
        cout << head->iData << ", ";
        head = head->next;
    }
    cout << head->iData <<"." << endl;
}

int main() {
	// Lista circular
	Node *head = new Node;
	head -> next = head;
	head -> iData = 10;
	insertOrdem(head, 11);
	insertOrdem(head, -11);
	insertOrdem(head, -5);
	insertOrdem(head, 120);
	
	// Lista normal
    Node *head2 = new Node;
    head2->iData = 666;
    
    for (size_t i = 10; i > 0; i--)
    {
        Node* aux = head2;
        Node* novo = (Node*) malloc(sizeof(Node));
        novo->iData = i;
        novo->next = head2;
        exibirLista(head2);
        head2 = novo;
    }
    
    
    //exibirLista(head);
    exibirLista(head2);
    
    // insert preserva o null para o final
    insert(head2, 2);
    insert(head2, 8);
    insert(head2, 3);
    insert(head2, 4);
	cout << verifyList(head) << endl;
	cout << verifyList(head2) << endl;
	
	return 0;
}