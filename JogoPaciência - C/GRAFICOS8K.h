#define NUMERO_COLUNAS 7
#define NUMERO_FILEIRAS 7
#define ESPACO_ENTRE_CARTAS 3
#define tf 100

void LimparOpcao() {
	
	textcolor(15);
    textbackground(0);
	
    for (int i = 12; i <= 19; i++) 
	{
        gotoxy(63, i);
        for (int j = 68; j <= 105; j++) 
		{ 
            printf(" ");
        }
    }
}

void LimparCarta(int x, int y) {
	
	textcolor(15);
    textbackground(2);
	
    int larguraCarta = 6; 
    int alturaCarta = 5; 

    for (int i = y; i < y + alturaCarta; i++) {
        for (int j = x; j < x + larguraCarta; j++) {
            gotoxy(j, i);
            printf(" ");
        }
    }
}

void LimparTabuleiro() {
	textbackground(2);
	
    for (int i = 2; i <= 36; i++) 
	{
        gotoxy(2, i);
        for (int j = 0; j <= 58; j++) 
		{ 
            printf(" ");
        }
    }
}

void LimparBase() {
	textbackground(2);
	
	for (int i = 21; i <= 36; i++) 
	{
        gotoxy(63, i);
        for (int j = 68; j <= 109; j++) 
		{ 
            printf(" ");
        }
    }
}

void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF)
{
	int i;
	textcolor(CorT);
	textbackground(CorF);
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CF,LF);
	printf("%c",188);
	for(i=CI+1; i<CF; i++)
	{
		gotoxy(i,LI); printf("%c",111);
		gotoxy(i,LF); printf("%c",111);
	}
	for(i=LI+1; i<LF; i++)
	{
		gotoxy(CI,i); printf("%c",186);
		gotoxy(CF,i); printf("%c",186);
	}
}


void desenharCarta(int x, int y, int valor, char naipe) {
    textbackground(15);
    
    switch (naipe) {
        case 'p':
            textcolor(0);
            break;
        case 'c':
            textcolor(4);
            break;
        case 'e':
            textcolor(0);
            break;
        case 'o':
            textcolor(4);
            break;
        default:
            textcolor(15);
            break;
    }
    
    gotoxy(x, y);   printf("x----x");
    
    gotoxy(x, y+1); 
    if (valor == 1) {
        printf("|A  %c|", naipe);
    } else if (valor == 11) {
        printf("|J  %c|", naipe);
    } else if (valor == 12) {
        printf("|Q  %c|", naipe);
    } else if (valor == 13) {
        printf("|K  %c|", naipe);
    } else if (valor == 10) {
        printf("|%d %c|", valor, naipe);
    }else {
    	printf("|%d  %c|", valor, naipe);
	}
	
    gotoxy(x, y+2); printf("|    |");
    gotoxy(x, y+3); printf("|    |");
    gotoxy(x, y+4); printf("x----x");
}

void desenharCartaViradaParaBaixo(int x, int y) {
	
	textcolor(8);
	textbackground(15);
    gotoxy(x, y);   printf("+----+");
    gotoxy(x, y+1); printf("|####|");
    gotoxy(x, y+2); printf("|####|");
    gotoxy(x, y+3); printf("|####|");
    gotoxy(x, y+4); printf("+----+");
}

void desenharBase(int x, int y, char naipe) {
	
    textcolor(8);
	textbackground(15);
    gotoxy(x, y);   printf("©----©");
    gotoxy(x, y+1); printf("|%c   |", naipe);
    gotoxy(x, y+2); printf("|    |");
    gotoxy(x, y+3); printf("|   %c|", naipe);
    gotoxy(x, y+4); printf("©----©");
}

void inserirCartaParaBaixo(int posicaoX, int posicaoY) {
	
	textcolor(15);
	textbackground(2);
	
    if (posicaoX < 0 || posicaoX >= NUMERO_COLUNAS || posicaoY < 0) {
        return;
    }

    desenharCartaViradaParaBaixo((posicaoX * 8) + 4, (posicaoY*2 ) + 3);	
}
 
void inicializarBase() {
	
	textcolor(0);
    textbackground(15);
	
	gotoxy(63, 29);
    printf("                   Base                   ");
	 
	char naipes[] = {'p', 'c', 'e', 'o'};
	int coluna,i = 0;
    for (coluna = NUMERO_COLUNAS; coluna < NUMERO_COLUNAS + 4; coluna++) {
        desenharBase((coluna * 10) - 4 , 31, naipes[i]);
        i++;
    }
}

void inserirCarta(int valor, char naipe, int posicaoX, int posicaoY) {
    if (posicaoX < 0 || posicaoX >= NUMERO_COLUNAS || posicaoY < 0) {
        return;
    }

    desenharCarta((posicaoX * 8) + 4, (posicaoY*2 ) + 3 ,valor, naipe);
}

void inserirCartaBase(int valor, char naipe) {

    if (naipe != 'p' && naipe != 'c' && naipe != 'e' && naipe != 'o') {
        gotoxy(73, 19);
        printf("Naipe inválido!");
        return;
    }

    int posicaoX;
    switch (naipe) {
        case 'p':
            posicaoX = NUMERO_COLUNAS;
            break;
        case 'c':
            posicaoX = NUMERO_COLUNAS + 1;
            break;
        case 'e':
            posicaoX = NUMERO_COLUNAS + 2;
            break;
        case 'o':
            posicaoX = NUMERO_COLUNAS + 3;
            break;
        default:
            break;
    }

    desenharCarta((posicaoX * 10) - 4, 35, valor, naipe);
}

void removerCarta(int posicaoX, int posicaoY) {
    if (posicaoX < 0 || posicaoX >= NUMERO_COLUNAS || posicaoY < 0 ) {
    	gotoxy(73, 19);
        printf("Posição inválida!");
        return;
    }

    LimparCarta((posicaoX * 8) + 4, (posicaoY * 2) + 3);
}

char MenuPrincipal(void)
{
    LimparOpcao();
    
    textcolor(0);
    textbackground(15);
    gotoxy(63, 2);
    printf("       Bem-Vindo ao Paciência Online      ");
    
	textcolor(15);
	textbackground(0);
    gotoxy(65, 4);
    printf("[1] Mover carta de uma Pilha --> Pilha");
    gotoxy(65, 5);
    printf("[2] Mover carta de uma Pilha --> Base");
    gotoxy(65, 6);
    printf("[3] Mover carta de uma Base --> Pilha");
    gotoxy(65, 7);
    printf("[4] Mover carta do Baralho --> Pilha");
    gotoxy(65, 8);
    printf("[5] Mover carta do Baralho --> Base");
    gotoxy(65, 9);
    printf("[6] Pegar carta do Baralho");
    gotoxy(65, 10);
    printf("[7] Recomeçar");
    gotoxy(93, 10);
    printf("[ESC] Sair");
    
	gotoxy(65,12);
	printf("Escolha: ");
    gotoxy(73, 12);
 
    return toupper(getche());
}

void inicializarBaralho(){
	
	textcolor(0);
    textbackground(15);
	
	gotoxy(63, 21);
    printf("                 Baralho                  ");
    
    
    desenharCartaViradaParaBaixo(66, 23);
    desenharCartaViradaParaBaixo(68, 23);
}

void TelaMoldura(void)
{

	Moldura(1,1,61,37,8,8);
	Moldura(62,1,105,20,8,8);
	Moldura(62,20,105,37,8,8);
}

void imprimirColuna(Baralho coluna, int posicaoColuna) {
    
    if (!Vazia(coluna.num_cartas)) {
        
        for (int linha = 0; linha <= coluna.num_cartas; linha++) {
            Carta carta = coluna.cartas[linha];
            if (carta.praCima == 1) {
                
                inserirCarta(carta.numero, carta.naipe, posicaoColuna, linha);
            } else {
                
                inserirCartaParaBaixo(posicaoColuna, linha);
            }
        }
    }
    
    gotoxy(73, 12);
}

void desenharTabuleiro(Baralho &c1, Baralho &c2, Baralho &c3, Baralho &c4, Baralho &c5, Baralho &c6, Baralho &c7){
	
	LimparTabuleiro();
	
	imprimirColuna(c1, 0);
	imprimirColuna(c2, 1);
	imprimirColuna(c3, 2);
	imprimirColuna(c4, 3);
	imprimirColuna(c5, 4);
	imprimirColuna(c6, 5);
	imprimirColuna(c7, 6);
	
	gotoxy(73, 12);
}

void desenharMenu(){
	
	TelaMoldura();
	
	LimparBase();
	
    inicializarBase();
    
    inicializarBaralho();
    
    gotoxy(73, 12);
}
