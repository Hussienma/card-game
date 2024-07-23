#pragma once
#include "Index.hpp"

struct Node {
	Node* prev;
	Player* player;
	Node* next;
	Node(Player* player): prev(nullptr), player(player), next(nullptr){}
	Node(): prev(nullptr), player(nullptr), next(nullptr){}
};

class LinkedList {
	private:
	Node* head;

	// INFO: These were not pointers
	Node player1;
	Node player2;
	void insert(Node* p);

	public:
	LinkedList(): head(nullptr){
	}
	void insertPlayer(Player& player);
	Player* getCurrentTurn();
	void goNext();
	void reverseTurns();
};	
