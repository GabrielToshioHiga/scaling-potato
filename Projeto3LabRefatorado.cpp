/*
==================================================================================

                               Calculo de Notas

==================================================================================
Empresa: Espartana
Equipe de Programadores:
               Nome: Fabrício José Machado Razera
               Nome: Gabriel de Oliveira Buchara
               Nome: Gabriel Toshio Hirokawa Higa
               Nome: Pedro Gabriel de Andrade
			   Nome: Rafael Vieira Rodrigues
Curso: Tecnologia Analise e Desenvolvimento de Sistemas
Disciplina: Laboratório de Programação 1
Data de início do projeto: 28/10/2022
----------------------------------------------------------------------------------
Descrição do Programa:
				Um programa que calcula as notas individuais de cada aluno que
realizou uma determinada prova informada, recebendo dados como a quantidade de
questões, o gabarito da prova, a quantidade de alunos, seus codigos de identi=
ficação, e suas respostas. 
Versão do programa: 1.0
Melhorias da versão: ("Primeira versão")		 
Data de lançamento da versão: 15/11/2022
==================================================================================
*/

#include <stdio.h>
#include <locale.h>
#include <ctype.h>


int main()
{
 
 	setlocale(LC_ALL, "Portuguese");
    
	//Declarando variaveis
    
	int questoesProva, quantidadeAlunos, i, contador, validacaoRA;
	float nota, valorQuestao, acertos;
	int validacaoGabarito, validacaoResposta;
	
	questoesProva = 0;
	quantidadeAlunos = 0;
	i = 0;
	validacaoGabarito = 0;
	validacaoResposta = 0;
	validacaoRA = 0;

	
	//Introducao
	
	printf("========================================================\n");
	printf("                        Bem vindo!                     \n");
	printf("========================================================\n");
	printf("                        Instruções                     \n");
	printf("\nEste programa foi desenvolvido com o intuito de calcular\n");
	printf("a pontuação dos alunos que realizaram uma prova.\n");
	printf("Por favor, Insira os dados solicitados.\n");
	printf("========================================================\n");
	
	
	

	
	//Quantidade de questoes
	
	
	while(questoesProva <= 0)
	{
		
		printf("Insira a quantidade de questões da prova:");
		scanf("%d", &questoesProva);
		printf("========================================================\n");
	}
	

	
	//Informe o gabarito da prova
	
	
	printf("Insira o gabarito da prova:\n");
	
	
	char vetorGabaritoProva[questoesProva];
	//refatorado

	for(i = 0; i < questoesProva; i++){	
		validacaoGabarito = 0;
		while(validacaoGabarito == 0){	
			printf("\nQuestão(%d) \nResposta:", i+1);
			scanf(" %c", &vetorGabaritoProva[i]);
			
			vetorGabaritoProva[i] = tolower(vetorGabaritoProva[i]);
			
	 		switch (vetorGabaritoProva[i]){
			 	case 'a'...'e': 
			 		validacaoGabarito = 1;
			 		break;
			 	default:
			 		printf("\nInsira um valor válido!\n");
					validacaoGabarito = 0; 
			 } 
		}
	}
	
	//Quantidade de alunos
	
		printf("========================================================");
		printf("\nInsira a quantidade de alunos que realizaram a prova: ");
		scanf("%d", &quantidadeAlunos);
		printf("========================================================");
	
	
	//Inserindo RAs
	
	printf("\nInsira o RA dos alunos:\n");
	
	int vetorIdentificaoAlunos[quantidadeAlunos];
	

		for(i = 0; i < quantidadeAlunos; i++)
		{
			printf("\nAluno(%d): ", i+1);
			scanf("%d", &vetorIdentificaoAlunos[i]);	
		}
		
	
	
	//Respostas dos alunos
	
	printf("========================================================");
	printf("\nInsira as respostas dos alunos:");
	
	float vetorNotas[quantidadeAlunos];
	char vetorRespostaAluno[questoesProva];
	
	contador = 0;
	valorQuestao = (10/questoesProva);
	
	while(contador < quantidadeAlunos)
	{
		printf("\n========================================================");
		printf("\nAluno(%d)\n", contador+1);
		validacaoResposta = 0;
		
		//refatorado
	for(i = 0; i < questoesProva; i++){	
		validacaoResposta = 0;
		while(validacaoResposta == 0)
		{
			printf("\nQuestão(%d)\n", i+1);
			printf("Resposta: ");
			scanf(" %c", &vetorRespostaAluno[i]);	
	 		
			 vetorRespostaAluno[i] = tolower(vetorRespostaAluno[i]);
			 
			 switch (vetorRespostaAluno[i]){
			 	case 'a'...'e': 
			 		validacaoResposta = 1;
			 		break;
			 	default:
			 		printf("\nInsira um valor válido!\n");
					validacaoResposta = 0; 
			 } 
		}
	}
		acertos = 0;
		
		//Comparando respostas com gabarito e calcular
		
		for(i = 0; i < questoesProva; i++)
		{
			if(vetorGabaritoProva[i] == vetorRespostaAluno[i])
			{
				acertos = acertos + 1;
			}				
		}
		
		//Guardando no vetor de notas
	
		nota = (acertos/questoesProva)*10.0;
	
		vetorNotas[contador] = nota;
	
		
		contador++; 
	}
	
	
	//Mostrando as notas com RAs
	
	printf("========================================================\n");
	printf("Relação de Notas:");
	
	for(i = 0; i < quantidadeAlunos; i++)
	{
		printf("\n\nAluno(RA:%d)", vetorIdentificaoAlunos[i]);
		printf("\nNota: %.2f", vetorNotas[i]);
	}
	
	printf("\n\n========================================================");
	printf("\nA equipe Espartana agradece pela preferencia.");
	printf("\n========================================================");
	
return 0;
}
