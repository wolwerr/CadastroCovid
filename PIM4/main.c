#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

typedef struct data DATA;
struct data
{
	int dia;
	int mes;
	int ano;
};

typedef struct local LOCAL;
struct local
{
	char rua[30];
	char n[10];
	char bairro[20];
	char cidade[20];
	char estado[10];
	char cep[10];
};

typedef struct paciente PACIENTE;
struct paciente
{
	char nome[40];
	char cpf[20];
	char telefone[20];
	LOCAL endereco;
	DATA nasc;
	char email[40];
	DATA diagnostico;
	char comorbidades[60];
};

void SetCursorPosition(int XPos, int YPos)
{
	COORD coord;
	coord.X = XPos;
	coord.Y = YPos;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int fileExists(const char *filename)
{
	FILE * file;
	if (file = fopen(filename, "r"))
	{
		fclose(file);
		return 1;
	}

	return 0;
}

int main()
{
	unsigned int cp = 1252;
	unsigned int cpin = GetConsoleCP();
	unsigned int cpout = GetConsoleOutputCP();

	SetConsoleCP(cp);
	SetConsoleOutputCP(cp);

	if (fileExists("users.txt") == 0)
	{
		FILE * users;
		users = fopen("users.txt", "w");
		fclose(users);
	}

	int opcao = 0;
	int podeEntrar = 0;
	int confirma = 0;

	// Logar ou criar usuário?
	do {
		system("cls");
		printf("\n  #-------------------  CADASTRO DE PACIENTES (COVID 19)  -------------------#");
		printf("\n  |                                                                          |");
		printf("\n  |                                                                          |");
		printf("\n  |                               BEM-VINDO!                                 |");
		printf("\n  |                                                                          |");
		printf("\n  |                                                                          |");
		printf("\n  |            1 - FAZER LOGIN                                               |");
		printf("\n  |            2 - CRIAR NOVO USUÁRIO                                        |");
		printf("\n  |                                                                          |");
		printf("\n  |                                                                          |");
		printf("\n  |            0 - SAIR                                                      |");
		printf("\n  |                                                                          |");
		printf("\n  |                                                                          |");
		printf("\n  |                                                                          |");
		printf("\n  |                                                                          |");
		printf("\n  |                                                                          |");
		printf("\n  #--------------------------------------------------------------------------#");
		printf("\n\n  > Escolha uma opção: ");
		scanf("%i", &opcao);

		switch (opcao)
		{
			case 1:
				{
					// Página de login
					do {
						char login[15];
						char senha[15];

						system("cls");
						printf("\n  #-------------------  CADASTRO DE PACIENTES (COVID 19)  -------------------#");
						printf("\n  |                                                                          |");
						printf("\n  |                                                                          |");
						printf("\n  |                               BEM-VINDO!                                 |");
						printf("\n  |                                                                          |");
						printf("\n  |                                                                          |");
						printf("\n  |                  FAVOR INSERIR SEUS DADOS DE ACESSO:                     |");
						printf("\n  |                                                                          |");
						printf("\n  |                  LOGIN:                                                  |");
						printf("\n  |                  SENHA:                                                  |");
						printf("\n  |                                                                          |");
						printf("\n  |                                                                          |");
						printf("\n  |                                                                          |");
						printf("\n  |                                                                          |");
						printf("\n  |                                                                          |");
						printf("\n  |                                                                          |");
						printf("\n  #--------------------------------------------------------------------------#");

						SetCursorPosition(28, 9);
						scanf("%s", &login);

						SetCursorPosition(28, 10);

						int p = 0;

						do {
							senha[p] = getch();

							if (senha[p] != '\r' && senha[p] != '\b')
							{
								printf("*");
							}

							if (senha[p] == '\b' && p >= 1)
							{
								p -= 2;
								SetCursorPosition(29 + p, 10);
								printf(" ");
								SetCursorPosition(29 + p, 10);
							}

							p++;

						}

						while (senha[p - 1] != '\r');

						senha[p - 1] = '\0';

						SetCursorPosition(0, 20);

						FILE * users;
						users = fopen("users.txt", "r");

						char usuario[15];
						char senhaCorreta[15];
						int encontrouUsuario = 0;

						while (fgets(usuario, sizeof(usuario), users) != NULL)
						{
							if (strstr(usuario, login) != NULL)
							{
								encontrouUsuario = 1;
								fscanf(users, "%[^\n]", senhaCorreta);
							}
						}

						fclose(users);

						if (encontrouUsuario == 1)
						{
							if (strstr(senha, senhaCorreta) != NULL)
							{
								podeEntrar = 1;
							}
							else
							{
								printf(" [!] Senha incorreta! Pressione ENTER para continuar...");
								podeEntrar = 0;
								getch();
							}
						}
						else
						{
							printf(" [!] Usuário não encontrado! Pressione ENTER para continuar...");
							podeEntrar = 0;
							getch();
						}
					}

					while (podeEntrar != 1);

					// Checando os arquivos
					if (fileExists("listaPacientes.txt") == 0)
					{
						FILE * listaPacientes;
						listaPacientes = fopen("listaPacientes.txt", "w");
						fclose(listaPacientes);
					}

					if (fileExists("grupoDeRisco.txt") == 0)
					{
						FILE * grupoDeRisco;
						grupoDeRisco = fopen("grupoDeRisco.txt", "w");
						fclose(grupoDeRisco);
					}

					// Menu Principal
					do {
						system("cls");
						printf("\n  #-------------------  CADASTRO DE PACIENTES (COVID 19)  -------------------#");
						printf("\n  |                                                                          |");
						printf("\n  |                                                                          |");
						printf("\n  |                             MENU PRINCIPAL                               |");
						printf("\n  |                                                                          |");
						printf("\n  |                                                                          |");
						printf("\n  |            1 - CONSULTAR LISTA DE PACIENTES                              |");
						printf("\n  |            2 - CONSULTAR LISTA DE PACIENTES DO GRUPO DE RISCO            |");
						printf("\n  |            3 - CADASTRAR UM NOVO PACIENTE                                |");
						printf("\n  |                                                                          |");
						printf("\n  |            0 - SAIR                                                      |");
						printf("\n  |                                                                          |");
						printf("\n  |                                                                          |");
						printf("\n  |                                                                          |");
						printf("\n  |                                                                          |");
						printf("\n  |                                                                          |");
						printf("\n  #--------------------------------------------------------------------------#");
						printf("\n\n  > Escolha uma opção: ");
						scanf("%i", &opcao);

						switch (opcao)
						{
							// Consulta de pacientes
							case 1:
								{
									system("cls");
									system("cls");
									printf("\n--------------------------  CONSULTA DE PACIENTES  ----------------------------");
									printf("\n\n\n\n");

									FILE * listaPacientes;
									listaPacientes = fopen("listaPacientes.txt", "r");

									if (listaPacientes == NULL)
									{
										printf(" [!] Não há pacientes cadastrados! Pressione ENTER para continuar...");
										break;
									}

									char pacientes[1500];

									while (fgets(pacientes, 1500, listaPacientes) != NULL)
									{
										printf("%s", pacientes);
									}

									fclose(listaPacientes);
									getch();

									break;
								}

                            // Consulta de pacientes do grupo de risco
							case 2:
								{
									system("cls");
									printf("\n-----------------  CONSULTA DE PACIENTES (GRUPO DE RISCO)  --------------------");
									printf("\n\n\n\n");

									FILE * grupoDeRisco;
									grupoDeRisco = fopen("grupoDeRisco.txt", "r");

									if (grupoDeRisco == NULL)
									{
										printf(" [!] Não há pacientes com comorbidades! Pressione ENTER para continuar...");
										break;
									}

									char comorbidades[1500];

									while (fgets(comorbidades, 1500, grupoDeRisco) != NULL)
									{
										printf("%s", comorbidades);
									}

									fclose(grupoDeRisco);
									getch();

									break;
								}

                            // Cadastro de pacientes
							case 3:
								{
									PACIENTE novoPaciente;
									int salvarCadastro = 0;
									int ano = 2020;
									int idade;

									do {
										char temp;

										system("cls");
										printf("\n  #-------------------  CADASTRO DE PACIENTES (COVID 19)  -------------------#");
										printf("\n  |                                                                          |");
										printf("\n  |                       CADASTRO DE NOVO PACIENTE                          |");
										printf("\n  |                                                                          |");
										printf("\n  |  NOME: ______________________________       CPF: ____________            |");
										printf("\n  |                                                                          |");
										printf("\n  |  TELEFONE: _______________       NASCIMENTO: __ / __ / ____              |");
										printf("\n  |                                                                          |");
										printf("\n  |  RUA: _____________________      N: ____    BAIRRO: ________________     |");
										printf("\n  |                                                                          |");
										printf("\n  |  CIDADE: _______________         ESTADO: __     CEP: _________           |");
										printf("\n  |                                                                          |");
										printf("\n  |  E-MAIL: ______________________________   DIAGNOSTICO: __ / __ / ____    |");
										printf("\n  |                                                                          |");
										printf("\n  |  COMORBIDADES: __________________________________________________        |");
										printf("\n  |                                                                          |");
										printf("\n  #--------------------------------------------------------------------------#");
										printf("\n\n   (Registre nos campos acima os dados do paciente)");
										printf("\n   (Caso não haja comorbidades, deixar o campo em branco)");

										SetCursorPosition(11, 5);
										scanf("%c", &temp);
										scanf("%[^\n]", &novoPaciente.nome);

										SetCursorPosition(53, 5);
										scanf("%c", &temp);
										scanf("%[^\n]", &novoPaciente.cpf);

										SetCursorPosition(15, 7);
										scanf("%c", &temp);
										scanf("%[^\n]", &novoPaciente.telefone);

										SetCursorPosition(49, 7);
										scanf("%i", &novoPaciente.nasc.dia);

										SetCursorPosition(54, 7);
										scanf("%c", &temp);
										scanf("%i", &novoPaciente.nasc.mes);

										SetCursorPosition(59, 7);
										scanf("%i", &novoPaciente.nasc.ano);

										SetCursorPosition(10, 9);
										scanf("%c", &temp);
										scanf("%[^\n]", &novoPaciente.endereco.rua);

										SetCursorPosition(40, 9);
										scanf("%c", &temp);
										scanf("%[^\n]", &novoPaciente.endereco.n);

										SetCursorPosition(56, 9);
										scanf("%c", &temp);
										scanf("%[^\n]", &novoPaciente.endereco.bairro);

										SetCursorPosition(13, 11);
										scanf("%c", &temp);
										scanf("%[^\n]", &novoPaciente.endereco.cidade);

										SetCursorPosition(45, 11);
										scanf("%c", &temp);
										scanf("%[^\n]", &novoPaciente.endereco.estado);

										SetCursorPosition(57, 11);
										scanf("%c", &temp);
										scanf("%[^\n]", &novoPaciente.endereco.cep);

										SetCursorPosition(13, 13);
										scanf("%c", &temp);
										scanf("%[^\n]", &novoPaciente.email);

										SetCursorPosition(59, 13);
										scanf("%i", &novoPaciente.diagnostico.dia);

										SetCursorPosition(64, 13);
										scanf("%c", &temp);
										scanf("%i", &novoPaciente.diagnostico.mes);

										SetCursorPosition(69, 13);
										scanf("%i", &novoPaciente.diagnostico.ano);

										SetCursorPosition(19, 15);
										scanf("%c", &temp);
										gets(novoPaciente.comorbidades);

										SetCursorPosition(1, 19);
										printf("                                                                               ");
										printf("                                                                               ");
										printf("                                                                               ");
										SetCursorPosition(1, 19);
										printf("  > Deseja salvar este cadastro? (1 = sim; 0 = não) _");
										SetCursorPosition(53, 19);
										scanf("%i", &salvarCadastro);

									}

									while (salvarCadastro != 1);

									FILE * listaPacientes;
									listaPacientes = fopen("listaPacientes.txt", "a");

									fprintf(listaPacientes, "NOME: %s\n", novoPaciente.nome);
									fprintf(listaPacientes, "CPF: %s\n", novoPaciente.cpf);
									fprintf(listaPacientes, "TELEFONE: %s\n", novoPaciente.telefone);
									fprintf(listaPacientes, "ENDEREÇO: %s, nº %s\n", novoPaciente.endereco.rua, novoPaciente.endereco.n);
									fprintf(listaPacientes, "BAIRRO: %s\n", novoPaciente.endereco.bairro);
									fprintf(listaPacientes, "CIDADE: %s - %s\n", novoPaciente.endereco.cidade, novoPaciente.endereco.estado);
									fprintf(listaPacientes, "CEP: %s\n", novoPaciente.endereco.cep);
									fprintf(listaPacientes, "DATA DE NASCIMENTO: %i / %i / %i\n", novoPaciente.nasc.dia, novoPaciente.nasc.mes, novoPaciente.nasc.ano);
									fprintf(listaPacientes, "E-MAIL: %s\n", novoPaciente.email);
									fprintf(listaPacientes, "DATA DO DIAGNÓSTICO: %i / %i / %i\n", novoPaciente.diagnostico.dia, novoPaciente.diagnostico.mes, novoPaciente.diagnostico.ano);

									if (!strcmp(novoPaciente.comorbidades, ""))
									{
										fprintf(listaPacientes, "COMORBIDADES:\n\n\n");
									}
									else
									{
										fprintf(listaPacientes, "COMORBIDADES: %s\n\n\n", novoPaciente.comorbidades);
									}

									idade = ano - novoPaciente.nasc.ano;

									fclose(listaPacientes);

									FILE * grupoDeRisco;
									grupoDeRisco = fopen("grupoDeRisco.txt", "a");

									if (idade > 65 || strcmp(novoPaciente.comorbidades, ""))
									{
										fprintf(grupoDeRisco, "IDADE: %i\n", idade);
										fprintf(grupoDeRisco, "CEP: %s\n\n\n", novoPaciente.endereco.cep);
									}

									fclose(grupoDeRisco);

									break;
								}

							case 0:
								{
									break;
								}

							default:
								{
									printf("\n\n [!] Opção inválida! Pressione ENTER para continuar...");
									getch();
									break;
								}
						}
					}

					while (opcao != 0);
					break;
				}

			case 2:
				{
					char novoLogin[15];
					char novaSenha[15];

					system("cls");
					printf("\n  #-------------------  CADASTRO DE PACIENTES (COVID 19)  -------------------#");
					printf("\n  |                                                                          |");
					printf("\n  |                                                                          |");
					printf("\n  |                           CRIAÇÃO DE USUÁRIO                             |");
					printf("\n  |                                                                          |");
					printf("\n  |                                                                          |");
					printf("\n  |              FAVOR INSERIR OS NOVOS DADOS DE ACESSO:                     |");
					printf("\n  |                                                                          |");
					printf("\n  |              NOVO LOGIN:                                                 |");
					printf("\n  |              NOVA SENHA:                                                 |");
					printf("\n  |                                                                          |");
					printf("\n  |                                                                          |");
					printf("\n  |                                                                          |");
					printf("\n  |                                                                          |");
					printf("\n  |                                                                          |");
					printf("\n  |                                                                          |");
					printf("\n  #--------------------------------------------------------------------------#");

					SetCursorPosition(29, 9);
					scanf("%s", &novoLogin);

					SetCursorPosition(29, 10);

					int p = 0;

					do {
						novaSenha[p] = getch();

						if (novaSenha[p] != '\r' && novaSenha[p] != '\b')
						{
							printf("*");
						}

						if (novaSenha[p] == '\b' && p >= 1)
						{
							p -= 2;
							SetCursorPosition(29 + p, 10);
							printf(" ");
							SetCursorPosition(29 + p, 10);
						}

						p++;

					}

					while (novaSenha[p - 1] != '\r');

					novaSenha[p - 1] = '\0';

					SetCursorPosition(0, 20);

					FILE * users;
					users = fopen("users.txt", "r");
					char usuario[15];
					int salvarUsuario = 1;
					while (fgets(usuario, sizeof(usuario), users) != NULL)
					{
						if (strstr(usuario, novoLogin) != NULL)
						{
							salvarUsuario = 0;
							printf(" [!] Usuário já cadastrado! Pressione ENTER para continuar...");
							getch();
						}
					}

					fclose(users);

					if (salvarUsuario == 1)
					{
						FILE * users;
						users = fopen("users.txt", "a");
						fprintf(users, "%s\n", novoLogin);
						fprintf(users, "%s\n", novaSenha);
						fclose(users);

						printf("  > Usuário criado com sucesso! Pressione ENTER para continuar...");
						getch();
					}

					break;
				}

			case 0:
				{
					break;
				}

			default:
				{
					printf("\n\n [!] Opção inválida! Pressione ENTER para continuar...");
					getch();
					break;
				}
		}
	}

	while (opcao != 0);

	SetConsoleCP(cpin);
	SetConsoleOutputCP(cpout);

	return 0;
}
