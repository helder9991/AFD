#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

using namespace std;

#define MAXESTADOS 25
#define MAXSIMBOLOS 25

// Cria dicionario verificando se existe elemento repetido
void Set_Simbolos(int qnt_simbolos,char simbolos[MAXSIMBOLOS]){
	
	int repetido = 1;
	while(repetido != 0){
		repetido = 0;
		cout << "Dicionario" << ":";
		cin >> simbolos;
	
		if (strlen(simbolos) == qnt_simbolos){
			for (int i=0 ; i<qnt_simbolos-1 ; i++){
				for(int j=i+1 ; j<qnt_simbolos ; j++){
					if (simbolos[i] == simbolos[j]){
						repetido += 1;
						break;
					}
				}
				if (repetido == 1){
					break;
				}
			}		
		}else{
			cout << "Dicionario maior ou menor que a quantidade de simbolos declarados" << endl;
			repetido++;
			system("pause");
		}
		// Caso não tenha numero repetido ele sai da função
		if (repetido == 0 ){
			return;
		}
	}
}

// Coloca todas as transoções possiveis para cada estado
int Set_Trans(int transicoes[][MAXSIMBOLOS],int qnt_estados, char simbolos[MAXSIMBOLOS]){
	
	int erro = 1;
	// While caso existem estados não alcaçados 
	while(erro == 1){
		int num;
		
		system("cls");
		cout << "------------ Colocando as Transições ------------\n";
		cout << "Alfabeto:" << simbolos << endl;
		cout << "Estados Existentes:";
		for (int i=0 ; i<qnt_estados ; i++){
			cout << "Q" << i << " ";
		}
		cout << endl;
	
		// Coloca dentro da matriz as transições - Colunas são os simbolos e Linhas são os estados
		for (int i=0 ; i<qnt_estados ; i++){
			for (int j=0 ; j<strlen(simbolos) ; j++){
				cout << "Transicao Q" << i << " para " << simbolos[j] << ":";
				cin >> num;
				
				// Caso a transição esteje fora do intervalo o algoritmo pede que coloque denovo
				if (num >= qnt_estados || num < 0){
					j--;
				}else{
					transicoes[i][j] = num;
				}
			}
		}
		
		// Verifica se existem estados não alcançados (k=1 pois não necessario voltar para Q0 pois é estado inicial)
		for (int k=1 ; k<qnt_estados ; k++){
			for (int i=0 ; i<qnt_estados ; i++){
				erro = 1;
				for (int j=0 ; j<strlen(simbolos) ; j++){
					if (k == transicoes[i][j]){
						erro = 0;
						break;
					}
				}
				if (erro == 0)
					break;
			}
			if (erro == 1){
				cout << "\nExistem estados que não podem ser alcançados, por favor coloque apenas estados alcançaveis\n  ";
				system("pause");
				break;
			}
		}
	}
	system("pause");
}

// Mostra todas as transições
void Mostra_Trans(int transicoes[][MAXSIMBOLOS], int qnt_estados, char simbolos[MAXSIMBOLOS]){
	system("cls");
	cout << "------------ Transiçoes ------------\n";
	for (int i=0 ; i<qnt_estados ;i++){
		cout << "Estado Q" << i << ":";
		for (int j=0 ; j<strlen(simbolos) ; j++){
			cout << "  " << simbolos[j] << "-> Q" << transicoes[i][j]; 
		}
		cout << endl;
	}
}

// Mostra Estados Finais
void Estados_Finais(int estado_final[MAXESTADOS],int qnt_estados){
	
	
	// Zera todos os estados finais
	for (int i=0 ; i<qnt_estados ; i++){
		estado_final[i] = -1;
	}
	
	// Usuario define os estados finais
	int num;
	
	cout << "\nDigite um estado final:";
	cin >> num;
			
	if (num > qnt_estados || num < 0){
		cout << "Valor fora do intervalo";
	}else{
		estado_final[num] = 1;	
	}

	// Caso o usuario deseje outro estado final
	char escolha = 's';
	
	while (escolha != 'n'){
		// Mostra estados existentes
		cout << "Estado Existentes:";
		for (int i=0 ; i<qnt_estados ; i++){
			cout <<	" Q" << i;
		}
		// Mostra estados finais
		cout << "\nEstado Final:";
		for (int i=0 ;i<qnt_estados ; i++){
			if (estado_final[i] != -1){
				cout << " Q" << i;
			}
		}
		
		cout << "\n\nAdicionar outro estado final ?('s' ou 'n'):";
		cin >> escolha;
		
		if (escolha == 's'){
			cout << "Digite um estado final:";
			cin >> num;
			
			if (num > qnt_estados || num < 0){
				cout << "Valor fora do intervalo";
			}else{
				estado_final[num] = 1;	
			}
		}	
	}
}

// Verifica se os simbolos da palavra estão corretos
void Verifica_Pal(char palavra[MAXSIMBOLOS], char simbolos[MAXSIMBOLOS]){
	int erro = 1;
	
	while (erro == 1){

		// For verifica se existem simbolos que não existem, para isso erro começa valendo 1 e se tiver uma palavra contida dentro do simbolo ele torna erro 0 
		for (int i=0 ; i<strlen(palavra) ; i++){
			erro = 1;
			for (int j=0 ; j<strlen(simbolos) ; j++){
				if (palavra[i] == simbolos[j]){
					erro = 0;
					break;
				}
			}
			if (erro == 1){
				cout << "\nPalavra com simbolos fora do alfabeto.\n";
				cout << "\nSimbolos Disponiveis:" << simbolos;
				cout << "\nDigite uma Palavra:";
				cin >> palavra;
				break;
			}
		}
		if (erro == 0){
			return;
		}
	}	
}

// Função que mostra As Transições, estado finais e a palavra
void Mostra_Tudo(int transicoes[][MAXSIMBOLOS], int estado_final[MAXSIMBOLOS], char palavra[MAXSIMBOLOS], char simbolos[MAXSIMBOLOS],int qnt_estados){
	Mostra_Trans(transicoes,qnt_estados,simbolos);
	
	// Mostra estados finais
	cout << "\nEstado Finais:";
	for (int i=0 ; i<qnt_estados ; i++){
		if (estado_final[i] == 1)
			cout << " Q" << i;
	}
	
	cout << "\nPalavra: " << palavra << endl;
}

void Leitura(int transicoes[][MAXSIMBOLOS], int estado_final[MAXSIMBOLOS], char palavra[MAXSIMBOLOS], char simbolos[MAXSIMBOLOS],int qnt_estados){
	int estado_atual=0;
	
	// Mostra as transições feitas pelo AFD
	cout << "\n*Transições:\n";
	for (int i=0 ; i<strlen(palavra) ; i++){
		for (int j=0 ; j<strlen(palavra) ; j++){
			if (palavra[i] == simbolos[j]){
				cout << "\t" << simbolos[j] << ": Q" << estado_atual << " -> Q" << transicoes[estado_atual][j] << endl;
				estado_atual = transicoes[estado_atual][j];
			}	
		}
	}
	
	for (int i=0 ; i<qnt_estados ; i++){
		if (estado_final[estado_atual] == 1){
			cout << "Palavra " << palavra << " é aceita\n";
			return;
		}
	}
	
	cout << "Palavra " << palavra << " não é aceita\n";
}

int Menu(){
	
	int erro = 1,escolha;
	while (erro == 1){
		erro = 0;
		system("cls");
		cout << "------------ Menu ------------\n";
		cout << "\n1 - Alterar somente a palavra.\n";
		cout << "2 - Alterar o AFD.\n";
		cout << "3 - Sair do AFD.\n";
		cout << "Opcao:";
		cin >> escolha;
		
		switch(escolha){
			case 1:
				return 1;
			case 2:
				system("cls");
				return 0;
			case 3:
				exit(0);
			default:
				cout << "Valor invalido.";
				erro = 1;
				break;
		}
	}
}

void Rotina(){
	int qnt_estados, qnt_simbolos,erro;
	// While caso o usuario deseje alterar os valores da maquina
	while(true){
		erro = 1;
		while(erro == 1){
			erro = 0;
			cout << "Quantidade de estados da maquina:";
			cin >> qnt_estados;
			cout << "Quantidade de simbolos do alfabeto:";
			cin >> qnt_simbolos;
		
			if (qnt_estados < 2 || qnt_estados > 25 || qnt_simbolos < 1 || qnt_simbolos > 25 ){
				cout << "Erro, digite novamente os valores.";
				erro++;
			}
		}
		
		// Cria quantidade de simbolos
		char simbolos[qnt_simbolos];
		Set_Simbolos(qnt_simbolos,simbolos);
		
	
		// Gera matriz que mostra as transições
		int transicoes[25][25];
		Set_Trans(transicoes,qnt_estados,simbolos);
		
		// Mostra os estados para cada simbolo
		Mostra_Trans(transicoes,qnt_estados,simbolos);
		system("pause");
		
		// Cria Estados finais
		int estado_final[qnt_estados];
		Estados_Finais(estado_final,qnt_estados);
		
		// Caso o usuario deseja mudar a palavra
		int repetir = 1;
		while(repetir == 1){
			
			char palavra[MAXSIMBOLOS];
			system("cls");
			strcpy(palavra," ");
			Mostra_Tudo(transicoes,estado_final,palavra,simbolos,qnt_estados);
			
			// Verifica se os simbolos da palavra estão no alfabeto
			
			cout << "\nDigite uma Palavra:";
			cin >> palavra;
			Verifica_Pal(palavra,simbolos);
			
			//Lê a palavra
			system("cls");
			Mostra_Tudo(transicoes,estado_final,palavra,simbolos,qnt_estados);
			Leitura(transicoes,estado_final,palavra,simbolos,qnt_estados);
		
			system("pause");
			repetir = Menu();
			
		}
	}
}


main(){
	setlocale(LC_ALL, "Portuguese");
	Rotina();
}

