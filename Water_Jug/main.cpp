#include<iostream>

using namespace std;

struct node {
	
	int jug_A, jug_B;
	node* parent = NULL;
	node* child[4] = { NULL, NULL, NULL, NULL };
	int i = 0;
	int count = 0;

	node* operator= (node* x) {
		node* temp = new node;
		temp->jug_A = x->jug_A;
		temp->jug_B = x->jug_B;
		temp->i = 0;
		temp->count = 0;
		temp->parent = NULL;
		return temp;
	}
};

int counting = 0;
node arrays[1000] = { 0 };

void intial(node* root) {
	root->jug_A = 0;
	root->jug_B = 0; 
}

void makechildren(node* root, int Jug_A, int Jug_B) {
	int stateA = root->jug_A, stateB = root->jug_B;

	if (root->jug_A != Jug_A) {
		node* child = new node;
		child->parent = root;
		root->child[root->i] = child;
		child->jug_A = Jug_A;
		child->jug_B = root->jug_B;
		root->i++;
	}

	if (root->jug_B != Jug_B) {
		node* child = new node;
		child->parent = root;
		root->child[root->i] = child;
		child->jug_B = Jug_B;
		child->jug_A = root->jug_A;
		root->i++;
	}

	if (root->jug_B != Jug_B && root->jug_A != 0) {
		node* child = new node;
		child->parent = root;
		root->child[root->i] = child;
		int freespace;
		freespace = Jug_B - root->jug_B;

		child->jug_A = root->jug_A;
		child->jug_B = root->jug_B;

		for (int i = 0; i < freespace; i++) {

			if (child->jug_A != 0) {
				child->jug_A -= 1;
				child->jug_B += 1;
			}
		}
		root->i++;
	}


	if (root->jug_A != Jug_A && root->jug_B != 0) {
		node* child = new node;
		child->parent = root;
		root->child[root->i] = child;
		int freespace;
		freespace = Jug_A - root->jug_A;

		child->jug_A = root->jug_A;
		child->jug_B = root->jug_B;

		for (int i = 0; i < freespace; i++) {

			if (child->jug_B != 0) {
				child->jug_B -= 1;
				child->jug_A += 1;
			}
		}
		root->i++;
	}

	if (root->jug_A != 0) {
		node* child = new node;
		child->parent = root;
		root->child[root->i] = child;
		child->jug_A = 0;
		child->jug_B = stateB;
		root->i++;
	}

	if (root->jug_B != 0) {
		node* child = new node;
		child->parent = root;
		root->child[root->i] = child;
		child->jug_B = 0;
		child->jug_A = stateA;
		root->i++;
	}
}


void waterjug(node *root, int fState_1, int fState_2, int Jug_A, int Jug_B) {
	arrays[counting] = *root;
	makechildren(root, Jug_A, Jug_B);

	for (int i = 0; i < root->i; i++) {
		for (int j = 0; j < counting; j++) {
			cout <<" root->count: " << root->count <<" i: "<<i<< " j: "<< j<< " arrays[j].jug_A: "<< arrays[j].jug_A <<" arrays[j].jug_B: "<< arrays[j].jug_B << endl;
			if (arrays[j].jug_A == root->child[root->count]->jug_A && arrays[j].jug_B == root->child[root->count]->jug_B) {
				root->count++;
			}
		}
	}
	counting++;
	cout << "Action: " << root->jug_A << root->jug_B << endl;

	if (root->jug_A != fState_1 || root->jug_B != fState_2) {
		root = root->child[root->count];
		waterjug(root, fState_1, fState_2, Jug_A, Jug_B);
	}

}

int main() {

	int Jug_A, Jug_B;
	int fState_1, fState_2;
	cout << "**!! IF THE PROGRAM HALTS OR CRASHES THEN THERE ARE NO SOLUTIONS !!**" << endl << endl;
	cout << "Enter the Size of the two Jugs" << endl;
	cin >> Jug_A >> Jug_B;
	cout << "Enter the final state of the Jugs" << endl;
	cin >> fState_1 >> fState_2;
	cout << endl;

	node root;
	intial(&root);
	waterjug(&root, fState_1, fState_2, Jug_A, Jug_B);
	return 0;
}