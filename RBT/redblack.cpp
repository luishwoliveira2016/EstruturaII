#include <stdio.h>
#include <stdlib.h>

struct node{
	int key;
	char color;
	node * left;
	node * right;
	node* parent;
};

struct tree{
	node * root;
	node *nil;
};

tree * start_tree(){
	tree * n = (tree * )malloc(sizeof(tree));
	n->nil = (node *)malloc(sizeof(node));
	n->nil->color = 'B';
	n->root = n->nil;
	return n;
}

void leftRotate(tree *T , node * z){}

void rightRotate(tree * T, node * z){
	node * y = z->left;
	
	z->left = y->right;
	
	if ( y->right != T->nil )
		y->right->parent = z;
	
	y->parent = z->parent;
	
	if ( z->parent == T->nil )
		T->root = y;
	else if ( z == z->parent->left )
		z->parent->left = y;
	else z->parent->right = y;
	
	y->right = z;
	z->parent = y;
}



node * fixUp(tree * T, node * z){
	node * y ;
	 	
	while(z->parent->color == 'R'){
		if (z ->parent == z->parent->parent->left){
			y = z->parent->parent->right;
			if(y->color == 'R'){
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color= 'R';
				z = z->parent->parent;
			}else{
				if(z == z->parent->right){
					z = z->parent;
					leftRotate(T,z);
				}
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				rightRotate(T,z); 
			}	
		}else{
			y = z->parent->parent->left;
			if(y->color == 'R'){
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color= 'R';
				z = z->parent->parent;
			}else{
				if(z == z->parent->left){
					z = z->parent;
					rightRotate(T,z);
				}
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				leftRotate(T,z); 
			}
		}
	}
	T->root->color = 'B';
}

void insert(tree *T, int z){

		node * aux =(node *)malloc (sizeof(node));
		aux->parent = aux->right = aux->left = T->nil;

		node * x;
		node *y;

		x = T->root;
		y=T->nil;

		while(x != T->nil){
			y  = x;
			if(aux->key<x->key){
				x = x->left;
			}else{
				x = x->right;
			}
		}

		aux->parent = y;

		if(y == T->nil){
			T->root = aux;
		}else{
			if(aux->key <y->key){
				y->left = aux;
			}else{
				y->right = aux;
			}
		}

		aux->left = T->nil;
		aux->right = T->nil;
		aux->color = 'R';
		fixUp(T,aux);
}

int main(){
	int opc;


	printf("1-Inserir\n2-Deletar\n3-Buscar\n4-inorder\n5-posorder\n6-preorder");
	scanf("%d",&opc);
	
	tree * T = start_tree();

	switch(opc){
		case 1 : 
			insert(T,0);
	} 	

	return 0;

}