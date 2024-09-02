#define MAXPILHA 52
#define MAXPILHA_BASE 13

typedef struct {
    int numero;
    char naipe;
    int praCima; // Indica se a carta está virada para cima ou para baixo
} Carta;

typedef struct {
    Carta cartas[MAXPILHA];
    int num_cartas;
} Baralho;

void inicializarBaralho(Baralho &B) {
	B.num_cartas = -1;
}

void Inicializar(Baralho &B){
	B.num_cartas = -1;
}

void Push(Baralho &B, Carta cartas){
	B.cartas[++B.num_cartas] = cartas;
}

Carta  Pop(Baralho &B){
	return B.cartas[B.num_cartas--];
}

Carta  ElementoTopo(Baralho &B){
	return B.cartas[B.num_cartas];
}

char Vazia(int num_cartas){
	return (num_cartas == -1);
}

char Cheia(int num_cartas){
	return (num_cartas == MAXPILHA-1);
}

void Exibir(Baralho B) {
    while (!Vazia(B.num_cartas)) {
        Carta carta = Pop(B);
        printf("\n CARTA %d / num %d, naipe %c",B.num_cartas+1, carta.numero, carta.naipe );
    }
    printf("\n");
}

void alterarParacimaPilha(Baralho &B) {
	
    B.cartas[B.num_cartas].praCima = 1;
}

Carta criarCartaAleatoria() {
	
    Carta novaCarta;
    novaCarta.numero = rand() % 13 + 1;
    novaCarta.praCima = 0;
    
    switch(rand() % 4) {
    	
        case 0:
            novaCarta.naipe = 'c';
            break;
        case 1:
            novaCarta.naipe = 'p';
            break;
        case 2:
            novaCarta.naipe = 'o';
            break;
        case 3:
            novaCarta.naipe = 'e';
            break;
    }
    
    return novaCarta;
}

// Função auxiliar para verificar se uma carta já existe no baralho
int cartaJaExiste(Carta baralho[], Carta novaCarta, int tamanho) {
    int i;
    
    for (i = 0; i < tamanho; i++) {
        if (baralho[i].numero == novaCarta.numero && baralho[i].naipe == novaCarta.naipe) {
            return 1; // Carta já existe
        }
    }
    return 0; // Carta não existe
}

// Função para criar um baralho completo
void criarBaralho(Carta baralho[]) {
    int i, j;
    int indice = 0;
    Carta novaCarta;

    for (i = 1; i <= 13; i++) {
        for (j = 0; j < 4; j++) {
            do {
                novaCarta = criarCartaAleatoria();
            } while (cartaJaExiste(baralho, novaCarta, indice));

            baralho[indice] = novaCarta;
            indice++;
        }
    }
}

void inicializarPilha(Baralho &B, Carta baralho[], int quantidade) {
    int comeca, termina;

    if (quantidade >= 1 && quantidade <= 7) {
        comeca = 0;
        termina = 0;
        for (int i = 1; i <= quantidade; i++) {
            termina += i;
            Push(B, baralho[termina - 1]);
        }
    } else if (quantidade == 111) {
        comeca = 28;
        termina = 52;
        for (int i = comeca; i < termina; i++) {
            Push(B, baralho[i]);
        }
    }
}

void exibirVetorBaralho(Carta baralho[], int tamanho) {
	
    for (int i = 0; i < tamanho; i++) {
        printf("Carta %d - Valor: %d/%c\n", i+1, baralho[i].numero, baralho[i].naipe);
    }
}

void reabastecerDraw(Baralho &draw, Baralho &descarte) {
	
    if (Vazia(draw.num_cartas)) {
        while (!Vazia(descarte.num_cartas)) {
            Carta carta = Pop(descarte);
            Push(draw, carta);
        }
    }
}

void pegarNovaCarta(Baralho &draw, Baralho &descarte){
	
    if (!Vazia(draw.num_cartas)) {
        Carta carta = Pop(draw);
        Push(descarte, carta);    
    }else{
    	reabastecerDraw(draw, descarte);
        // Após reabastecer, tentar pegar uma carta novamente
        pegarNovaCarta(draw, descarte);
	}
}

int verificacao(Baralho pilhaauxiliar, int cartas) {
    int i;
    
    for (i = 0; i < cartas; i++) {
    	
        Carta cartaAuxiliar = ElementoTopo(pilhaauxiliar);
        
        if (!cartaAuxiliar.praCima)
            return 0; // Se alguma carta não estiver virada para cima, o movimento é inválido
            
        Pop(pilhaauxiliar); // Remove a carta da pilha auxiliar após verificar
    }
    
    return 1; // Todas as cartas estão viradas para cima
}

int moverCarta(Baralho &origem, Baralho &destino,Baralho &pilhaauxiliar,int cartas) {
    int i=0;
    Carta cartaOrigem;
    
    // Verifica se a pilha de origem
    if (Vazia(origem.num_cartas))
        return 0;

	if(cartas == 1){
		cartaOrigem = ElementoTopo(origem);
	}else{
		cartaOrigem = origem.cartas[origem.num_cartas - cartas+1];
	}
    	
    Carta cartaDestino = ElementoTopo(destino);
    
    // se o destino estiver vazio e a carta da origem for um Reis deixar mover.
    if (Vazia(destino.num_cartas) && cartaOrigem.numero == 13 && cartas == 1) {
    	
        Carta cartaMovida = Pop(origem);
        cartaMovida.praCima = 1;
        Push(destino, cartaMovida);
        
        Carta carta = ElementoTopo(origem);
        if (carta.praCima == 0) {
            Carta cartaMudar = Pop(origem);
            cartaMudar.praCima = 1;
            Push(origem, cartaMudar);
        }
        
        return 1; // Movimento bem-sucedido
    }
    
 	if (verificacao(origem, cartas)){
    // Verifica se a carta na pilha de origem pode ser colocada na pilha de destino
    
    	if (cartaOrigem.numero == cartaDestino.numero - 1 && ((cartaOrigem.naipe == 'c' || cartaOrigem.naipe == 'o') && (cartaDestino.naipe == 'p' || cartaDestino.naipe == 'e')) || ((cartaOrigem.naipe == 'p' || cartaOrigem.naipe == 'e') && (cartaDestino.naipe == 'c' || cartaDestino.naipe == 'o'))) {

            for(i=0; i< cartas; i++){
            	
	            Carta cartaMovida = Pop(origem);
	            Push(pilhaauxiliar, cartaMovida);
        	}
                
            for(i=0; i< cartas; i++){
            	
	            Carta cartaMovida2 = Pop(pilhaauxiliar);
	            Push(destino, cartaMovida2);
            }
            
            Carta carta = ElementoTopo(origem);
            if (carta.praCima==0)
            {
            	Carta cartaMudar = Pop(origem);
            	cartaMudar.praCima = 1;
            	Push(origem, cartaMudar);
            }
            
            return 1; // Movimento bem-sucedido
        }    
    }

    return 0; // Movimento inválido
}

int moverCartaBasePilha(Baralho &origem, Baralho &destino) {
    int i=0;

    // Verifica se a pilha de origem 
    if (Vazia(origem.num_cartas))
        return 0;

	Carta cartaOrigem = ElementoTopo(origem);
    Carta cartaDestino = ElementoTopo(destino);
	
	// se o destino estiver vazio e a carta da origem for um Reis deixar mover.
	if (Vazia(destino.num_cartas) && cartaOrigem.numero == 13) {
		
        Carta cartaMovida = Pop(origem);
        cartaMovida.praCima = 1;
        Push(destino, cartaMovida);
        
        Carta carta = ElementoTopo(origem);
        if (carta.praCima == 0) {
            Carta cartaMudar = Pop(origem);
            cartaMudar.praCima = 1;
            Push(origem, cartaMudar);
        }
        
        return 1; // Movimento bem-sucedido
        
    } else if (cartaOrigem.numero == cartaDestino.numero - 1 && ((cartaOrigem.naipe == 'c' || cartaOrigem.naipe == 'o') && (cartaDestino.naipe == 'p' || cartaDestino.naipe == 'e')) || ((cartaOrigem.naipe == 'p' || cartaOrigem.naipe == 'e') && (cartaDestino.naipe == 'c' || cartaDestino.naipe == 'o'))) {

        Carta cartaMovida = Pop(origem);
        cartaMovida.praCima = 1;
    	Push(destino, cartaMovida);
        
        return 1; // Movimento bem-sucedido
    }    
    
    return 0; // Movimento inválido
}

int moverCartaBaralhoBase(Baralho &origem, Baralho &b1_paus, Baralho &b2_copas, Baralho &b3_espada, Baralho &b4_ouro) {
	
    Carta cartaOrigem = ElementoTopo(origem);
    Baralho *destino = NULL; // Usaremos um ponteiro para Baralho para poder atribuir o destino corretamente
    Carta cartaDestino;

    // Verifica o naipe da carta de origem e atribui a pilha de destino apropriada
    if (cartaOrigem.naipe == 'p') {
        destino = &b1_paus;
        cartaDestino = ElementoTopo(b1_paus);
    }
    else if (cartaOrigem.naipe == 'c') {
        destino = &b2_copas;
        cartaDestino = ElementoTopo(b2_copas);
    }
    else if (cartaOrigem.naipe == 'e') {
        destino = &b3_espada;
        cartaDestino = ElementoTopo(b3_espada);
    }
    else if (cartaOrigem.naipe == 'o') {
        destino = &b4_ouro;
        cartaDestino = ElementoTopo(b4_ouro);
    }

    // Verifica se o destino está vazio e se a carta de origem é um Ás (valor 1). Se for verdadeiro, move a carta.
    if (destino != NULL && Vazia(destino->num_cartas) && cartaOrigem.numero == 1) {
    	
        Carta cartaMovida = Pop(origem);
        Push(*destino, cartaMovida);

        Carta carta = ElementoTopo(origem);
        if (carta.praCima == 0) {
            Carta cartaMudar = Pop(origem);
            cartaMudar.praCima = 1;
            Push(origem, cartaMudar);
        }

        return 1; // Movimento bem-sucedido
    }

    // Verifica se o destino não está vazio e se a carta de origem pode ser colocada sobre a carta do destino.
    // (Ou seja, se o número da carta de origem é um a mais do que o número da carta do destino). Se for verdadeiro, move a carta.
    if (destino != NULL && !Vazia(destino->num_cartas) && cartaOrigem.numero == cartaDestino.numero + 1) {

        Carta cartaMovida = Pop(origem);
        Push(*destino, cartaMovida);

        Carta carta = ElementoTopo(origem);
        if (carta.praCima == 0) {
            Carta cartaMudar = Pop(origem);
            cartaMudar.praCima = 1;
            Push(origem, cartaMudar);
        }

        return 1; // Movimento bem-sucedido
    }

    return 0; // Movimento inválido
}

int moverCartaBaralhoPilha(Baralho &origem, Baralho &destino, Baralho &descarte) {
	
    Carta cartaOrigem = ElementoTopo(origem);
    Carta cartaDestino = ElementoTopo(destino);
    
    // se o destino estiver vazio e a carta da origem for um Reis deixar mover.
    if (Vazia(destino.num_cartas) && cartaOrigem.numero == 13) {
		
        Carta cartaMovida = Pop(origem);
        cartaMovida.praCima = 1;
        Push(destino, cartaMovida);
        
        Carta carta = ElementoTopo(origem);
        if (carta.praCima == 0) {
            Carta cartaMudar = Pop(origem);
            cartaMudar.praCima = 1;
            Push(origem, cartaMudar);
        }
        
        //pegar nova carta do baralho
        pegarNovaCarta(origem, descarte);
        
        return 1; // Movimento bem-sucedido
        
    } else if (cartaOrigem.numero == cartaDestino.numero - 1 && ((cartaOrigem.naipe == 'c' || cartaOrigem.naipe == 'o') && (cartaDestino.naipe == 'p' || cartaDestino.naipe == 'e')) || ((cartaOrigem.naipe == 'p' || cartaOrigem.naipe == 'e') && (cartaDestino.naipe == 'c' || cartaDestino.naipe == 'o'))) {

        Carta cartaMovida = Pop(origem);
        cartaMovida.praCima = 1;
    	Push(destino, cartaMovida);
    	
        return 1; // Movimento bem-sucedido
    }
	     
	return 0; // Movimento inválido	
}

int moverCartaPilhaBase(Baralho &origem, Baralho &b1_paus, Baralho &b2_copas, Baralho &b3_espada, Baralho &b4_ouro) {
	
    if (Vazia(origem.num_cartas)) {
        return 0; // A pilha de origem está vazia, nenhum movimento possível
    }

    // Verifica se a pilha de origem não está vazia
    Carta cartaOrigem = ElementoTopo(origem);
    Carta cartaDestino;

    Baralho *destino = NULL;

    // Determina o destino com base no naipe da carta de origem
    if (cartaOrigem.naipe == 'p') {
        destino = &b1_paus;
        cartaDestino = ElementoTopo(b1_paus);
    } else if (cartaOrigem.naipe == 'c') {
        destino = &b2_copas;
        cartaDestino = ElementoTopo(b2_copas);
    } else if (cartaOrigem.naipe == 'e') {
        destino = &b3_espada;
        cartaDestino = ElementoTopo(b3_espada);
    } else if (cartaOrigem.naipe == 'o') {
        destino = &b4_ouro;
        cartaDestino = ElementoTopo(b4_ouro);
    }

    // Se a carta no topo da pilha de origem tiver um valor de "1",
    // mova essa carta para a pilha de destino diretamente
    if (cartaOrigem.numero == 1) {
        Carta cartaMovida = Pop(origem);
        Push(*destino, cartaMovida);
        
        Carta carta = ElementoTopo(origem);
	    if (carta.praCima==0)
	    {
	    	Carta cartaMudar = Pop(origem);
	    	cartaMudar.praCima = 1;
	    	Push(origem, cartaMudar);
	    }
            
        return 1; // Movimento bem-sucedido
    }

    // Verifica se a carta na pilha de origem pode ser colocada na pilha de destino
    if (destino != NULL && !Vazia(destino->num_cartas) && cartaOrigem.numero == cartaDestino.numero + 1 ) {
	
	    Carta cartaMovida = Pop(origem);
	    Push(*destino, cartaMovida);
	    
	    Carta carta = ElementoTopo(origem);
	    if (carta.praCima==0)
	    {
	    	Carta cartaMudar = Pop(origem);
	    	cartaMudar.praCima = 1;
	    	Push(origem, cartaMudar);
	    }
	     
        return 1; // Movimento bem-sucedido  
    }
    
    return 0; // Movimento inválido
} 

int verificarVitoria(Baralho b1_paus, Baralho b2_copas, Baralho b3_espada, Baralho b4_ouro) {
	
    int vitoria = 0; // Assume que o jogador não ganhou inicialmente

    // Verifica se todas as pilhas de fundação têm 13 cartas
    if (b1_paus.num_cartas == 12 && b2_copas.num_cartas == 12 && b3_espada.num_cartas == 12 && b4_ouro.num_cartas == 12) {
        // Verifica se as cartas nas pilhas de fundação estão em ordem crescente e do mesmo naipe
        int i;
        
        for (i = 0; i < 12; i++) {
            // Verifica se a carta atual é um número maior que a anterior
            if (b1_paus.cartas[i].numero != i + 1 || b1_paus.cartas[i].naipe != 'p') {
                return vitoria;
            }
            if (b2_copas.cartas[i].numero != i + 1 || b2_copas.cartas[i].naipe != 'c') {
                return vitoria;
            }
            if (b3_espada.cartas[i].numero != i + 1 || b3_espada.cartas[i].naipe != 'e') {
                return vitoria;
            }
            if (b4_ouro.cartas[i].numero != i + 1 || b4_ouro.cartas[i].naipe != 'o') {
                return vitoria;
            }
        }
        // Se todas as cartas nas pilhas de fundação estiverem em ordem, o jogador ganhou
        if (i == 12) {
            vitoria = 1;
        }
    }
    
    return vitoria;
}

void inicializarJogo(Carta baralho[],Baralho& inicial, Baralho& c1, Baralho& c2, Baralho& c3, Baralho& c4, Baralho& c5, Baralho& c6, Baralho& c7, Baralho& b1_paus, Baralho& b2_copas, Baralho& b3_espada, Baralho& b4_ouro, Baralho& draw, Baralho& descarte, Baralho& pilhaauxiliar){

    criarBaralho(baralho);
    
	//Baralho Complementar
	inicializarBaralho(inicial);
	inicializarBaralho(draw);
	inicializarBaralho(descarte);
	inicializarBaralho(pilhaauxiliar);
	
	//Pilha da Base
	inicializarBaralho(b1_paus);
	inicializarBaralho(b2_copas);
	inicializarBaralho(b3_espada);
	inicializarBaralho(b4_ouro);

	//Pilha do Tabuleiro
	inicializarBaralho(c1);
	inicializarBaralho(c2);
	inicializarBaralho(c3);
	inicializarBaralho(c4);
	inicializarBaralho(c5);
	inicializarBaralho(c6);
	inicializarBaralho(c7);
	
	//Coloca cartas do Baralho para as Pilhas do tabuleiro
    inicializarPilha(c1, baralho, 1);
    inicializarPilha(c2, baralho, 2);
    inicializarPilha(c3, baralho, 3);
    inicializarPilha(c4, baralho, 4);
    inicializarPilha(c5, baralho, 5);
    inicializarPilha(c6, baralho, 6);
    inicializarPilha(c7, baralho, 7);
    inicializarPilha(draw, baralho, 111);
    
    //Muda o valor do topo de Paracima = 1;
    alterarParacimaPilha(c1);
    alterarParacimaPilha(c2);
    alterarParacimaPilha(c3);
    alterarParacimaPilha(c4);
    alterarParacimaPilha(c5);
    alterarParacimaPilha(c6);
    alterarParacimaPilha(c7);
}
