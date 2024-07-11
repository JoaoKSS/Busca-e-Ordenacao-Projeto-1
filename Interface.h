#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
using namespace std;

class Interface{

public:

  void apresentarContinuar(){
    cout << "\n\nPressione Enter para continuar...\n\n";
    cin.get();     //pressione Enter
    cin.ignore();  //pressione Enter
  }

  void apresentarOpcaoInvalida(){
    cout << "\n\t\tOpção inválida. Tente novamente!\n";
    apresentarContinuar();
  }

  void apresentarMenu(){
    system("cls || clear");
    cout << "------------ MENU PRINCIPAL ------------\n\n";
    cout << "Selecione a operação desejada:\n\n\t( 0 ) Encerrar Sessão\n\t( 1 ) Cinema\n\t( 2 ) Filme\n\n----------------------------------------\n\nEntrada: ";
  }

  void apresentarFimExecucao(){
    system("cls || clear");
    cout << "\n\t\tSessão Encerrada!\t\t\n\n";
  }

  void apresentarMenuFilmes(){
    system("cls || clear");
    cout << "------------ Menu de Filmes ------------\n\n";
    cout << "Selecione a operação desejada:\n\n\t( 0 ) Voltar ao Menu Principal\n\n\t( 1 ) Filtrar por Título Principal\n\t( 2 ) Filtrar por Tipo\n\t( 3 ) Filtrar por Gênero\n\t( 4 ) Filtrar por Duração\n\t( 5 ) Filtrar por Ano\n\nOperações adicionais:\n\n\t( 6 ) Mostrar Filmes Encontrados\n\t( 7 ) Limpar Filtros\n\n----------------------------------------\n\nEntrada: ";
  }

  void apresentarOpcoesAno(){
    system("cls || clear");
    cout << "---------- Filtragem por Ano -----------\n\n";
    cout << "Selecione a operação desejada:\n\n\t( 0 ) Voltar ao Menu de Filmes\n\n\t( 1 ) Filtrar por Ano Específico\n\t( 2 ) Filtrar por Intervalo de Anos\n\n----------------------------------------\n\nEntrada: ";
  }

  void apresentarMenuAnoEspecifico(int &anoInf){
    system("cls || clear");
    cout << "---------- Filtragem por Ano -----------\n\n";
    cout << "\nDigite o ano desejado: ";
    cin >> anoInf;
    system("cls || clear");
    cout << "------------ Filmes de " << anoInf << " ------------\n\n";
  }

  void apresentarMenuIntervaloAnos(int &anoInf, int &anoSup){
    system("cls || clear");
    cout << "---------- Filtragem por Ano -----------\n\n";
    cout << "\nDigite o ano inicial: \t";
    cin >> anoInf;
    cout << "\nDigite o ano final: \t";
    cin >> anoSup;
    system("cls || clear");
    cout << "-------- Filmes de " << anoInf << " a " << anoSup << " ---------\n\n";
  }

  void apresentarMenuTipo(string &tipo){
    system("cls || clear");
    cout << "--------- Filtragem por Tipo -----------\n\n";
    cout << "\nDigite o tipo de filme desejado: ";
    cin >> tipo;
    system("cls || clear");
    cout << "--------- Filmes do tipo " << tipo << " ---------\n\n";
  }

  void apresentarOpcoesGenero(){
    system("cls || clear");
    cout << "-------- Filtragem por Genero ----------\n\n";
    cout << "Selecione o gênero desejado:\n\n( 0 ) Voltar ao Menu de Filmes\n\n( 1 ) Drama\t\t(  9 ) Biography\t( 17 ) Horror\n( 2 ) Action\t( 10 ) Documentary\t( 18 ) Talk-Show\n( 3 ) Short\t\t( 11 ) Adventure\t( 19 ) Mystery\n( 4 ) Animation\t( 12 ) Musical\t\t( 20 ) Sci-Fi\n( 5 ) Music\t\t( 13 ) Crime\t\t( 21 ) Reality-TV\n( 6 ) History\t( 14 ) Fantasy\t\t( 22 ) News\n( 7 ) Sport\t\t( 15 ) Romance\t\t( 23 ) Family\n( 8 ) Comedy\t( 16 ) Thriller\t\t( 24 ) Outro: digitar gênero\n\n----------------------------------------\n\nEntrada: ";
  }

  void definirGenero(int &resp, string &genero){

  switch (resp){
  case 1:
    genero = "Drama";
    break;
  case 2:
    genero = "Action";
    break;
  case 3:
    genero = "Short";
    break;
  case 4:
    genero = "Animation";
    break;
  case 5:
    genero = "Music";
    break;
  case 6:
    genero = "History";
    break;
  case 7:
    genero = "Sport";
    break;
  case 8:
    genero = "Comedy";
    break;
  case 9:
    genero = "Biography";
    break;
  case 10:
    genero = "Documentary";
    break;
  case 11:
    genero = "Adventure";
    break;
  case 12:
    genero = "Musical";
    break;
  case 13:
    genero = "Crime";
    break;
  case 14:
    genero = "Fantasy";
    break;
  case 15:
    genero = "Romance";
    break;
  case 16:
    genero = "Thriller";
    break;
  case 17:
    genero = "Horror";
    break;
  case 18:
    genero = "Talk-Show";
    break;
  case 19:
    genero = "Mystery";
    break;
  case 20:
    genero = "Sci-Fi";
    break;
  case 21:
    genero = "Reality-TV";
    break;
  case 22:
    genero = "News";
    break;
  case 23:
    genero = "Family";
    break;
  case 24:
    return;
  default:
    resp = 0;
    return;  
  }
    if(resp != 0){
      system("cls || clear");
      cout << "--------- Filmes do gênero " << genero << " ---------\n\n";
    }
  }

  void apresentarMenuGenero(string &genero){
    system("cls || clear");
    cout << "--------- Filtragem por Gênero -----------\n\n";
    cout << "OBS.: inicial do gênero maiúscula!" << endl << endl;
    cout << "\nDigite o gênero de filme desejado: ";
    cin >> genero;
    system("cls || clear");
    cout << "--------- Filmes do gênero " << genero << " ---------\n\n";
  }

  void apresentarMenuTitulo(string &titulo){
    system("cls || clear");
    cout << "--------- Filtragem por Título -----------\n\n";
    cout << "OBS.: pode-se pesquisar por apenas um termo!" << endl << endl;
    cout << "\nDigite o título do filme desejado: ";
    cin >> titulo;
    system("cls || clear");
    cout << "--------- Filmes do título \"" << titulo << "\" ---------\n\n";
  }

  void apresentarOpcoesDuracao(){
    system("cls || clear");
    cout << "-------- Filtragem por Duração ---------\n\n";
    cout << "Selecione a operação desejada:\n\n\t( 0 ) Voltar ao Menu de Filmes\n\n\t( 1 ) Filtrar por Duração Específica\n\t( 2 ) Filtrar por Intervalo de Duração\n\n----------------------------------------\n\nEntrada: ";
  }

  void apresentarMenuDuracaoEspecifica(int &limInf){
    system("cls || clear");
    cout << "-------- Filtragem por Duração ---------\n\n";
    cout << "OBS.: duração em minutos!" << endl << endl;
    cout << "Digite a duração desejada: ";
    cin >> limInf;
    system("cls || clear");
    cout << "---------- Filmes de " << limInf << " min -----------\n\n";
  }

  void apresentarMenuIntervaloDuracao(int &limInf, int &limSup){
    system("cls || clear");
    cout << "-------- Filtragem por Duração ---------\n\n";
    cout << "OBS.: duração em minutos!" << endl << endl;
    cout << "Digite a duração inicial: \t";
    cin >> limInf;
    cout << "\nDigite a duração final: \t";
    cin >> limSup;
    system("cls || clear");
    cout << "------ Filmes de " << limInf << " a " << limSup << " min --------\n\n";
  }

/////////////// Interface de Cinemas abaixo:

  void apresentarMenuCinemas(){
    system("cls || clear");
    cout << "----------- Menu de Cinemas ------------\n\n";
    cout << "Selecione a operação desejada:\n\n\t( 0 ) Voltar ao Menu Principal\n\n\t( 1 ) Filtrar Cinema por Nome do Cinema\n\t( 2 ) Filtrar Cinema por Tipo de Filmes\n\t( 3 ) Filtrar Cinema por Gênero de Filmes\n\t( 4 ) Filtrar Cinema por Duração de Filmes\n\t( 5 ) Filtrar Cinema por Ano de Filmes\n\t( 6 ) Filtrar Cinema por Localização\n\t( 7 ) Filtrar Cinema por Preço de Ingressos\n\nOperações adicionais:\n\n\t( 8 ) Mostrar Cinemas Encontrados\n\t( 9 ) Limpar Filtros\n\n----------------------------------------\n\nEntrada: ";
  }

  void apresentarMenuNome(string &nomeCinema){
    system("cls || clear");
    cout << "---------- Filtragem por Nome ------------\n\n";
    cout << "OBS.: pode-se pesquisar por apenas um termo!" << endl << endl;
    cout << "\nDigite o nome do Cinema desejado: ";
    cin >> nomeCinema;
    system("cls || clear");
  }

  void apresentarMenuTipoCine(string &tipo){
    system("cls || clear");
    cout << "--------- Filtragem por Tipo -----------\n\n";
    cout << "\nDigite o tipo de filme desejado: ";
    cin >> tipo;
    system("cls || clear");
    cout << "--------- Cinemas c/ Filmes do tipo " << tipo << " ---------\n\n";
  }

  void apresentarMenuGeneroCine(string &genero){
    system("cls || clear");
    cout << "--------- Filtragem por Gênero -----------\n\n";
    cout << "OBS.: inicial do gênero maiúscula!" << endl << endl;
    cout << "\nDigite o gênero de filme desejado: ";
    cin >> genero;
    system("cls || clear");
    cout << "--------- Cinema c/ Filmes do gênero " << genero << " ---------\n\n";
  }

  void apresentarOpcoesDuracaoCine(){
    system("cls || clear");
    cout << "-------- Filtragem por Duração ---------\n\n";
    cout << "Selecione a operação desejada:\n\n\t( 0 ) Voltar ao Menu de Cinemas\n\n\t( 1 ) Filtrar por Duração Específica\n\t( 2 ) Filtrar por Intervalo de Duração\n\n----------------------------------------\n\nEntrada: ";
  }

  void apresentarMenuDuracaoEspecificaCine(int &limInf){
    system("cls || clear");
    cout << "-------- Filtragem por Duração ---------\n\n";
    cout << "OBS.: duração em minutos!" << endl << endl;
    cout << "Digite a duração desejada: ";
    cin >> limInf;
    system("cls || clear");
    cout << "---------- Cinemas c/ Filmes de " << limInf << " min -----------\n\n";
  }

  void apresentarMenuIntervaloDuracaoCine(int &limInf, int &limSup){
    system("cls || clear");
    cout << "-------- Filtragem por Duração ---------\n\n";
    cout << "OBS.: duração em minutos!" << endl << endl;
    cout << "Digite a duração inicial: \t";
    cin >> limInf;
    cout << "\nDigite a duração final: \t";
    cin >> limSup;
    system("cls || clear");
    cout << "------ Cinemas c/ Filmes de " << limInf << " a " << limSup << " min --------\n\n";
  }

  void apresentarOpcoesAnoCine(){
    system("cls || clear");
    cout << "---------- Filtragem por Ano -----------\n\n";
    cout << "Selecione a operação desejada:\n\n\t( 0 ) Voltar ao Menu de Cinemas\n\n\t( 1 ) Filtrar por Ano Específico\n\t( 2 ) Filtrar por Intervalo de Anos\n\n----------------------------------------\n\nEntrada: ";
  }

  void apresentarMenuAnoEspecificoCine(int &anoInf){
    system("cls || clear");
    cout << "---------- Filtragem por Ano -----------\n\n";
    cout << "\nDigite o ano desejado: ";
    cin >> anoInf;
    system("cls || clear");
    cout << "------------ Cinemas c/ Filmes de " << anoInf << " ------------\n\n";
  }

  void apresentarMenuIntervaloAnosCine(int &anoInf, int &anoSup){
    system("cls || clear");
    cout << "---------- Filtragem por Ano -----------\n\n";
    cout << "\nDigite o ano inicial: \t";
    cin >> anoInf;
    cout << "\nDigite o ano final: \t";
    cin >> anoSup;
    system("cls || clear");
    cout << "-------- Cinemas c/ Filmes de " << anoInf << " a " << anoSup << " ---------\n\n";
  }

  void apresentarMenuPrecoCine(float &Pmax){
    system("cls || clear");
    cout << "--------- Filtragem por Preço de Ingressos -----------\n\n";
    cout << "OBS.: digite também a casa dos centavos!" << endl << endl;
    cout << "\nDigite um limite preço: ";
    cin >> Pmax;
    system("cls || clear");
    cout << "--------- Cinemas c/ Limite Preço Maximo de R$" << Pmax << " ---------\n\n";
  }

  void apresentarMenuLocalizacao(long &x, long &y){
    system("cls || clear");
    cout << "--------- Filtragem por Localização -----------\n\n";
    cout << endl << "Digite a coordenada x: ";
    cin >> x;
    cout << endl << "Digite a coordenada y: ";
    cin >> y;
    system("cls || clear");
    cout << "-------- Cinemas Mais Próximos de  (" << x << "," << y << ") ---------\n\n";
  }

  void definirTipo(int &resp, string &tipo){

  switch (resp){
  case 1:
    tipo = "tvEpisode";
    break;
  case 2:
    tipo = "tvMovie";
    break;
  case 3:
    tipo = "tvSpecial";
    break;
  case 4:
    tipo = "tvSeries";
    break;
  case 5:
    tipo = "tvShort";
    break;
  case 6:
    tipo = "short";
    break;
  case 7:
    tipo = "video";
    break;
  case 8:
    tipo = "movie";
    break;
  case 9:
    tipo = "videoGame";
    break;
  case 10:
    return;
  default:
    resp = 0;
    return;  
  }
    if(resp != 0){
      system("cls || clear");
      cout << "---------- Filmes do tipo " << tipo << " ----------\n\n";
    }
  }

  void apresentarOpcoesTipo(){
    system("cls || clear");
    cout << "--------- Filtragem por Tipo -----------\n\n";
    cout << "Selecione o tipo desejado:\n\n( 0 ) Voltar ao Menu de Filmes\n\n( 1 ) tvEpisode\t\t( 6 ) short\n( 2 ) tvMovie\t\t( 7 ) video\n( 3 ) tvEspecial\t( 8 ) movie\n( 4 ) tvSeries\t\t( 9 ) videoGame\n( 5 ) tvShort\t\t( 10 ) Outro: digitar tipo\n\n----------------------------------------\n\nEntrada: ";
  }

};

#endif