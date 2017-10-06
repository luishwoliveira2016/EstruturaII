/*trabalho arvore de busca binaria*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>


struct node{
	int key;  					//chave de identificação do nodo	
	node * left, * right;		//ponteiros para os filhos
	node * pai;
};

struct tree{    //esrtrutura da arvore
	node *raiz;
};


//busca por uma chave k na árvore com raiz r
//caso a chave não estiver na árvore retorna NULL

node * search (node * r, int key){ // encontra o nodo com a key informada
	if(!r || r->key == key )  return r;				

	if(key <= r->key) return search (r->left, key);
	
	return search (r->right, key); 	
}

void inorder(node *r){ // mostra nodos da arvore  metodo inorder
	if(r){
		inorder(r->left);
		printf("%d",r->key);
		inorder(r->right);
	}
}

void preorder(node *r){ // mostra nodos da arvore  metodo preorder
	if(r){
		
		printf("%d",r->key);
		preorder(r->left);
		preorder(r->right);
	}
}

void posorder(node *r){ // mostra nodos da arvore  metodo posorder
	if(r){
		posorder(r->left);
		posorder(r->right);
		printf("%d",r->key);
	}
}

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

	n->pai = it;
	return r;
	
}

node * remove(node *r,int v){
	
	if(r == NULL){   
		return NULL;
	}
	else if (r->key > v){
		r->left = remove(r->right ,v);
	}
	else if(r->key < v){
		r->right = remove(r->right , v);
	}
	else{
		if(!r->left && !r->right){ // nodo sem filhos
			free(r);
			r = NULL;
		}
	
		else if(!r->left){ // nodo com filho a direita
			node *t = r;
			r= r->right;
			free(t); 
		}

		else if(!r->right){ // nodo com filho a esquerda
			node *t = r;
			r= r->left;
			free(t); 
		}

		else{ // nodo com dois filhos
			node * f= r->left;
			while (f->right != NULL){
				f = f->right;
			}
		
			r->key = f->key; // faz as trocas
			f->key = v;
			r->left = remove(r->left , v);
		}
	}
	
	return r;
}

int main ( void ){
	
	int key , opc;
	tree t;
	node * aux;
	t.raiz = NULL;

	
	while (scanf("%d", &key)){
		t.raiz= insert(t.raiz,key);
	}

	fflush(stdin);
	getchar();

	while(opc != 0 ){

		printf("\n1-Travessia Preorder\n2-Travessia Posrder\n3-Travessia Inorder\n4-Remover Elemento\n5-Buscar Elemento\n0-Sair\n");
		scanf("%d",&opc);


		switch(opc){
			case 0 :
				return 0;
			case 1:
				preorder(t.raiz);
				break;
			case 2:
				posorder(t.raiz);
				break;
			case 3:
				inorder(t.raiz);
				break;
			case 4 :
				printf("elemento a deletar : ");
				scanf("%d",&key);

				aux  = search(t.raiz , key);
				if(!aux) printf("chave não existe\n"); 

				else {
					printf("chave a ser deletada : %d",key);
					aux = remove(t.raiz,key);
				}
				break;
			case 5:
				printf("elemento  a buscar:\n");
				scanf("%d",&key);
				aux = search(t.raiz,key);
				if(!aux) printf("a chave não existe\n");
				else if(aux->key == key) printf("encontrou %d !!\n",aux->key );
				break;
			default:
				printf("opcao invalida\n");
				break;
		}
	}

	return 0;
}





