typedef struct nodo{
	struct nodo **hijos;
	int *movimientos;
	int n_hijos;
	char tablero[N][N];
	double valor;
	int nivel;
} Nodo;

void CopiaTablero(char [N][N],char [N][N]);
Nodo CreaNodo(char [N][N],int ,int );
void CreaNivel(Nodo *,char ,int );
void CreaDobleNivel(Nodo *,int );
void CreaArbol(Nodo *,int ,int );
void BorraArbol(Nodo *);
void ImprimirArbol(Nodo *);
void ValorarHojas(Nodo *);
void MiniMax(Nodo *);
int ElegirTirada(char [N][N],int );