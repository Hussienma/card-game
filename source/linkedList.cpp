#include "LinkedList.hpp"

LinkedList::LinkedList(Player& p1, Player& p2): head(nullptr), player1(&p1), player2(&p2){
	head = &player1;
	insert(&player2);
}

void LinkedList::insert(Node* p){
	p->next = head;
	head->next = p;
}

Player* LinkedList::getCurrentTurn(){
	Player* player = head->player;
	return player;
}

void LinkedList::goNext(){
	Node* newHead = head->next;
	head = newHead;
}

void LinkedList::reverseTurns(){
	for(int i=0; i < 4; ++i){
		// TODO: reverse turns
	}
}
