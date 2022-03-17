#include <stdio.h>		// Header de Entrada e Saída, como printf
#include <sys/types.h>	// Definições de tipos de dados, como pid_t
#include <unistd.h>		// Define funções como pipe() e fork()
#include <sys/wait.h>	// Define funções de espera como wait()
#include <stdlib.h>		// Define funções gerais como exit()

int value = 5;

long long int fatorial(int limit){
	long long int result = 1; // Resultado
	int mult;
	
	for (mult = 1; mult<=limit; mult++) { // Calcula multiplicação do Fatorial de forma iterativa
        result = result * mult; // Calcula a proxima iteração do fatorial
	}
	
	return result; // Retorna Fatorial Calculado
}

int main(){
	printf("Resultado %lld", fatorial(9));
}

int main_(){
	// pip[0] = Read     pip[1] = Write
	// Se pipe_status for -1, ocorreu um erro
	int pip[2], pipe_status;
	pid_t pid;

	pipe_status = pipe(pip);
	if (pipe_status == -1){ // Checa se algum erro ocorreu com o pipe()
		perror("Erro ao definir Pipe");
		exit(1);
	}
	
	pid = fork(); // Bifurca o processo
	
	if (pid == -1) { // Checa se algum erro ocorreu com o fork()
		perror("Erro ao dividir processo");
		exit(1);
	}
	else if (pid == 0) { // Processo Filho
		printf("Entrei no filho!\n\n");
		
		value += 15;
		
		printf ("CHILD\tvalue = %d\n",value);
		
		// Escreve o valor de value no pipe, para que o Parent possa ler
		write(pip[1], &value, 1);  
		
		return 0;
	}
	else if (pid > 0) { // Processo Pai
		wait(NULL);
		
		// Lê o valor de value do pipe, escrito pelo processo Child
		read(pip[0], &value, sizeof(int)); 
		
		printf("PARENT\tvalue = %d\n",value);
		return 0;
	}
}
