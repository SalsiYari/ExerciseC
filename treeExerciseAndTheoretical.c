/*albero:
-OGNI nodo rappresenta un passo della ricorsione
-ogni nodo NON FOGLIA corrisponde ad una soluzione parziale del problema
-ogni nodo foglia rappresenta una possibile soluzione che verrà verificata
-ogni ramo dell'albero corrisponde ad una scelta(chiamata della funz ricorsiava)
-ogni livello (e quindi ogni nodo che appartiene a quel livello) è associato ad indice i
-----------------------------------------------------------------------------------------
*/
//ombrelloni
(k)amici (n)ombrelloni senza essere vicini tra loro. (i)la posizione attuale(corrisponde 
al livello dell'albero che stiamo esplorando). vcurr, array->indica lo stato delgi omb
(1=occ),all'inizio tutti 0. (cnt), contatore per il num ragazzi posizionati nella sol
cornte, non indispen. nsol,il numero totale di soluzioni trovate
	
visualizziamo lo stato di sol completo, SENZA IL PRUNING

//ad ogni nodo posso scegliere se posizionare o no un ragazzo (DUE SCELTE)
//ho n+1 livelli=5 dell'albero (da 0 a 4)

void ombrelloni(int k,int n,unsigned i,bool *vcurr, unsigned cnt,unsigned *nsol){
	
	if(i==n){					//arrivato alla foglia vedo se la soluzione va bene
	
		if(cnt!=k)  			//errore dovevo posizionare 2 ragazzi
			return;
		for(int j=1;j<n-1;j++){ //-----> evito di accedere a posizioni errate
			if(vcurr[j]== 1 && (vcurr[j-1]==1 && vcurr[j+1]==1))
				return;
		}
		//stampa e conta la soluzione
		(*nsol)++;
		for(int j=0;j<n;j++){
			printf("%d",vcurr[j]);																					
		}
		return;
	}
	vcurr[i]=0; 							//lascio libero l'ombrellone corrente 
	ombrelloni(k,n,i+1,vcurr,cnt,nsol);
	
	vcurr[i]=1; 							//posiziono un ragazzo nel corrente
	ombrelloni(k,n,i+1,vcurr,cnt+1,nsol);//->il +1->"conto che ho incrementato un ragazzo"
}
pruning POTATURA dell'albero -> se ho 01 scarto la possibilità di andare verso un altro 1
//se posiziono due ragazzi senza essere arrivato alla foglia-> non ha senso continuare
//PROBLEMA: vcurr essendo condiviso tra le soluzioni, trovato un 101->lui me la stampa
//(anche se magri prima mi ritrovavo un 1001) stampando quindi un->1011(errata)
//aggiorniamo quindi il vettore posizione aggiungendo 0 a tutte le posizioni sucessive a
// quella corrente ---> memset(vcurr+1,0,(n-)*sizeof(bool)

void ombrelloni(int k,int n,unsigned i,bool *vcurr, unsigned cnt,unsigned *nsol){
	if(cnt==k){ //posizionati k ragazzi ho una sol valida
		(*nsol)++;
		memset(vcurr+1,0,(n-i)*sizeof(bool));
		for(int j=0;j<n;j++){
			printf("%d",vcurr[j]);
		}
		return;
	}
	//ma allora arrivato alla foglia ho già fatto tutto
	if(i==n)
		return;
	
	vcurr[i]=0; 								//lascio libero l'ombrellone corrente 
	ombrelloni(k,n,i+1,vcurr,cnt,nsol);
	
//se sono a liv 0 oppure se sono ad un altro liv e l'ombrellone in posizione i-1 è libero:
	if(i==0 || (i>0 && vcurr[i-1]==0)){ 
		vcurr[i]=1; 							//posiziono un ragazzo nel corrente
		ombrelloni(k,n,i+1,vcurr,cnt+1,nsol);
	}
}

int main(void){
	int ...
	
	bool *vcurr=malloc(n*sizeof(bool));			//soluzione corrente vett n elementi
	
	ombrelloni(k,n,0,vcurr,0,&nsol);
	
	free(vcurr);
	
	return 0;//return EXIT_SUCCESS;
}
-----------------------------------------------------------------------------------------
//babbonatale
slitta con portata massima(p)Kg. funzione deve individuare tra (n)regali di peso pacchi[i]
quali caricare per MASIMIZZARE il numero totale occhio alla portata. output su stdout 
es: se ho p=20 pacchi={10,11,1,3,3} l'output deve essere 0 1 1 1 1
/*
pacchi->vettore che mi dice il peso di ogni pacco, n-> dimensione pacchi[](numero pacchi), 
vcurr-> soluzione attuale, vbest->soluzione migliore trovata fino a questo momento (bool),
max-> numero regali in vbest, cnt-> numero regali in vcurr, sum-> somma dei pesi in vcurr
questi ultimi due sono anche ricavabili ma è più comodo portaresli dietro*/
 
//albero -> tanti livelli quanti pacchi; sempre due scelte possibili;  pruning 
 
#incl..
void babbonatale(int p,int const *pacchi, int n,unsigned i,bool *vcurr,bool *vbest,
											unsigned *max, unsigned cnt, int sum){
	
	if(i==n){
		if(cnt >(*max)){
			(*max)=cnt;
			//copio dentro vbestgli elementi di vcurr , specifico uanti byte
			memcp(vbest,vcurr,n*sizeof(bool));
		}
		return;
	}
	
	vcurr[i]=0;
	babbonatale(p,pacchi,n,i+1,vcurr,vbest,&max,cnt,sum); 
	
	if( sum+pacchi[i] <=p){   //se pacchiCaricati + pesoPaccoCorrente rispetta la portata
		vcurr[i]=1;
		babbonatale(p,pacchi,n,i+1,vcurr,vbest,&max,cnt+1,sum + pacchi[i]);
	}
}

int main(void){
	int p=20;
	unsigned pacchi[]={10,11,1,3,3};		//pesi pacchi
	int n=sizeof(pacchi)/sizeof(unsigned);	//numero pacchi
	unsigned max=0;							//pacchi caricati nella soluzione best
	
	bool *vbest,*vcurr;
	vbest=calloc(n,sizeof(bool));			//soluzione ottima
	vcurr=mallco(n*sizeof(bool)); 			// soluzione corrente
	
	babbonatale(p,pacchi,n,0,vcurr,vbest,&max,0,0);	
	
	for(int i=0;i<n;i++){
		printf("%d",vbest[i]);
	}
	printf("\n");
	free(vbest);
	free(vcurr);
	return 0;
}
------------------------------------------------------------------------------------------
//torre dei cartoni
(n) cartoni, ogni carone ha ...deve stampare su stdout la SOL OTTIMA in "verticale" 
es: con c={{.p=10,.a=20,.l=40},{.p=10,.a=10,.l=8},{.p=9,.a=3,.l=5}} avrà il seg output:
1
0
altezza: 30 cm
//ogni cartone è un numero che corrisponde al indice nel vettore c 1° indice: testa torre)
//occorre UNA FUNZIONE ASUILIARIA perchè i parametri c e n non suff per il backtracking
//inoltre definiamo una struttura dati ausiliaria che ci identifica la torre
//ho tante SCELTE quanti cartoni disponibili. prima scelta che faccio è il cartone che 
//metterò in cima; cogni volta che scendo dall'albero avrò n-1 scelte
//PRUNING ->se il pacco 0 ha peso 10 Kg e il pacco 1 ha 9Kg:quel ramo non posso esplorarlo
//I LIVELLI sono in funzione dei cartoni disponibili

-nel fie torrecartoni.h-
#ifndef TORRE_CARTONI_H
#define TORRE_CARTONI_H
typedef struct{
	unsigned p;				//peso grammi
	unsigned a;				//altezza cm
	unsigned l; 			//peso massimo che può sostenere
} cartone;
#endif //TORRE_CARTONI_H

-nel file torrecartoni.c-
#include <stdlib.h>
#include <torrecartoni.h>
#in...

typedef struct{
	unsigned a; 			//altezza
	int *c_ids; //vettore di caroni, indica indici dei cartoni utilizzati (testa al basso)
	int size; 	//dimensione effettiva della torre(vettore)
} torre;
//funz ausiliaria
void Backtracking (cartone *c,int n,int i,torre *vcurr,torre *vbest,bool *usati,){	
	if(i == n){
		if(vcurr->a < vbest->a){
			vbest->a = curr->a ;
			vbest->size =c urr->size ;
			memcpy(vbest->c_ids , vcurr->c_ids , vcurr->size * sizeof(int)) ;	/
			//metto dentro vbest->c_ids i dati di vcurr->c_ids, tenti byte quanti...
			}
		return;
	}
	unsigned p = 0;
	for(int j = 0 ; j < n ; j++){	//calcoliamo la somma dei pesi della sol corrente
		p=p+c[vcurr->c_ids[j]].p;	//vcurr->c_ids: contenitore di indici (i pacchi usati)
	}
	for(int j = 0 ; j < n ; j++){	//n perchè "ad ogni passo una scelta"(numero di pacchi
		if( !usati[j] ){			//se il cartone jesimo non è stato usato
			if(p <= c[j].l ){
				vcurr->a = vcurr->a + c[j].a;	//aggiornamento di i soluzione corrente
				vcurr->c_ids[vcurr->size] = j;
				vcurr[j] -> size++;
				vcurr[j] = 1;
				
				Backtracking(c,n,i+1,vcurr,vbest,usati;)
				
//tornati in dietro(di un nodo dell'albero) l'aggiornamento di i deve essere annullato
				vcurr->a = vcurr->a - c[j].a ;					
				//vcurr->c_ids[vcurr->size] = j;	<-posso ignorarlo perchè la size 
				vcurr[j] -> size--;
				vcurr[j] = 0;
			}
			else
				Backtracking(c,n,n,vcurr,vbest,usati;)	//caso non trovo pacchi corretti 
//in questo modo fingiamo che siamo ad un caso base(qualora avessi solo un pacco)
		}		
	}
}

void TorreCartoni (cartone *c,int n){
	bool *usati = calloc(n , sizeof(n));	//vettore quali cartoni usati->inizia. a falso
	torre vcurr={.p=0,.c_ids=malloc(n*sizeof(bool);}	//struct simil "vettore corrente"
	torre vbest={.p=0,.c_ids=malloc(n*sizeof(bool);}
	
	Backtracking( c , n , 0 , &vcurr , &vbest , usati);
	 
	for(int j = 0 ; j < vbest.size ; j++){
		printf("%i\n",vbest.c_ids[i]);
	}
	printf("Altezza : %i cm",vbest.a);
	
	free(usati);
	free(vcurr.c_ids);
	free(vbest.c_ids);
	
	return;
}

int main(void){
	cartone c1[] = {{.p=10,.a=20,.l=40},{.p=10,.a=10,.l=8},{.p=9,.a=3,.l=5}}
	int n1 = sizeof(c1) / sizeof(cartone);
	TorreCartoni(c1,n1);
	}
------------------------------------------------------------------------------------------
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
------------------------------------------------------------------------------------------
|LISTE|

siano date:							// funzioni specifiche per la creazione,eliminzaione..
struct ElemType{					int ElemCompare(const ElemType *e1,const ElemType *e2)
	int *data;						ElemType ElemCopy(const ElemType *e);
	size_t size;					void ElemDelete(ElemType *e);
};									ElemType ReadElem(FILE *f);
typedef struct ElemType ElemType;	ElemType ReadStdinElem();
									void WriteElem(const ElemType *e, FILE *f);
truct Item{							void WriteStdoutElem(const ElemType *e);
	ElemType value;												
	struct Item *next;			//funzioni primitive e non
};								Item* CreateEmptyList(void);
typedef struct Item Item;		Item* InsertheadList(const ElemType *e,item* i);
								bool IsEmptylist(const item *i);
								Item* GetTailList(const Item* i);
								item* InsertBackList(Item* i, const ElemType *e);
								void DeleteList(item* item);
								void WriteList(const Item *i,FILE *f);
								void WriteStdoutList(const Item *i);
------------------------------------------------------------------------------------------
//INTRASEC
funzione,in input due liste (puntatori alla testa) e ne restituisce una terza(punt..) 
contenente tutti i valori presenti in entrambe le liste di input. SI uso delle PRIMITIVE

#define _CRT_SECURE_NO_WARNINGS
#include "list_int.h"
//definire una funzione ausiliaria->se un elemento è presente o meno in una lista(bool)
bool Contains(const Item* i, const ElemType *e) {
    bool found = false;
    while (!IsEmptyList(i) && !found) {
        found = (ElemCompare(GetHeadValueList(i), e) == 0); //true se i(elem testa)= e
        i = GetTailList(i);									//ritorna il next (elemento)
    }
    return found;
}

Item* Intersect(const Item* i1, const Item* i2) { 
    Item * r = CreateEmptyList();						//creo una nuova lista
    while (!IsEmptyList(i1)) {							//scorro una delle due liste
        const ElemType *cur = GetHeadValueList(i1);		//puntat all'elemento temporaneo
        if (Contains(i2, cur)) 							//controllo se la testa è in i2
            r = InsertHeadList(cur, r);

        i1 = GetTailList(i1); 							// i1 = i1->next;
    }
    return r;
}

Item* LoadList(const char *filename)
{
    FILE *f;
    f = fopen(filename, "r");

    Item *i = CreateEmptyList();
    if (!f) 
        return i; // return NULL

    while (1) {
        ElemType tmp;
        if (1 != ReadElem(f, &tmp))
            break;
        i = InsertHeadList(&tmp, i);
    }
    fclose(f);
    return i;
}
int main(void) {			
    
        Item* i1 = LoadList("data_00.txt");
        Item* i2 = LoadList("data_01.txt");
        Item* r = Intersect(i1, i2);
        WriteStdoutList(r);
        DeleteList(i1);
        DeleteList(i2);
        DeleteList(r);
}								
------------------------------------------------------------------------------------------
//DIFF
//prende input 2 liste(puntatori alla testa) e restituisce una terza lista (puntatore 
//a testa)costruita da 0,contenente tutti i valori presenti in I1 che non compaiono in i2. 
SENZA usare le primitive			//							\\->i3=i1-i2 

#define _CRT_SECURE_NO_WARNINGS
#include "list_int.h"
#include <stdlib.h>  

bool ConainsNoPrimitives(const Item* i,const ElemType *e){	//elemento presente o meno 
	bool found = false;;
	while (i && !found ){									//equivale a finchè i vero
		found = i->value == *e; 		  //value a found ->true se il valore di e = i
		i = i->next; 					  //i = GetTailList(i);
	}
	return found;
}
Item* Diff(const Item* i1 , const Item* i2){
	Item* r = NULL; 										// creo una lista vuota
	while(i1 != NULL){								//si può scrivere come while(i1)
		ElemType cur = i1->value;
		if( !ContainsNoPrimitives( i2 , &cur ) ){
			Item *new_i = malloc(sizeof(Item));			//ins in testa
			new_i->value = cur;							//senza usare
			new_i->next = r;							//primitive
			r = new_i;									//
		}
		i1 = i1->next; 										//per passare all'elem succ
	}
	return r;
}

Item* LoadList(const char *filename){
	FILE *f;
	f = fopen(filename,"r");
	.
	.
}

int main(void) {
    {
        char filename[] = "data_00.txt";
        Item* i = LoadList(filename);
        WriteStdoutList(i);
        ElemType e = MaxElement(i);
        printf("\n%d\n", e);
    }
}
------------------------------------------------------------------------------------------
//MAX
#define _CRT_SECURE_NO_WARNINGS
#include "list_int.h"

ElemType MaxElement(const Item* i) {
    ElemType max = ElemCopy(GetHeadValueList(i));
    for (i = GetTailList(i); !IsEmptyList(i); i = GetTailList(i)) {
        if (ElemCompare(GetHeadValueList(i), &max) > 0) 
            max = ElemCopy(GetHeadValueList(i));
    }
    return max;
}

Item* LoadList(const char *filename) {
    FILE *f;
    .
	.
	.
}

int main(void) 
    {
        char filename[] = "data_00.txt";
        Item* i = LoadList(filename);
        WriteStdoutList(i);
        ElemType e = MaxElement(i);
        printf("\n%d\n", e);
    }
------------------------------------------------------------------------------------------
da ora in poi e per l'esame
ElemType ReadElem(FILE *f); ---diventano --->		int ReadElem(FILE *f,ElemType *e);
ElemType ReadStdinElem();							int ReadStdinElem(ElemType *e);
------------------------------------------------------------------------------------------
//RUBRICA
adattare le primitive da liste di interi a liste di indirizzi

/*struct address{					
	char name[20];
	char street[50]:
	int number;
	char city[30];
	char province[3];
	char postal_code[6]
};
typedef struct address ElemType;

struct item{
	ElemType value;
	struct item *mext;
};
typedef struct Item Item;*/

-nel file.h-
#ifndef LIST_INT_H_ ---> diventa	#ifndef LIST_ADDRESS_H_
#define LIST_INT_H_					#define LIST_ADDRESS_H_
.
.
#endif //LIST_INT_H					#endif //LIST_ADDRESS_H

inoltre modifico la definizione del tipo che da typedef int ElemType; ci metto

struct address{
	char name[20];
	char street[50]:
	int number;
	char city[30];
	char province[3];
	char postal_code[6]
};
typedef struct address ElemType;

-nel file.c-		-->modifico soltanto

void WriteElem(const ElemType *e,FILE *f){
	fprint(f,"%s-%s-%d..",e->name,e->street,e->number,e->city,e->province,e->postal_code);
}
#include <string.h>
int main(void){
	ElemType e1={"federico","roma",50,"mo","41126"};
	ElemType e2={	...			...			};
	ElemType e3={...		...			... };
	
	Item *ab=CreateEmmptyList();		//lista di partenza
	ab = InsertBackList(ab,&e1);
	ab = InsertBackList(ab,&e2);
	ab =  ...     ...
	
	return 0;
}

//funzione find, dato un nome della struttura address,ritorna il puntatore all'elemento
const ElemType* Find(const Item* i,const char *name){
	const Item *tmp = i; 								   //"tmp" lo faccio pure in "i"
	while( !isEmptylist(tmp)){
		if(strcmp(tmp->value.name,name) == 0)			//se trovato l'elemento cercato
			return &tmp->value;					//& perchè serve l'indirizzo dell'elemento
		tmp=GetTailList(tmp);
	}
	return NULL;
}
//preso in input una lista di indirizzi e un nome->l'elemento corrente
Item* Delete(Item *i,const char *name){
	Item *new_list=CreateEmmptyList();
	Item *tmp = i;			//mentre prima tmp superfluo, qui serve perchè vado a liberare
	while( !isEmptylist(tmp)){
		if(strcmp(tmp->value.name,name) != 0)		
			new_list = InsertBackList(new_list, &tmp->value);
		tmp=GetTailList(tmp);
	}
	DeleteList(i);
	return new_list;
}
//ordinamento-> facciamo lo swap del contenuto degli item. trovo il min->e in prima pos
void Swap(Item *a, Item *b) {
    ElemType tmp = b->value;	
    b->value = a->value;
    a->value = tmp;
}
Item* Sort(Item* i) {
    Item *tmp_a = i;
    while (!IsEmptyList(tmp_a)) {					//	per ogni elemento della lista
        Item *tmp_b = tmp_a->next;					//  guardiamo tutti i sucessivi
        while (!IsEmptyList(tmp_b)) {
            if (ElemCompare(GetHeadValueList(tmp_a), GetHeadValueList(tmp_b)) > 0) {
                Swap(tmp_a, tmp_b);
            }
            tmp_b = GetTailList(tmp_b);
        }
        tmp_a = GetTailList(tmp_a);
    }
    return i;
}

------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------
|ALBERI|
//funzione deve aggiungere all'albero avente radice nel nodo puntato da n, un nuovo nodo 
//di chiave e. RISPETTARE LE proprietà BST dopo l'inserimento e ritornare l'albero ris
// (puntatore al nodo radice).se vuoto, ritorno un nuovo albero con solo 1 nodo chiave e.
#include "tree_int.h"
#include "tree_int.h"

Node* BstInsert(const ElemType *e, Node *n)
{
    if (IsEmptyTree(n)) 									//se albero dinput è vuoto
        return CreateRootTree(e, CreateEmptyTree(), CreateEmptyTree());

    Node *root = n;											//traccia della vecchia root

    while (!IsEmptyTree(n)) {								//finchè non è vuoto
        if (ElemCompare(e, GetRootValueTree(n)) <= 0) {		//se la chiave è<=vado a sinix
            if (IsEmptyTree(LeftTree(n))) {					//controllo se è un nodo vuoto
                n->left = CreateRootTree(e, CreateEmptyTree(), CreateEmptyTree());	
				//faccio puntare il sinistro a nodo nuovo di chiave con due figli Null
                n = LeftTree(n);								//sostituibile con break 
            }
            n = LeftTree(n);
        }
        else {							//operazione come la precedente ma l'altro lato
            if (IsEmptyTree(RightTree(n))) {
                n->right = CreateRootTree(e, CreateEmptyTree(), CreateEmptyTree());
                n = RightTree(n);
            }
            n = RightTree(n);
        }
    }
    return root;
}

int main(void) 
{
    ElemType v[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Node* n = CreateRootTree(&v[5], 
        CreateRootTree(&v[3], CreateEmptyTree(), CreateEmptyTree()),
        CreateRootTree(&v[10], CreateEmptyTree(), CreateEmptyTree())
        );
    DeleteTree(n);
}
------------------------------------------------------------------------------------------
//in input un albero bst e ritorna l'indirizzo dell'elemento di valore massimo. o NULL
-BST->IL NODO PIù A DESTRA HA VAL MAX-
#include "tree_int.h"

const ElemType* BstTreeMax(const Node *n)
{
    if (IsEmptyTree(n))							//se nodo vuoto
        return NULL;

    while (!IsEmptyTree(RightTree(n))) {		//finchè c'è un nodo destro (no ricorsione)
        n = RightTree(n);
    }
    return &(n->value);
}
//stessa ma ricorsiva->+ funzione ausiliaria con parametro per il punt a punt del val minimo
-ALBERO GENERICO-
void TreeMinRec(const Node *n, const ElemType **min)
{
    if (IsEmptyTree(n)) 
        return;

    if (n->value < **min) 		//essendo min puntatore a puntare 
        *min = &n->value;		//indirizzo della chiave

    TreeMinRec(LeftTree(n), min);
    TreeMinRec(RightTree(n), min);
}

const ElemType* TreeMin(const Node* n)
{
    if (IsEmptyTree(n)) 
        return NULL;

    const ElemType *min = GetRootValueTree(n);
    TreeMinRec(n, &min);
    return min;
}
//main 
int main(void) 
{
    ElemType v[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    Node* n = CreateRootTree(&v[5], 
        CreateRootTree(
            &v[3],
            CreateRootTree(&v[2], CreateEmptyTree(), CreateEmptyTree()),
            CreateRootTree(&v[8], CreateEmptyTree(), CreateEmptyTree())
            ),
        CreateRootTree(
            &v[10], 
            CreateEmptyTree(),
            CreateEmptyTree())
        );
    
    const ElemType *max = BstTreeMax(n);
    const ElemType *min = TreeMin(n);
    DeleteTree(n);
}
------------------------------------------------------------------------------------------
//funzione prende in input un Albero binario, ritorna il nummero di nodi dominanti->ovvero 
//se non è una foglia e contiene un valore > della somma dei valori  nei suoi due figli
QUANDO DEVO SCORRERE UN ALBERO E ANDARE SIA A SINIX CHE A DX DEVO FARE UNA RICORSIONE
#include "tree_int.h"

int CountDominant(const Node* n) {
    if (IsEmptyTree(n) || IsLeafTree(n)) //se nodo corrente è nodo vuoto o foglia->ret 0
        return 0;
    
    ElemType l = 0, r = 0;				//salvo in due variabili sia left che right nodi
    if (!IsEmptyTree(LeftTree(n))) 					
        l = *GetRootValueTree(LeftTree(n));

    if (!IsEmptyTree(RightTree(n))) 
        r = *GetRootValueTree(RightTree(n));

    int dominant = 0; 								
	//se il nodo corrente ha come chiave un valore >= alla somma dei valori nei figli 
    if (*GetRootValueTree(n) >= r + l) 				
        dominant = 1;

    return dominant + CountDominant(LeftTree(n)) + CountDominant(RightTree(n));
}

int main(void) 
{
    ElemType v[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };				
    Node* n = CreateRootTree(&v[5], 
        CreateRootTree(
            &v[11],
            CreateRootTree(&v[2], CreateEmptyTree(), CreateEmptyTree()),
            CreateRootTree(&v[8], CreateEmptyTree(), CreateEmptyTree())
            ),
        CreateRootTree(
            &v[10], 
            CreateEmptyTree(),
            CreateEmptyTree())
        );
    
    int dom = CountDominant(n);
    DeleteTree(n);
}
------------------------------------------------------------------------------------------
ELIMINAZIONE NODO BST
//input albero BST e una chiave,si elimina dall'albero il nodo avente la chiave specifica
//(se presente), rispettando le prop. BST, ritorno l'albero ottenuto
si possono verificare diversi casi: (3)
(1)se il nodo da el. è foglia->elimino il nodo,aggiorno il padre e ritorno la stessa root 
(2)se il nodo ha un solo figlio->sostituisco il nodo con il figlio
(3)se il nodo ha entrambi i figli->sostituisco il nodo con un nodo che garantisca BST. 
			ovvero è il nodo che si trova nella foglia più a dest del sottoalbero sinix 
#include "tree_int.h"
#include <stdlib.h>

Node* MaximumKey(Node *n){			//mi fermo all'ultimo nodo che trovo a destra
    while (!IsEmptyTree(RightTree(n))) {
        n = RightTree(n);
    }
    return n;
}

Node* DeleteBstNodeRec(Node *n, const ElemType *key)
{
    if (IsEmptyTree(n)) 
        return NULL;

    if (ElemCompare(key, GetRootValueTree(n)) < 0) 				//vado a sinix
        n->left = DeleteBstNodeRec(LeftTree(n), key);
    
    else {
        if (ElemCompare(key, GetRootValueTree(n)) > 0) 			//vado a dx
            n->right = DeleteBstNodeRec(RightTree(n), key);
        
        else {
            // Caso 1: il nodo da eliminare è foglia; 
            if (IsLeafTree(n)) {								//è foglia o no?
                DeleteTree(n);
                return NULL;
            }
            // Caso 3: il nodo da eliminare ha entrambi i figli; 
            else {
                if (LeftTree(n) && RightTree(n)) {
                    Node *predecessor = MaximumKey(LeftTree(n));

                    ElemDelete(&n->value);
                    n->value = ElemCopy(GetRootValueTree(predecessor));
                    n->left = DeleteBstNodeRec(LeftTree(n), GetRootValueTree(predecessor))
                    return n;
                }
                else {
                    // Caso 2: il nodo da eliminare ha un solo figlio; 
                    Node* child = (LeftTree(n)) ? LeftTree(n) : RightTree(n);
                    Node* curr = n;

                    n = child;

                    ElemDelete(&curr->value);
                    free(curr);
                    return n;
                }
            }
        }
    }
    return n;
}

Node* DeleteBstNode(Node *n, const ElemType *key) {
    return DeleteBstNodeRec(n, key);
}

int main(void) 
{
    ElemType v[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    Node* n = CreateRootTree(&v[5], 
        CreateRootTree(
            &v[3],
            CreateRootTree(&v[2], CreateEmptyTree(), CreateEmptyTree()),
            CreateRootTree(&v[8], CreateEmptyTree(), CreateEmptyTree())
            ),
        CreateRootTree(
            &v[10], 
            CreateEmptyTree(),
            CreateEmptyTree())
        );
    
    n = DeleteBstNode(n, &v[2]);
    DeleteTree(n);
}
