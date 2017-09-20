/*trabalho arvore de busca binaria*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>


struct node{
	int key;  					//chave de identificação do nodo	
	node * left, * right;		//ponteiros para os filhos
	node * pai;
};

struct tree{
	node *raiz;
};


//busca por uma chave k na árvore com raiz r
//caso a chave não estiver na árvore retorna NULL

node * search (node * r, int key){
	if(!r || r->key == key )  return r;				//n encontrou a chave

	if(key <= r->key) return search (r->left, key);
	
	return search (r->right, key); 	
}

void inorder(node *r){
	if(r){
		inorder(r->left);
		printf("%d",r->key);
		inorder(r->right);
	}
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


//mostra todas as chaves da árvore

void * print (node * r){}

//insere um nodo com chave key na árvore com raiz r
//retorna um ponteiro para a raiz da árvore

node * insert (node * r,int key){
	node * n = (node *)malloc(sizeof(node));		//cria um novo nodo
	n->left = n->right = n->pai=NULL;
	n->key = key;
	
	if(!r) return n;			// se a arvore estiver vazia

	node * it = r;	

	while(1){
		if(key < it->key){
			if(!it->left){
				it->left = n; 		//atualiza o filho da esquerda de r	
				break;		
			}
			it = it->left;	
		}else{
			if(!it->right){
				it->right = n;
				break;			
			}
			it = it->right;
		}
				
	}

	return r;
	r->pai = it;
}

node *tree_min(node *r){
	return (!r->left)? r: tree_min(r->left);
}

void transplante(tree * t , node * u , node * v){
	if(!u->pai){
		t->raiz = v;
	}else if(u=u->pai->left){
		u->pai->left = v;

	}else{
		u->pai->right = v;
	}
	if(!v){
		v->pai=u->pai;
	}
}

//remove o nodo da árvore com raiz r que possui chave igual a key
//(lembra que tem que dar free no nodo)
void remove (node * r, int key){
	//if(key->esquerda == NULL){
		//transplante(r,key,key->direita);
	//}
}

int main ( void ){

	int n , key;
	
	node * root = NULL;

	int opc , x = 0, i = 0;

	printf("quantidade de elementos a ser inserido\n");
	scanf("%d",&x);

	
	while(i<x){
		scanf("%d", &n);
		root = insert(root, n);
		i++;
	}

	while(opc != 0 ){

		printf("\n1-travessia preorder\n2-travessia posrder\n3-travessia inorder\n4-Remover elemento\n5-Mostrar Arvore\n6-Buscar Elemento\n0-Sair\n");
		scanf("%d",&opc);

	
		if(opc == 1) preorder(root);
		else if(opc==2) posorder(root);
		else if(opc==3) inorder(root);
		else if(opc==4) {
			printf("elemento a deletar : ");
			scanf("%d",&key);
			remove(root,key);

		}
		else if(opc==5) print(root);
		else if(opc==6) {
			printf("elemento  a buscar:\n");
			scanf("%d",&key);
			search(root,key);
		}
	}

	return 0;
}





