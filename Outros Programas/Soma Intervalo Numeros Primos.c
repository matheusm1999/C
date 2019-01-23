#include <stdio.h>

//Entrada: Numero que será verificado
//Saída: 1 caso o número seja primo, ou 0 caso o contrário
//Pré condição: Nenhuma
//Pós: Nenhuma
int e_primo(int numero){
  int i;
  int qtd_divisores = 0;
  for (i=2;i<=numero;i++){ //Testo todos os divisores de 2 até esse número
    if(numero%i == 0) //ele é divisivel por i, caso numero%i == 0
      qtd_divisores++;
      //printf("qtd de divisores: %d\n",qtd_divisores);
    }

  if(qtd_divisores == 1) {
      return 1; //É primo
      //printf("qtd de divisores: %d",qtd_divisores);
  }else
      return 0;
}


//Entrada: Onde começa o intervalo e onde termina esse intervalo
//Saída: Nenhuma
//Pré condição: Primeiro parâmetro precisa ser o início do intervalo (número menor) e o segundo parâmetro precisa ser onde termina (maior valor), ou seja, precisam estar em ordem
//Pós: Nenhumavoid soma_intervalos(int inicio_intervalo,int fim_intervalo){
  int numero;
  int soma = 0; //responsável por fazer a soma dos números primos
  for(numero = inicio_intervalo+1;numero<fim_intervalo;numero++){
    if(e_primo(numero)){
      soma += numero;
      printf("numero primo adicionado %d\n", numero);
    }
  }
  printf("Soma dos numeros primos: %d",soma);
}


int main() {
  soma_intervalos(2,19);
  //e_primo(9);
  return 0;
}
