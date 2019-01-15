#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Sistema bancário que possúi vários clientes, contas e movimentacões bancárias
//Cada linha do arquivo possui numero de 6 digitos seguids de um caractere identificador. Ex: 123456-a, ALém disso, tem o nome do cliente e o saldo inicial

//Arquivo movimentos.txt = informações de cada lançamento de um determinado dia. Cada linha possui numero da conta, caractere identificador e valor de lançamento.
//Se for positivo, esse valor de lançamento, é um crédito. Se for negativo, é um débito.

//QtdadeMovimento
//SomaDosCréditos
//SomaDosDébitos
//SaldoFinal

//Preciso registar essas tranferências.



typedef struct {
  int quantidade_movimentacoes;
  float credito; //se for maior que zero, armazeno aqui
  float debito;//se for menor que zero, armazeno aqui
}Movimentacao;


typedef struct {
  char *nome;
  char* numero_conta;
  float saldo;
  float saldo_final;
  Movimentacao* movimentacao; //Cada cliente possúi uma struct movimetanção, responsável por armazenar os valroes de débito, crédito, e quantas movimentações foram feitas
}Cliente;


void carrega_para_memoria(char* nome_do_arquivo,Cliente *cliente[],int *quantidade_structs){


  FILE* arquivo;
  arquivo = fopen(nome_do_arquivo,"r");

  if(arquivo == NULL)
    printf("Erro na abertura do arquivo!");

  int i, b,c;
  float saldo_aux;
  char linha[300];
  char *a;
  char segundo_aux[30];

  for(i=0;!feof(arquivo);i++){

        cliente[i] = malloc(sizeof(Cliente));
        cliente[i]->nome = malloc( sizeof(char) *60);
        cliente[i]->movimentacao = malloc(sizeof(Movimentacao));
        cliente[i]->movimentacao->credito = 0;
        cliente[i]->movimentacao->debito = 0;
        cliente[i]->movimentacao->quantidade_movimentacoes = 0;
        cliente[i]->numero_conta = malloc( sizeof(char) *12);

        fscanf(arquivo,"%s",cliente[i]->numero_conta); //leio todos os meus numeros, e avanço até o meu primeiro espaço em branco depois do numero do meu cliente
        fgets(linha,300,arquivo); //guarda minha linha do arquivo - linha é a variável que uso para guardar, 300 (chute) é até quantos caracteres eu vou ler
        //(como não sei o tamanho da linha, deixei 300), e 'arquivo' é de onde vou ler

        //Nese momento, estou exatamente em cima de um espaço em branco
        //printf("%s\n",linha); //--Descomente essa linha para visualizar melhor--

      a = linha; //Meu ponteiro "a" aponta para a posição inicial de "linha" (que é o espaço em branco)

      a++; //Pulo meu primeiro caracter de "a", ou seja, pulo para minha primeira letra do nome que vou ler, pois não quero ler o espaço em branco
      //(lembrando que meu primeiro caractere de da minha varíavel a é um espaço em branco)


      strcpy(segundo_aux,a); /*Faço minha segunda variável auxiliar apontar para 'a', ou seja, "segundo_aux" agora está apontando para onde começa o nome que vou ler.
      O motivo disso, é porque quero ler tudo que estiver antes do meu ";". Para fazer isso, vou percorrer a string até o "\n" (como fiz no for abaixo)
      e a cada caractere, vou fazendo uma verificação, que é "segundo_aux[c] == ';', ou seja, pergunto se o caractere na posição c é igual a ";".
      Caso seja, eu troco ";" por "\0", ou seja, termino a string ali mesmo, portanto, não contém mais a informação que se encontra depois do ";".
      Por esse motivo, criei uma nova string auxiliar: para encontrar meu ';' e dizer que ali é o fim da minha string.
      Quando digo que ali é o final da minha string, quer dizer que não vou ler nem o meu ';' e nem o que estiver depois, pois perco esses caracteres.
      Por isso uma cópia da string original teve que ser feita
      */


      for(c=0; segundo_aux[c]!='\n' ;c++) //for que percorre minha string até o final
        if(segundo_aux[c] == ';') //pergunto se o meu caractere na posição "c" é igual a ";", caso seja...
          segundo_aux[c] = '\0'; //digo que ali é o final da minha string

        strcpy(cliente[i]->nome,segundo_aux); /*meu cliente recebe o conteúdo de "segundo_aux", ou seja, o nome completo do cliente.
        Lembrete: strcpy foi usado, pois o nome do meu cliente está inicialmente em "segundo_aux", e para passar de "segundo_aux" para o campo
        "nome", da minha struct cliente, que também é uma string, preciso usar a função strcpy, que copia o que está na direita para a esquerda. */


      for(;*a !=';';a++); //Agora, volto a minha variável original, e preciso andar até o ";"
      //printf("%s",a); //--Descomente essa linha para visualizar o que está acontecendo--
      //Agora, estou exatamente em cima do meu ";"
      a+=2; //Com isso,pulo meu ";" e meu espaço em branco, ficando exatamente em cima dos meus números
      //printf("%s",a); //--Descomente essa linha para visualizar o que está acontecendo--

      //Agora que estou em cima dos meus números, vou ler e armazenar no meu campo 'saldo'
      saldo_aux = atof(a); //a função "atoaf()" converte uma string para um float. Então, faço essa conversão e armazeno em "saldo"
      cliente[i]->saldo = saldo_aux; //agora, o campo "saldo" de cliente, recebe o valor armazenado em "saldo" (variável acima)
      cliente[i]->saldo_final = saldo_aux;

      //Obs: poderia fazer também: cliente[i]->saldo_aux = atoaf(a), o resultado ia ser o mesmo e não precisaria usar a variavel saldo_aux
  }
   *quantidade_structs = i;//i armazena minha quantidade total de structs, e faço o meu parâmetro "quantidade_structs" receber essa variável, pois preciso saber
  //a quantidade de structs para a função seguinte

    //for(b=0;b<100;b++)
     //printf("%s %s %f\n",cliente[b]->numero_conta,cliente[b]->nome,cliente[b]->saldo);

  fclose(arquivo);

}


void carrega_movimentacoes_para_memoria(char* nome_do_arquivo,Cliente* cliente[],int quantidade_structs){
  FILE* arquivo;
  arquivo = fopen(nome_do_arquivo,"r");

  if(arquivo == NULL)
    printf("Erro na abertura do arquivo!");

    int i,j,k,l;
    char linha[80];
    char linha_aux[80];
    char* aux; //auxiliar que guardará apenas o código contido no arquivo "movimentos.txt"
    char* segundo_aux; //auxiliar que guardará apenas o meu valor contido no arquivo "movimentos.txt"
    float valor;

    for(i=0;!feof(arquivo);i++){

      fgets(linha,80,arquivo); //leio as linhas do meu arquivo
      //printf("%s\n",linha); //--Descomente essa linha para visualizar melhor--
      aux = linha; //aux aponta para linha, pois assim que encontrar meu espaço em branco, vou finalizar a string, e comprar o meu código
      strcpy(linha_aux,linha);
      segundo_aux = linha_aux;// "segundo aux" vai percorrer até o primeiro número, e ali será o início de "segundo_aux"
      //que está armzenado em aux com o código armazenado em cliente

      for(j=0;aux[j] != '\n';j++) //percorro até o final da minha string
        if(aux[j] == ' ') //caso eu encontre um espaço em branco
          aux[j] = '\0'; //digo que ali é o final da minha string


      //Agora, aux possúi apenas o código
      //printf("%s\n",aux); //--Descomente essa linha para visualizar melhor--

      for(;*segundo_aux!=' ';segundo_aux++);
      //Agora, estou em cima de um espaço em branco
      //printf("%s\n",segundo_aux ); //--Descomente essa linha para visualizar melhor--
      segundo_aux++; //E agora estou em cima do meu primeiro caractere valor
      valor = atof(segundo_aux); //converto meu código em float, e armazeno em valor
      //printf("%f\n",valor);


      for(k=0;k<quantidade_structs;k++){
        if(strcmp(cliente[k]->numero_conta,aux) == 0){ //agora, comparo o código contido em aux, com todos o código de todos os clientes, até encontrar algum que seja igual (==0)
          //printf("Codigo da struct:%s  Codigo no arquivo:%s\n",cliente[k]->numero_conta,aux); //--Descomente essa linha para ver melhor a comparação--
          //Quando encontrar algum código que for igual, vou verificar se o valor é débito (negativo) ou crédito (positivo)

          if(valor < 0) { //se for negativo
            //printf("%f\n",valor);
              cliente[k]->movimentacao->debito += valor; // débito vai receber esse valor
            //  printf("Cliente %s recebe %f em debito, valor atualizado: %f\n",cliente[k]->nome,valor,cliente[k]->movimentacao->debito); //--Descomente essa linha para ver melhor--
          }


          else if(valor >= 0) { //se for maior ou igual a 0, credito recebe esse valor
            cliente[k]->movimentacao->credito +=valor;
          //  printf("Cliente %s recebe %f em debito, valor atualizado: %f\n",cliente[k]->nome,valor,cliente[k]->movimentacao->credito); //--Descomente essa linha para ver melhor--
          }
          cliente[k]->saldo_final += valor;
          cliente[k]->movimentacao->quantidade_movimentacoes++; //cada linha do arquivo "movimentos.txt" é um movimentação. Cada movimentação (linha) faz com que a varíavel
          //"quantidade_movimentacoes" seja incrementada em 1. Dessa forma, sei quantas movimentações foram feitas na conta de posição k
        }
      }



    }
    //i = 0;
    //for(;i<quantidade_structs;i++)
      //printf("%d\n",cliente[i]->movimentacao->credito);

}

void gerar_relatorio(char* nome_do_arquivo,Cliente *cliente[],int quantidade_structs){
  FILE* arquivo;
  arquivo = fopen(nome_do_arquivo,"w");

  int i;
  fprintf(arquivo, "SEQ   CONTA       NOME          \t\t\t\tINIT        #MOV       CRED          DEB       FINAL \n" );
  for(i=0;i<quantidade_structs;i++){
    //fprintf(arquivo, "%d \t\t%s \t\t%s %-80f\n",i,ciente[i]->numero_conta,cliente[i]->nome,cliente[i]->saldo);
    fprintf(arquivo, "%-4d %-12s %-40s  %-10.2f %8d %12.2f %12.2f %12.2f\n",i,cliente[i]->numero_conta,cliente[i]->nome,cliente[i]->saldo,cliente[i]->movimentacao->quantidade_movimentacoes,cliente[i]->movimentacao->credito,cliente[i]->movimentacao->debito,cliente[i]->saldo_final);
  }

}



int main(){
  Cliente *cliente[30];
  int quantidade_structs;


  carrega_para_memoria("contas.txt",cliente,&quantidade_structs);
  //printf("%d",quantidade_structs);
  carrega_movimentacoes_para_memoria("movimentos.txt",cliente,quantidade_structs);
  gerar_relatorio("saida.txt",cliente,quantidade_structs);

  return 0;
}
