#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>
#include <time.h>

#include "controla_pilha.h"
#include "GRAFICOS8K.h"

void desenharBaseBaralho(Baralho b1_paus, Baralho b2_copas, Baralho b3_espada, Baralho b4_ouro, Baralho draw){
	
	if(!Vazia(b1_paus.num_cartas)){
    	desenharCarta(66, 31, ElementoTopo(b1_paus).numero, ElementoTopo(b1_paus).naipe);
	}
	
	if(!Vazia(b2_copas.num_cartas)){
		desenharCarta(76, 31, ElementoTopo(b2_copas).numero, ElementoTopo(b2_copas).naipe);
	}
	
	if(!Vazia(b3_espada.num_cartas)){
		desenharCarta(86, 31, ElementoTopo(b3_espada).numero, ElementoTopo(b3_espada).naipe);
	}
	
	if(!Vazia(b4_ouro.num_cartas)){
		desenharCarta(96, 31, ElementoTopo(b4_ouro).numero, ElementoTopo(b4_ouro).naipe);
	}
	
	if (!Vazia(draw.num_cartas)) {
        desenharCarta(76, 23, ElementoTopo(draw).numero, ElementoTopo(draw).naipe);
	}
	
	gotoxy(73, 12);
}

int main()
{
	system("mode con: cols=105 lines=37");
	
	HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_SIZEBOX | WS_MAXIMIZEBOX));
    
	srand(time(NULL));
	setlocale(LC_ALL, "Portuguese");
	
	int colunaOrigem, colunaDestino, baseOrigem, baseDestino, numCartas;
    char opcao;
    
    Baralho inicial, c1, c2, c3, c4, c5, c6, c7, b1_paus, b2_copas, b3_espada, b4_ouro, draw, descarte, pilhaauxiliar;
    
    Carta baralho[52];
    
    inicializarJogo(baralho, inicial, c1, c2, c3, c4, c5, c6, c7, b1_paus, b2_copas, b3_espada, b4_ouro, draw, descarte, pilhaauxiliar );
	
	desenharMenu();
	
	desenharBaseBaralho(b1_paus, b2_copas, b3_espada, b4_ouro, draw);
	
	desenharTabuleiro(c1,c2,c3,c4,c5,c6,c7);
	
    do
	{
	    opcao = MenuPrincipal();
    
        switch (opcao)
        {
        	
        	case '1':
        		
				gotoxy(65,14);
			    printf("Retirar da coluna (1 a 7): ");
			    scanf("%d", &colunaOrigem);
			    
			    // Verifica se a coluna 
			    if (colunaOrigem < 1 || colunaOrigem > 7) {
				    gotoxy(65,18);
				    printf("Coluna inválida!");
				    getch();
				    break;
				}
				
			    gotoxy(65,15);
			    printf("Digite quantas cartas mover: ");
			    scanf("%d", &numCartas);
		    
			    // Verifica se o número de cartas é válido
			    if (numCartas < 1) {
			    	gotoxy(65,18);
			        printf("Escolha pelo menos uma carta.");
			        getch();
			        break;
			    }
		
			    // Move as cartas Pilha para Pilha
			  	switch(colunaOrigem) {
			  		
			    	case 1:
			    		
				        if (Vazia(c1.num_cartas)) {
				        	gotoxy(65,18);
				            printf("A pilha de origem está vazia.");
				            break;
				            
				        } else {
				        	gotoxy(65,16);
			    			printf("Inserir na coluna (1 a 7): ");
		        			scanf("%d", &colunaDestino);
		        			
		        			// Verifica se a coluna 
						    if (colunaDestino < 1 || colunaDestino > 7) {
							    gotoxy(65,18);
							    printf("Coluna inválida!");	
							    break;
							}
		        			
		            		switch(colunaDestino) {
		            		 	
						        case 1:
						        	gotoxy(65,18);
							        printf("Movimento inválido.");
							    break;
							        
							    case 2:
							        if (moverCarta(c1, c2, pilhaauxiliar, numCartas)) {
							        	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 3:	
							        if (moverCarta(c1, c3, pilhaauxiliar, numCartas)) {
							         	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 4:
							        if (moverCarta(c1, c4, pilhaauxiliar, numCartas)) {
							          	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 5:
							        if (moverCarta(c1, c5, pilhaauxiliar, numCartas)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 6:
							        if (moverCarta(c1, c6, pilhaauxiliar, numCartas)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 7:
							        if (moverCarta(c1, c7, pilhaauxiliar, numCartas)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    default:
							    	gotoxy(65,18);
							        printf("Coluna de destino inválida.\n");
							    break;
							}	
				        }
				        
			        break;
			        
			    	case 2:
			    	
				        if (Vazia(c2.num_cartas)) {
				        	gotoxy(65,18);
				            printf("A pilha de origem está vazia.");
				            break;
				            
				        } else {
				        	gotoxy(65,16);
			    			printf("Inserir na coluna (1 a 7): ");
		        			scanf("%d", &colunaDestino);
		        			
		        			// Verifica se a coluna 
						    if (colunaDestino < 1 || colunaDestino > 7) {
							    gotoxy(65,18);
							    printf("Coluna inválida!");
							    break;
							}
		        			
		        			switch(colunaDestino) {
		        				
							    case 1:
							        if (moverCarta(c2, c1, pilhaauxiliar, numCartas)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 2:
							    	gotoxy(65,18);
							        printf("Movimento inválido.");
							    break;
							        
							    case 3:
							        if (moverCarta(c2, c3, pilhaauxiliar, numCartas)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							    
							    case 4:
							        if (moverCarta(c2, c4, pilhaauxiliar, numCartas)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 5:
							        if (moverCarta(c2, c5, pilhaauxiliar, numCartas)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 6:
							        if (moverCarta(c2, c6, pilhaauxiliar, numCartas)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 7:
							        if (moverCarta(c2, c7, pilhaauxiliar, numCartas)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    default:		
							    	gotoxy(65,18);
							        printf("Coluna de destino inválida.");
							    break;
							}
						}
						
			        break;
			        
				    case 3:
				    	
				        if (Vazia(c3.num_cartas)) {
				        	gotoxy(65,18);
				            printf("A pilha de origem está vazia.");
				            break;
				            
				        } else {
				        	
				        	gotoxy(65,16);
			    			printf("Inserir na coluna (1 a 7): ");
		        			scanf("%d", &colunaDestino);
		        			
		        			// Verifica se a coluna 
						    if (colunaDestino < 1 || colunaDestino > 7) {
							    gotoxy(65,18);
							    printf("Coluna inválida!");
							    break;
							}
		        			
		        			switch(colunaDestino) {
		        				
							    case 1:
							        if (moverCarta(c3, c1, pilhaauxiliar, numCartas)) {
							          	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 2:
							        if (moverCarta(c3, c2, pilhaauxiliar, numCartas)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 3:
							    	gotoxy(65,18);
							        printf("Movimento inválido.");
							    break;
							        
							    case 4: 	
							        if (moverCarta(c3, c4, pilhaauxiliar, numCartas)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 5:
							        if (moverCarta(c3, c5, pilhaauxiliar, numCartas)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 6:
							        if (moverCarta(c3, c6, pilhaauxiliar, numCartas)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 7:
							        if (moverCarta(c3, c7, pilhaauxiliar, numCartas)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    default:
							    	gotoxy(65,18);
							        printf("Coluna de destino inválida.");
							    break;
							}
						}
						
				    break;
			        
			    	case 4:
				        if (Vazia(c4.num_cartas)) {
				        	gotoxy(65,18);
				            printf("A pilha de origem está vazia.");
				            break;
				            
				        } else {
				        	
				        	gotoxy(65,16);
			    			printf("Inserir na coluna (1 a 7): ");
		        			scanf("%d", &colunaDestino);
		        			
		        			// Verifica se a coluna 
						    if (colunaDestino < 1 || colunaDestino > 7) {
							    gotoxy(65,18);
							    printf("Coluna inválida!");
							    break;
							}
							
		        			switch(colunaDestino) {
		        				
							    case 1:
							        if (moverCarta(c4, c1, pilhaauxiliar, numCartas)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 2:
							        if (moverCarta(c4, c2, pilhaauxiliar, numCartas)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
								break;
								
							    case 3:
							        if (moverCarta(c4, c3, pilhaauxiliar, numCartas)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 4:
							    	gotoxy(65,18);
							        printf("Movimento inválido.");
							    break;
							        
							    case 5:
							        if (moverCarta(c4, c5, pilhaauxiliar, numCartas)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 6:
							        if (moverCarta(c4, c6, pilhaauxiliar, numCartas)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							    
							    case 7:
							        if (moverCarta(c4, c7, pilhaauxiliar, numCartas)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    default:
							    	gotoxy(65,18);
							        printf("Coluna de destino inválida.");
							    break;
							}
						
						}
			        break;
			        
			    	case 5:
			    		
					    if (Vazia(c5.num_cartas)) {
					    	gotoxy(65,18);
					        printf("A pilha de origem está vazia.");
					        break;
					        
					    } else {
					    	
					        gotoxy(65,16);
			   				printf("Inserir na coluna (1 a 7): ");
					        scanf("%d", &colunaDestino);
					        
					        // Verifica se a coluna 
						    if (colunaDestino < 1 || colunaDestino > 7) {
							    gotoxy(65,18);
							    printf("Coluna inválida!");
							    break;
							}
					        
					        switch(colunaDestino) {
					        	
					            case 1:
					                if (moverCarta(c5, c1, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					            break;
					                
					            case 2:
					                if (moverCarta(c5, c2, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					            break;
					            
					            case 3:
					                if (moverCarta(c5, c3, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					            break;
					            
					            case 4:
					                if (moverCarta(c5, c4, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					            break;
					            
					            case 5:
					            	gotoxy(65,18);
					                printf("Movimento inválido.");
					            break;
					            
					            case 6:
					                if (moverCarta(c5, c6, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					            break;
					            
					            case 7:
					                if (moverCarta(c5, c7, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					            break;
					            
					            default:
					            	gotoxy(65,18);
					                printf("Coluna de destino inválida.");
					            break;
					    	}
						}
						
				    break;
				    
			    	case 6:
			    		
					    if (Vazia(c6.num_cartas)) {
					    	gotoxy(65,18);
					        printf("A pilha de origem está vazia.");
					        break;
					        
					    } else {
					    	
					        gotoxy(65,16);
			   				printf("Inserir na coluna (1 a 7): ");
					        scanf("%d", &colunaDestino);
					        
					        // Verifica se a coluna 
						    if (colunaDestino < 1 || colunaDestino > 7) {
							    gotoxy(65,18);
							    printf("Coluna inválida!");
							    break;
							}
					        
					        switch(colunaDestino) {
					        	
					            case 1:
					                if (moverCarta(c6, c1, pilhaauxiliar, numCartas)) {
					                   	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					                break;
					            case 2:
					                if (moverCarta(c6, c2, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					                break;
					            case 3:
					                if (moverCarta(c6, c3, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					                break;
					            case 4:
					                if (moverCarta(c6, c4, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					            break;
					                
					            case 5:
					                if (moverCarta(c6, c5, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
								break;
								
					            case 6:
					            	gotoxy(65,18);
					                printf("Movimento inválido.");
					            break;
					                
					            case 7:
					                if (moverCarta(c6, c7, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					            break;
					            
					            default:
					            	gotoxy(65,18);
					                printf("Coluna de destino inválida.");
					            break;
					        }
				    	}
				    	
				    break;
	
					case 7:
						
					    if (Vazia(c7.num_cartas)) {
					    	gotoxy(65,18);
					        printf("A pilha de origem está vazia.");
					        break;
					        
					    } else {
					    	
					        gotoxy(65,16);
		    				printf("Inserir na coluna (1 a 7): ");
					        scanf("%d", &colunaDestino);
					        
					        // Verifica se a coluna 
						    if (colunaDestino < 1 || colunaDestino > 7) {
							    gotoxy(65,18);
							    printf("Coluna inválida!");
							    break;
							}
					        
					        switch(colunaDestino) {
					        	
					            case 1:
					                if (moverCarta(c7, c1, pilhaauxiliar, numCartas)) {
						                gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					            break;
					            
					            case 2:
					                if (moverCarta(c7, c2, pilhaauxiliar, numCartas)) {
						                gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					            break;
					            
					            case 3:
					                if (moverCarta(c7, c3, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
						            	printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					            break;
					            
					            case 4:
					                if (moverCarta(c7, c4, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
						            	printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					            break;
					            
					            case 5:
					                if (moverCarta(c7, c5, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
						            	printf("Cartas movidas com sucesso!");
						        } else {
						        	gotoxy(65,18);
						            printf("Movimento inválido.");
						        }
					                break;
					            case 6:
					                if (moverCarta(c7, c6, pilhaauxiliar, numCartas)) {
					                    gotoxy(65,18);
						            	printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
					            break;
					            
					            case 7:
					            	gotoxy(65,18);
					                printf("Movimento inválido.");
					            break;
					                
					            default:
					            	gotoxy(65,18);
					                printf("Coluna de destino inválida.");
					            break;
					        }
					    }
					    
					break;   
				
				}

		desenharTabuleiro(c1,c2,c3,c4,c5,c6,c7);
			
		desenharBaseBaralho(b1_paus, b2_copas, b3_espada, b4_ouro, draw);
				  
		getch();
			
		break;
			
        case '2':
        	
			gotoxy(65,14);
		    printf("Mover para Pilha (1 a 7): ");
		    scanf("%d", &colunaOrigem);
		    
			// Verifica se a coluna 
		    if (colunaOrigem < 1 || colunaOrigem > 7) {
			    gotoxy(65,18);
			    printf("Coluna inválida!");
			    getch();
			    break;
			}		    

		    // Move as cartas da pilha para a base
			switch(colunaOrigem) {
		  		
				case 1:
			    	
					if (Vazia(c1.num_cartas)) {
				    	gotoxy(65,18);
				        printf("A pilha de origem está vazia.");
				        break;
				        
				    } else {
				    	
			        	if (moverCartaPilhaBase(c1, b1_paus, b2_copas, b3_espada, b4_ouro)) {
		                    gotoxy(65,18);
			            	printf("Cartas movidas com sucesso!");
				        } else {
				        	gotoxy(65,18);
				            printf("Movimento inválido.");
					    }
				    }
				break;
				    
			    case 2:
			    	
					if (Vazia(c2.num_cartas)) {
				    	gotoxy(65,18);
				        printf("A pilha de origem está vazia.");
				        break;
				        
				    } else {
				    	
			        	if (moverCartaPilhaBase(c2, b1_paus, b2_copas, b3_espada, b4_ouro)) {
		                    gotoxy(65,18);
			            	printf("Cartas movidas com sucesso!");
				        } else {
				        	gotoxy(65,18);
				            printf("Movimento inválido.");
					    }
				    }
				    
			    break;
				
				case 3:
					
					if (Vazia(c3.num_cartas)) {
				    	gotoxy(65,18);
				        printf("A pilha de origem está vazia.");
				        break;
				        
				    } else {
				    	
				       	if (moverCartaPilhaBase(c3, b1_paus, b2_copas, b3_espada, b4_ouro)) {
		                    gotoxy(65,18);
			            	printf("Cartas movidas com sucesso!");
				        } else {
				        	gotoxy(65,18);
				            printf("Movimento inválido.");
				   	 	}	
			    	}
			    break;
			    
			    case 4:
			    	
					if (Vazia(c4.num_cartas)) {
				    	gotoxy(65,18);
				        printf("A pilha de origem está vazia.");
				        break;
				        
				    } else {
				    	
			        	if (moverCartaPilhaBase(c4, b1_paus, b2_copas, b3_espada, b4_ouro)) {
		                    gotoxy(65,18);
			            	printf("Cartas movidas com sucesso!");
				        } else {
				        	gotoxy(65,18);
				            printf("Movimento inválido.");
					    }
				    }
			    break;
			    
			    case 5:
			    	
					if (Vazia(c5.num_cartas)) {
				    	gotoxy(65,18);
				        printf("A pilha de origem está vazia.");
				        break;
				        
				    } else {
				    	
			        	if (moverCartaPilhaBase(c5, b1_paus, b2_copas, b3_espada, b4_ouro)) {
		                    gotoxy(65,18);
			            	printf("Cartas movidas com sucesso!");
				        } else {
				        	gotoxy(65,18);
				            printf("Movimento inválido.");
					    }
				    }
			    break;
			    
			    
			    case 6:
			    	
					if (Vazia(c6.num_cartas)) {
				    	gotoxy(65,18);
				        printf("A pilha de origem está vazia.");
				        break;
				        
				    } else {
				    	
			        	if (moverCartaPilhaBase(c6, b1_paus, b2_copas, b3_espada, b4_ouro)) {
		                    gotoxy(65,18);
			            	printf("Cartas movidas com sucesso!");
				        } else {
				        	gotoxy(65,18);
				            printf("Movimento inválido.");
					    }
				    }
			    break;
			    
			    
			    case 7:
			    	
					if (Vazia(c7.num_cartas)) {
				    	gotoxy(65,18);
				        printf("A pilha de origem está vazia.");
				        break;
				        
				    } else {
				    	
			    		if (moverCartaPilhaBase(c7, b1_paus, b2_copas, b3_espada, b4_ouro)) {
		                    gotoxy(65,18);
			            	printf("Cartas movidas com sucesso!");
				        } else {
				        	gotoxy(65,18);
				            printf("Movimento inválido.");
				    	}
				    }
				    
			    break;
		    		
				}
			
			desenharBaseBaralho(b1_paus, b2_copas, b3_espada, b4_ouro, draw);
	    
			desenharTabuleiro(c1,c2,c3,c4,c5,c6,c7);
	    	
	    	getch();
		
            break;
            
            case '3':
            	
            	gotoxy(65,14);
			    printf("Retirar da base (1 a 4): ");
			    scanf("%d", &baseOrigem);
			    
			    // Verifica se a coluna 
			    if (baseOrigem < 1 || baseOrigem > 4) {
				    gotoxy(65,18);
				    printf("Coluna inválida!");
				    getch();
				    break;
				}
			    
			    // Move as cartas Base para Pilha
			  	switch(baseOrigem) {
			  		
			    	case 1:
			    		
				        if (Vazia(b1_paus.num_cartas)) {
				        	gotoxy(65,18);
				            printf("A pilha de origem está vazia.");
				            break;
				            
				        } else {
				        	gotoxy(65,16);
			    			printf("Inserir na coluna (1 a 7): ");
		        			scanf("%d", &colunaDestino);
		        			
		        			// Verifica se a coluna 
						    if (colunaDestino < 1 || colunaDestino > 7) {
							    gotoxy(65,18);
							    printf("Coluna inválida!");
							    break;
							}		
		        			
		            		switch(colunaDestino) {
		            		 	
						        case 1:
						        	if (moverCartaBasePilha(b1_paus, c1)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 2:
							        if (moverCartaBasePilha(b1_paus, c2)) {
							        	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 3:	
							        if (moverCartaBasePilha(b1_paus, c3)) {
							         	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 4:
							        if (moverCartaBasePilha(b1_paus, c4)) {
							          	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 5:
							        if (moverCartaBasePilha(b1_paus, c5)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 6:
							        if (moverCartaBasePilha(b1_paus, c6)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 7:
							        if (moverCartaBasePilha(b1_paus, c7)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    default:
							    	gotoxy(65,18);
							        printf("Coluna de destino inválida.\n");
							    break;
							}	
				        }
				        
			        break;
			        
			    	case 2:
			    	
				        if (Vazia(b2_copas.num_cartas)) {
				        	gotoxy(65,18);
				            printf("A pilha de origem está vazia.");
				            break;
				            
				        } else {
				        	gotoxy(65,16);
			    			printf("Inserir na coluna (1 a 7): ");
		        			scanf("%d", &colunaDestino);
		        			
		        			// Verifica se a coluna 
						    if (colunaDestino < 1 || colunaDestino > 7) {
							    gotoxy(65,18);
							    printf("Coluna inválida!");
							    break;
							}	
		        			
		        			switch(colunaDestino) {
		        				
							    case 1:
							        if (moverCartaBasePilha(b2_copas, c1)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 2:
							    	if (moverCartaBasePilha(b2_copas, c2)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 3:
							        if (moverCartaBasePilha(b2_copas, c3)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							    
							    case 4:
							        if (moverCartaBasePilha(b2_copas, c4)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 5:
							        if (moverCartaBasePilha(b2_copas, c5)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 6:
							        if (moverCartaBasePilha(b2_copas, c6)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 7:
							        if (moverCartaBasePilha(b2_copas, c7)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    default:		
							    	gotoxy(65,18);
							        printf("Coluna de destino inválida.");
							    break;
							}
						}
						
			        break;
			        
				    case 3:
				    	
				        if (Vazia(b3_espada.num_cartas)) {
				        	gotoxy(65,18);
				            printf("A pilha de origem está vazia.");
				            break;
				            
				        } else {
				        	
				        	gotoxy(65,16);
			    			printf("Inserir na coluna (1 a 7): ");
		        			scanf("%d", &colunaDestino);
		        			
		        			// Verifica se a coluna 
						    if (colunaDestino < 1 || colunaDestino > 7) {
							    gotoxy(65,18);
							    printf("Coluna inválida!");
							    break;
							}	
		        			
		        			switch(colunaDestino) {
		        				
							    case 1:
							        if (moverCartaBasePilha(b3_espada, c1)) {
							          	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 2:
							        if (moverCartaBasePilha(b3_espada, c2)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 3:
							    	if (moverCartaBasePilha(b3_espada, c3)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 4: 	
							        if (moverCartaBasePilha(b3_espada, c4)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 5:
							        if (moverCartaBasePilha(b3_espada, c5)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 6:
							        if (moverCartaBasePilha(b3_espada, c6)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 7:
							        if (moverCartaBasePilha(b3_espada, c7)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    default:
							    	gotoxy(65,18);
							        printf("Coluna de destino inválida.");
							    break;
							}
						}
						
				    break;
			        
			    	case 4:
				        if (Vazia(b4_ouro.num_cartas)) {
				        	gotoxy(65,18);
				            printf("A pilha de origem está vazia.");
				            break;
				            
				        } else {
				        	
				        	gotoxy(65,16);
			    			printf("Inserir na coluna (1 a 7): ");
		        			scanf("%d", &colunaDestino);
		        			
		        			// Verifica se a coluna 
						    if (colunaDestino < 1 || colunaDestino > 7) {
							    gotoxy(65,18);
							    printf("Coluna inválida!");
							    break;
							}	
									
		        			switch(colunaDestino) {
		        				
							    case 1:
							        if (moverCartaBasePilha(b4_ouro, c1)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 2:
							        if (moverCartaBasePilha(b4_ouro, c2)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
								break;
								
							    case 3:
							        if (moverCartaBasePilha(b4_ouro, c3)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 4:
							    	if (moverCartaBasePilha(b4_ouro, c4)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 5:
							        if (moverCartaBasePilha(b4_ouro, c5)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    case 6:
							        if (moverCartaBasePilha(b4_ouro, c6)) {
							           	gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							    
							    case 7:
							        if (moverCartaBasePilha(b4_ouro, c7)) {
							            gotoxy(65,18);
							            printf("Cartas movidas com sucesso!");
							        } else {
							        	gotoxy(65,18);
							            printf("Movimento inválido.");
							        }
							    break;
							        
							    default:
							    	gotoxy(65,18);
							        printf("Coluna de destino inválida.");
							    break;
							}
						
						}
			        break;
				}
			
			inicializarBase();
			
			desenharBaseBaralho(b1_paus, b2_copas, b3_espada, b4_ouro, draw);
	    
			desenharTabuleiro(c1,c2,c3,c4,c5,c6,c7);	
				
			getch();
		
            break;
            
            case '4':
            		
				gotoxy(65,14);
			    printf("Mover para Pilha (1 a 7): ");
			    scanf("%d", &colunaDestino);
			    
			    // Verifica se a coluna 
			    if (colunaDestino < 1 || colunaDestino > 7) {
				    gotoxy(65,18);
				    printf("Coluna inválida!");
				    getch();
				    break;
				}	
	
			    // Move as cartas do baralho para pilha
			  	switch(colunaDestino) {
			  		
					case 1:
				    	
				    	if (moverCartaBaralhoPilha(draw, c1, descarte)) {
							gotoxy(65,16);
							printf("Cartas movidas com sucesso!");
						} else {
							gotoxy(65,16);
							printf("Movimento inválido.");
						}
					break;
							  
				    case 2:
				        if (moverCartaBaralhoPilha(draw, c2, descarte )) {
				        	gotoxy(65,16);
				            printf("Cartas movidas com sucesso!");
				        } else {
				        	gotoxy(65,16);
				            printf("Movimento inválido.");
				        }
				        break;
				        
				    case 3:
				    	
				        if (moverCartaBaralhoPilha(draw, c3, descarte)) {
				         	gotoxy(65,16);
				            printf("Cartas movidas com sucesso!");
				        } else {
				        	gotoxy(65,16);
				            printf("Movimento inválido.");
				        }
				    break;
				        
				    case 4:
				    	
				        if (moverCartaBaralhoPilha(draw, c4, descarte)) {
				          	gotoxy(65,16);
				            printf("Cartas movidas com sucesso!");
				        } else {
				        	gotoxy(65,16);
				            printf("Movimento inválido.");
				        }
					break;
						
					case 5:
						
				        if (moverCartaBaralhoPilha(draw, c5, descarte)) {
				          	gotoxy(65,16);
				            printf("Cartas movidas com sucesso!");
				        } else {
				        	gotoxy(65,16);
				            printf("Movimento inválido.");
				        }
					break;
						
					case 6:
						
				        if (moverCartaBaralhoPilha(draw, c6, descarte)) {
				          	gotoxy(65,16);
				            printf("Cartas movidas com sucesso!");
				        } else {
				        	gotoxy(65,16);
				            printf("Movimento inválido.");
				        }
					break;
						
					case 7:
						
				        if (moverCartaBaralhoPilha(draw, c7, descarte)) {
				          	gotoxy(65,16);
				            printf("Cartas movidas com sucesso!");
				        } else {
				        	gotoxy(65,16);
				            printf("Movimento inválido.");
				        }
					break;
						
					default:
		            	gotoxy(65,18);
		                printf("Coluna de destino inválida.");
		            break;		
				}
			
			desenharTabuleiro(c1,c2,c3,c4,c5,c6,c7);
			
			desenharBaseBaralho(b1_paus, b2_copas, b3_espada, b4_ouro, draw);
					
			getch();	
		
	        break;
            
            case '5':
            	
        		if (moverCartaBaralhoBase(draw, b1_paus, b2_copas, b3_espada, b4_ouro)){
		        	gotoxy(65,16);
		            printf("Cartas movidas com sucesso!");
		        } else {
		        	gotoxy(65,16);
		            printf("Movimento inválido.");
			    }
			
			desenharBaseBaralho(b1_paus, b2_copas, b3_espada, b4_ouro, draw);
	    
			getch();
			
	        break;
            
            case '6':
            	
		        pegarNovaCarta(draw, descarte);
		        
		        if(Vazia(draw.num_cartas))
		        	pegarNovaCarta(draw, descarte);
		        	
		        if (!Vazia(draw.num_cartas)) {
			        desenharCarta(76, 23, ElementoTopo(draw).numero, ElementoTopo(draw).naipe);
				}
		        
            break;
            
            case '7':

				inicializarJogo(baralho, inicial, c1, c2, c3, c4, c5, c6, c7, b1_paus, b2_copas, b3_espada, b4_ouro, draw, descarte, pilhaauxiliar );
				
				desenharMenu();
				
				desenharTabuleiro(c1,c2,c3,c4,c5,c6,c7);
			    	
			    desenharBaseBaralho(b1_paus, b2_copas, b3_espada, b4_ouro, draw);
				
            break;
            
            case '8':
            	
            	system("mode con: cols=105 lines=105");
        		
        		gotoxy(2,2);
        		
        		printf("\n Coluna 1");
        		Exibir(c1);
        		
        		printf("\n Coluna 2");
        		Exibir(c2);
        		
        		printf("\n Coluna 3");
        		Exibir(c3);
        		
        		printf("\n Coluna 4");
        		Exibir(c4);
        		
        		printf("\n Coluna 5");
        		Exibir(c5);
        		
        		printf("\n Coluna 6");
        		Exibir(c6);
        		
        		printf("\n Coluna 7");
        		Exibir(c7);
        		
        		printf("\n Base 1 - Paus");
        		Exibir(b1_paus);
        		
        		printf("\n Base 2 - Copas");
        		Exibir(b2_copas);
        		
        		printf("\n Base 3 - Espada");
        		Exibir(b3_espada);
        		
        		printf("\n Base 4 - Ouro");
        		Exibir(b4_ouro);
        		
        		printf("\n Baralho");
        		Exibir(draw);
        		
        		printf("\n Descarte");
        		Exibir(descarte);
        		
        	getch();
            	
            break;
            
            case '9':
            	
            	system("mode con: cols=105 lines=37");

				desenharMenu();

			    desenharTabuleiro(c1,c2,c3,c4,c5,c6,c7);
			    	
			    desenharBaseBaralho(b1_paus, b2_copas, b3_espada, b4_ouro, draw);
			    	
            break;
        
		}
     
	} while (opcao != 27 || !verificarVitoria(b1_paus, b2_copas, b3_espada, b4_ouro));
	
    return 0;
}
