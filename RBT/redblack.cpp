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

void inorder(node *r){
	if(r){
		inorder(r->left);
		printf("%d",r->key);
		inorder(r->right);
	}else printf("bug\n");
}

void preorder(node *r){
	if(r){
		
		printf("%d",r->key);
		preorder(r->left);
		preorder(r->right);
	}
}

void posorder(node *r){
	if(r){
		posorder(r->left);
		posorder(r->right);
		printf("%d",r->key);
	}
}

tree * start_tree(){
	tree * n = (tree * )malloc(sizeof(tree));
	n->nil = (node *)malloc(sizeof(node));
	n->nil->color = 'B';
	n->root = n->nil;
	return n;
}

void leftRotate(tree *T , node * z){
	node * y = z->right;

	z->right = y->left;
	
	if ( y->left != T->nil )
		y->left->parent = z;

	y->parent = z->parent;

	if ( z->parent == T->nil )
		T->root = y;
	else if( z == z->parent->left )
		z->parent->left = y;
	else z->parent->right = y;
	
	y->left = z;
	z->parent = y;
}

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
	
	 	
	while(z != T->root && z->parent->color == 'R'){
		if (z ->parent == z->parent->parent->left){
			node * y = z->parent->parent->right;
			if(y->color == 'R'){
				y->color = 'B';
				z->parent->color = 'B';
				z->parent->parent->color= 'R';
				z = z->parent->parent;
			}else{
				if(z == z->parent->right){
					z = z->parent;
					leftRotate(T,z);
				}
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				rightRotate(T,z->parent->parent); 
			}	
		}else{
			node *t = z->parent->parent->left;
			if(t->color == 'R'){
				t->parent->color = 'B';
				t->color = 'B';
				z->parent->parent->color= 'R';
				z = z->parent->parent;
			}else{
				if(z == z->parent->left){
					z = z->parent;
					rightRotate(T,z);
				}
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				leftRotate(T,z->parent->parent); 
			}
		}
	}
	T->root->color = 'B';
}

void drawTree(tree * t, node * n, int h){
	if(n->left != t->nil)
		drawTree(t, n->left, h+1);	

	int i;
	for(i=0; i<h; i++){
		printf("    ");
	}
	
	if(n->color == 'R')
		printf("R-%d\n", n->key);	
	else
		printf("B-%d\n", n->key);		
	
	if(n->right != t->nil)
		drawTree(t, n->right, h+1);	
}

void insert(tree *T, int z){

		node * aux =(node *)malloc (sizeof(node));
		aux->parent = aux->right = aux->left = T->nil;
		aux->key = z;
		aux->color = 'R';

		node * x;
		node *y;

		x = T->root;
		y=T->nil;

		while(x != T->nil){
			y  = x;
			if(z<x->key){
				x = x->left;
			}else{
				x = x->right;
			}
		}

		aux->parent = y;

		if(y == T->nil){
			T->root = aux;
		}else if(z < y->key){
				y->left = aux;
		}else{
			y->right = aux;
		}
		
		fixUp(T,aux);
}

int main(void){
	int opc,key;

	tree * T = start_tree();

	while(opc != 0 ){
		printf("1-Inserir\n2-Deletar\n3-Buscar\n4-inorder\n5-posorder\n6-preorder\n");
		scanf("%d",&opc);

		switch(opc){
			case 1 : 
				printf("Insira a chave : \n");
				scanf("%d",&key);
				insert(T,key);
				break;
			case 2 :
				printf("deletar\n");
				break;
			case 3 : 
				printf("buscar\n");
				break;
			case 4 : 
				inorder(T->root);
				break;
		} 	
	}

	return 0;

}