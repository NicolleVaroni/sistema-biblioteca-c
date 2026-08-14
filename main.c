#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Adicionei esta linha para a função exit()

// =======================================================
// VARIÁVEIS GLOBAIS
// =======================================================
struct livros {
    int id;
    char titulo[100];
    char autor[100];
    int ano_lancamento;
    char categoria[25];
    int formato_fisico;
    int formato_digital;
    int formato_audiobook;
    int estoque_fisico;
};

struct livros biblioteca[100];
int totalLivros = 0;

// =======================================================
// PROTÓTIPOS
// =======================================================
void carregarArquivo();
void salvarArquivo();

void validacaoBibliotecario();
void opcoesBibliotecario();
void opcoesUsuario();

void adicionarLivro();
void listarLivros();
void procurarPorTitulo();
void procurarPorAutor();
void excluirLivro();
void editarLivro();
void buscarPorFormato();
void limparBuffer();

// =======================================================
// MAIN
// =======================================================
int main(){
    carregarArquivo(); // <-- CARREGAR ARQUIVO AO INICIAR

    int opcaoUsuario;

    printf("---------------------------------------------\n");
    printf("|               BIBLIOTECA                 |\n");
    printf("---------------------------------------------\n");
    printf("| Escolha o tipo de usuário                |\n");
    printf("| Bibliotecário (1)                        |\n");
    printf("| Aluno         (2)                        |\n");
    printf("---------------------------------------------\n");
    printf("Opção: ");
    scanf("%d", &opcaoUsuario);
    limparBuffer(); // <-- LIMPAR BUFFER

    if (opcaoUsuario == 1){
        validacaoBibliotecario();
        opcoesBibliotecario();
    } 
    else if(opcaoUsuario == 2){
        opcoesUsuario();
    } 
    else{
        printf("Opção inválida!\n");
    }

    return 0;
}

// =======================================================
// ARQUIVOS: CARREGAR ARQUIVO AO INICIAR
// =======================================================
void carregarArquivo() {
    FILE *file = fopen("livros.txt", "r");
    if (!file) {
        return; // ainda não existe arquivo
    }

    while (!feof(file)) {
        struct livros L;
        if (fscanf(file, "%d;%99[^;];%99[^;];%d;%24[^;];%d;%d;%d;%d\n", // considerando o tamanho máximo de cada campo
                   &L.id, L.titulo, L.autor, &L.ano_lancamento,
                   L.categoria, &L.formato_fisico, &L.formato_digital,
                   &L.formato_audiobook, &L.estoque_fisico) == 9) 
        {
            biblioteca[totalLivros++] = L;
        }
    }

    fclose(file);
}

// =======================================================
// ARQUIVOS: SALVAR APÓS QUALQUER ALTERAÇÃO
// =======================================================
void salvarArquivo() {
    FILE *file = fopen("livros.txt", "w");
    int i;
    for (i = 0; i < totalLivros; i++) {
        fprintf(file, "%d;%s;%s;%d;%s;%d;%d;%d;%d\n",
                biblioteca[i].id, biblioteca[i].titulo, 
                biblioteca[i].autor, biblioteca[i].ano_lancamento,
                biblioteca[i].categoria, biblioteca[i].formato_fisico,
                biblioteca[i].formato_digital, biblioteca[i].formato_audiobook,
                biblioteca[i].estoque_fisico);
    }

    fclose(file);
}

// =======================================================
// VALIDAÇÃO DO BIBLIOTECÁRIO
// =======================================================
void validacaoBibliotecario(){
  int senha = 12345; //senha do bibliotecário
  int senha_digitada;

  printf("Digite a senha: ");
  scanf("%d", &senha_digitada);
  limparBuffer(); // <-- LIMPAR BUFFER

  if (senha_digitada == senha){
    printf("\nAcesso concedido! Bem-vindo(a)!\n\n");
  }
  else{
    printf("\nAcesso negado!\n");
    exit(0);
  }
}

// =======================================================
// MENU DO BIBLIOTECÁRIO
// =======================================================
void opcoesBibliotecario(){
    int opcao;

    while (1) {
        printf("---------------------------------------------\n");
        printf("| Escolha uma opção:                        |\n");
        printf("| Verificar livros         (1)              |\n");
        printf("| Adicionar livros         (2)              |\n");
        printf("| Procurar por título      (3)              |\n");
        printf("| Procurar por autor       (4)              |\n");
        printf("| Buscar por formato       (5)              |\n"); 
        printf("| Editar livro             (6)              |\n"); // <-- OPÇÃO EDITAR ADICIONADA
        printf("| Excluir livro            (7)              |\n"); // <-- EXCLUIR AGORA É 7
        printf("| Sair                     (0)              |\n");
        printf("---------------------------------------------\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limparBuffer(); // <-- LIMPAR BUFFER

        switch(opcao){
            case 1: listarLivros(); break;
            case 2: adicionarLivro(); break;
            case 3: procurarPorTitulo(); break;
            case 4: procurarPorAutor(); break;
            case 5: buscarPorFormato(); break; 
            case 6: editarLivro(); break;        // <-- NOVA CHAMADA
            case 7: excluirLivro(); break;       // <-- EXCLUIR AGORA É 7
            case 0: salvarArquivo(); return;
            default: printf("Opção inválida!\n");
        }
    }
}
// =======================================================
// MENU DO USUÁRIO
// =======================================================
void opcoesUsuario(){
    int opcao;

    while (1) {
        printf("\n---------------------------------------------\n");
        printf("|             SEJA BEM VINDO(A)             |\n");
        printf("---------------------------------------------\n");
        printf("| Verificar livros         (1)              |\n");
        printf("| Procurar por título      (2)              |\n");
        printf("| Procurar por autor       (3)              |\n");
        printf("| Buscar por formato       (4)              |\n");
        printf("| Sair                     (0)              |\n");
        printf("---------------------------------------------\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limparBuffer(); // <-- LIMPAR BUFFER

        switch(opcao){
            case 1: listarLivros(); break;
            case 2: procurarPorTitulo(); break;
            case 3: procurarPorAutor(); break;
            case 4: buscarPorFormato(); break;
            case 0: return;
            default: printf("Opção inválida!\n");
        }
    }
}

// =======================================================
// ADICIONAR LIVRO
// =======================================================
void adicionarLivro(){
    struct livros L;

    L.id = totalLivros + 1;

    printf("Título: ");
    scanf(" %[^\n]", L.titulo);

    printf("Autor: ");
    scanf(" %[^\n]", L.autor);

    printf("Ano de lançamento: ");
    scanf("%d", &L.ano_lancamento);
    limparBuffer(); // <-- LIMPAR BUFFER

    printf("Categoria: ");
    scanf(" %[^\n]", L.categoria);

    printf("Formato físico? (1=Sim, 0=Não): ");
    scanf("%d", &L.formato_fisico);
    limparBuffer(); // <-- LIMPAR BUFFER

    printf("Formato digital? (1=Sim, 0=Não): ");
    scanf("%d", &L.formato_digital);
    limparBuffer(); // <-- LIMPAR BUFFER

    printf("Audiobook? (1=Sim, 0=Não): ");
    scanf("%d", &L.formato_audiobook);
    limparBuffer(); // <-- LIMPAR BUFFER

    printf("Estoque físico: ");
    scanf("%d", &L.estoque_fisico);
    limparBuffer(); // <-- LIMPAR BUFFER

    biblioteca[totalLivros++] = L;
    salvarArquivo();

    printf("\nLivro adicionado com sucesso!\n\n");
}

// =======================================================
// LISTAR LIVROS
// =======================================================
void listarLivros(){
    int i;
    if (totalLivros == 0){
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    for (i = 0; i < totalLivros; i++){
        printf("\nID: %d\nTítulo: %s\nAutor: %s\nAno: %d\nCategoria: %s\nFísico: %d\nDigital: %d\nAudiobook: %d\nEstoque: %d\n",
               biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autor,
               biblioteca[i].ano_lancamento, biblioteca[i].categoria,
               biblioteca[i].formato_fisico, biblioteca[i].formato_digital,
               biblioteca[i].formato_audiobook, biblioteca[i].estoque_fisico);
    }
}

// =======================================================
// PROCURAR POR TÍTULO
// =======================================================
void procurarPorTitulo(){
    int i;
    char busca[100];
    int encontrado = 0;

    printf("Digite o título: ");
    scanf(" %[^\n]", busca);

    for (i = 0; i < totalLivros; i++){
        if (strcasecmp(biblioteca[i].titulo, busca) == 0){
            printf("\nLivro encontrado!\nID: %d\nTítulo: %s\nAutor: %s\nAno: %d\nCategoria: %s\nFísico: %d\nDigital: %d\nAudiobook: %d\nEstoque: %d\n\n",
            biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autor,
            biblioteca[i].ano_lancamento, biblioteca[i].categoria,
            biblioteca[i].formato_fisico, biblioteca[i].formato_digital,
            biblioteca[i].formato_audiobook, biblioteca[i].estoque_fisico);
            encontrado = 1;
        }
    }

    if (!encontrado){
        printf("Nenhum livro com esse título.\n");
    }
}

// =======================================================
// PROCURAR POR AUTOR
// =======================================================
void procurarPorAutor(){
    int i;
    char busca[100];
    int encontrado = 0;

    printf("Digite o autor: ");
    scanf(" %[^\n]", busca);

    for (i = 0; i < totalLivros; i++){
        if (strcasecmp(biblioteca[i].autor, busca) == 0){
            printf("\nLivro encontrado!\nID: %d\nTítulo: %s\nAutor: %s\nAno: %d\nCategoria: %s\nFísico: %d\nDigital: %d\nAudiobook: %d\nEstoque: %d\n\n",
                biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autor,
                biblioteca[i].ano_lancamento, biblioteca[i].categoria,
                biblioteca[i].formato_fisico, biblioteca[i].formato_digital,
                biblioteca[i].formato_audiobook, biblioteca[i].estoque_fisico);
                encontrado = 1;
        }
    }

    if (!encontrado){
        printf("Nenhum livro encontrado desse autor.\n");
    }
}

// =======================================================
// BUSCAR POR FORMATO
// =======================================================
void buscarPorFormato() {
    int i;
    int formato;
    int encontrado = 0;

    printf("\n---------------------------------------------\n");
    printf("|           BUSCAR POR FORMATO              |\n");
    printf("---------------------------------------------\n");
    printf("| Formato Físico       (1)                  |\n");
    printf("| Formato Digital      (2)                  |\n");
    printf("| Formato Audiobook    (3)                  |\n");
    printf("| Todos os formatos    (4)                  |\n");
    printf("---------------------------------------------\n");
    printf("Escolha o formato: ");
    scanf("%d", &formato);
    limparBuffer(); // <-- LIMPAR BUFFER

    printf("\nLivros encontrados:\n");
    printf("===================\n");

    for (i = 0; i < totalLivros; i++) {
        int mostrar = 0;

        switch(formato) {
            case 1: // Físico
                if (biblioteca[i].formato_fisico == 1) {
                    mostrar = 1;
                }
                break;
            case 2: // Digital
                if (biblioteca[i].formato_digital == 1) {
                    mostrar = 1;
                }
                break;
            case 3: // Audiobook
                if (biblioteca[i].formato_audiobook == 1) {
                    mostrar = 1;
                }
                break;
            case 4: // Todos os formatos
                if (biblioteca[i].formato_fisico == 1 || 
                    biblioteca[i].formato_digital == 1 || 
                    biblioteca[i].formato_audiobook == 1) {
                    mostrar = 1;
                }
                break;
            default:
                printf("Opção de formato inválida!\n");
                return;
        }

        if (mostrar) {
            printf("\nID: %d\n", biblioteca[i].id);
            printf("Título: %s\n", biblioteca[i].titulo);
            printf("Autor: %s\n", biblioteca[i].autor);
            printf("Ano: %d\n", biblioteca[i].ano_lancamento);
            printf("Categoria: %s\n", biblioteca[i].categoria);
            printf("Formatos disponíveis:\n");
            if (biblioteca[i].formato_fisico == 1) 
                printf("  - Físico (Estoque: %d)\n", biblioteca[i].estoque_fisico);
            if (biblioteca[i].formato_digital == 1) 
                printf("  - Digital\n");
            if (biblioteca[i].formato_audiobook == 1) 
                printf("  - Audiobook\n");
            printf("----------------------------------------\n");
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum livro encontrado com o formato selecionado.\n");
    }
}

// =======================================================
// EDITAR LIVRO 
// =======================================================
void editarLivro(){
    int i;
    if (totalLivros == 0) {
        printf("\nNão há livros cadastrados.\n");
        return;
    }

    int id;
    printf("\nDigite o ID do livro que deseja editar: ");
    scanf("%d", &id);
    limparBuffer();

    int encontrado = -1;

    // Buscar livro pelo ID
    for (i = 0; i < totalLivros; i++) {
        if (biblioteca[i].id == id) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nLivro não encontrado!\n");
        return;
    }

    // Exibir livro atual
    printf("\nLivro encontrado:\n");
    printf("ID: %d\n", biblioteca[encontrado].id);
    printf("Título: %s\n", biblioteca[encontrado].titulo);
    printf("Autor: %s\n", biblioteca[encontrado].autor);
    printf("Ano: %d\n", biblioteca[encontrado].ano_lancamento);
    printf("Categoria: %s\n", biblioteca[encontrado].categoria);
    printf("Formato Físico: %s\n", biblioteca[encontrado].formato_fisico ? "Sim" : "Não");
    printf("Formato Digital: %s\n", biblioteca[encontrado].formato_digital ? "Sim" : "Não");
    printf("Formato Audiobook: %s\n", biblioteca[encontrado].formato_audiobook ? "Sim" : "Não");
    printf("Estoque Físico: %d\n", biblioteca[encontrado].estoque_fisico);

    printf("\nDigite os novos dados (digite 'manter' para preservar o valor atual):\n");

    char entrada[100];

    // Editar título
    printf("Novo título [%s]: ", biblioteca[encontrado].titulo);
    scanf(" %[^\n]", entrada);
    if (strcasecmp(entrada, "manter") != 0) {
        strcpy(biblioteca[encontrado].titulo, entrada);
    }

    // Editar autor
    printf("Novo autor [%s]: ", biblioteca[encontrado].autor);
    scanf(" %[^\n]", entrada);
    if (strcasecmp(entrada, "manter") != 0) {
        strcpy(biblioteca[encontrado].autor, entrada);
    }

    // Editar ano
    printf("Novo ano de lançamento [%d]: ", biblioteca[encontrado].ano_lancamento);
    scanf(" %[^\n]", entrada);
    if (strcasecmp(entrada, "manter") != 0) {
        int novoAno = atoi(entrada);
        if (novoAno > 0) {
            biblioteca[encontrado].ano_lancamento = novoAno;
        } else {
            printf("Ano inválido! Mantendo ano atual.\n");
        }
    }

    // Editar categoria
    printf("Nova categoria [%s]: ", biblioteca[encontrado].categoria);
    scanf(" %[^\n]", entrada);
    if (strcasecmp(entrada, "manter") != 0) {
        strcpy(biblioteca[encontrado].categoria, entrada);
    }

    // Editar formato físico
    printf("Formato físico? (1=Sim, 0=Não) [%d]: ", biblioteca[encontrado].formato_fisico);
    scanf(" %[^\n]", entrada);
    if (strcasecmp(entrada, "manter") != 0) {
        if (strcmp(entrada, "1") == 0 || strcasecmp(entrada, "sim") == 0) {
            biblioteca[encontrado].formato_fisico = 1;
        } else if (strcmp(entrada, "0") == 0 || strcasecmp(entrada, "não") == 0 || strcasecmp(entrada, "nao") == 0) {
            biblioteca[encontrado].formato_fisico = 0;
        } else {
            printf("Valor inválido! Use 1/Sim ou 0/Não. Mantendo valor atual.\n");
        }
    }

    // Editar formato digital
    printf("Formato digital? (1=Sim, 0=Não) [%d]: ", biblioteca[encontrado].formato_digital);
    scanf(" %[^\n]", entrada);
    if (strcasecmp(entrada, "manter") != 0) {
        if (strcmp(entrada, "1") == 0 || strcasecmp(entrada, "sim") == 0) {
            biblioteca[encontrado].formato_digital = 1;
        } else if (strcmp(entrada, "0") == 0 || strcasecmp(entrada, "não") == 0 || strcasecmp(entrada, "nao") == 0) {
            biblioteca[encontrado].formato_digital = 0;
        } else {
            printf("Valor inválido! Use 1/Sim ou 0/Não. Mantendo valor atual.\n");
        }
    }

    // Editar formato audiobook
    printf("Formato audiobook? (1=Sim, 0=Não) [%d]: ", biblioteca[encontrado].formato_audiobook);
    scanf(" %[^\n]", entrada);
    if (strcasecmp(entrada, "manter") != 0) {
        if (strcmp(entrada, "1") == 0 || strcasecmp(entrada, "sim") == 0) {
            biblioteca[encontrado].formato_audiobook = 1;
        } else if (strcmp(entrada, "0") == 0 || strcasecmp(entrada, "não") == 0 || strcasecmp(entrada, "nao") == 0) {
            biblioteca[encontrado].formato_audiobook = 0;
        } else {
            printf("Valor inválido! Use 1/Sim ou 0/Não. Mantendo valor atual.\n");
        }
    }

    // Editar estoque físico
    printf("Novo estoque físico [%d]: ", biblioteca[encontrado].estoque_fisico);
    scanf(" %[^\n]", entrada);
    if (strcasecmp(entrada, "manter") != 0) {
        int novoEstoque = atoi(entrada);
        if (novoEstoque >= 0) {
            biblioteca[encontrado].estoque_fisico = novoEstoque;
        } else {
            printf("Estoque inválido! Deve ser maior ou igual a zero. Mantendo valor atual.\n");
        }
    }

    salvarArquivo();
    printf("\nLivro editado com sucesso!\n");
}

// =======================================================
// EXCLUIR LIVRO PELO ID
// =======================================================
void excluirLivro() {
    int i;
    if (totalLivros == 0) {
        printf("\nNão há livros cadastrados.\n");
        return;
    }

    int id;
    printf("\nDigite o ID do livro que deseja excluir: ");
    scanf("%d", &id);
    limparBuffer(); // <-- LIMPAR BUFFER

    int encontrado = -1;

    // Buscar livro pelo ID
    for (i = 0; i < totalLivros; i++) {
        if (biblioteca[i].id == id) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nLivro não encontrado!\n");
        return;
    }

    // Desloca tudo uma posição para trás
    for (i = encontrado; i < totalLivros - 1; i++) {
        biblioteca[i] = biblioteca[i + 1];
        biblioteca[i].id = i + 1; // reatribuir IDs sequenciais
    }

    totalLivros--;
    salvarArquivo();

    printf("\nLivro removido com sucesso!\n");
}

// =======================================================
// LIMPAR BUFFER
// =======================================================
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
