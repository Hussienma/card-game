#pragma once
#include "Player.hpp"

struct Node {
	Node* prev;
	Node* next;
	Player* player;
	Node(Player* player): prev(nullptr), player(player), next(nullptr){}
};

class LinkedList {
	private:
	Node* head;
	Node player1;
	Node player2;

	public:
	LinkedList(Player& p1, Player& p2);
	void insert(Node* p);
	Player* getCurrentTurn();
	void goNext();
	void reverseTurns();
};	
