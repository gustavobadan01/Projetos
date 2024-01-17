#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define tf 100

struct tpdata
{
    int d, m, a;
};

struct forn
{
    int codforn;
    int status;
    char nomeforn[tf], cidadeforn[tf];
};

struct tpprod
{
    int codprod;
    int status;
    int estoque;
    struct tpdata valid;
    char descr[tf];
    float preco;
    int codforn;
};

struct clientes
{
	int status;
    int cpfcli;
    int qtdcompras;
    char nomecli[tf];
    float valortotcomprado;
};

struct vendas
{
	int status;
    int codvenda;
	int cpfcli;
	struct tpdata valid;
    float totvenda;
};

struct vendasprod
{
	int status;
	int codprod;
	int codvenda;
    int qtde;
    float valorunitario;
};


void LimparMenu() {
	
for (int i = 2; i <= 5; i++) 
	{
        gotoxy(3, i);
        for (int j = 2; j <= 77; j++) 
		{ 
            printf(" ");
        }
    }
    
}

void LimparMensagem() {
	
	gotoxy(13,23);
    for (int i = 13; i <= 77; i++) {
        printf(" ");
    }
      
}

void LimparExibicao() {
    for (int i = 7; i <= 20; i++) 
	{
        gotoxy(3, i);
        for (int j = 2; j <= 77; j++) 
		{ 
            printf(" ");
        }
    }
}

int buscaprod(FILE *Ptr,int Prod)
{
	tpprod R;
	rewind(Ptr);
	fread(&R,sizeof(tpprod),1,Ptr);
	while (!feof(Ptr) && Prod!=R.codprod)
		fread(&R,sizeof(tpprod),1,Ptr);
	
	if (!feof(Ptr))
		return ftell(Ptr)-sizeof(tpprod);
	else
		return -1;
}

int buscaforn(FILE *Ptr,int Forn)
{
	forn R;
	rewind(Ptr);
	fread(&R,sizeof(forn),1,Ptr);
	while (!feof(Ptr) && Forn!=R.codforn)
		fread(&R,sizeof(forn),1,Ptr);
	
	if (!feof(Ptr))
		return ftell(Ptr)-sizeof(forn);
	else
		return -1;
}

int buscacliente(FILE *Ptr,int Cli)
{
	clientes R;
	rewind(Ptr);
	fread(&R,sizeof(clientes),1,Ptr);
	while (!feof(Ptr) && Cli!=R.cpfcli)
		fread(&R,sizeof(clientes),1,Ptr);
	
	if (!feof(Ptr))
		return ftell(Ptr)-sizeof(clientes);
	else
		return -1;
}


int buscavenda(FILE *Ptr,int Venda)
{
	vendas R;
	rewind(Ptr);
	fread(&R,sizeof(vendas),1,Ptr);
	while (!feof(Ptr) && Venda!=R.codvenda)
		fread(&R,sizeof(vendas),1,Ptr);
	
	if (!feof(Ptr))
		return ftell(Ptr)-sizeof(vendas);
	else
		return -1;
}

int BuscaProdSeqIndProd(FILE *Ptr, int prod) 
{
	tpprod R;
	rewind(Ptr);
	fread(&R,sizeof(tpprod),1,Ptr);
	
	while (!feof(Ptr) && prod > R.codprod)
		fread(&R,sizeof(tpprod),1,Ptr);
	
	if (!feof(Ptr) && prod == R.codprod){
	
		return ftell(Ptr)-sizeof(tpprod);
	}
		
	else
		return -1;
}

int BuscaSentinelaforn(FILE *PtrForn, int Forn) {
	int tlf, poss;
    forn F, Temp;
    
    FILE *PtrTemp = fopen("tempf.dat","wb+");
    
    fseek(PtrForn,0,2);
    tlf = ftell(PtrForn)/sizeof(forn);
    
    rewind(PtrForn);
    fread(&F, sizeof(forn), 1, PtrForn);
    while (!feof(PtrForn)) {
        fwrite(&F, sizeof(forn), 1, PtrTemp);
        fread(&F, sizeof(forn), 1, PtrForn);
    }

    fseek(PtrTemp, 0, SEEK_END);
    Temp.codforn = Forn;
    fwrite(&Temp, sizeof(forn), 1, PtrTemp);

    rewind(PtrTemp);

    fread(&Temp, sizeof(forn), 1, PtrTemp);
    while (!feof(PtrTemp) && Forn != Temp.codforn) {
        fread(&Temp, sizeof(forn), 1, PtrTemp);
    }
    
    
	
	poss = ftell(PtrTemp) - sizeof(forn);
	
    if ( Forn == Temp.codforn && poss < (tlf * sizeof(forn))  ) {
    	
    	fclose(PtrTemp);
    	remove("tempf.dat");
    
        return poss;
        
    } else {
    	
    	fclose(PtrTemp);
    	remove("tempf.dat");
        
        return -1;
    }
}



int BuscaBinariaCliente(FILE *Ptr, char auxnome[50]) {

    clientes C;
    
    int inicio = 0, meio = 0, fim = 0;
    
    fseek(Ptr, 0, 2);
    fim = ftell(Ptr)/sizeof(clientes);
    meio = fim/2;
    
    fseek(Ptr, meio*sizeof(clientes),0);
    fread(&C, sizeof(clientes),1, Ptr);
    while(inicio<fim && (stricmp(C.nomecli, auxnome) != 0 )){
    	
    	if(stricmp(C.nomecli, auxnome) < 0)
    		inicio = meio+1;
    	else
    		fim = meio-1;
    		
    	meio = (inicio+fim)/2;
    	fseek(Ptr, meio*sizeof(clientes), 0 );
    	fread(&C, sizeof(clientes), 1, Ptr);
	}
    
    if(stricmp(C.nomecli, auxnome) == 0){
    	return meio*sizeof(clientes);
	}
	
    return -1;
}


void BSclientes(void) {
    int a, b, QtdeReg;
    clientes RA, RB;

    FILE *PtrCli = fopen("clientes.dat", "rb+");

    if (PtrCli == NULL) {
        printf("Erro ao abrir o arquivo!");
    } else {
        fseek(PtrCli, 0, 2);
        QtdeReg = ftell(PtrCli) / sizeof(clientes);

        for (a = 0; a < QtdeReg - 1; a++) {
            for (b = a + 1; b < QtdeReg; b++) {
                fseek(PtrCli, a * sizeof(clientes), 0);
                fread(&RA, sizeof(clientes), 1, PtrCli);

                fseek(PtrCli, b * sizeof(clientes), 0);
                fread(&RB, sizeof(clientes), 1, PtrCli);

                if (stricmp(RA.nomecli, RB.nomecli) > 0) {
                	
                    fseek(PtrCli, a * sizeof(clientes), 0);
                    fwrite(&RB, sizeof(clientes), 1, PtrCli);

                    fseek(PtrCli, b * sizeof(clientes), 0);
                    fwrite(&RA, sizeof(clientes), 1, PtrCli);
                }
            }
        }
        
        LimparMensagem();
        gotoxy(13, 23);
        printf("Clientes ordenados pelo nome!");
    }

    fclose(PtrCli);
}


void BSprodutos(void)
{
	int a,b,QtdeReg;
	
	tpprod RA, RB;
	
	FILE *PtrProd= fopen("produtos.dat","rb+");
	
	if (PtrProd==NULL){

		gotoxy(4,8);
        printf("Erro ao abrir o arquivo !");
	    
	} else {	
	
			fseek(PtrProd,0,2);
			QtdeReg = ftell(PtrProd)/sizeof(tpprod);
			
			for(a=0; a<QtdeReg-1; a++){
			
			
				for(b=a+1; b<QtdeReg; b++)
				{
					fseek(PtrProd,a*sizeof(tpprod),0);
					fread(&RA,sizeof(tpprod),1,PtrProd);
					
					fseek(PtrProd,b*sizeof(tpprod),0);
					fread(&RB,sizeof(tpprod),1,PtrProd);
					
					if(RA.codprod > RB.codprod)
					{
						fseek(PtrProd,a*sizeof(tpprod),0);
						fwrite(&RB,sizeof(tpprod),1,PtrProd);
						
						fseek(PtrProd,b*sizeof(tpprod),0);
						fwrite(&RA,sizeof(tpprod),1,PtrProd);
					}
				}
			}
			
			LimparMensagem();
			gotoxy(13, 23);
        	printf("Código dos Produtos foram Ordenados!");
	}
	
	fclose(PtrProd);	
	getch();
}

void BSfornecedor(void)
{
	int a,b,QtdeReg;
	
	forn RA, RB;
	
	FILE *PtrForn= fopen("fornecedor.dat","rb+");
	
	if (PtrForn==NULL){

		gotoxy(4,8);
        printf("Erro ao abrir o arquivo !");
	    
	} else {	
	
			fseek(PtrForn,0,2);
			QtdeReg = ftell(PtrForn)/sizeof(forn);
			
			for(a=0; a<QtdeReg-1; a++){
			
			
				for(b=a+1; b<QtdeReg; b++)
				{
					fseek(PtrForn,a*sizeof(forn),0);
					fread(&RA,sizeof(forn),1,PtrForn);
					
					fseek(PtrForn,b*sizeof(forn),0);
					fread(&RB,sizeof(forn),1,PtrForn);
					
					if(RA.codforn > RB.codforn)
					{
						fseek(PtrForn,a*sizeof(forn),0);
						fwrite(&RB,sizeof(forn),1,PtrForn);
						
						fseek(PtrForn,b*sizeof(forn),0);
						fwrite(&RA,sizeof(forn),1,PtrForn);
					}
				}
			}
			
			LimparMensagem();
			gotoxy(13, 23);
        	printf("Código dos Fornecedores foram Ordenados!");
	}
	
	fclose(PtrForn);
	getch();
}

void SelecaoDiretaProdutos(void) {
    int TL, i, j;
    tpprod ProdAtual, Menor, Temp;

    FILE *arquivo = fopen("produtos.dat", "rb+");
    if (arquivo == NULL) {
        gotoxy(4, 8);
        printf("Erro ao abrir o arquivo !");
    } else {
        fseek(arquivo, 0, SEEK_END);
        TL = ftell(arquivo) / sizeof(struct tpprod);

        for (i = 0; i < TL - 1; i++) {
            fseek(arquivo, i * sizeof(struct tpprod), SEEK_SET);
            fread(&Menor, sizeof(struct tpprod), 1, arquivo);

            int posMenor = i;

            for (j = i + 1; j < TL; j++) {
                fseek(arquivo, j * sizeof(struct tpprod), SEEK_SET);
                fread(&ProdAtual, sizeof(struct tpprod), 1, arquivo);

                if (ProdAtual.codprod < Menor.codprod) {
                    Menor = ProdAtual;
                    posMenor = j;
                }
            }

            if (posMenor != i) {
                fseek(arquivo, i * sizeof(struct tpprod), SEEK_SET);
                fread(&Temp, sizeof(struct tpprod), 1, arquivo);

                fseek(arquivo, i * sizeof(struct tpprod), SEEK_SET);
                fwrite(&Menor, sizeof(struct tpprod), 1, arquivo);

                fseek(arquivo, posMenor * sizeof(struct tpprod), SEEK_SET);
                fwrite(&Temp, sizeof(struct tpprod), 1, arquivo);
            }
        }
		
		LimparMensagem();
        gotoxy(13, 23);
        printf("Produtos foram Ordenados!");
    }

    getch();
    fclose(arquivo);
}

void InsDiretaFornecedor(void) {
    int TL, i, j;

    FILE *arquivo = fopen("fornecedor.dat", "rb+");
    
    if (arquivo == NULL) {
        gotoxy(4, 8);
        printf("Erro ao abrir o arquivo !");
    } else {
    	
        fseek(arquivo, 0, SEEK_END);
        TL = ftell(arquivo) / sizeof(struct forn);
        
        forn fornAtual, fornAnterior;
        
        for (i = 1; i < TL; i++) {
            fseek(arquivo, i * sizeof(forn), SEEK_SET);
            fread(&fornAtual, sizeof(forn), 1, arquivo);

            j = i - 1;
            fseek(arquivo, j * sizeof(struct forn), SEEK_SET);
            fread(&fornAnterior, sizeof(forn), 1, arquivo);

            while (j >= 0 && fornAtual.codforn < fornAnterior.codforn) {
                fseek(arquivo, (j + 1) * sizeof(forn), SEEK_SET);
                fwrite(&fornAnterior, sizeof(forn), 1, arquivo);

                fseek(arquivo, j * sizeof(forn), SEEK_SET);
                fwrite(&fornAtual, sizeof(forn), 1, arquivo);

                j--;
                
                if (j >= 0) {
                    fseek(arquivo, j * sizeof(forn), SEEK_SET);
                    fread(&fornAnterior, sizeof(forn), 1, arquivo);
                }
            }
        }
		
		LimparMensagem();
        gotoxy(13, 23);
        printf("Fornecedores foram Ordenados!");
    }

    getch();
    fclose(arquivo);
}

void excluirlogicafornecedor(void)
{
	int pos;
	forn F;
	FILE *PtrForn = fopen("fornecedor.dat","rb+");
	
	if (PtrForn == NULL)
	{
  		gotoxy(4,8);
        printf("Não há dados!");
	    getch();   
	    
	} else {
		
		LimparExibicao();

		gotoxy(4, 8);
		printf("Código do fornecedor que deseja excluir logicamente (ou 0 para sair): ");
		gotoxy(4, 9);
		scanf("%d", &F.codforn);
			
			
			while (F.codforn > 0)
			{
				pos = buscaforn(PtrForn,F.codforn);
				
				if (pos==-1){
					
					gotoxy(4, 9);
					printf("Não foi encontrada!");
					
				} else {   
				
						fseek(PtrForn,pos,0);
						fread(&F,sizeof(forn),1,PtrForn);
						
						if(F.status != 0){
							
							gotoxy(4, 10);
					        printf("Fornecedor encontrado:");
					        gotoxy(4, 11);
					        printf("Código do fornecedor: %d", F.codforn);
					        gotoxy(4, 12);
					        printf("Nome do fornecedor: %s", F.nomeforn);
					        gotoxy(4, 13);
					        printf("Cidade do fornecedor: %s", F.cidadeforn);
					        
					        gotoxy(4, 15);
					        printf("Confirma Exclusao Logica (S/N)?");
					
							if (toupper(getche())=='S')
							{
								F.status = 0;
								fseek(PtrForn,pos,0);
								fwrite(&F,sizeof(forn),1,PtrForn);
								gotoxy(4, 17);
								printf("Registro foi deletado logicamente!!");
							}
							
						} else {
			
							gotoxy(4, 10);
				        	printf("Registro foi excluido!");
						}
				}
				getch();
				
				LimparExibicao();
				
				gotoxy(4, 8);
				printf("Código do fornecedor que deseja excluir logicamente (ou 0 para sair): ");
				gotoxy(4, 9);
				scanf("%d", &F.codforn);
			}	
			fclose(PtrForn);
		}
}

void excluirlogicaclientes(void)
{
	int pos;
	clientes C;
	FILE *PtrCli = fopen("clientes.dat","rb+");
	
	if (PtrCli == NULL)
	{
  		gotoxy(4,8);
        printf("Não há dados!");
	    getch();   
	    
	} else {
		
		LimparExibicao();

		gotoxy(4, 8);
		printf("CPF do cliente que deseja excluir logicamente (ou 0 para sair): ");
		gotoxy(4, 9);
		scanf("%d", &C.cpfcli);
			
			
			while (C.cpfcli > 0)
			{
				pos = buscacliente(PtrCli,C.cpfcli);
				
				if (pos==-1){
					
					gotoxy(4, 9);
					printf("Não foi encontrada!");
					
				} else {   
				
						fseek(PtrCli,pos,0);
						fread(&C,sizeof(clientes),1,PtrCli);
						
						if(C.status != 0){
				    	
					    	gotoxy(4, 10);
					        printf("Cliente encontrado:");
					        gotoxy(4, 11);
					        printf("CPF: %d", C.cpfcli);
					        gotoxy(4, 12);
					        printf("Nome: %s", C.nomecli);
					        gotoxy(4, 13);
					        printf("Quantidade de compras: %d", C.qtdcompras);
					        gotoxy(4, 14);
					        printf("Valor total comprado: %.2f", C.valortotcomprado);
					        gotoxy(4, 16);
							printf("Confirma Exclusao Logica (S/N)? ");
							if (toupper(getche())=='S')
							{
								C.status = 0;
								fseek(PtrCli,pos,0);
								fwrite(&C,sizeof(clientes),1,PtrCli);
								gotoxy(4, 18);
								printf("Registro foi deletado logicamente!!");
							}
							
						} else {
			
							gotoxy(4, 10);
				        	printf("Registro foi excluido!");
						}
				}
				getch();
				
				LimparExibicao();

				gotoxy(4, 8);
				printf("CPF do cliente que deseja excluir logicamente (ou 0 para sair): ");
				gotoxy(4, 9);
				scanf("%d", &C.cpfcli);
			}	
			fclose(PtrCli);
		}
}

void excluirlogicaprodutos(void)
{
	int pos;
	tpprod P;
	FILE *PtrProd = fopen("produtos.dat","rb+");
	
	if (PtrProd == NULL)
	{
  		gotoxy(4,8);
        printf("Não há dados!");
	    getch();
		   
	} else {
		
		LimparExibicao();

		gotoxy(4, 8);
		printf("Código do produto que deseja excluir logicamente (ou 0 para sair): ");
		gotoxy(4, 9);
		scanf("%d", &P.codprod);
			
			
			while (P.codprod > 0)
			{
				pos = BuscaProdSeqIndProd(PtrProd,P.codprod);
				
				if (pos==-1){
					
					gotoxy(4, 9);
					printf("Não foi encontrada!");
					
				} else {   
				
						fseek(PtrProd,pos,0);
						fread(&P,sizeof(tpprod),1,PtrProd);
						
						if(P.status != 0){
							
					    	gotoxy(4, 10);
					        printf("Produto encontrado:");
					        gotoxy(4,11);
					        printf("Código do produto: %d", P.codprod);
					        gotoxy(4, 12);
					        printf("Descrição: %s", P.descr);
					        gotoxy(4, 13);
					        printf("Estoque: %d", P.estoque);
					        gotoxy(4, 14);
					        printf("Preço: %.2f", P.preco);
					        gotoxy(4, 15);
					        printf("Data de Validade: %d/%d/%d", P.valid.d, P.valid.m, P.valid.a);
					        gotoxy(4,16);
					        printf("Código do fornecedor: %d", P.codforn);
					        
					    	gotoxy(4,18);
							printf("Confirma Exclusao Logica (S/N)? ");
							
							if (toupper(getche())=='S')
							{
								P.status = 0;
								fseek(PtrProd,pos,0);
								fwrite(&P,sizeof(tpprod),1,PtrProd);
								gotoxy(4, 20);
								printf("Registro foi deletado logicamente!!");
							}
							
						} else {
			
							gotoxy(4, 10);
				        	printf("Registro foi excluido!");
						}
							
							
				}
				getch();
				
				LimparExibicao();

				gotoxy(4, 8);
				printf("Código do produto que deseja excluir logicamente (ou 0 para sair): ");
				gotoxy(4, 9);
				scanf("%d", &P.codprod);
			}	
			fclose(PtrProd);
		}
}

void excluirproduto(void)
{
	tpprod P;
	FILE *PtrProd = fopen("produtos.dat","rb+");
	
	if (PtrProd == NULL)
	{
  		gotoxy(4,8);
        printf("Não há dados!");
	    getch();
		   
	} else {
	
	LimparExibicao();

	gotoxy(4, 8);
	printf("Confirma Exclusão Física (S/N)? ");
							
	if (toupper(getche())=='S')
	{
								
		FILE *PtrTemp = fopen("Temp.dat","wb");
		rewind(PtrProd);
		fread(&P,sizeof(tpprod),1,PtrProd);
								
		while (!feof(PtrProd))
		{
			if (P.status != 0)
				fwrite(&P,sizeof(tpprod),1,PtrTemp);
									
		fread(&P,sizeof(tpprod),1,PtrProd);
		}
								
		fclose(PtrProd);
		fclose(PtrTemp);
		remove("produtos.dat");
		rename("Temp.dat","produtos.dat");
		remove("Temp.dat");
								
		gotoxy(4,20);
		printf("Registros deletado!!");
			                
		} else {
			fclose(PtrProd);
			gotoxy(4,20);
			printf("Exclusão foi cancelada!");
		}
    }
} 

void excluircliente(void)
{
	clientes C;
	FILE *PtrCli = fopen("clientes.dat","rb+");
	
	if (PtrCli == NULL)
	{
  		gotoxy(4,8);
        printf("Não há dados!");
	    getch();
		   
	} else {
	
	LimparExibicao();

	gotoxy(4, 8);
	printf("Confirma Exclusão Física (S/N)? ");
							
	if (toupper(getche())=='S')
	{
								
		FILE *PtrTemp = fopen("Temp.dat","wb");
		rewind(PtrCli);
		fread(&C,sizeof(clientes),1,PtrCli);
								
		while (!feof(PtrCli))
		{
			if (C.status != 0)
				fwrite(&C,sizeof(clientes),1,PtrTemp);
									
		fread(&C,sizeof(clientes),1,PtrCli);
		}
								
		fclose(PtrCli);
		fclose(PtrTemp);
		remove("clientes.dat");
		rename("Temp.dat","clientes.dat");
		remove("Temp.dat");
								
		gotoxy(4,20);
		printf("Registros deletado!!");
			                
		} else {
			fclose(PtrCli);
			gotoxy(4,20);
			printf("Exclusão foi cancelada!");
		}
    }
}

void excluirfornecedor(void)
{
	forn F;
	FILE *PtrForn = fopen("fornecedor.dat","rb+");
	
	if (PtrForn == NULL)
	{
  		gotoxy(4,8);
        printf("Não há dados!");
	    getch();
		   
	} else {
	
	LimparExibicao();

	gotoxy(4, 8);
	printf("Confirma Exclusão Física (S/N)? ");
							
	if (toupper(getche())=='S')
	{
								
		FILE *PtrTemp = fopen("Temp.dat","wb");
		rewind(PtrForn);
		fread(&F,sizeof(forn),1,PtrForn);
								
		while (!feof(PtrForn))
		{
			if (F.status != 0)
				fwrite(&F,sizeof(forn),1,PtrTemp);
									
		fread(&F,sizeof(forn),1,PtrForn);
		}
								
		fclose(PtrForn);
		fclose(PtrTemp);
		remove("fornecedor.dat");
		rename("Temp.dat","fornecedor.dat");
		remove("Temp.dat");
								
		gotoxy(4,20);
		printf("Registros deletado!!");
			                
		} else {
			fclose(PtrForn);
			gotoxy(4,20);
			printf("Exclusão foi cancelada!");
		}
    }
}

void consultaProduto(void)
{
	int pos;
	
	tpprod P;
	forn F;
	
	FILE *PtrProd = fopen("produtos.dat","rb");
	if (PtrProd == NULL){

		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		
	} else {
   
    LimparExibicao();

    gotoxy(4, 8);
    printf("Digite o código do produto que deseja consultar (ou 0 para sair): ");
    gotoxy(4, 9);
    scanf("%d", &P.codprod);
    
    while(P.codprod > 0 ){
	
    pos = BuscaProdSeqIndProd(PtrProd,P.codprod);
    
    if (pos != -1) {
    	
    	fseek(PtrProd,pos,0);
		fread(&P,sizeof(tpprod),1,PtrProd);
		
		if(P.status != 0){
			
	    	gotoxy(4, 10);
	        printf("Produto encontrado:");
	        gotoxy(4,11);
	        printf("Código do produto: %d", P.codprod);
	        gotoxy(4, 12);
	        printf("Descrição: %s", P.descr);
	        gotoxy(4, 13);
	        printf("Estoque: %d", P.estoque);
	        gotoxy(4, 14);
	        printf("Preço: %.2f", P.preco);
	        gotoxy(4, 15);
	        printf("Data de Validade: %d/%d/%d", P.valid.d, P.valid.m, P.valid.a);
	       
	       	FILE *PtrForn = fopen("fornecedor.dat","rb");
			int posFornecedor = buscaforn(PtrForn, P.codforn);
			
			fseek(PtrForn,posFornecedor,0);
			fread(&F,sizeof(forn),1,PtrForn);
					            
			if (posFornecedor != -1)
			{
				gotoxy(4, 16);
				printf("Código: %d | Nome: %s | Cidade: %s ",F.codforn,F.nomeforn,F.cidadeforn);
			}
			else
			{
				gotoxy(4, 16);
				printf("Fornecedor não foi encontrado. ");
			}
		
	        gotoxy(4,18);
	        printf("Consulta foi feita com sucesso!");
	        
	        fclose(PtrForn);
        
        } else {
			
			gotoxy(4, 10);
        	printf("Registro foi excluido!");
		}
        
    } else {
    	gotoxy(4, 11);
        printf("Produto não foi encontrado!");
    }
    
    getch();
    
    LimparExibicao();

    gotoxy(4, 8);
    printf("Novo código do produto que deseja consultar (ou 0 para sair): ");
    gotoxy(4, 9);
    scanf("%d", &P.codprod);
    }
    
    fclose(PtrProd);
	}	
}

void consultaCliente(void)
{
	int pos;
	clientes C;
	
	FILE *PtrCli = fopen("clientes.dat","rb");
	if (PtrCli == NULL){
	
		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		 
	} else {
    
    LimparExibicao();

    gotoxy(4, 8);
    printf("Digite o nome do Cliente que deseja consultar (ou "" para sair): ");
    gotoxy(4, 9);
    fflush(stdin);
	gets(C.nomecli);
    
    if(C.nomecli != "" ){
	
    pos = BuscaBinariaCliente(PtrCli,C.nomecli);
    
	    if (pos != -1) {
	    	
	    	fseek(PtrCli,pos,0);
			fread(&C,sizeof(clientes),1,PtrCli);
			
				if(C.status != 0) {
		    	
			    	gotoxy(4, 10);
			        printf("Cliente encontrado:");
			        gotoxy(4, 11);
			        printf("CPF: %d", C.cpfcli);
			        gotoxy(4, 12);
			        printf("Nome: %s", C.nomecli);
			        gotoxy(4, 13);
			        printf("Quantidade de compras: %d", C.qtdcompras);
			        gotoxy(4, 14);
			        printf("Valor total comprado: %.2f", C.valortotcomprado);
			        gotoxy(4, 16);
			        printf("Consulta foi feita com sucesso!");
		        
		        } else {
					
					gotoxy(4, 10);
		        	printf("Registro foi excluido!");
				}
	        
		    } else {
		    	gotoxy(4, 11);
		        printf("Cliente não foi encontrado!");
   		 }
    }
    getch();
    fclose(PtrCli);
    }
}

void consultaFornecedor(void)
{
	int pos;
	
	forn F;
	
	FILE *PtrForn = fopen("fornecedor.dat","rb+");
	if (PtrForn == NULL) {
		

		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		
	} else {
    

	    LimparExibicao();
	
	    gotoxy(4, 8);
	    printf("Digite o Código do fornecedor que deseja consultar (ou 0 para sair): ");
	    gotoxy(4, 9);
	    scanf("%d", &F.codforn);
		
		if(F.codforn > 0){
	
	    pos = BuscaSentinelaforn(PtrForn, F.codforn);
		    
		    if (pos != -1) {
		    	
		    	fseek(PtrForn,pos,0);
				fread(&F,sizeof(forn),1,PtrForn);
				
				if(F.status != 0) {
					
					gotoxy(4, 10);
			        printf("Fornecedor encontrado:");
			        gotoxy(4, 11);
			        printf("Código do fornecedor: %d", F.codforn);
			        gotoxy(4, 12);
			        printf("Nome do fornecedor: %s", F.nomeforn);
			        gotoxy(4, 13);
			        printf("Cidade do fornecedor: %s", F.cidadeforn);
			        gotoxy(4, 15);
			        printf("Consulta foi feita com sucesso!");
		        
				} else{
					
					gotoxy(4, 10);
		        	printf("Registro foi excluido!");
				}
				
		    	
		        
		    } else {
		    	gotoxy(4, 11);
		        printf("Fornecedor não foi encontrado!");
		    }
	    
		    getch();
		    
		    LimparExibicao();
	
		}
	
	fclose(PtrForn);
	remove("tempf.dat");
	
	}
}

void alteraFornecedor(void)
{
	int pos;
	forn F;
	
	FILE *PtrForn = fopen("fornecedor.dat","rb+");
	if (PtrForn == NULL){

		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		
	} else {
   
    LimparExibicao();

    gotoxy(4, 8);
    printf("Digite o código do fornecedor que deseja alterar (ou 0 para sair): ");
    gotoxy(4, 9);
    scanf("%d", &F.codforn);
	
	while(F.codforn > 0){
	
    pos = buscaforn(PtrForn, F.codforn);
    
    if (pos != -1) {
    	
    	fseek(PtrForn,pos,0);
		fread(&F,sizeof(forn),1,PtrForn);
		
		if(F.status != 0){
						
	    	gotoxy(4, 10);
	        printf("Fornecedor encontrado:");
	        gotoxy(4, 11);
	        printf("Código do fornecedor: %d ", F.codforn);
	        gotoxy(4, 12);
	        printf("Nome atual do fornecedor: %s", F.nomeforn);
	        gotoxy(4, 13);
	        printf("Cidade atual do fornecedor: %s", F.cidadeforn);
	        
	      	gotoxy(4, 15);
	        printf("Novo nome do fornecedor: ");       
	        fflush(stdin);
	        gets(F.nomeforn);
	        gotoxy(4, 16);
	        printf("Nova Cidade do fornecedor: ");
	        fflush(stdin);
	        gets(F.cidadeforn);
	        gotoxy(4, 18);
	        printf("Fornecedor foi alterado com sucesso!");
	        fseek(PtrForn,pos,0);
			fwrite(&F,sizeof(forn),1,PtrForn);
		
		} else {
			
			gotoxy(4, 10);
        	printf("Registro foi excluido!");
		}
        
    } else {
    	gotoxy(4, 11);
        printf("Fornecedor não foi encontrado!");
    }
    
    getch();
    
    LimparExibicao();

    gotoxy(4, 8);
    printf("Novo código do fornecedor que deseja alterar (ou 0 para sair): ");
    gotoxy(4, 9);
    scanf("%d", &F.codforn);
	}
	
	fclose(PtrForn);
	}
}

void alteraCliente(void)
{
	int pos;
	clientes C;
	
	FILE *PtrCli = fopen("clientes.dat","rb+");
	if (PtrCli == NULL){

		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		
	} else {
	
    LimparExibicao();

    gotoxy(4, 8);
    printf("Digite o cpf do cliente que deseja alterar (ou 0 para sair): ");
    gotoxy(4, 9);
    scanf("%d", &C.cpfcli);
	
	while(C.cpfcli > 0){
		
    pos = buscacliente(PtrCli, C.cpfcli);
    
    if (pos != -1) {
    	
    	fseek(PtrCli,pos,0);
		fread(&C,sizeof(clientes),1,PtrCli);
		
		if(C.status != 0) {
    	
	    	gotoxy(4, 10);
	        printf("Cliente encontrado:");
	        gotoxy(4, 11);
	        printf("CPF: %d", C.cpfcli);
	        gotoxy(4, 12);
	        printf("Nome atual: %s", C.nomecli);
	        gotoxy(4, 13);
	        printf("Qtde Comprada: %d", C.qtdcompras);
	        gotoxy(4, 14);
	        printf("Total de Compras: %.2f", C.valortotcomprado);
	        
	        gotoxy(4, 16);
	        printf("Novo nome do cliente: ");
	        fflush(stdin);
	        gets(C.nomecli);
	        
	        gotoxy(4, 17);
	        printf("Novo quantidade compras do cliente: ");
	        scanf("%d", &C.qtdcompras);
	        
	        gotoxy(4, 18);
	        printf("Novo valor Total do cliente: ");
	        scanf("%f", &C.valortotcomprado);
	        
	        gotoxy(4, 20);
	        printf("Cliente foi alterado com sucesso!");
	        
	        fseek(PtrCli,pos,0);
			fwrite(&C,sizeof(clientes),1,PtrCli);
			
        } else {
			
			gotoxy(4, 10);
        	printf("Registro foi excluido!");
		}
		
    } else {
    	gotoxy(4, 11);
        printf("Cliente não foi encontrado!");
    }
    
    getch();
    
    LimparExibicao();

    gotoxy(4, 8);
    printf("Novo cpf do cliente que deseja alterar (ou 0 para sair): ");
    gotoxy(4, 9);
    scanf("%d", &C.cpfcli);
    }
    
    fclose(PtrCli);
	}
}


void alteraProduto(void) 
{
	int pos,posFornecedor,aux;
	
	tpprod P;
	forn F;
	
	FILE *PtrProd = fopen("produtos.dat","rb+");
	if (PtrProd == NULL){

		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		
	} else {
	
    LimparExibicao();

    gotoxy(4, 7);
    printf("Digite o código do produto que deseja alterar (ou 0 para sair): ");
    gotoxy(4, 8);
    scanf("%d", &P.codprod);
	
	while (P.codprod > 0) {
		
        pos = BuscaProdSeqIndProd(PtrProd , P.codprod);
    
        if (pos != -1) {
        	
        	fseek(PtrProd,pos,0);
			fread(&P,sizeof(tpprod),1,PtrProd);
			
			if(P.status != 0){
	        	
				gotoxy(4, 9);
	            printf("Produto encontrado:");
	            gotoxy(4, 10);
	            printf("Código do produto: %d", P.codprod);
	            gotoxy(4, 11);
	            printf("Código do fornecedor: %d", P.codforn);
	            gotoxy(4, 12);
	            printf("Descrição atual: %s", P.descr);
	            gotoxy(4, 13);
	            printf("Estoque atual: %d", P.estoque);
	            gotoxy(4, 14);
	            printf("Preço atual: %.2f", P.preco);
	            gotoxy(4,15);
	            printf("Data de Validade: %d/%d/%d", P.valid.d, P.valid.m, P.valid.a);
	            
	            getch();
	            LimparExibicao();
	            
	            gotoxy(4, 9);
	            printf("Novo Código do fornecedor do produto: ");
			    gotoxy(4, 10);
			    scanf("%d", &aux);
			    
			    FILE *PtrForn = fopen("fornecedor.dat","rb+");
				posFornecedor = buscaforn(PtrForn, aux);
			    
			    if(posFornecedor != -1){
			    	
			    	P.codforn = aux;
			    	
			    	gotoxy(4, 11);
		            printf("Nova descrição: ");
		            fflush(stdin);
		            gets(P.descr);  
		            
		            gotoxy(4, 12);
		            printf("Novo estoque: ");
		            scanf("%d", &P.estoque);  
		            
		            gotoxy(4, 13);
		            printf("Novo preço: ");
		            scanf("%f", &P.preco);   
					
					gotoxy(4, 14);
		            printf("Nova Data de Validade [dd mm aa]: ");
		            scanf("%d %d %d", &P.valid.d, &P.valid.m, &P.valid.a);
		            
		            gotoxy(4, 16);
	       			 printf("Produto foi alterado com sucesso!");
		            
		            fseek(PtrProd,pos,0);
					fwrite(&P,sizeof(tpprod),1,PtrProd);
			    	
			    	fclose(PtrForn);
			    	
				}
				else{
					
					gotoxy(4, 11);
	            	printf("Fornecedor não foi encontrado!");
				}
			
			} else {
				
				gotoxy(4, 10);
	        	printf("Registro foi excluido!");
        	
			}
			
        } else {
        	gotoxy(4, 10);
            printf("Produto não foi encontrado!");
        }
        
	    getch();
	    
	    LimparExibicao();
	
	    gotoxy(4, 7);
	    printf("Novo código do produto que deseja alterar (ou 0 para sair): ");
	    gotoxy(4, 8);
	    scanf("%d", &P.codprod);

	}

	fclose(PtrProd);
	}
}

void aumentarpreco(void)
{
	tpprod P;

	FILE *PtrProd = fopen("produtos.dat","rb+");

	int aux;
	
	float aumento,aux2;
	
	LimparExibicao();
	
	if (PtrProd == NULL){

		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		
	} else {
    
	    gotoxy(4, 8);
		printf("Qual a %% voce deseja aumentar o preço");
	    gotoxy(4, 9);
		scanf ("%f",&aumento);
	    gotoxy(4, 10);
		printf("Digite o código do fornecedor");
		gotoxy(4, 11);
		scanf("%d", &aux);
		
		fread(&P,sizeof(tpprod),1,PtrProd);
		
		while (!feof(PtrProd))
		{
		
	        if (P.codforn == aux && P.status != 0 ) {
	            
				gotoxy(4, 13);
		        printf("Preço do produto código [%d]", P.codprod);
		        
		        gotoxy(4, 15);
		        printf("Preço antes do aumento: R$ %.2f.", P.preco);
		        
		        P.preco += (aumento / 100.0) * P.preco;
		
				gotoxy(4, 16);
		        printf("Preço após o aumento: R$ %.2f.", P.preco);
	
		        getche();
            	LimparExibicao();
            	
            	fseek(PtrProd, -sizeof(tpprod), SEEK_CUR);
            	fwrite(&P, sizeof(tpprod), 1, PtrProd);
            	fseek(PtrProd, 0, SEEK_CUR);
	        }
	        
	        fread(&P,sizeof(tpprod),1,PtrProd);
		}
    }
    
    fclose(PtrProd);
    getche();
}


void cadproduto(void)
{
	tpprod P;
	forn F;
	
	LimparExibicao();
	
	FILE *PtrProd = fopen("produtos.dat","ab+");
	FILE *PtrForn = fopen("fornecedor.dat","ab+");
	
    int pos;
    gotoxy(4, 8);
    printf("Código do fornecedor do produto (ou 0 para sair): ");
    gotoxy(4, 9);
    scanf("%d", &P.codforn);
    
    while (P.codforn > 0) {
    
    pos = buscaforn(PtrForn, P.codforn);
    
    if (pos != -1) {
    	
    	gotoxy(4, 10);
		printf("Codigo do produto (ou 0 para sair): ");
		gotoxy(4, 11);
        scanf("%d", &P.codprod);
        	
            pos = buscaprod(PtrProd, P.codprod);
            
            if (pos == -1)
            {
            	
                gotoxy(4, 12);
                printf("Descrição do produto: ");
                gotoxy(4, 13);
                fflush(stdin);
                gets(P.descr);
                gotoxy(4, 14);
                printf("Quantidade em Estoque: ");
                gotoxy(4, 15);
                scanf("%d", &P.estoque);
                gotoxy(4, 16);
                printf("Preço: ");
                gotoxy(4, 17);
                scanf("%f", &P.preco);
                gotoxy(4, 18);
                printf("Data de Validade [dd mm aa]: ");
                gotoxy(4, 19);
                scanf("%d %d %d", &P.valid.d, &P.valid.m, &P.valid.a);
                gotoxy(4,20);
            	printf("Produto foi Cadastro com sucesso !");
            	P.status = 1;
            	fwrite(&P,sizeof(tpprod),1,PtrProd);
            	
            }
            else
            {
            	gotoxy(4,20);
                printf("Produto já foi cadastrado!");
              
            }
	    }
	    else
	    {
	    	gotoxy(4,10);
	 		printf("Fornecedor não foi encontrado !");
	        
	    }
	    
	getche();
	    
	LimparExibicao();
    gotoxy(4, 8);
    printf("Novo código do fornecedor do produto: ");
    gotoxy(4, 9);
    scanf("%d", &P.codforn);
    
    }
    
    fclose(PtrProd);
    fclose(PtrForn);
    
    SelecaoDiretaProdutos();
}



void cadfornecedor(void)
{
	forn F;
	
	LimparExibicao();
	
	FILE *PtrForn = fopen("fornecedor.dat","ab+");
	
    int pos;
    gotoxy(4, 8);
    printf("Codigo do fornecedor (ou 0 para sair): ");
    gotoxy(4, 9);
    scanf("%d", &F.codforn);

    while (F.codforn > 0)
    {
        pos = buscaforn(PtrForn, F.codforn);
        
        if (pos == -1)
        {
			gotoxy(4, 10);
            printf("Nome do fornecedor: ");
            gotoxy(4, 11);
            fflush(stdin);
            gets(F.nomeforn);
            gotoxy(4, 12);
            printf("Cidade do fornecedor: ");
            gotoxy(4, 13);
            fflush(stdin);
            gets(F.cidadeforn);
            gotoxy(4,14);
            printf("Fornecedor foi Cadastro com sucesso !");
    
            F.status = 1;
            fwrite(&F,sizeof(forn),1,PtrForn);
        }
        else
        {
        	gotoxy(4,10);
        	printf("Fornecedor já foi cadastrado !");
        	
        }
        
        getche();
        
		LimparExibicao();
	    gotoxy(4, 8);
	    printf("Novo código do fornecedor (ou 0 para sair): ");
	    gotoxy(4, 9);
	    scanf("%d", &F.codforn);
    }
    fclose(PtrForn);
    InsDiretaFornecedor();
}


void cadclientes(void) {
	
    clientes C;
    LimparExibicao();
    FILE *PtrCli = fopen("clientes.dat", "ab+");

    int pos;

    gotoxy(4, 8);
    printf("Cpf do Cliente (ou 0 para sair): ");
    gotoxy(4, 9);
    scanf("%d", &C.cpfcli);

    while (C.cpfcli > 0) {
    	
        pos = buscacliente(PtrCli, C.cpfcli);

        if (pos != -1) {
            gotoxy(4, 10);
            printf("Cliente já foi cadastrado !");
        } else {
        	C.qtdcompras = 0;
        	C.valortotcomprado = 0;
            gotoxy(4, 10);
            printf("Nome do Cliente: ");
            gotoxy(4, 11);
            fflush(stdin);
            gets(C.nomecli);
            gotoxy(4, 12);
            printf("Cliente foi cadastrado com sucesso !");

            C.status = 1;
            fwrite(&C, sizeof(clientes), 1, PtrCli);
        }

        getche();
        LimparExibicao();

        gotoxy(4, 8);
        printf("Novo Cpf do Cliente (ou 0 para sair): ");
        gotoxy(4, 9);
        scanf("%d", &C.cpfcli);
    }

    fclose(PtrCli);
    BSclientes();
}



int buscarProdutoNaVenda(FILE *PtrVendaProd, int codVenda, int codProduto) {
    int encontrou = 0;
    vendasprod VP;

    rewind(PtrVendaProd);

    while (fread(&VP, sizeof(vendasprod), 1, PtrVendaProd) == 1 && !encontrou) {
        if (VP.codvenda == codVenda && VP.codprod == codProduto) {
            encontrou = 1;
        }
    }

    return encontrou;
}

void vendaprod(void) {
	
    tpprod P;
    vendasprod VP;
    vendas V;
    clientes C;
    
    FILE *PtrVendaProd = fopen("vendasprod.dat", "rb+");
    FILE *PtrVendas = fopen("vendas.dat", "rb+");
    FILE *PtrCli = fopen("clientes.dat", "rb+");
    
    float somador = 0;
    int tlv = 0, cpf, x, prod, i, unidades;
    
    if (PtrVendas == NULL || PtrVendaProd == NULL || PtrCli == NULL){

		gotoxy(4,8);
		printf("Erro de ARQUIVO!");
		getch();
		
	} else {

	    gotoxy(4, 8);
	    printf("Digite o CPF do cliente: ");
	    gotoxy(4, 9);
	    scanf("%d", &cpf);
	
	    while (cpf > 0) {
	    	
	        x = buscacliente(PtrCli, cpf);
	        
	        fseek(PtrCli,x,0);
			fread(&C,sizeof(clientes),1,PtrCli);
	        
	        if (x != -1) {
	        	
	            LimparExibicao();
	
	            gotoxy(4, 8);
	            printf("Digite o codigo do produto que deseja comprar (ou 0 para sair): ");
	            gotoxy(4, 9);
	            scanf("%d", &prod);
	
	            while (prod > 0) {
	            	
	            	FILE *PtrProd = fopen("produtos.dat", "rb+");
	            	
	                i = buscaprod(PtrProd, prod);
	                
	                fseek(PtrProd,i,0);
					fread(&P,sizeof(tpprod),1,PtrProd);
	
	                if (i != -1 ) {
	                	
	                    fseek(PtrProd, i * sizeof(tpprod), SEEK_SET);
	                    fread(&P, sizeof(tpprod), 1, PtrProd);
	
	                    gotoxy(4, 12);
	                    printf("* Detalhes do Produto *");
	                    gotoxy(4, 13);
	                    printf("Código: %d", P.codprod);
	                    gotoxy(4, 14);
	                    printf("Descrição: %s", P.descr);
	                    gotoxy(4, 15);
	                    printf("Estoque: %d", P.estoque);
	                    gotoxy(4, 16);
	                    printf("Preço: R$ %.2f", P.preco);
	                    gotoxy(4, 17);
	                    printf("Data de Validade: %d/%d/%d", P.valid.d, P.valid.m, P.valid.a);
	                    gotoxy(4, 18);
	                    
	                    printf("Confirme o Produtos (S/N)");
	                    char confirmacao = toupper(getche());
	
	                    if (confirmacao == 'S') {
	                        LimparExibicao();
	                        gotoxy(4, 8);
	                        printf("Quantos produtos deseja comprar ?");
	                        gotoxy(4, 9);
	                        scanf("%d", &unidades);
	
	                        if (P.estoque >= unidades && unidades > 0) {
	                        	
	                        	int produtoJaAdicionado = buscarProdutoNaVenda(PtrVendaProd, tlv, P.codprod);
	                        	
	                        	if (produtoJaAdicionado)
	                        	{
	                        		gotoxy(4, 10);
						            printf("Produto já adicionado à venda");
						            gotoxy(4, 11);
						            printf("Atualizando quantidade...");
						            getch();
						
						            fseek(PtrVendaProd, -1 * sizeof(vendasprod), SEEK_CUR);
						            fread(&VP, sizeof(vendasprod), 1, PtrVendaProd);
						
						            VP.qtde += unidades;
						            VP.valorunitario = P.preco;
						            somador += P.preco * unidades;
						            fseek(PtrVendaProd, -1 * sizeof(vendasprod), SEEK_CUR);
						            fwrite(&VP, sizeof(vendasprod), 1, PtrVendaProd);
						            
						            P.estoque = P.estoque - unidades;
						            fseek(PtrProd, i, 0);
					        		fwrite(&P, sizeof(tpprod), 1, PtrProd);
	                        	}
	                        	else{

	                        	fseek(PtrVendas, 0, SEEK_END);
	                            tlv = ftell(PtrVendas) / sizeof(vendas);
	                            P.estoque = P.estoque - unidades;
	                            somador += P.preco * unidades;
	                            VP.qtde = unidades;
	                            VP.status = 1;
	                            VP.codprod = P.codprod;
	                            VP.valorunitario = P.preco;
	                            VP.codvenda = tlv;
	                            
	                            fseek(PtrProd, i, 0);
					        	fwrite(&P, sizeof(tpprod), 1, PtrProd);
	
	                            fseek(PtrVendaProd, 0, SEEK_END);
	                            fwrite(&VP, sizeof(vendasprod), 1, PtrVendaProd);
	                           	}
	                            
	                        } else 
							{
	                            gotoxy(4, 10);
	                            printf("Quantidade inválida ou produto sem estoque!");
	                            getch();
	                        }
	                    }
	                    
		                LimparExibicao();
		
		                gotoxy(4, 8);
		                printf("Digite o codigo do produto que deseja comprar (ou 0 para sair): ");
		                gotoxy(4, 9);
		                scanf("%d", &prod);
		                
		             	
	           		}
	           		fclose(PtrProd);
	    		}
	
	            if (somador > 0) {
	            	
	                LimparExibicao();
	
	                gotoxy(4, 8);
	                printf("Data da Venda [dd mm aa]: ");
	                gotoxy(4, 9);
	                scanf("%d %d %d", &V.valid.d, &V.valid.m, &V.valid.a);
	                gotoxy(4, 11);
	                printf("Código da Venda: %d ",tlv);
	                getche();
					
	                V.status = 1;
					V.codvenda = tlv;
					V.cpfcli = C.cpfcli;
					V.totvenda = somador;
					fseek(PtrVendas, 0, SEEK_END);
					fwrite(&V, sizeof(vendas), 1, PtrVendas);
					
					C.valortotcomprado += somador;
					C.qtdcompras = C.qtdcompras + 1;
					
					fseek(PtrCli, x, 0);
					fwrite(&C, sizeof(clientes), 1, PtrCli);
	                
	       		}
	       		
	       		
		    } else {
		        	
		        gotoxy(4, 10);
		        printf("Cliente não foi cadastrado!");
		        
		   	}
		        
	        getch();
	
	        LimparExibicao();
	        
	        somador = 0;
	
	        gotoxy(4, 8);
	        printf("Digite o CPF do novo cliente (ou 0 para sair): ");
	        gotoxy(4, 9);
	        scanf("%d", &cpf);
	        
	    }
     
	}   
	
    fclose(PtrVendaProd);
    fclose(PtrVendas);
    fclose(PtrCli);

}

   







void excluirvendas(void)
{
	int i,j,z,aux,pos,codigoVendaParaExcluir,posCliente,codigoCliente,codigoProduto,qtdeVendida,posProd;
	
	tpprod P;
    vendasprod VP;
    vendas V;
    clientes C;
    
    FILE *PtrVendaProd = fopen("vendasprod.dat", "rb+");
    FILE *PtrVendas = fopen("vendas.dat", "rb+");
    FILE *PtrCli = fopen("clientes.dat", "rb+");
    
    if (PtrVendas == NULL || PtrVendaProd == NULL || PtrCli == NULL){

		gotoxy(4,8);
		printf("Erro de ARQUIVO!");
		getch();
		
	} else {
	
	gotoxy(4,8);
	printf ("Qual o código da venda deseja excluir ?");
	gotoxy(4,9);
	scanf ("%d",&aux);
	
	if (aux > 0)
  	{
	
		pos = buscavenda(PtrVendas, aux);
		
		if (pos != -1){
			
				fseek(PtrVendas,pos,0);
				fread(&V,sizeof(vendas),1,PtrVendas);
	                    
				gotoxy(4,11);
	            printf("Venda encontrada:");
	            gotoxy(4,12);
	            printf("Código da venda %d",  V.codvenda);
	            gotoxy(4,13);
				printf("Data da Venda: %d/%d/%d", V.valid.d, V.valid.m, V.valid.a);
				gotoxy(4,15);
				printf("CPF: [%d]", V.cpfcli);
				
		   	 	posCliente = buscacliente(PtrCli,V.cpfcli);
		   	 	
		   	 	fseek(PtrCli,posCliente,0);
				fread(&C,sizeof(clientes),1,PtrCli);
		
				gotoxy(4,16);
				printf("Nome: %s.", C.nomecli);
				
				gotoxy(4,18);
	            printf("Confirma Exclusão? (S/N): ");
	            
	            char confirmacao = getch();
	
	            if (toupper(confirmacao) == 'S')
	            {
	            	FILE *PtrProd = fopen("produtos.dat", "rb+");
	            	
	            	codigoVendaParaExcluir = V.codvenda;
	            	
	                FILE *PtrTemp = fopen("Temp.dat","wb");
					rewind(PtrVendas);
					fread(&V,sizeof(vendas),1,PtrVendas);
											
					while (!feof(PtrVendas))
					{
						if (V.codvenda != codigoVendaParaExcluir){
							
							fwrite(&V,sizeof(vendas),1,PtrTemp);
							
						}
							
												
					fread(&V,sizeof(vendas),1,PtrVendas);
					}
											
					fclose(PtrVendas);
					fclose(PtrTemp);
					remove("vendas.dat");
					rename("Temp.dat","vendas.dat");
					remove("Temp.dat");
											
	                FILE *PtrTempVP = fopen("TempVP.dat","wb");
					rewind(PtrVendaProd);
					fread(&VP,sizeof(vendasprod),1,PtrVendaProd);
											
					while (!feof(PtrVendaProd))
					{
		               	if (VP.codvenda != codigoVendaParaExcluir) {
                    		fwrite(&VP, sizeof(vendasprod), 1, PtrTempVP);
		                } else {
		                    
					        C.valortotcomprado -= (VP.qtde * VP.valorunitario);
					        C.qtdcompras--;
					
					        fseek(PtrCli, posCliente, 0);
					        fwrite(&C, sizeof(clientes), 1, PtrCli);
					        
					        posProd = buscaprod(PtrProd, VP.codprod);
					        
					        if (posProd != -1) {
					        	
					            fseek(PtrProd, posProd, 0);
					            fread(&P, sizeof(tpprod), 1, PtrProd);
					
					            P.estoque += VP.qtde;
					
					            fseek(PtrProd, posProd, 0);
					            fwrite(&P, sizeof(tpprod), 1, PtrProd);
					        }
		            	}
		        
		            fread(&VP,sizeof(vendasprod),1,PtrVendaProd);
	           		}
	           		
	           		fclose(PtrVendaProd);
					fclose(PtrTempVP);
					remove("vendasprod.dat");
					rename("TempVP.dat","vendasprod.dat");
					remove("TempVP.dat");
	           		
	                gotoxy(4,20);
	                printf("Venda foi excluída com sucesso!");
	                
	                fclose(PtrProd);
	                fclose(PtrCli);
	            }
	            else
	            {
	            	gotoxy(4,20);
	                printf("Exclusão foi cancelada!");
	            }
	        }
	        else
	        {
	        	gotoxy(4,11);
	            printf("Venda não foi encontrado!");
	        }
	        
	        getch();
	
		}
	} 
}


void imprimirNotaFiscal(void) 
{
	int auxcod,i,pos,codigoVenda,posCliente;
	
	vendas V;
	
	FILE *PtrVenda = fopen("vendas.dat","rb");
	
	if (PtrVenda == NULL){

		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		
	} else {
	
		gotoxy(5, 7);
		printf("Código da Venda (ou 0 para sair): ");
		gotoxy(5, 8);
		scanf("%d", &auxcod);
		
		while(auxcod > 0)
		{
		
		int y=14;
		
		pos = buscavenda(PtrVenda, auxcod);
		
		fseek(PtrVenda,pos,0);
		fread(&V,sizeof(vendas),1,PtrVenda);
    
	    if (pos != -1) {

	    	clientes C;
	
			FILE *PtrCli = fopen("clientes.dat","rb");
	    	
	    	LimparExibicao();
	    	
	    	posCliente = buscacliente(PtrCli, V.cpfcli);
    
	    	fseek(PtrCli,posCliente,0);
			fread(&C,sizeof(clientes),1,PtrCli);
		
			gotoxy(5,7);
			printf("***************************** NOTA FISCAL ******************************");	
			    	
			gotoxy(5,8);
			printf("Código da Venda: %d",V.codvenda);
			
			gotoxy(50,8);
			printf("Data da Venda: %d/%d/%d", V.valid.d, V.valid.m, V.valid.a);
			
			gotoxy(5,10);
			printf("Nome: %s", C.nomecli);
			
			gotoxy(50,10);
		    printf("CPF: %d", C.cpfcli);
				
			gotoxy(5,12);
			printf("Código");
			
			gotoxy(15,12);
			printf("Produto");
			
			gotoxy(35,12);
			printf("QTD");
			
			gotoxy(45,12);
			printf("Valor");
			
			gotoxy(60,12);
			printf("Sub.Total");
			
			
			vendasprod VP;
	
			FILE *PtrVendaProd = fopen("vendasprod.dat","rb");
			
			fread(&VP,sizeof(vendasprod),1,PtrVendaProd);
			while (!feof(PtrVendaProd))
			{
			
			    	if (VP.codvenda == auxcod)
			    	{
				    	tpprod P;
		
						FILE *PtrProd = fopen("produtos.dat","rb");
				    		
						int posProd = buscaprod(PtrProd, VP.codprod);
						
						fseek(PtrProd,posProd,0);
						fread(&P,sizeof(tpprod),1,PtrProd);
							                   
						gotoxy(5, y);
				        printf("%d", VP.codprod);
				        gotoxy(15, y);
				        printf("%s", P.descr);
				        gotoxy(35, y);
				        printf("%d", VP.qtde);
				        gotoxy(45, y);
				        printf("R$ %.2f", VP.valorunitario);
				        gotoxy(60, y);
				        printf("R$ %.2f", VP.valorunitario * VP.qtde);
				        y++;
						
	    				fclose(PtrProd);
					}
					
					fread(&VP,sizeof(vendasprod),1,PtrVendaProd);
			}
			
			gotoxy(5,y);
			printf("------------------------------------------------------------------------");
			y++;
			gotoxy(5,y);
			printf("Total R$ %.2f",V.totvenda);
			y++;
			gotoxy(5,y);
			printf("------------------------------------------------------------------------");
			y++;
			gotoxy(5,y);
			
			fclose(PtrCli);
			fclose(PtrVendaProd);
		}
		else{
			gotoxy(5,10);
			printf("Venda não foi encontrada!");
		}
	    
	    getch();
	
	    LimparExibicao();
	    
	    gotoxy(5, 7);
		printf("Novo código da Venda (ou 0 para sair): ");
		gotoxy(5, 8);
		scanf("%d", &auxcod);
	
		}
		
		fclose(PtrVenda);
	}
}

void InserirDadosProdutos(void)
{
	
	tpprod P;

	FILE *PtrProd = fopen("produtos.dat","ab+");
	
	P.codprod = 5000;
	P.codforn = 1000;
	strcpy(P.descr,"Arroz");
	P.estoque = 6548;
	P.preco = 28;
	P.valid.d = 8;
	P.valid.m = 6;
	P.valid.a = 2027;
	P.status = 1;
    fwrite(&P,sizeof(tpprod),1,PtrProd);
	
	P.codprod = 5001;
	P.codforn = 1001;
	strcpy(P.descr,"Arroz Integral");
	P.estoque = 220;
	P.preco = 65;
	P.valid.d = 26;
	P.valid.m = 7;
	P.valid.a = 2032;
	P.status = 1;
    fwrite(&P,sizeof(tpprod),1,PtrProd);
	
	P.codprod = 5002;
	P.codforn = 1002;
	strcpy(P.descr,"arroz Carreteiro");
	P.estoque = 658;
	P.preco = 15;
	P.valid.d = 20;
	P.valid.m = 12;
	P.valid.a = 2025;
	P.status = 1;
    fwrite(&P,sizeof(tpprod),1,PtrProd);
	
	gotoxy(5,10);
	printf("*** Dados de Produtos inseridos! ***");
	
	fclose(PtrProd);
	SelecaoDiretaProdutos();
}

void InserirDadosFornecedor(void)
{
	
	forn F;

	FILE *PtrForn = fopen("fornecedor.dat","ab+");
	
	
	F.codforn = 1000;
	strcpy(F.cidadeforn,"Presidente Prudente");
	strcpy(F.nomeforn,"Coca-Cola");
	F.status = 1;
    fwrite(&F,sizeof(forn),1,PtrForn);
	
	F.codforn = 1001;
	strcpy(F.cidadeforn,"Presidente Venceslau");
	strcpy(F.nomeforn,"Anceli");
	F.status = 1;
    fwrite(&F,sizeof(forn),1,PtrForn);
	
	F.codforn = 1002;
	strcpy(F.cidadeforn,"Santo Anastacio");
	strcpy(F.nomeforn,"Monster");
	F.status = 1;
    fwrite(&F,sizeof(forn),1,PtrForn);
	
	gotoxy(5,8);
	printf("*** Dados de Fornecedor inseridos! ***");
	
	
	fclose(PtrForn);
	InsDiretaFornecedor();
	
}


void InserirDadosClientes(void)
{
	clientes C;

	FILE *PtrCli = fopen("clientes.dat","ab+");
	
	C.cpfcli = 12345;
	strcpy(C.nomecli,"Pedro");
	C.qtdcompras = 2;
	C.valortotcomprado = 1285;
	C.status = 1;
    fwrite(&C,sizeof(clientes),1,PtrCli);
	
	C.cpfcli = 98745;
	strcpy(C.nomecli,"Julia");
	C.qtdcompras = 1;
	C.valortotcomprado = 780;
	C.status = 1;
    fwrite(&C,sizeof(clientes),1,PtrCli);
	
	C.cpfcli = 54321;
	strcpy(C.nomecli,"Gustavo");
	C.qtdcompras = 1;
	C.valortotcomprado = 495;
	C.status = 1;
    fwrite(&C,sizeof(clientes),1,PtrCli);
	
	gotoxy(5,12);
	printf("*** Dados de Clientes inseridos! ***");
	
	fclose(PtrCli);
	BSclientes();
}


void InserirDadosVendas(void)
{
	
	vendas V;

	FILE *PtrVenda = fopen("vendas.dat","ab+");
	
	V.codvenda = 2000;
	V.cpfcli = 12345;
	V.totvenda = 1285,32;
	V.valid.d = 7;
	V.valid.m = 9;
	V.valid.a = 2022;
	V.status = 1;
    fwrite(&V,sizeof(vendas),1,PtrVenda);
	
	V.codvenda = 2001;
	V.cpfcli = 98745;
	V.totvenda = 780;
	V.valid.d = 18;
	V.valid.m = 4;
	V.valid.a = 2018;
	V.status = 1;
    fwrite(&V,sizeof(vendas),1,PtrVenda);
	
	V.codvenda = 2002;
	V.cpfcli = 54321;
	V.totvenda = 495;
	V.valid.d = 11;
	V.valid.m = 11;
	V.valid.a = 2011;
	V.status = 1;
    fwrite(&V,sizeof(vendas),1,PtrVenda);
    
	gotoxy(5,14);
	printf("*** Dados de Venda inseridos! ***");
	
	fclose(PtrVenda);

}


void InserirDadosVendasProd(void)
{
	
	vendasprod VP;

	FILE *PtrVendaProd = fopen("vendasprod.dat","ab+");
	
	VP.codvenda = 2000;
	VP.codprod = 5000;
	VP.qtde = 25;
	VP.valorunitario = 28;
	VP.status = 1;
    fwrite(&VP,sizeof(vendasprod),1,PtrVendaProd);
	
	VP.codvenda = 2000;
	VP.codprod = 5001;
	VP.qtde = 9;
	VP.valorunitario = 65;
	VP.status = 1;
    fwrite(&VP,sizeof(vendasprod),1,PtrVendaProd);
	
	VP.codvenda = 2001;
	VP.codprod = 5001;
	VP.qtde = 12;
	VP.valorunitario = 65;
	VP.status = 1;
    fwrite(&VP,sizeof(vendasprod),1,PtrVendaProd);
	
	VP.codvenda = 2002;
	VP.codprod = 5002;
	VP.qtde = 33;
	VP.valorunitario = 15;
	VP.status = 1;
    fwrite(&VP,sizeof(vendasprod),1,PtrVendaProd);
	
	gotoxy(5,16);
	printf("*** Dados de Venda de Produtos inseridos! ***");
	getch();
	
	
	fclose(PtrVendaProd);
}




void RelatorioProdutos(void)
{
   
    int pos,y=8;
    
	tpprod P;
	forn F;
	
	FILE *PtrProd = fopen("produtos.dat","rb");
	FILE *PtrForn = fopen("fornecedor.dat","rb");
	
	if (PtrProd == NULL){

		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		
	} else {
        
        gotoxy(20,7);
		printf("# # # Relatório de Produtos # # #");
		
		
		fread(&P,sizeof(tpprod),1,PtrProd);
		while (!feof(PtrProd))
		{
			if(P.status != 0){
					
				y++;
				gotoxy(5,y);
				printf("------------------------------------------------------------------------");
				y++;
				gotoxy(5,y);
				printf("ID: %d | Nome: %s | Estoque: %d | Preco: %.2f  ",P.codprod,P.descr,P.estoque,P.preco);
				y++;
		
				int posFornecedor = buscaforn(PtrForn, P.codforn);
				
				fseek(PtrForn,posFornecedor,0);
				fread(&F,sizeof(forn),1,PtrForn);
					            
				if (posFornecedor != -1 && F.status != 0 )
				{
					gotoxy(5,y);
					printf("Validade %d/%d/%d | Fornecedor: %s | Cidade: %s ",P.valid.d, P.valid.m, P.valid.a, F.nomeforn,F.cidadeforn);
				}
				else
				{
					y++;
					gotoxy(5,y);
					printf("Fornecedor não foi encontrado. ");
				}
				if(y>10)
				{
					y++;
					gotoxy(5,y+1);
					printf("Aperte alguma tecla para mais Produtos");
					y++;
					gotoxy(5,y+1);
					getch();
					LimparExibicao();
					y=7;	
				}
			}
			fread(&P,sizeof(tpprod),1,PtrProd);
		}		
    }
    fclose(PtrForn);
    fclose(PtrProd);
    getch();
}

void RelatorioFornecedores(void)
{
    int pos,y=8;
    
	forn F;
	
	FILE *PtrForn = fopen("fornecedor.dat","rb");
	
	if (PtrForn == NULL){

		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		
	} else {
       
        	gotoxy(20,7);
			printf("# # # Relatório de Fornecedores # # #");
			
			fread(&F,sizeof(forn),1,PtrForn);
			while (!feof(PtrForn))
			{
				if(F.status != 0){
					
					y++;	
					gotoxy(5,y);
					printf("------------------------------------------------------------------------");
					y++;
					gotoxy(5,y);
					printf("Código: %d | Nome: %s | Cidade: %s ",F.codforn,F.nomeforn,F.cidadeforn);
					if(y>13)
					{
						y++;
						gotoxy(5,y+1);
						printf("Aperte alguma tecla para mais Fornecedores");
						y++;
						gotoxy(5,y+1);
						getch();
						LimparExibicao();
						y=7;		
					}
				}
				fread(&F,sizeof(forn),1,PtrForn);
			}	
    }
    fclose(PtrForn);
    getch();
}

void RelatorioClientes(void)
{
    int pos,y=8;
    
	clientes C;
	
	FILE *PtrCli = fopen("clientes.dat","rb");
	
	if (PtrCli == NULL){

		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		
	} else {
		
	    gotoxy(20,7);
	    printf("# # # Relatório de Clientes # # #");
	    	
	   	fread(&C,sizeof(clientes),1,PtrCli);
		while (!feof(PtrCli))
		{
			
			if(C.status != 0){
		
				y++;
		    	gotoxy(5,y);
				printf("------------------------------------------------------------------------");
				y++;
				gotoxy(5,y);
				printf("CPF: %d | Nome: %s | Qtd: %d | Total: %.2f ", C.cpfcli, C.nomecli, C.qtdcompras, C.valortotcomprado);
				
				if(y>13)
				{
					y++;
					gotoxy(5,y+1);
					printf("Aperte alguma tecla para mais Clientes");
					y++;
					gotoxy(5,y+1);
					getch();	
					LimparExibicao();
					y=7;						
				}
			} 
			
			fread(&C,sizeof(clientes),1,PtrCli);
    	}
	}
	fclose(PtrCli);
	getch();
}

void RelatorioVendas(void)
{
    int pos,y=8;
    
	vendas V;
	
	FILE *PtrVenda = fopen("vendas.dat","rb");
	
	if (PtrVenda == NULL){

		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		
	} else {
		
		gotoxy(20,7);
	    printf("# # # Relatório de Vendas # # #");
        
	    fread(&V,sizeof(vendas),1,PtrVenda);
		while (!feof(PtrVenda))
		{
	    	y++;
			gotoxy(5,y);
	    	printf("Código da Venda: %d",V.codvenda);
			y++;
			
			gotoxy(5,y);
	    	printf("Produtos:");
			y++;
			
			vendasprod VP;
	
			FILE *PtrVendaProd = fopen("vendasprod.dat","rb");
			
			fread(&VP,sizeof(vendasprod),1,PtrVendaProd);
			while (!feof(PtrVendaProd))
			{
			
			    	if (VP.codvenda == V.codvenda)
			    	{
				    	tpprod P;
		
						FILE *PtrProd = fopen("produtos.dat","rb");
				    		
						int posProd = buscaprod(PtrProd, VP.codprod);
						
						fseek(PtrProd,posProd,0);
						fread(&P,sizeof(tpprod),1,PtrProd);
						
						if(P.status != 0){
							
						forn F;
		
						FILE *PtrForn = fopen("fornecedor.dat","rb");
						
						int posForn = buscaforn(PtrForn, P.codforn);
					
						fseek(PtrForn,posForn,0);
						fread(&F,sizeof(forn),1,PtrForn);
								                   
						gotoxy(5,y);
						printf("%d", VP.codprod);
						gotoxy(12,y);
						printf("%s", P.descr);
						gotoxy(33,y);
						printf("%d", VP.qtde);
						gotoxy(40,y);
						printf("R$ %.2f", (VP.valorunitario * VP.qtde));
						gotoxy(55,y);
						printf("%s", F.nomeforn);
						y++;
						
						fclose(PtrForn);
						
						}
						
						
	    				fclose(PtrProd);
					}
					
					fread(&VP,sizeof(vendasprod),1,PtrVendaProd);
			}
			
			fclose(PtrVendaProd);
			
			gotoxy(5,y);
			printf("Total R$ %.2f",V.totvenda);
			y++;
			
			gotoxy(5,y);
			printf("------------------------------------------------------------------------");
		
			if(y>13)
			{
				y++;
				gotoxy(5,y+1);
				printf("Aperte alguma tecla para mais Vendas");
				y++;
				gotoxy(5,y+1);
				getch();	
				LimparExibicao();
				y=6;						
			}
			
			fread(&V,sizeof(vendas),1,PtrVenda);
    	}
    	
    }
    
    fclose(PtrVenda);
    getch();

}

void RelatorioVendasProd(void)
{
    int pos,y=8;
    
	vendasprod VP;
	
	FILE *PtrVendaProd = fopen("vendasprod.dat","rb");
	
	if (PtrVendaProd == NULL){

		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		
	} else {
		
      	gotoxy(20,7);
	    printf("# # # Relatório de Vendas de Produtos # # #");
	    	
	    fread(&VP,sizeof(vendasprod),1,PtrVendaProd);
		while (!feof(PtrVendaProd))
		{
			
			y++;
	    	gotoxy(5,y);
			printf("------------------------------------------------------------------------");
			y++;
			gotoxy(5,y);
			printf("Cód.Produto: %d | Cód.Venda: %d | Qtd: %d | Unitario: %.2f ", VP.codprod, VP.codvenda, VP.qtde, VP.valorunitario );
			if(y>13)
			{
			y++;
			gotoxy(5,y+1);
			printf("Aperte alguma tecla para mais Vendas");
			y++;
			gotoxy(5,y+1);
			getch();	
			LimparExibicao();
			y=7;
					
			}
			
			fread(&VP,sizeof(vendasprod),1,PtrVendaProd);	
    	}
    }
    fclose(PtrVendaProd);
    getch();

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
		gotoxy(i,LI); printf("%c",205);
		gotoxy(i,LF); printf("%c",205);
	}
	for(i=LI+1; i<LF; i++)
	{
		gotoxy(CI,i); printf("%c",186);
		gotoxy(CF,i); printf("%c",186);
	}
	
	textcolor(7);
	textbackground(0);
}

char MenuPrincipal(void)
{
    LimparMenu();
    LimparMensagem();

    textcolor(15);
    gotoxy(30, 2);
    printf("# # # MENU # # #");

    gotoxy(4, 3);
    printf("[1] Cadastro");
    gotoxy(17, 3);
    printf("[2] Relatório");
    gotoxy(31, 3);
    printf("[3] Excluir");
    gotoxy(43, 3);
    printf("[4] Consulta");
    gotoxy(56, 3);
    printf("[5] Alterar");
    gotoxy(4, 4);
    printf("[6] Inserir Dados");
    gotoxy(22, 4);
    printf("[7] Aumentar Preços");
    gotoxy(43, 4);
    printf("[8] Vendas");
    gotoxy(56, 4);
    printf("[9] Exclusão Lógica");
    
    
    gotoxy(68, 5);
    printf("[ESC] Sair");

    gotoxy(13, 23);

    return toupper(getche());
}

char MenuCadastro(void)
{
    LimparMenu();
    LimparMensagem();

    textcolor(15);
    gotoxy(30, 2);
    printf("# # # CADASTROS # # #");
    gotoxy(4, 4);
    printf("[A] Cliente");
    gotoxy(16, 4);
    printf("[B] Produto");
    gotoxy(28, 4);
    printf("[C] Fornecedor");

    gotoxy(71, 5);
    printf("[9] <--");

    gotoxy(13, 23);

    return toupper(getche());
}

char MenuRelatorio(void)
{
    LimparMenu();
    LimparMensagem();

    textcolor(15);
    gotoxy(30, 2);
    printf("# # # RELATÓRIOS # # #");

    gotoxy(4, 4);
    printf("[J] Cliente");
    gotoxy(16, 4);
    printf("[K] Produto");
    gotoxy(28, 4);
    printf("[L] Fornecedor");
    gotoxy(43, 4);
    printf("[M] Venda");
    gotoxy(53, 4);
    printf("[N] Venda Produto");

    gotoxy(71, 5);
    printf("[9] <--");

    gotoxy(13, 23);

    return toupper(getche());
}

char MenuExcluir(void)
{
    LimparMenu();
    LimparMensagem();

    textcolor(15);
    gotoxy(30, 2);
    printf("# # # EXCLUIR FÍSICAMENTE # # #");

    gotoxy(4, 4);
    printf("[S] Cliente");
    gotoxy(16, 4);
    printf("[T] Produto");
    gotoxy(28, 4);
    printf("[U] Fornecedor");
    
    gotoxy(71, 5);
    printf("[9] <--");

    gotoxy(13, 23);

    return toupper(getche());
}


char MenuExcluirLogica(void)
{
    LimparMenu();
    LimparMensagem();

    textcolor(15);
    gotoxy(30, 2);
    printf("# # # EXCLUIR LOGICAMENTE # # #");

    gotoxy(4, 4);
    printf("[X] Cliente");
    gotoxy(16, 4);
    printf("[Y] Produto");
    gotoxy(28, 4);
    printf("[Z] Fornecedor");
    
    gotoxy(71, 5);
    printf("[9] <--");

    gotoxy(13, 23);

    return toupper(getche());
}

char MenuAlterar(void)
{
    LimparMenu();
    LimparMensagem();

    textcolor(15);
    gotoxy(30, 2);
    printf("# # # ALTERAR # # #");

    gotoxy(4, 4);
    printf("[D] Cliente");
    gotoxy(16, 4);
    printf("[E] Produto");
    gotoxy(28, 4);
    printf("[F] Fornecedor");

    gotoxy(71, 5);
    printf("[9] <--");

    gotoxy(13, 23);

    return toupper(getche());
}

char MenuConsulta(void)
{
    LimparMenu();
    LimparMensagem();

    textcolor(15);
    gotoxy(30, 2);
    printf("# # # CONSULTAR # # #");

    gotoxy(4, 4);
    printf("[G] Cliente");
    gotoxy(16, 4);
    printf("[H] Produto");
    gotoxy(28, 4);
    printf("[I] Fornecedor");

    gotoxy(71, 5);
    printf("[9] <--");

    gotoxy(13, 23);

    return toupper(getche());
}

char MenuVendas(void)
{
    LimparMenu();
    LimparMensagem();

    textcolor(15);
    gotoxy(30, 2);
    printf("# # # VENDAS # # #");

    gotoxy(4, 4);
    printf("[R] Nova Venda");
    
    gotoxy(19, 4);
    printf("[P] Excluir Venda");
    
    gotoxy(37, 4);
    printf("[Q] Nota Fiscal");

    gotoxy(71, 5);
    printf("[9] <--");

    gotoxy(13, 23);

    return toupper(getche());
}


void TelaMoldura(void)
{
	
	//Moldura em volta de tudo
	Moldura(1,1,80,25,7,7);
	
	//Moldura do Menu topo
	Moldura(2,1,79,6,7,7);
	
	//Moldura Central de Exb
	Moldura(2,6,79,21,7,7);
	
	//Moldura da mensagem
	Moldura(2,21,79,25,7,7);
	
	
	gotoxy(4,23);
	printf("Mensagem: ");

}

int main()
{
	setlocale(LC_ALL, "Portuguese");
    char opcao;
    
    TelaMoldura();

    do
    {
    	opcao = MenuPrincipal();
    
        switch (opcao)
        {
        	
        	case '1':
        		
        	opcao = MenuCadastro();
        	
	        switch (opcao)
	        {
	        	case 'A':
		        	
					cadclientes();
		        	
				LimparExibicao();
		        break;
		
		        case 'B':
		        	
		            cadproduto();
		            
				LimparExibicao();
		        break;
		
		        case 'C':
		        	
					cadfornecedor();
		            
				LimparExibicao();
		        break;
        		
			}
			
        	LimparExibicao();
            break;
            
            case '2':
            	
        	opcao = MenuRelatorio();
        	
        	switch (opcao)
	        {
     	
		        case 'J':
		        	
		        	RelatorioClientes();
		            
				LimparExibicao();
		        break;
          
				case 'K':
					
		            RelatorioProdutos();
		           
				LimparExibicao();
				break;
      
		        case 'L':
		        	
		        	RelatorioFornecedores();
		        	
				LimparExibicao();
		        break;
		        	
			
		        case 'M':
		        	
		        	RelatorioVendas();
		            
				LimparExibicao();	
		        break;
			
		        case 'N':
		        	
		            RelatorioVendasProd();
		            
				LimparExibicao();
		        break;
		
			}
        	
        	
        	LimparExibicao();
            break;
            
            case '3':
        	
        	opcao = MenuExcluir();
        	
        	switch (opcao)
	        {
	        	
		        case 'S':
		        	
		        	excluircliente();
		        	
				LimparExibicao();
		        break;
		        	
		        case 'T':
		        	
		        	excluirproduto();
		        	
				LimparExibicao();	
		        break;
		        	
		        	
		        case 'U':
		        	
		        	excluirfornecedor();
		        	
				LimparExibicao();
		        break;
	        	
			}
			
        	LimparExibicao();
            break;
            
            case '4':
        	
        	opcao = MenuConsulta();
        	
        	switch (opcao)
        	{
        		
	        	case 'G':
		        	
		            consultaCliente();
		            
				LimparExibicao();
		        break;
		        
		        case 'H':
		        	
		        	consultaProduto();
		        	
				LimparExibicao();
		        break;
		
		        case 'I':
		        	
		            consultaFornecedor();
		            
				LimparExibicao();
		        break;
        		
			}
			
        	LimparExibicao();
            break;
            
            case '5':
        	
        	opcao = MenuAlterar();
        	
        	switch (opcao)
        	{
        		
	        	case 'D':
		        	
		    		alteraCliente();
		         	
				LimparExibicao();
		        break;
		
		        case 'E':
		        	
		            alteraProduto();
		            
				LimparExibicao();
		        break;
		
		        case 'F':
		        	
		            alteraFornecedor();
		            
				LimparExibicao(); 
		        break;	
        		
			}
        	
        	LimparExibicao();
            break;
            
            case '6':
            	
            	InserirDadosFornecedor();
	            InserirDadosProdutos();
	            InserirDadosClientes();
	            InserirDadosVendas();
	            InserirDadosVendasProd();
            
			LimparExibicao();
            break;
            
            case '7':
        	
	        	aumentarpreco();
	        	
			LimparExibicao();
            break;
            
            

          	case '8':
        	
        	opcao = MenuVendas();
        	
        	switch (opcao)
        	{
        		
	        	case 'R':
		        	
		        	vendaprod();
		        
				LimparExibicao();
		    	break;
		    	  	
		    	case 'P':
		    		
		    		excluirvendas();
		    		
		     	LimparExibicao();  
		        break;
		        
		        case 'Q':
		       		
		       	    imprimirNotaFiscal();
		    		
				LimparExibicao();
		        break;
        	
			}
				
			LimparExibicao();
		    break;	

			case '9':
        	
        	opcao = MenuExcluirLogica();
        	
        	switch (opcao)
	        {
	        	
		        case 'X':
		        	
		        	excluirlogicaclientes();
		        	
				LimparExibicao();
		        break;
		        	
		        case 'Y':
		        	
		        	excluirlogicaprodutos();
		        	
				LimparExibicao();	
		        break;
		        	
		        	
		        case 'Z':
		        	
		        	excluirlogicafornecedor();
		        	
				LimparExibicao();
		        break;
	        	
			}
			
        	LimparExibicao();
            break;
    
	    }
        
    } while (opcao != 27);
    return 0;
}
