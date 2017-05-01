/* Variables que es necesario definir en el juego */
#define N 8
#define VALOR_VICTORIA 1024
#define FICHA_CPU 'X'
#define FICHA_JUGADOR 'O'

void ImprimirTablero(char [N][N]);
int Posibilidades(char [N][N]);
int VictoriaCPU(char partida[N][N]);
int VictoriaJugador(char partida[N][N]);
void AplicarTirada(char [N][N],int ,char );
double Heuristica(char [N][N]);
