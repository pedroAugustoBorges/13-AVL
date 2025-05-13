#include <iostream>
using namespace std;

/* -----------------------------------------------------------
   Estrutura do nó da Árvore AVL
----------------------------------------------------------- */
struct NO {
    int valor;
    NO* esq;
    NO* dir;
    int altura;       // usado para o balanceamento
};

/* Raiz da árvore (global para simplificar o exemplo didático) */
NO* raiz = NULL;

/* ----------------- Protótipos ----------------------------- */
// Interface principal
void menu();
void inicializar();
void inserir();
void exibir();
void exibirQuantidade();
void buscar();

// Funções auxiliares da árvore
NO* insereArvore(NO* no, int valor);
NO* criaNO(int valor);
int   elementosArvore(NO* no);
void  exibirElementosArvore(NO* no, int espaco, bool direita);
void  buscarElementoArvore(NO* no, int valor);

// Funções auxiliares de balanceamento
int   alturaNo(NO* no);
int   fatorBalanceamento(NO* no);
NO* girarDireita(NO* no);
NO* girarEsquerda(NO* no);
int   maior(int a, int b);

/* ================= IMPLEMENTAÇÃO ========================= */
// ---------- Funções de interface ---------
int main() {
    menu();
}

void menu() {
    int op = 0;
    while (op != 6) {
        system("cls");                // Limpa console (Windows)
        cout << "========== Menu Arvore AVL ==========\n\n";
        cout << "1 - Inicializar Arvore\n";
        cout << "2 - Exibir quantidade de elementos\n";
        cout << "3 - Inserir elemento\n";
        cout << "4 - Exibir arvore\n";
        cout << "5 - Buscar elemento\n";
        cout << "6 - Sair\n\n";
        cout << "Opcao: ";
        cin >> op;

        switch (op) {
                   case 1:
                       inicializar();
                       break;
                   case 2:
                       exibirQuantidade();
                       break;
                   case 3:
                       inserir();
                       break;
                   case 4:
                       exibir();
                       break;
                   case 5:
                       buscar();
                       break;
               }

		cout << endl; 
        if (op != 6) system("pause"); // Aguarda tecla (Windows)
    }
}

void inicializar() {
    raiz = NULL;
    cout << "Arvore inicializada!\n";
}

void inserir() {
    int v;
    cout << "Digite o elemento: ";
    cin >> v;
    raiz = insereArvore(raiz, v);
}

void exibirQuantidade() {
    cout << "Quantidade de elementos: "
        << elementosArvore(raiz) << "\n";
}

void exibir() {
    if (raiz == NULL) {
        cout << "Arvore vazia!\n";
        return;
    }
    cout << "\n===== Estrutura da Arvore (raiz no topo) =====\n\n";
    exibirElementosArvore(raiz, 0, false);
}

void buscar() {
    int v;
    cout << "Digite o elemento: ";
    cin >> v;
    buscarElementoArvore(raiz, v);
}

// ---------- Criação e inserção ----------
NO* criaNO(int valor) {
    NO* novo = (NO*)malloc(sizeof(NO));
    if (novo == NULL) return NULL;      // Falha de alocação

    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 0;
    return novo;
}

int alturaNo(NO* no) {
    if (no == NULL) return -1;
    return no->altura;
}

int maior(int a, int b) {
    if (a > b) return a;
    return b;
}

int fatorBalanceamento(NO* no) {
    if (no == NULL) return 0;
    return alturaNo(no->esq) - alturaNo(no->dir);
}

NO* girarDireita(NO* no) {  
   /* Rotação simples à direita  
             y                x  
            / \              / \  
           x   T3   =>      T1  y  
          / \                  / \  
        T1  T2               T2  T3  
   */  

   // Passo 1: Armazene o filho esquerdo de 'y' em uma variável temporária 'x'.  
   // Passo 2: Transfira a subárvore direita de 'x' para a subárvore esquerda de 'y'.  
   // Passo 3: Atualize 'x' para ser o novo nó raiz da subárvore.  
   // Passo 4: Recalcule as alturas dos nós afetados.  
   // Passo 5: Retorne o novo nó raiz ('x').  

	// provisoriamente retorna o ponteiro passado como parâmetro

    NO* l = no->esq;
    NO*lr = l->dir;
   
    l->dir = no;
    no->esq = lr;

    // recalcular altura

    int altEsqNo = alturaNo(no->esq);
    int altDirNo = alturaNo(no->dir);

    no->altura = maior(altEsqNo, altDirNo) + 1;

    int altEsqL = alturaNo(l->esq);
    int altDirL = alturaNo(l->dir);
    l->altura = maior(altEsqL, altDirL) + 1;


    
	return l; 
}  

NO* girarEsquerda(NO* no) {  
   /* Rotação simples à esquerda  
           x                    y  
          / \                  / \  
         T1  y      =>        x  T3  
            / \              / \  
           T2 T3            T1 T2  
   */  

   // Passo 1: Armazene o filho direito de 'x' em uma variável temporária 'y'.  
   // Passo 2: Transfira a subárvore esquerda de 'y' para a subárvore direita de 'x'.  
   // Passo 3: Atualize 'y' para ser o novo nó raiz da subárvore.  
   // Passo 4: Recalcule as alturas dos nós afetados.  
   // Passo 5: Retorne o novo nó raiz ('y').  


    // provisoriamente retorna o ponteiro passado como parâmetro

    NO* r = no->dir;

    NO* rl = r->esq;

    r->esq = no;

    no->dir = rl;

    int altEsqNo = alturaNo(no->esq);
    int altDirNo = alturaNo(no->dir);
    no->altura = maior(altEsqNo, altDirNo) + 1;

    int altEsq = alturaNo(r->esq);
    int altDir = alturaNo(r->dir);
   r->altura = maior(altEsq, altDir) + 1;


    return r; 
}

NO* insereArvore(NO* no, int valor) {
    /* Inserção binária normal ----------------------------- */
    if (no == NULL) {
        return criaNO(valor);
    }

    if (valor < no->valor) {
        no->esq = insereArvore(no->esq, valor);
    }
    else if (valor > no->valor) {
        no->dir = insereArvore(no->dir, valor);
    }
    else {
        /* Valor já existe – não insere duplicado */
        return no;
    }

    /* Atualiza altura do nó */
    int altEsq = alturaNo(no->esq);
    int altDir = alturaNo(no->dir);
    no->altura = maior(altEsq, altDir) + 1;

    /* ---------- Balanceamento AVL ---------- */
    int fb = fatorBalanceamento(no);

    // Caso Esquerda-Esquerda
    if (fb > 1 && valor < no->esq->valor)
        return girarDireita(no);

    // Caso Direita-Direita
    if (fb < -1 && valor > no->dir->valor)
        return girarEsquerda(no);

    // Caso Esquerda-Direita
    if (fb > 1 && valor > no->esq->valor) {
        no->esq = girarEsquerda(no->esq);
        return girarDireita(no);
    }

    // Caso Direita-Esquerda
    if (fb < -1 && valor < no->dir->valor) {
        no->dir = girarDireita(no->dir);
        return girarEsquerda(no);
    }

    return no; // nenhum desbalanceamento
}

// ---------- Utilidades ----------
int elementosArvore(NO* no) {
    if (no == NULL) return 0;
    return 1 + elementosArvore(no->esq) + elementosArvore(no->dir);
}

void exibirElementosArvore(NO* no, int espaco, bool direita) {
    /* Impressão recursiva “deitada”:
       └── valor
          ├── ...
          └── ...
    */
    if (no == NULL) return;

    const int DIST = 6; // deslocamento entre níveis
    espaco += DIST;

    // Exibe primeiro a subárvore direita (fica “em cima” no console)
    exibirElementosArvore(no->dir, espaco, true);

    // Impressão do nó atual
    cout << endl;
    for (int i = DIST; i < espaco; i++) cout << " ";

    if (direita)
        cout << "/-- ";
    else
        cout << "\\-- ";

    cout << no->valor << endl;

    // Exibe subárvore esquerda
    exibirElementosArvore(no->esq, espaco, false);
}

void buscarElementoArvore(NO* no, int valor) {
    if (no == NULL) {
        cout << "Elemento NAO encontrado.\n";
        return;
    }

    if (valor == no->valor) {
        cout << "Elemento encontrado!\n";
        return;
    }

    if (valor < no->valor)
        buscarElementoArvore(no->esq, valor);
    else
        buscarElementoArvore(no->dir, valor);
}
