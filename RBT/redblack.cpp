/*
	Implementação RedBlack Tree

	Acadêmico Luis Henriqu Wasem de Oliveira

*/
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

node* min(tree* T, node* no){
	node* aux = no;
	while(aux->left != T->nil)
		aux = aux->left;
	return aux;
}

node* sucessor(tree* T,node* n){
	if(n->right != T->nil)
		return min(T,n->right);
	node* aux= n->parent;
	while(aux != T->nil && n == aux->right){
		n = aux;
		aux = aux->parent;
	}
	return aux;
}

void inorder(node *r,node *nil){
	if(r!=nil){
		inorder(r->left,nil);
		printf("%d",r->key);
		printf("%c\n",r->color);
		inorder(r->right,nil);
	}	
}

void preorder(node *r,node* nil){
	if(r!=nil){
		printf("%d",r->key);
		printf("%c\n",r->color);
		preorder(r->left,nil);
		preorder(r->right,nil);
	}
}

void posorder(node *r,node *nil){
	if(r!=nil){
		posorder(r->left,nil);
		posorder(r->right,nil);
		printf("%d",r->key);
		printf("%c\n",r->color);
	}
}
//inicialização da arvore
tree * start_tree(){
	tree * n = (tree * )malloc(sizeof(tree));
	n->nil = (node *)malloc(sizeof(node));
	n->nil->color = 'B';
	n->nil->parent = NULL;
	n->nil->left = NULL;
	n->nil->right = NULL;
	n->root = n->nil;
	
	return n;
}
//busca nodo
node * search_node(tree* T, node * r, int key){
	if(r == T->nil || r->key == key ) return r;				
	if(key <= r->key) return search_node(T,r->left, key);
	return search_node(T,r->right, key);
}
//rotação a esquerda
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
//rotação a direita
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


// arrumar arvore ao inserir novo nodo
node * fixUp_insert(tree * T, node * z){

	while( z->parent->color == 'R'){
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
			
					z->parent->color = 'B';
					z->parent->parent->color = 'R';
					rightRotate(T,z->parent->parent); 
				}else{
					z = z->parent;
					rightRotate(T,z);
				}
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
					z->parent->color = 'B';
					z->parent->parent->color = 'R';
					leftRotate(T,z->parent->parent); 
				}else{
					z = z->parent;
					leftRotate(T,z);
				}
			
		}
	}
		
	}
	T->root->color = 'B';
}
// desenhar a  árvore (meritos ao colega)
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
//inserção de um novo nodo
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
		
		fixUp_insert(T,aux);
}
//arrumar a arvore apos deleção
void fix_up_delecao(tree* T,node* x){
	node* aux;

	while(x != T->root && x->color == 'B'){
		if(x == x->parent->left){
			aux = x->parent->right;
			if(aux->color == 'R'){
				x->parent->color = 'R';
				aux->color = 'B';
				leftRotate(T,x->parent);
				aux = x->parent->right;
			}
			if(aux->left->color == 'B' && aux->right->color == 'B'){
				aux->color = 'R';
				x = x->parent;
				}else if(aux->right->color == 'B'){
					aux->left->color = 'B';
					aux->color = 'R';
					rightRotate(T,aux);
					aux = x->parent->right;
				}else{
				aux->color = aux->parent->color;
				x->parent->color = 'B';
				aux->right->color = 'B';
				leftRotate(T,x->parent);
				x = T->root;
			}
		}else{
			aux = x->parent->left;
			if(aux->color == 'R'){
				aux->color = 'B';
				x->parent->color = 'R';
				rightRotate(T,x->parent);
				aux = x->parent->left;
			}
			if(aux->right->color == 'B' && aux->left->color == 'B'){
				aux->color = 'R';
				x = x->parent;
				}else if(aux->left->color == 'B'){
					aux->right->color = 'B';
					aux->color = 'R';
					leftRotate(T,aux);
					aux = x->parent->left;
				}else{
				aux->color= aux->parent->color;
				x->parent->color = 'B';
				aux->left->color = 'B';
				rightRotate(T,x->parent);
				x = T->root;
			}
		}
	}
	x->color = 'B';
}

//deletar nodo da arvore
node* del_node(tree* T, int key){
	node* z = search_node(T, T->root, key);
	node* y ,* x;
	if(z == T->nil){
		return z;
	}
	if(z->left == T->nil || z->right == T->nil)
		y = z;
		else
			y = sucessor(T,z);
	if(y->left != T->nil)
		x = y->left;
		else
			x = y->right;
	x->parent = y->parent;
	if(y->parent == T->nil)
		T->root = x;
		else if(y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	if(y != z)
		z->key = y->key;
	if(y->color == 'B')
		fix_up_delecao(T,x);
	return z;
}



int main(void){	
	int opc,key;

	tree * T = start_tree();

	while(opc != 0 ){
		printf("1-Inserir\n2-Deletar\n3-Buscar\n4-inorder\n5-posorder\n6-preorder\n7-desenhar\n0-sair:  ");
		scanf("%d",&opc);

		switch(opc){
			case 0 :
				return 0;
			case 1 : 
				printf("Insira a chave : \n");
				scanf("%d",&key);
				insert(T,key);

				break;
			case 2 :
				printf("Insira o a cahve que deseja deletar:\n");
				scanf("%d",&key);
				del_node(T,key);
				break;
			case 3 : 
				printf("insira a chave que deseja buscar:\n");
				scanf("%d",&key);
				if(search_node(T,T->root,key)!= T->nil){
					printf("encontrou\n");
				}else{
					printf("o nodo nao esta na arvore\n");
				}
				break;
			case 4 : 
				inorder(T->root,T->nil);
				break;
			case 5:
				posorder(T->root,T->nil);
				break;
			case 6:
				preorder(T->root,T->nil);
				break;
			case 7 :
				drawTree(T,T->root,4);
		} 	
	}
	return 0;
}