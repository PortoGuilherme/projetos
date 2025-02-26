#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <time.h>

void cabecalhoLogin(){
    printf("\033[0;32m");
    printf("========================================================================================================================\n");
    printf("========================================================================================================================\n");
    printf("============================== |                               SEJA BEM-VINDO                 |=========================\n");
    printf("========================================================================================================================\n");
    printf("============================== |                                   LOGIN                      |=========================\n");
    printf("========================================================================================================================\n");
    printf("\033[0;0m");
}

void cabecalho(){
    printf("\033[0;32m");
    printf("========================================================================================================================\n");
    printf("============================== |                           FRESH FRUTIS                       |=========================\n");
    printf("========================================================================================================================\n");
    printf("\033[0;0m");
}

//Funções de cadastros e consultas
//-----------------------------------------------------------------------------------------------

// Função para centralizar texto
void centralizarTexto(const char* texto) {
    int larguraConsole = 80;
    int comprimentoTexto = strlen(texto);
    int espacos = (larguraConsole - comprimentoTexto) / 2;

    for (int i = 0; i < espacos; i++) {
        printf(" ");
    }
    printf("%s\n", texto);
}


// Estrutura para armazenar os dados do usuário
typedef struct {
    int acesso;
    char nome[15];
    char senha[15];
} CadastroUsuario;


// Função para verificar se um usuário já existe no arquivo
int usuarioJaExiste(const char *nome) {
    FILE *arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: arquivo não encontrado!\n");
        return 0;
    }

    CadastroUsuario usuarioExistente;
    while (fscanf(arquivo, "%d %s %s", &usuarioExistente.acesso, usuarioExistente.nome, usuarioExistente.senha) != EOF) {
        if (strcmp(usuarioExistente.nome, nome) == 0) {
            fclose(arquivo);
            return 1; // Usuário já existe
        }
    }

    fclose(arquivo);
    return 0; // Usuário não existe
}

// Função para capturar a senha mascarada com '*'
void capturarSenha(char *senha, int tamanhoMaximo) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch(); // Captura o caractere sem exibir no console

        // Enter finaliza a senha
        if (ch == '\r') { // '\r' representa Enter no Windows
            senha[i] = '\0';
            break;
        }
        // Backspace permite apagar caracteres
        else if (ch == '\b' && i > 0) { // '\b' representa Backspace
            i--;
            printf("\b \b"); // Apaga o último asterisco no console
        }
        // Limita o tamanho da senha
        else if (i < tamanhoMaximo - 1 && ch != '\b') {
            senha[i++] = ch;
            printf("*"); // Exibe '*' no lugar do caractere digitado
        }
    }
}

// Função para cadastrar e salvar os usuários
void cadastrousuario() {
    CadastroUsuario usuario;
    FILE *arquivo;
    char opcao;

    do {
    system("cls");

    cabecalho();


        // Abrir o arquivo para adicionar um novo usuário
        arquivo = fopen("usuarios.txt", "a");
        if (arquivo == NULL) {
            printf("Erro: arquivo não encontrado!\n");
            return;
        }

        // Receber e validar o nível de acesso
        do {
            printf("Digite (0) para Op.caixa ou (1) para Administrador:\n ");
            scanf("%d", &usuario.acesso);
            if (usuario.acesso != 0 && usuario.acesso != 1 && usuario.acesso != 2) {
                printf("Nível de acesso inválido! Digite 0 para Operador de Caixa ou 1 para Administrador.\n");
            }
        } while (usuario.acesso != 0 && usuario.acesso != 1 && usuario.acesso != 2);

        // Receber o nome do usuário com limite de caracteres e verificar duplicidade
        do {
            printf("Digite o nome do usuario (maximo 14 caracteres):\n ");
            scanf("%14s", usuario.nome);

            if (usuarioJaExiste(usuario.nome)) {
                printf("Erro: Usuario '%s' ja existe! Escolha outro nome.\n", usuario.nome);
            }
        } while (usuarioJaExiste(usuario.nome));

        // Receber a senha do usuário
        printf("Digite uma senha (minimo 6 caracteres e maximo 14 caracteres):\n ");
        scanf("%14s", usuario.senha);

        // Gravar os dados no arquivo txt
        fprintf(arquivo, "%d %s %s\n", usuario.acesso, usuario.nome, usuario.senha);
        fclose(arquivo);

        // Pergunta se deseja cadastrar outro usuário
        printf("Cadastrado com sucesso!\n");
        printf("Deseja cadastrar um novo usuario? Sim(s) ou Não(n):\n");
        scanf(" %c", &opcao);

    } while (opcao == 's' || opcao == 'S');

    // Chama a função de menu de usuário ao terminar os cadastros
    menusuario();
}


// Estrutura para armazenar os dados
typedef struct {
    int Cprod;
    char Pnome[30];
    float preco;
    char tipoVenda[10];  // "peso" ou "unidade"
    float quantidade;    // Usar como float para produtos vendidos por peso, pode ser usado como int para unidades
} CadastroProduto;

// Função para cadastrar e salvar
void cadastroproduto(){

    system("cls");

    cabecalho();

    CadastroProduto produto;
    FILE *arquivo;

    // Abrir o arquivo
    arquivo = fopen("estoque.txt", "a");
    if (arquivo == NULL){
        printf("Erro: arquivo não encontrado!\n");
        return;
    }

    // Receber as informações de cadastro
    printf("Codigo:\n ");
    scanf("%d", &produto.Cprod);

    printf("Descricao:\n ");
    getchar(); // Limpa o buffer para evitar problemas na leitura com fgets
    fgets(produto.Pnome, sizeof(produto.Pnome), stdin);
    produto.Pnome[strcspn(produto.Pnome, "\n")] = 0;

    printf("Preco:\n ");
    scanf("%f", &produto.preco);

    // Receber o tipo de venda
    printf("Tipo de venda (peso/unidade):\n ");
    scanf("%s", produto.tipoVenda);

    // Receber a quantidade em estoque de acordo com o tipo de venda
    if (strcmp(produto.tipoVenda, "peso") == 0) {
        printf("Quantidade em kg:\n ");
        scanf("%f", &produto.quantidade);
    } else if (strcmp(produto.tipoVenda, "unidade") == 0) {
        printf("Quantidade em unidades:\n ");
        int unidades;
        scanf("%d", &unidades);
        produto.quantidade = (float)unidades;  // Armazena como float para consistência
    } else {
        printf("Tipo de venda invalido!\n");
        fclose(arquivo);
        return;
    }

    // Gravar os dados no arquivo txt com o separador "-"
    fprintf(arquivo, "%d - %s - %.2f - %s - %.2f\n",
    produto.Cprod, produto.Pnome, produto.preco, produto.tipoVenda, produto.quantidade);
    fclose(arquivo);

    char opcao;
    do {
        printf("Cadastrado com sucesso!\n");
        printf("Deseja cadastrar um novo produto? sim(s) ou nao(n):\n");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            cadastroproduto();
        } else if (opcao == 'n') {
            estoque();
        } else {
            printf("Opção invalida! Tente novamente.\n");
        }
    } while (opcao != 's' && opcao != 'n');
}

// Estrutura para armazenar os dados
typedef struct {
    int Cfornecedor, Telfornecedor;
    char Fnome[30];
    char Femail[30];
} cadastrofornecedor;

// Função para cadastrar e salvar fornecedor
void CadastroFornecedor(){
    system("cls");

    cabecalho();

    cadastrofornecedor cdfornecedor;
    FILE *arquivo;

    // Abrir o arquivo
    arquivo = fopen("fornecedores.txt", "a");
    if (arquivo == NULL){
        printf("Erro: arquivo não encontrado!\n");
        return;
    }

    // Receber as informações de cadastro
    printf("Codigo do fornecedor:\n ");
    scanf("%d", &cdfornecedor.Cfornecedor);

    printf("Nome da empresa:\n ");
    getchar(); // Limpa o buffer para evitar problemas na leitura com fgets
    fgets(cdfornecedor.Fnome, sizeof(cdfornecedor.Fnome), stdin);
    cdfornecedor.Fnome[strcspn(cdfornecedor.Fnome, "\n")] = 0;

    printf("Telefone:\n ");
    scanf("%d", &cdfornecedor.Telfornecedor);

    printf("E-mail:\n ");
    getchar(); // Limpa o buffer antes de usar fgets
    fgets(cdfornecedor.Femail, sizeof(cdfornecedor.Femail), stdin);
    cdfornecedor.Femail[strcspn(cdfornecedor.Femail, "\n")] = 0;

    // Gravar os dados no arquivo txt com o separador "-"
    fprintf(arquivo, "%d - %s - %d - %s\n",
    cdfornecedor.Cfornecedor, cdfornecedor.Fnome, cdfornecedor.Telfornecedor, cdfornecedor.Femail);
    fclose(arquivo);

    char opcao;
    do {
        printf("Cadastrado com sucesso!\n");
        printf("Deseja cadastrar um novo? sim(s) ou nao(n):\n");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            CadastroFornecedor();
        } else if (opcao == 'n') {
            fornecedores();
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 's' && opcao != 'n');
}

//função para ler arquivo do estoque
void consultarestoque(){
    system("cls");

    FILE*arquivo;
    char linha[50];

    //Abrir o arquivo
    arquivo = fopen("estoque.txt","r");
        if(arquivo == NULL){
            printf("Erro: Arquivo Nao encontrado!\n");
            return;
        }
        cabecalho();

        //Exibir dados do arquivo
        while (fgets(linha, sizeof(linha), arquivo) != NULL){
            printf("%s", linha);
        }

        fclose(arquivo);

        //Pressionar Enter para retornar ao menu
        printf("\nAperte Enter para retornar ao menu!");
        getchar();  // Captura o Enter deixado no buffer após o fechamento do arquivo
        getchar();  // Aguarda o usuário pressionar Enter

    estoque();
}

//função para ler aqruivo de forncedores
void consultarfornecedor(){
    system("cls");

    FILE*arquivo;
    char linha[50];

    //Abrir o arquivo
    arquivo = fopen("fornecedores.txt","r");
        if(arquivo == NULL){
            printf("Erro: Arquivo Nao encontrado!\n");
            return;
        }
        cabecalho();

        //Exibir dados do arquivo
        while (fgets(linha, sizeof(linha), arquivo) != NULL){
                printf("%s", linha);
        }

        fclose(arquivo);

        //Pressionar enter para retornar ao menu
        printf("\nAperte Enter para retornar ao menu!");
        getchar();  // Captura o Enter deixado no buffer após o fechamento do arquivo
        getchar();  // Aguarda o usuário pressionar Enter

        fornecedores();
}

//função para ler arquivo do estoqueoperador
void consultarestoqueop(){
    system("cls");

    FILE*arquivo;
    char linha[50];

    //Abrir o arquivo
    arquivo = fopen("estoque.txt","r");
        if(arquivo == NULL){
            printf("Erro: Arquivo Nao encontrado!\n");
            return;
        }
        cabecalho();

        //Exibir dados do arquivo
        while (fgets(linha, sizeof(linha), arquivo) != NULL){
            printf("%s", linha);
        }

        fclose(arquivo);

        //Pressionar Enter para retornar ao menu
        printf("\nAperte Enter para retornar ao menu!");
        getchar();  // Captura o Enter deixado no buffer após o fechamento do arquivo
        getchar();  // Aguarda o usuário pressionar Enter

    telaOperador();
}


//função para ler arquivo de vendas
void consultavendas(){
    system("cls"); //limpa o console antes de trazer o arquivo

    FILE*arquivo;
    char linha[50]; //limita os caracteres da linha a ser mostrada

    //Abrir o arquivo
    arquivo = fopen("valores_venda.txt","r");
        if(arquivo == NULL){
            printf("Erro: Arquivo Nao encontrado!\n");
            return;
        }
        cabecalho(); //titulo do hortifruti

        //Exibir dados do arquivo
        while (fgets(linha, sizeof(linha), arquivo) != NULL){
            printf("%s", linha);
        }

        fclose(arquivo);

        //Pressionar Enter para retornar ao menu
        printf("\nAperte Enter para retornar ao menu!");
        getchar();  // Captura o Enter deixado no buffer após o fechamento do arquivo
        getchar();  // Aguarda o usuário pressionar Enter

    financeiro();
}


//função para ler arquivo de usuarios
void consultarusuario(){
    system("cls");

    FILE*arquivo;
    char linha[50];

    //Abrir o arquivo
    arquivo = fopen("usuarios.txt","r");
        if(arquivo == NULL){
            printf("Erro: Arquivo Nao encontrado!\n");
            return;
        }
        cabecalho();

        //Exibir dados do arquivo
        while (fgets(linha, sizeof(linha), arquivo) != NULL){
            printf("%s", linha);
        }

        fclose(arquivo);

        //Pressionar Enter para retornar ao menu
        printf("\nAperte Enter para retornar ao menu!");
        getchar();  // Captura o Enter deixado no buffer após o fechamento do arquivo
        getchar();  // Aguarda o usuário pressionar Enter

    menusuario();
}


// Função para buscar o produto pelo código
int buscarProduto(int codigo, CadastroProduto *produto) {
    FILE *arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: Arquivo não encontrado!\n");
        return 0;
    }

    while (fscanf(arquivo, "%d - %29s - %f - %9s - %f",
                  &produto->Cprod, produto->Pnome, &produto->preco, produto->tipoVenda, &produto->quantidade) != EOF) {
        if (produto->Cprod == codigo) {
            fclose(arquivo);
            return 1;  // Produto encontrado
        }
    }

    fclose(arquivo);
    return 0;  // Produto não encontrado
}

// Função para atualizar o estoque após uma venda
void atualizarEstoque(CadastroProduto produtoVendido, float quantidadeVendida) {
    FILE *arquivo = fopen("estoque.txt", "r+"); // Abre o arquivo para leitura e escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    CadastroProduto produto;
    long int posicao = 0;
    int produtoEncontrado = 0;

    // Percorre o arquivo para encontrar o produto e atualizar a quantidade
    while (fscanf(arquivo, "%d - %29s - %f - %9s - %f",
                  &produto.Cprod, produto.Pnome, &produto.preco, produto.tipoVenda, &produto.quantidade) != EOF) {
        if (produto.Cprod == produtoVendido.Cprod) {
            produto.quantidade -= quantidadeVendida; // Atualiza a quantidade em estoque
            produtoEncontrado = 1;

            // Volta para a posição do produto no arquivo para sobrescrever
            fseek(arquivo, posicao, SEEK_SET);
            fprintf(arquivo, "%d - %s - %.2f - %s - %.2f\n",
                    produto.Cprod, produto.Pnome, produto.preco, produto.tipoVenda, produto.quantidade);
            fflush(arquivo);  // Força a escrita no arquivo
            break;
        }
        posicao = ftell(arquivo);  // Armazena a posição do arquivo para poder sobrescrever mais tarde
    }

    if (!produtoEncontrado) {
        printf("Produto não encontrado no estoque.\n");
    }

    fclose(arquivo);
}

// Função para atualizar o estoque após uma entrada
void EntradaEstoque(CadastroProduto produtoEntrada, float quantidadeEntrada) {
    FILE *arquivo = fopen("estoque.txt", "r+"); // Abre o arquivo para leitura e escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque!\n");
        return;
    }

    CadastroProduto produto;
    long int posicao = 0;
    int produtoEncontrado = 0;

    // Percorre o arquivo para encontrar o produto e atualizar a quantidade
    while (fscanf(arquivo, "%d - %29s - %f - %9s - %f\n",
                  &produto.Cprod, produto.Pnome, &produto.preco, produto.tipoVenda, &produto.quantidade) != EOF) {
        if (produto.Cprod == produtoEntrada.Cprod) {
            produto.quantidade += quantidadeEntrada; // Atualiza a quantidade em estoque
            produtoEncontrado = 1;

            // Volta para a posição do produto no arquivo para sobrescrever
            fseek(arquivo, posicao, SEEK_SET);
            fprintf(arquivo, "%d - %s - %.2f - %s - %.2f\n",
                    produto.Cprod, produto.Pnome, produto.preco, produto.tipoVenda, produto.quantidade);
            fflush(arquivo);  // Força a escrita no arquivo
            break;
        }
        posicao = ftell(arquivo);  // Armazena a posição do arquivo para poder sobrescrever mais tarde
    }

    if (!produtoEncontrado) {
        printf("Produto não encontrado no estoque.\n");
    }

    fclose(arquivo);
}


// Função para realizar a venda e atualizar
void telaVenda() {
    system("cls");

    int codigo, finalizar = 0;
    char opcao;
    float totalVenda = 0.0;

    printf("\033[0;32m");
    printf("========================================================================================================================\n");
    printf("============================== |                           FRESH FRUTIS                       |=========================\n");
    printf("========================================================================================================================\n");
    printf("============================== |                              VENDA                           |=========================\n");
    printf("========================================================================================================================\n");
    printf("\033[0;0m");

    while (!finalizar) {
        CadastroProduto produto;
        float quantidadeVendida, totalProduto;

        printf("Digite o codigo do produto: ");
        scanf("%d", &codigo);

        if (buscarProduto(codigo, &produto)) {
            printf("%s ", produto.Pnome);
            printf("R$:%.2f ", produto.preco);
            printf("Venda por: %s\n", produto.tipoVenda);

            if (strcmp(produto.tipoVenda, "peso") == 0) {
                printf("Digite o kg: ");
                scanf("%f", &quantidadeVendida);
            } else {
                printf("Digite a quantidade em unidades: ");
                scanf("%f", &quantidadeVendida);
            }

            totalProduto = produto.preco * quantidadeVendida;
            totalVenda += totalProduto;
            printf("Subtotal para %s: R$%.2f\n", produto.Pnome, totalProduto);

            // Atualiza o estoque após a venda
            atualizarEstoque(produto, quantidadeVendida);

            // Pergunta se deseja adicionar mais itens ou finalizar
            printf("Digite (s) para adicionar mais itens (n) para finalizar: ");
            scanf(" %c", &opcao);

            if (opcao == 'n') {
                finalizar = 1;
            }
        } else {
            printf("Produto não encontrado. Tente novamente.\n");
        }
    }

    // Exibir recibo final
    printf("\n======== Recibo ========\n");
    printf("Total da compra: R$%.2f\n", totalVenda);
    printf("========================\n");
    printf("Obrigado pela compra!\n");

    // Obter a data e hora atual
    time_t agora = time(NULL);
    struct tm *tempoLocal = localtime(&agora);

    // Salva a data, hora e valor total da venda em um arquivo
    FILE *valorArquivo = fopen("valores_venda.txt", "a");
    if (valorArquivo != NULL) {
        fprintf(valorArquivo, "Realizada em: %02d/%02d/%04d As %02d:%02d:%02d - Total: R$%.2f\n",
                tempoLocal->tm_mday, tempoLocal->tm_mon + 1, tempoLocal->tm_year + 1900,
                tempoLocal->tm_hour, tempoLocal->tm_min, tempoLocal->tm_sec, totalVenda);
        fclose(valorArquivo);

        // Pressionar Enter para retornar ao menu
        printf("\nAperte Enter para retornar ao menu!");
        getchar();  // Captura o Enter deixado no buffer após o fechamento do arquivo
        getchar();  // Aguarda o usuário pressionar Enter
        telaOperador();
    } else {
        printf("Erro ao salvar o valor da venda!\n");
    }
}

// Função para dar entrada no produto
void EntradaProd() {
    system("cls");

    int codigo, finalizar = 0;
    char opcao;

    printf("\033[0;32m");
    printf("========================================================================================================================\n");
    printf("============================== |                           FRESH FRUTIS                       |=========================\n");
    printf("========================================================================================================================\n");
    printf("\033[0;0m");

    while (!finalizar) {
        CadastroProduto produto;
        float qtdEntrada;

        printf("Digite o codigo do produto: ");
        scanf("%d", &codigo);

        if (buscarProduto(codigo, &produto)) {
            printf("%s - ", produto.Pnome);
            printf("Qtd. Atual: %.2f - ", produto.quantidade);
            printf("Vendido em: %s\n", produto.tipoVenda);

            if (strcmp(produto.tipoVenda, "peso") == 0) {
                printf("Digite o kg de entrada: ");
                scanf("%f", &qtdEntrada);
            } else {
                printf("Digite a quantidade de unidades de entrada: ");
                scanf("%f", &qtdEntrada);
            }


            // Atualiza o estoque após a venda
            EntradaEstoque(produto, qtdEntrada);

            // Pergunta se deseja adicionar mais itens ou finalizar
            printf("Digite (s) para adicionar mais itens (n) para finalizar: ");
            scanf(" %c", &opcao);

            if (opcao == 'n') {
                finalizar = 1;
            }
        } else {
            printf("Produto não encontrado. Tente novamente.\n");
        }
        estoque();
    }

}

//-----------------------------------------------------------------------------------------------

//Função de menus ADM
//-----------------------------------------------------------------------------------------------
// Função para acesso à tela de administrador
void telaAdministrador(){
    system("cls"); //limpa o que ja foi digitado no console

    cabecalho();

    printf("Logado como Administrador\n");

    int valor; //variavel para digitar aopção do menu

    printf ("1 Financeiro\n");
    printf ("2 Estoque\n");
    printf ("3 Forncedores\n");
    printf ("4 Usuario\n");
    printf ("5 sair..\n\n");
    printf("digite uma opcao: ");
    scanf("%d", &valor);


  switch ( valor )
  {
    case 1 :
    financeiro();
    break;

    case 2 :
        estoque();
    break;

    case 3 :
        fornecedores();
    break;

    case 4 :
        menusuario();

    break;

    case 5 :
        main();

    default :
    printf ("Valor invalido!\n");
  }

  getch();
  return 0;

}

//Função para acessar sub menu adm/financeiro
void financeiro(){

    system("cls"); //limpa o que ja foi digitado no console

    cabecalho();

    int valor;

    printf ("1 Consultar Vendas\n");
    printf ("2 voltar\n\n");
    printf("digite uma opcao: ");
    scanf("%d", &valor);

    switch ( valor )
  {
    case 1 :
        consultavendas();
    break;

    case 2 :
        telaAdministrador();
    break;

    default :
    printf ("Valor invalido!\n");
  }

  getch();
  return 0;
}

void estoque(){
 system("cls"); //limpa o que ja foi digitado no console

    cabecalho();

    int valor;

    printf ("1 Consultar\n");
    printf ("2 Cadastrar\n");
    printf ("3 Dar entrada\n");
    printf ("4 voltar\n\n");
    printf("digite uma opcao: ");
    scanf("%d", &valor);

    switch ( valor )
  {
    case 1 :
        consultarestoque();
    break;

    case 2 :
        cadastroproduto();
    break;

    case 3 :
        EntradaProd();
    break;

    case 4 :
        telaAdministrador();
    break;

    default :
    printf ("Valor invalido!\n");
  }

  getch();
  return 0;
}

void fornecedores(){
    system("cls"); //limpa o que ja foi digitado no console

    cabecalho();

    int valor;

    printf ("1 Consultar\n");
    printf ("2 Cadastrar\n");
    printf ("3 voltar\n\n");
    printf("digite uma opcao: ");
    scanf("%d", &valor);

    switch ( valor )
  {
    case 1 :
        consultarfornecedor();
    break;

    case 2 :
        CadastroFornecedor();
    break;

    case 3 :
        telaAdministrador();
    break;

    default :
    printf ("Valor invalido!\n");
  }

  getch();
  return 0;
}

void menusuario(){
     system("cls"); //limpa o que ja foi digitado no console

    cabecalho();

    int valor;

    printf ("1 Consultar\n");
    printf ("2 Cadastrar\n");
    printf ("3 voltar\n\n");
    printf("digite uma opcao: ");
    scanf("%d", &valor);

    switch ( valor )
  {
    case 1 :
        consultarusuario();
    break;

    case 2 :
        cadastrousuario();
    break;

    case 3 :
        telaAdministrador();
    break;

    default :
    printf ("Valor invalido!\n");
  }

  getch();
  return 0;
}
//-----------------------------------------------------------------------------------------------

// Função para acesso à tela de operador
void telaOperador(){
    system("cls"); //limpa o que ja foi digitado no console

    cabecalho();

    printf("Logado como Operador de Caixa!\n");

    int valor;

    printf ("1 Venda\n");
    printf ("2 Estoque\n");
    printf ("3 Fechar caixa\n");
    printf("digite uma opcao: ");
    scanf("%d", &valor);


  switch ( valor )
  {
    case 1 :
        telaVenda();
    break;

    case 2 :
        consultarestoqueop();
    break;

    case 3 :
        main();
    break;

    default :
    printf ("Valor invalido!\n");
  }

  getch();
  return 0;

}

//Função para acessar menu de estoquista

void telaEstoque(){
   system("cls"); //limpa o que ja foi digitado no console

    cabecalho();

    printf("Logado como Estoquista!\n");

    int valor;

    printf ("1 Consultar\n");
    printf ("2 Cadastrar\n");
    printf ("3 Dar entrada\n");
    printf ("4 Logoff\n");
    printf("digite uma opcao: ");
    scanf("%d", &valor);

    switch ( valor )
  {
    case 1 :
        TEconsultarestoque();
    break;

    case 2 :
        TEcadastroproduto();
    break;

    case 3 :
        TEEntradaProd();
    break;

    case 4 :
        main();
    break;

    default :
    printf ("Valor invalido!\n");
  }

  getch();
  return 0;
}

//função para ler arquivo do estoque
void TEconsultarestoque(){
    system("cls");

    FILE*arquivo;
    char linha[50];

    //Abrir o arquivo
    arquivo = fopen("estoque.txt","r");
        if(arquivo == NULL){
            printf("Erro: Arquivo Nao encontrado!\n");
            return;
        }
        cabecalho();

        //Exibir dados do arquivo
        while (fgets(linha, sizeof(linha), arquivo) != NULL){
            printf("%s", linha);
        }

        fclose(arquivo);

        //Pressionar Enter para retornar ao menu
        printf("\nAperte Enter para retornar ao menu!");
        getchar();  // Captura o Enter deixado no buffer após o fechamento do arquivo
        getchar();  // Aguarda o usuário pressionar Enter

    telaEstoque();
}

// Função para dar entrada no produto
void TEEntradaProd() {
    system("cls");

    int codigo, finalizar = 0;
    char opcao;

    printf("\033[0;32m");
    printf("========================================================================================================================\n");
    printf("============================== |                           FRESH FRUTIS                       |=========================\n");
    printf("========================================================================================================================\n");
    printf("\033[0;0m");

    while (!finalizar) {
        CadastroProduto produto;
        float qtdEntrada;

        printf("Digite o codigo do produto: ");
        scanf("%d", &codigo);

        if (buscarProduto(codigo, &produto)) {
            printf("%s - ", produto.Pnome);
            printf("Qtd. Atual: %.2f - ", produto.quantidade);
            printf("Vendido em: %s\n", produto.tipoVenda);

            if (strcmp(produto.tipoVenda, "peso") == 0) {
                printf("Digite o kg de entrada: ");
                scanf("%f", &qtdEntrada);
            } else {
                printf("Digite a quantidade de unidades de entrada: ");
                scanf("%f", &qtdEntrada);
            }


            // Atualiza o estoque após a venda
            EntradaEstoque(produto, qtdEntrada);

            // Pergunta se deseja adicionar mais itens ou finalizar
            printf("Digite (s) para adicionar mais itens (n) para finalizar: ");
            scanf(" %c", &opcao);

            if (opcao == 'n') {
                finalizar = 1;
            }
        } else {
            printf("Produto não encontrado. Tente novamente.\n");
        }
        telaEstoque();
    }

}

// Função para cadastrar e salvar
void TEcadastroproduto(){

    system("cls");

    cabecalho();

    CadastroProduto produto;
    FILE *arquivo;

    // Abrir o arquivo
    arquivo = fopen("estoque.txt", "a");
    if (arquivo == NULL){
        printf("Erro: arquivo não encontrado!\n");
        return;
    }

    // Receber as informações de cadastro
    printf("Codigo:\n ");
    scanf("%d", &produto.Cprod);

    printf("Descricao:\n ");
    getchar(); // Limpa o buffer para evitar problemas na leitura com fgets
    fgets(produto.Pnome, sizeof(produto.Pnome), stdin);
    produto.Pnome[strcspn(produto.Pnome, "\n")] = 0;

    printf("Preco:\n ");
    scanf("%f", &produto.preco);

    // Receber o tipo de venda
    printf("Tipo de venda (peso/unidade):\n ");
    scanf("%s", produto.tipoVenda);

    // Receber a quantidade em estoque de acordo com o tipo de venda
    if (strcmp(produto.tipoVenda, "peso") == 0) {
        printf("Quantidade em kg:\n ");
        scanf("%f", &produto.quantidade);
    } else if (strcmp(produto.tipoVenda, "unidade") == 0) {
        printf("Quantidade em unidades:\n ");
        int unidades;
        scanf("%d", &unidades);
        produto.quantidade = (float)unidades;  // Armazena como float para consistência
    } else {
        printf("Tipo de venda invalido!\n");
        fclose(arquivo);
        return;
    }

    // Gravar os dados no arquivo txt com o separador "-"
    fprintf(arquivo, "%d - %s - %.2f - %s - %.2f\n",
    produto.Cprod, produto.Pnome, produto.preco, produto.tipoVenda, produto.quantidade);
    fclose(arquivo);

    char opcao;
    do {
        printf("Cadastrado com sucesso!\n");
        printf("Deseja cadastrar um novo produto? sim(s) ou nao(n):\n");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            TEcadastroproduto();
        } else if (opcao == 'n') {
            telaEstoque();
        } else {
            printf("Opção invalida! Tente novamente.\n");
        }
    } while (opcao != 's' && opcao != 'n');
}
//-----------------------------------------------------------------------------------------------

//Função de login

int login(CadastroUsuario *usuarioLogado) {
    FILE *arquivo;
    CadastroUsuario usuario;
    char nomeDigitado[15];
    char senhaDigitada[15];

    printf("Digite seu nome de usuario:\n");
    scanf("%14s", nomeDigitado);

    printf("Digite sua senha:\n");
    capturarSenha(senhaDigitada, sizeof(senhaDigitada));
    printf("\n"); // Move para a próxima linha após a senha

    // Abrir o arquivo para leitura e buscar o usuário
    arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: arquivo não encontrado!\n");
        return 0;
    }

    // Percorrer o arquivo para validar o usuário e senha
    while (fscanf(arquivo, "%d %s %s", &usuario.acesso, usuario.nome, usuario.senha) != EOF) {
        if (strcmp(usuario.nome, nomeDigitado) == 0 && strcmp(usuario.senha, senhaDigitada) == 0) {
            fclose(arquivo);
            *usuarioLogado = usuario; // Salva as informações do usuário logado
            return 1; // Login bem-sucedido
        }
    }

    fclose(arquivo);
    printf("Usuário ou senha incorretos.\n");
    return 0; // Login falhou
}
//-----------------------------------------------------------------------------------------------

int main() {

    system("cls"); //limpa o que ja foi digitado no console

    cabecalhoLogin();

    CadastroUsuario usuarioLogado;

    // Tenta logar até que o login seja bem-sucedido
    while (!login(&usuarioLogado));

    // Direciona para a tela correta com base no nível de acesso
    if (usuarioLogado.acesso == 0) {
        telaAdministrador();
    } else if (usuarioLogado.acesso == 1) {
        telaOperador();
    // Chama a função de venda, passando o nome do usuário
        telaVenda(usuarioLogado.nome);
    } else if (usuarioLogado.acesso == 2) {
        telaEstoque();
    // Chama a função de venda, passando o nome do usuário
        telaVenda(usuarioLogado.nome);
    }else {
        printf("Nível de acesso inválido.\n");
    }

    return 0;
}

