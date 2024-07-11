#ifndef FILMES_H
#define FILMES_H

#include "Cinemas.h"
#include <fstream>
#include <iostream>
#include <sstream> 
#include <string>
#include <vector>
#include <chrono>

using namespace std;

struct Filme {
  string tconst;
  string titleType;
  string primaryTitle;
  string originalTitle;
  int isAdult;
  int startYear;
  string endYear;
  string runtimeMinutes;
  string genres;
  string Cinema_ID;
};

class Filmes {
private:

  void printExecutionTime(chrono::steady_clock::time_point start, chrono::steady_clock::time_point end) {
    auto diff = end - start;
    cout << "Tempo de execução em segundos: " << chrono::duration <double, ratio<1>>(diff).count() << " s" << endl;
  }

  vector<Filme> vetorFilmes;

  void inserirFilmes(const string &arquivoNome) {
    begin = chrono::steady_clock::now();
    string linha;
    ifstream arquivo(arquivoNome);

    if (!arquivo.is_open()) {
      cout << "Erro ao abrir o arquivo." << endl;
      return;
    }


    while (getline(arquivo, linha)) {
      stringstream ss(linha);
      Filme filme;

      // Lê os campos da linha e armazena na estrutura Filme
      getline(ss, filme.tconst, '\t');
      getline(ss, filme.titleType, '\t');
      getline(ss, filme.primaryTitle, '\t');
      getline(ss, filme.originalTitle, '\t');
      ss >> filme.isAdult;
      ss.ignore(); // Ignora o separador '\t'
      ss >> filme.startYear;
      ss.ignore();
      getline(ss, filme.endYear, '\t');
      getline(ss, filme.runtimeMinutes, '\t');
      getline(ss, filme.genres);

      vetorFilmes.push_back(filme); // Adiciona o filme ao vetor
    }
    vetorFilmes.erase(vetorFilmes.begin()); //remove a 1a linha do arquivo
    arquivo.close();

    end = chrono::steady_clock::now();
    cout << "Tempo Filmes: " << endl;
    printExecutionTime(begin, end);
  }

  //imprime todos os filmes do vetor do parâmetro
  void imprimirDetalhesFilme(vector<Filme> &vetorAtualFilmes){

    for (int i = 0; i < vetorAtualFilmes.size(); i++) {
      Filme filme = vetorAtualFilmes[i];

      cout << "Título Principal: \t" << filme.primaryTitle << endl;
      cout << "Título Original: \t" << filme.originalTitle << endl;
      cout << "Tipo de Conteúdo: \t" << filme.titleType << endl;
      cout << "Conteúdo Adulto: \tNão" << endl;
      cout << "Lançamento: \t\t" << filme.startYear << endl;
      if (filme.runtimeMinutes != "\\N")
        cout << "Duração (minutos): \t" << filme.runtimeMinutes << endl;
      if (filme.genres != "\\N")
        cout << "Gêneros: \t\t\t" << filme.genres << endl;
      cout << "--------------------------" << endl;
    }

    cout << endl << "Qtde de filmes encontrados: " << vetorAtualFilmes.size();

  }

  void inserirVetorFilmesAtual(vector<Filme> &vetorFilmesAtual, Filme filme){
    vetorFilmesAtual.push_back(filme);
  }

  void inserirVetorAux(vector<Filme> &vetorAux, Filme filme){
    vetorAux.push_back(filme);
  }

  void copiarVetor(vector<Filme> &vetorFilmesAtual, vector<Filme> &vetorAux){

    for(int i=0; i < vetorAux.size(); i++){
      vetorFilmesAtual.push_back(vetorAux[i]);
    }

  }

  int stringToInt(string &str) {
    int result = 0;
    for (char c : str) {
      if (c >= '0' && c <= '9') {
        result = result * 10 + (c - '0');
      } 
    }
    return result;
  }

public:

  chrono::steady_clock::time_point begin, end;

  Filmes() { 
    inserirFilmes("filmesCrop.txt"); 
  }

  void retirarFiltros(vector<Filme> &vetorFilmesAtual, bool &primeiraExecucao){
    vetorFilmesAtual.clear();
    primeiraExecucao = true;
    cout << "\n\t\tSua lista agora está vazia!\n";
  }

  void mostrarFilmesEncontrados(vector<Filme> &vetorFilmesAtual){
    if(vetorFilmesAtual.empty())
      cout << "\n\t\tNenhum filme filtrado!\n";
    else{
      system("cls || clear");
      cout << "---------- Lista de Filmes ----------\n\n";
      imprimirDetalhesFilme(vetorFilmesAtual);
    }
  }

  void encontrarFilmes(const int acesso, vector<Filme> &vetorFilmesAtual, vector<Filme> &vetorAux, bool &primeiraExecucao, const string &tconst, const string &tipo, const string &titulo,  const int &anoInf, const int &anoSup, int &limInf, int &limSup, const string &genero){
    Filme filme;
    unsigned tam;
    int runtime; //lembrar de trocar**

    begin = chrono::steady_clock::now();

    if(primeiraExecucao || acesso == 1)
      tam = vetorFilmes.size();
    else
      tam = vetorFilmesAtual.size();

    for (int i = 0; i < tam; i++) {

      if(primeiraExecucao || acesso == 1)
        filme = vetorFilmes[i];
      else
        filme = vetorFilmesAtual[i];

      switch(acesso){
        case 1:
          if (filme.titleType.find(tipo) != string::npos){

              inserirVetorFilmesAtual(vetorFilmesAtual, filme);

          }
          break;
        case 2:
          if (filme.primaryTitle.find(titulo) != string::npos){ 
            if(primeiraExecucao)
              inserirVetorFilmesAtual(vetorFilmesAtual, filme);
            else
              inserirVetorAux(vetorAux, filme);
          }
          break;
        case 4:
          if(filme.startYear >= anoInf && filme.startYear <= anoSup){
            if(primeiraExecucao)
              inserirVetorFilmesAtual(vetorFilmesAtual, filme);
            else
              inserirVetorAux(vetorAux, filme);
          }
          break;
        case 5:
          if (filme.genres.find(genero) != string::npos){
            if(primeiraExecucao)
              inserirVetorFilmesAtual(vetorFilmesAtual, filme);
            else
              inserirVetorAux(vetorAux, filme);
          }
          break;
        case 7:
          runtime = stringToInt(filme.runtimeMinutes);
          if (runtime >= limInf && runtime <= limSup && filme.runtimeMinutes != "\\N") {
            if(primeiraExecucao)
              inserirVetorFilmesAtual(vetorFilmesAtual, filme);
            else
              inserirVetorAux(vetorAux, filme);
          }
          break;
        case 8:
          if(filme.startYear == anoInf){
            if(primeiraExecucao)
              inserirVetorFilmesAtual(vetorFilmesAtual, filme);
            else
              inserirVetorAux(vetorAux, filme);
          }
          break;
        case 9:
          runtime = stringToInt(filme.runtimeMinutes);
          if(runtime == limInf && limInf != 0){
            if(primeiraExecucao)
              inserirVetorFilmesAtual(vetorFilmesAtual, filme);
            else
              inserirVetorAux(vetorAux, filme);
          }
          break;
      }//fim do switch


    } //fim do for
    end = chrono::steady_clock::now();
    printExecutionTime(begin, end);

    if(primeiraExecucao || acesso == 1){
      imprimirDetalhesFilme(vetorFilmesAtual);
      primeiraExecucao = false;
    }else{
      vetorFilmesAtual.clear();
      copiarVetor(vetorFilmesAtual, vetorAux); //vetorFilmesAtual = vetorAux
      vetorAux.clear();
      imprimirDetalhesFilme(vetorFilmesAtual);
    }

  }//fim da função encontrarFilmes()


  Filme encontrarFilmePorTconst(string &tconst) {
    Filme filmeVazio; 
    for (Filme filme : vetorFilmes) {
      if (filme.tconst == tconst) { 
        return filme;
      }
    }
    filmeVazio.primaryTitle = "vazio";
    return filmeVazio;
  }  

  void limparVetor(){
    vetorFilmes.clear();
  }

  ~Filmes(){
    limparVetor();
  }

};

#endif