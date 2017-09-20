/*trabalho arvore de busca binaria*/

#include <stdlib.h>
#include <stdio.h>


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
	if(!r || r->key == key ) return r;				//n encontrou a chave

	if(key <= r->key) return search (r->left, key);
	
	return search (r->right, key); 	
}

node * inorder(node *r){
	if(r !=NULL){
		inorder(r->left);
		printf("%d",r->key);
		inorder(r->right);
	}
}

node * preorder(node *r){
	if(r !=NULL){
		
		printf("%d",r->key);
		preorder(r->left);
		preorder(r->right);
	}
}

node * posrder(node *r){
	if(r !=NULL){
		posrder(r->left);
		posrder(r->right);
		printf("%d",r->key);
	}
}


//mostra todas as chaves da árvore

void * print (node * r){}

//insere um nodo com chave key na árvore com raiz r
//retorna um ponteiro para a raiz da árvore

node * insert (node * r,node * q->key){
	node * n = (node *)malloc(sizeof(node));		//cria um novo nodo
	n->left = n->right = NULL;
	n->key = key;
	n->pai = NULL;

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
		r->pai = it;		
	}

	return r;
}

void transplante(node * t , node * u , node * v){
	if(u->pai == NULL){
		//t->raiz = v;
	}
}

//remove o nodo da árvore com raiz r que possui chave igual a key
//(lembra que tem que dar free no nodo)
void remove (node * r, int key){
	if(key->esquerda == NULL){
		transplante(r,key,key->direita);
	}
	
		


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

	printf("1-travessia preorder\n2-travessia posrder\n3-travessia inorder\n4-Remover elemento\n5-Mostrar Arvore\n6-Buscar Elemento\n0-Sair\n");
	scanf("%d",&opc);

	while(opc !=0){
		switch(opc){
			case 1:
				preorder(root);
			case 2:
				posrder(root);
			case 3:
				inorder(root);
			case 4:
				printf("elemento a ser deletado :");
				scanf("%d",&key);
				remove(root,key);
			case 5 : 
				print(root);

		}
	}

	return 0;
}





