#include <stdio.h>		// Header de Entrada e Saída, como printf
#include <sys/types.h>	// Definições de tipos de dados, como pid_t
#include <unistd.h>		// Define funções como pipe() e fork()
#include <sys/wait.h>	// Define funções de espera como wait()
#include <stdlib.h>		// Define funções gerais como exit()

// Calcula multiplicacoes sucessivas
// limit = Ultima Multiplicação
// inicio  = Primeira Multiplicação
long long int multSucessiva(int limit, int inicio){ // Retorna -1 em caso de ERRO
	long long int result = 1; // Resultado
	int mult;
	for (mult = inicio; mult<=limit; mult++) { // Calcula multiplicação do Fatorial de forma iterativa
        result = result * mult; // Calcula a proxima iteração do fatorial
	}
	return result; // Retorna Fatorial Calculado
}

// Limit = Numero do Fatorial
long long int fatorialMultiprocess(int limit){
	/*    SET VARIAVEIS DE PARA O FORK    */
	pid_t pid; // Process ID
	int process_io[2], pipe_status;
	
	pipe_status = pipe(process_io);
	if (pipe_status == -1){ // Checa se algum erro ocorreu com o pipe()
		perror("Erro ao definir Pipe");
		return -1; // ERRO
	}
	
	/*    CHAMA AS FUNCOES QUE CALCULAM FATORIAL    */
	long long int result; // Resultado
	long long int result_buffer; // Recebe o resultado de outro processo
	
	if ( limit == 0 || limit == 1 )
		return 1;
	
	else if (limit > 1){
		pid = fork(); // Bifurca o processo
		
		if (pid == -1) { // Checa se algum erro ocorreu com o fork()
			perror("Erro ao dividir processo");
			return -1; // ERRO
		}
		
		if (pid == 0) { // Processo Filho
			result_buffer = multSucessiva( limit/2, 1 );
			
			// Escreve o valor de result_buffer no pipe, para que o Parent possa ler
			write(process_io[1], &result_buffer, sizeof(result_buffer));  
			
			exit(0); // Sai do processo
		}
		
		// else if (pid > 0) Processo Pai
		result = multSucessiva( limit, (limit/2)+1);
		
		wait(NULL);
		
		// Lê o valor de result_buffer do pipe, escrito pelo processo Child
		read(process_io[0], &result_buffer, sizeof(result_buffer)); 
		
		result = result*result_buffer;
	}
	
	return result; // Retorna Fatorial Calculado
}

int value = 5;
int main(){
	int num;
	
	printf(" Calcular o fatorial de (int)\n");
	printf(" ->");
	
	scanf("%d", &num);
	
	printf(" Resultado %lld\n", fatorialMultiprocess(num));
}
