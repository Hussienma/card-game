#include "LinkedList.hpp"

LinkedList::LinkedList(Player& p1, Player& p2): head(nullptr), player1(&p1), player2(&p2){
	head = &player1;
	insert(&player2);
}

void LinkedList::insert(Node* p){
	p->next = head;
	p->prev = head;
	head->next = p;
	head->prev = p;
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
