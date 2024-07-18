#include "LinkedList.hpp"

void LinkedList::insert(Node* p){
	if(head == nullptr){
		head = p;
		return;
	}
	p->next = head;
	p->prev = head;
	head->next = p;
	head->prev = p;
}

void LinkedList::insertPlayer(Player& player){
	Node* node = new Node(&player);
	insert(node);
}

Player* LinkedList::getCurrentTurn(){
	Player* player = head->player;
	return player;
}

void LinkedList::goNext(){
	Node* newHead = head->next;
	head = newHead;
	std::cout<<getCurrentTurn()->getName()<<" turn now.\n";
}

void LinkedList::reverseTurns(){
	Node* node = head->next;
	for(int i=0; i < 2; ++i){
		Node* temp = node->next;
		std::cout<<"temp="<<temp<<std::endl;
		node->next = node->prev;
		std::cout<<"temp="<<temp<<std::endl;
		node->prev = temp;
		node = node->next;
	}
}
