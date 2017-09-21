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

node * tree_min(node *r){
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

void remove (tree *T, node *z){
		node * y;
	if(!z->left)
		transplante(T, z, z->right);
	else if(!z->right)
		transplante(T, z, z->left);
	else{
		y = tree_min(z->right);
		if(y->pai != z){
			transplante(T, y, y->right);
			y->right = z->right;
			y->right->pai = y;
		}
		transplante(T, z, y);
		y->left = z->left;
		y->left->pai = y;
	}	
}

node * tree_sucessor(node * x){
	if(x->right) return tree_min(x->right);

	node * y = x->pai;

	while(y && x == y->right){
		x = y;
		y = y->pai;
	}
	return y;
}


int main ( void ){

	int n , key , opc;

	tree t;

	node * aux;

	t.raiz = NULL;

	
	while (scanf("%d", &n)){
		t.raiz= insert(t.raiz,n);
	}

	fflush(stdin);
	getchar();

	while(opc != 0 ){

		printf("\n1-travessia preorder\n2-travessia posrder\n3-travessia inorder\n4-Remover elemento\n5-Buscar Elemento\n0-Sair\n");
		scanf("%d",&opc);

	
		if(opc == 1) preorder(t.raiz);
		else if(opc==2) posorder(t.raiz);
		else if(opc==3) inorder(t.raiz);
		else if(opc==4) {
			printf("elemento a deletar : ");
			scanf("%d",&n);
			aux  = search(t.raiz , n);
			printf("chave a ser deletada : %d",aux->key);
			if(aux){
				remove(&t,aux);
				free(aux);

			}else printf("a chave não existe\n");
			

		}
		else if(opc==5) {
			printf("elemento  a buscar:\n");
			scanf("%d",&key);
			
			aux = search(t.raiz,key);

			if(!aux) printf("a chave não existe\n");

			else if(aux->key == key) printf("encontrou %d !!\n",aux->key );

		}
	}

	return 0;
}





