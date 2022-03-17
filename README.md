# SO Lab 5: Fatorial Multi-processo
Lab 4 de Sistemas operacionais

## Grupo
Igor Soler Cavalcanti - 42013550

Paloma de Sousa Bezerra - 32094264

Rafael Miranda Ferreira - 42080932


# Como Executar o Código
Compile e Execute o arquivo main.c em seu compilador de escolha (GCC foi o Utilizado)

Possíveis comandos para compilar o programa

`make main`

`gcc .\main.c`

Possível comando para executar o programa após compilá-lo
`./main`

## O que o programa faz?
Após inicar o programa, o usuario deve entrar um valor. O programa irá calcular o fatorial deste valor.

Ao entrar o valor, a função `fatorialMultiprocess(valor)` é chamada. Esta função divide o valor entrado pelo usuario em 2 metades e calcula usa cada medade como parâmetro para a função `multSucessiva()`. Os resultados da função mencionada anteriormente são multiplica-los para se obter o fatorial de `valor`. Entretanto, as 2 chamadas da `multSucessiva()` ocorrem simultaneamente em processos diferentes.

A primeira ação de  `fatorialMultiprocess()` é criar um pipe que será utilizado para que o processo filho criado em seguida passe o resultado de sua `multSucessiva()` para o processo pai. Desta forma, assim que os 2 processos finalizarem as suas execuções de `multSucessiva()`, os resultados já multiplicados e `fatorialMultiprocess()` retorna o fatorial de `valor`.
