#ifndef CINEMAS_H
#define CINEMAS_H

#include "Filmes.h"
#include "Interface.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <chrono>

using namespace std;

struct Distancia{
  string Cinema_ID;
  long Coordenada_X;
  long Coordenada_Y;
  double distancia;
};

struct Cinema {
  string Cinema_ID;
  string Nome_do_Cinema;
  long Coordenada_X;
  long Coordenada_Y;
  float PrecoIngresso;
  vector<string> Filmes_Em_Exibicao;
};

class Cinemas {
private:

  vector<Cinema> vetorCinemas;

  vector<Distancia> vetorDistancia;

  void printExecutionTime(chrono::steady_clock::time_point start, chrono::steady_clock::time_point end) {
      auto diff = end - start;
      cout << "Tempo de execução em segundos: " << chrono::duration <double, ratio<1>>(diff).count() << " s" << endl;
  }

  void inserirCinemas(string arquivoNome) {
    begin = chrono::steady_clock::now();
    string linha;
    ifstream arquivo(arquivoNome);

    if (!arquivo.is_open()) {
      cout << "Erro ao abrir o arquivo." << endl;
      return;
    }

    while (getline(arquivo, linha)) {

      stringstream ss(linha);
      Cinema cinema;

      getline(ss, cinema.Cinema_ID, ',');
      getline(ss, cinema.Nome_do_Cinema, ',');

      cinema.Nome_do_Cinema.erase(0, cinema.Nome_do_Cinema.find_first_not_of(" \t\n\r\f\v")); //retira o espaço do início

      ss >> cinema.Coordenada_X;
      ss.ignore();
      ss >> cinema.Coordenada_Y;
      ss.ignore();
      ss >> cinema.PrecoIngresso;
      ss.ignore();

      string filmes;
      while (getline(ss, filmes, ',')) {
          stringstream filmStream(filmes);
          string filme;
          while (getline(filmStream, filme, ' ')) {
              cinema.Filmes_Em_Exibicao.push_back(filme);
          }
      }

      vetorCinemas.push_back(cinema);
    }
    vetorCinemas.erase(vetorCinemas.begin());
    arquivo.close();

    end = chrono::steady_clock::now();
    cout << "Tempo Cinemas: " << endl;
    printExecutionTime(begin, end); 
  }

  void inserirVetorCinemasAtual(vector<Cinema> vetorCinemasAtual, Cinema cinema){
    vetorCinemasAtual.push_back(cinema);
  }

  double encontrarDistancia(string cinema_ID){
    for(Distancia d : vetorDistancia){
      if(d.Cinema_ID.find(cinema_ID) != string::npos){
        return d.distancia;
      }
    }
  }

  void imprimirCinemas(vector<Cinema> vetorCinemasAtual, vector<Filme> vetorAtualFilmes, bool &controle) {
    for (Cinema cinema : vetorCinemasAtual) {
      cout << "\n-------------------------------------------" << endl;
      cout << "\t\tCinema: " << cinema.Nome_do_Cinema << endl;
      cout << "-------------------------------------------" << endl;
      cout << "Coordenada X: \t\t\t" << cinema.Coordenada_X << endl;
      cout << "Coordenada Y: \t\t\t" << cinema.Coordenada_Y << endl;
      cout << "Preço do Ingresso: \t\tR$ " << cinema.PrecoIngresso << endl;
      if(controle) //mostra distância se já foi pesquisada
        cout << "Distância: \t\t\t\t" << encontrarDistancia(cinema.Cinema_ID) << endl;
      cout << "-----------------------------------" << endl;

      bool controle = true;
      for (string tconst : cinema.Filmes_Em_Exibicao) {
        for (Filme filmeCinema : vetorAtualFilmes) {
          if (filmeCinema.tconst == tconst && tconst != "") {

            if(controle){ //executa apenas na primeira vez
              cout << "\t\tFilmes em Exibição: " << endl;
              cout << "-----------------------------------" << endl;
              controle = false; //se o cinema não tiver filmes, não aparece o "Filmes em Exibição"
            }

            cout << "Título Principal: \t" << filmeCinema.primaryTitle << endl;
            cout << "Tipo de Conteúdo: \t" << filmeCinema.titleType << endl;
            cout << "Conteúdo Adulto: \tNão" << endl;
            cout << "Lançamento: \t\t" << filmeCinema.startYear << endl;
            if (filmeCinema.runtimeMinutes != "\\N")
              cout << "Duração (minutos): \t" << filmeCinema.runtimeMinutes << endl;
            cout << "Gêneros: \t\t\t" << filmeCinema.genres << endl;
            cout << "-----------------------------------\n" << endl;
            break;
          }
        }
      }

      if(controle){ //só executa quando não há filmes em exibição nesse cinema
        cout << "Filmes em Exibição: indisponível" << endl;
        cout << "-----------------------------------" << endl;
      }

    }
    cout << endl << "Qtde total de cinemas encontrados: " << vetorCinemasAtual.size();
    cout << endl << "Qtde total de filmes  encontrados: " << vetorAtualFilmes.size() << endl;
  }

  double calcularDistancia(double cx, double cy, double x, double y){
      //a coordenada (cx,cy) é do cinema
      //a coordenada (x,y) é do usuário

      return sqrt((cx-x) * (cx-x) + (cy-y) * (cy-y));
      //retorna a distância entre (cx,cy) e (x,y)
  }

  void trocar(Distancia &a, Distancia &b) {
      Distancia temp = a;
      a = b;
      b = temp;
  }

  int particionar(vector<Distancia> &vetorDistancia, int baixo, int alto) {
      double pivot = vetorDistancia[alto].distancia; //escolhe o pivô
      int i = baixo - 1;

      for (int j = baixo; j < alto; j++) {
          if (vetorDistancia[j].distancia <= pivot) {
              i++;
              trocar(vetorDistancia[i], vetorDistancia[j]);
          }
      }
      trocar(vetorDistancia[i + 1], vetorDistancia[alto]);
      return i + 1;
  }

  void quicksortVetorDistancia(vector<Distancia> &vetorDistancia, int baixo, int alto) {
      if (baixo < alto) {
          int indice_pivo = particionar(vetorDistancia, baixo, alto);

          quicksortVetorDistancia(vetorDistancia, baixo, indice_pivo - 1);
          quicksortVetorDistancia(vetorDistancia, indice_pivo + 1, alto);
      }
  }

  void reordenarVetorCinemasAtual(vector<Cinema> &vetorCinemasAtual){

    vetorCinemasAtual.clear();
    set<string> cinemasRepetidos;

    for(Distancia d : vetorDistancia){
      Cinema cinema = encontrarCinemaID(d.Cinema_ID);
      if(cinemasRepetidos.find(cinema.Cinema_ID) == cinemasRepetidos.end()){
        vetorCinemasAtual.push_back(cinema);
        cinemasRepetidos.insert(cinema.Cinema_ID);
      }
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

  void copiarVetorCine(vector<Cinema> &cinemasFiltrados, vector<Cinema> &vetorAuxCinemas){

    for(int i=0; i < vetorAuxCinemas.size(); i++){
      cinemasFiltrados.push_back(vetorAuxCinemas[i]);
    }

  }

  void copiarVetorFilme(vector<Filme> &filmesFiltrados, vector<Filme> &vetorAuxFilmesFiltrados){

    for(int i=0; i < vetorAuxFilmesFiltrados.size(); i++){
      filmesFiltrados.push_back(vetorAuxFilmesFiltrados[i]);
    }

  }

  Cinema encontrarCinemaID(string &CinemaID) {
    Cinema cinemaVazio; 
    for (Cinema cinema : vetorCinemas) {
      if (cinema.Cinema_ID == CinemaID) { 
        return cinema;
      }
    }
    return cinemaVazio;
  }  

public:

  chrono::steady_clock::time_point begin, end;

  Cinemas() { 
    inserirCinemas("cinemas.txt");
  }

  void retirarFiltros(vector<Cinema> &vetorCinemasAtual, vector<Filme> &filmesFiltrados, bool &primeiraExecucao){
    vetorCinemasAtual.clear();
    filmesFiltrados.clear();
    vetorDistancia.clear();
    primeiraExecucao = true;
    cout << "\n\t\tSua lista agora está vazia!\n";
  }

  void mostrarCinemasEncontrados(vector<Cinema> &vetorCinemasAtual, vector<Filme> &filmesFiltrados, bool &controle){
    if(vetorCinemasAtual.empty())
      cout << "\n\t\tNenhum cinema filtrado!\n";
    else{
      system("cls || clear");
      cout << "---------- Lista de Cinemas ----------\n\n";
      imprimirCinemas(vetorCinemasAtual, filmesFiltrados, controle);
    }
  }

  void encontrarCinemas(int acesso, string nomeCinema, string tipo, string genero, int &Tmin, int &Tmax, float precoMax, int AnoIni, int AnoFim, Filmes filme, bool &controle, bool &primeiraExecucao, vector<Cinema> &cinemasFiltrados, vector<Cinema> &vetorAuxCinemas, vector<Filme> &filmesFiltrados, vector<Filme> &vetorAuxFilmesFiltrados, vector<Cinema> &vetorCinemasAtual) {

    set<string> vetorCinemasAtualRepetido;
    set<string> vetorAuxCinemasRepetidos;
    set<string> cinemasRepetidos;
    int count = 0;
    Cinema cinema;
    Filme filmeCinema;
    int tam, tam2;
    bool verifica;
    //begin
    // begin = chrono::steady_clock::now();

    if(primeiraExecucao || acesso == 0 || acesso == 6){
      tam = vetorCinemas.size();
      cinemasRepetidos.clear();
    }
    else{
      tam = vetorCinemasAtual.size();
    }

    for(int i=0; i < tam; i++) {

      if(primeiraExecucao || acesso == 0)
        cinema = vetorCinemas[i];
      else
        cinema = vetorCinemasAtual[i];

      if(acesso == 6){ //procura cinema específico e mostra filmes em exibição
        if(cinema.Nome_do_Cinema.find(nomeCinema) != string::npos){
          vetorCinemasAtual.clear();
          filmesFiltrados.clear();
          for(string filmeExibicao : cinema.Filmes_Em_Exibicao){
            Filme filmeCinema = filme.encontrarFilmePorTconst(filmeExibicao);
            if(filmeCinema.primaryTitle != "vazio" && filmeExibicao != "")
              filmesFiltrados.push_back(filmeCinema);
          }
          vetorCinemasAtual.push_back(cinema);
          imprimirCinemas (vetorCinemasAtual, filmesFiltrados, controle);
          return;
        }
        continue;
      }

      int runt, runtime;
      string filmeExibicao;


      tam2 = cinema.Filmes_Em_Exibicao.size();


      for(int j=0; j < tam2; j++){

        verifica = false;

        filmeExibicao = cinema.Filmes_Em_Exibicao[j];

        filmeCinema = filme.encontrarFilmePorTconst(filmeExibicao);
        filmeCinema.Cinema_ID = cinema.Cinema_ID;

        if(filmeCinema.primaryTitle != "vazio" && filmeExibicao != "")
        switch(acesso){
          case 0:  
            if (filmeCinema.titleType.find(tipo) != string::npos) {

                filmesFiltrados.push_back(filmeCinema);
                if(vetorCinemasAtualRepetido.find(cinema.Cinema_ID) == vetorCinemasAtualRepetido.end()){
                  vetorCinemasAtual.push_back(cinema);
                  vetorCinemasAtualRepetido.insert(cinema.Cinema_ID);
                }

            }
          break;
          case 1:
            if (filmeCinema.genres.find(genero) != string::npos) {
              if (primeiraExecucao) { //bloco da primeira execução
                filmesFiltrados.push_back(filmeCinema);
                if(vetorCinemasAtualRepetido.find(cinema.Cinema_ID) == vetorCinemasAtualRepetido.end()){
                  vetorCinemasAtual.push_back(cinema);
                  vetorCinemasAtualRepetido.insert(cinema.Cinema_ID);
                }
              }
              if(!primeiraExecucao){ //bloco das execuções seguintes
                for(Filme filmeFilt : filmesFiltrados){
                  if(filmeFilt.Cinema_ID == filmeCinema.Cinema_ID)
                    verifica = true;
                }
                if(verifica){
                  vetorAuxFilmesFiltrados.push_back(filmeCinema);
                  if(vetorAuxCinemasRepetidos.find(cinema.Cinema_ID) == vetorAuxCinemasRepetidos.end()){
                    vetorAuxCinemas.push_back(encontrarCinemaID(filmeCinema.Cinema_ID));
                    vetorAuxCinemasRepetidos.insert(filmeCinema.Cinema_ID);
                  }
                }
              }



            }
          break;
          case 3:
            if (cinema.PrecoIngresso <= precoMax) {
              if (primeiraExecucao) { //bloco da primeira execução
                filmesFiltrados.push_back(filmeCinema);
                if(vetorCinemasAtualRepetido.find(cinema.Cinema_ID) == vetorCinemasAtualRepetido.end()){
                  vetorCinemasAtual.push_back(cinema);
                  vetorCinemasAtualRepetido.insert(cinema.Cinema_ID);
                }
              }
              if(!primeiraExecucao){ //bloco das execuções seguintes
                for(Filme filmeFilt : filmesFiltrados){
                  if(filmeFilt.Cinema_ID == filmeCinema.Cinema_ID)
                    verifica = true;
                }
                if(verifica){
                  vetorAuxFilmesFiltrados.push_back(filmeCinema);
                  if(vetorAuxCinemasRepetidos.find(cinema.Cinema_ID) == vetorAuxCinemasRepetidos.end()){
                    vetorAuxCinemas.push_back(encontrarCinemaID(filmeCinema.Cinema_ID));
                    vetorAuxCinemasRepetidos.insert(filmeCinema.Cinema_ID);
                  }
                }
              }



            }
          break;
          case 4:  //intervalo de anos
            if (filmeCinema.startYear >= AnoIni && filmeCinema.startYear <= AnoFim) {
              if (primeiraExecucao) { //bloco da primeira execução
                filmesFiltrados.push_back(filmeCinema);
                if(vetorCinemasAtualRepetido.find(cinema.Cinema_ID) == vetorCinemasAtualRepetido.end()){
                  vetorCinemasAtual.push_back(cinema);
                  vetorCinemasAtualRepetido.insert(cinema.Cinema_ID);
                }
              }
              if(!primeiraExecucao){ //bloco das execuções seguintes
                for(Filme filmeFilt : filmesFiltrados){
                  if(filmeFilt.Cinema_ID == filmeCinema.Cinema_ID)
                    verifica = true;
                }
                if(verifica){
                  vetorAuxFilmesFiltrados.push_back(filmeCinema);
                  if(vetorAuxCinemasRepetidos.find(cinema.Cinema_ID) == vetorAuxCinemasRepetidos.end()){
                    vetorAuxCinemas.push_back(encontrarCinemaID(filmeCinema.Cinema_ID));
                    vetorAuxCinemasRepetidos.insert(filmeCinema.Cinema_ID);
                  }
                }
              }


            }
          break;
          case 5:  //ano específico
            if (filmeCinema.startYear == AnoIni) {
              if (primeiraExecucao) { //bloco da primeira execução
                filmesFiltrados.push_back(filmeCinema);
                if(vetorCinemasAtualRepetido.find(cinema.Cinema_ID) == vetorCinemasAtualRepetido.end()){
                  vetorCinemasAtual.push_back(cinema);
                  vetorCinemasAtualRepetido.insert(cinema.Cinema_ID);
                }
              }
              if(!primeiraExecucao){ //bloco das execuções seguintes
                for(Filme filmeFilt : filmesFiltrados){
                  if(filmeFilt.Cinema_ID == filmeCinema.Cinema_ID)
                    verifica = true;
                }
                if(verifica){
                  vetorAuxFilmesFiltrados.push_back(filmeCinema);
                  if(vetorAuxCinemasRepetidos.find(cinema.Cinema_ID) == vetorAuxCinemasRepetidos.end()){
                    vetorAuxCinemas.push_back(encontrarCinemaID(filmeCinema.Cinema_ID));
                    vetorAuxCinemasRepetidos.insert(filmeCinema.Cinema_ID);
                  }
                }
              }


            }
          break;
          case 7: //duração específica
            if(filmeCinema.runtimeMinutes.empty()){
              break; //sai do switch caso tconst não exista
            }

            runt = stringToInt(filmeCinema.runtimeMinutes);

            if (runt == Tmin && primeiraExecucao) { //bloco da primeira execução
              filmesFiltrados.push_back(filmeCinema);
              if(vetorCinemasAtualRepetido.find(cinema.Cinema_ID) == vetorCinemasAtualRepetido.end()){
                vetorCinemasAtual.push_back(cinema);
                vetorCinemasAtualRepetido.insert(cinema.Cinema_ID);
              }
            }
            if(runt == Tmin && !primeiraExecucao){ //bloco das execuções seguintes
              for(Filme filmeFilt : filmesFiltrados){
                if(filmeFilt.Cinema_ID == filmeCinema.Cinema_ID)
                  verifica = true;
              }
              if(verifica){
                vetorAuxFilmesFiltrados.push_back(filmeCinema);
                if(vetorAuxCinemasRepetidos.find(cinema.Cinema_ID) == vetorAuxCinemasRepetidos.end()){
                  vetorAuxCinemas.push_back(encontrarCinemaID(filmeCinema.Cinema_ID));
                  vetorAuxCinemasRepetidos.insert(filmeCinema.Cinema_ID);
                }
              }
            }

          break;
          case 2: //intervalo de duração
            if(filmeCinema.runtimeMinutes.empty()){
              break; //sai do switch caso tconst não exista
            }
            runtime = stringToInt(filmeCinema.runtimeMinutes);

            if (runtime >= Tmin && runtime <= Tmax && primeiraExecucao) { //bloco da primeira execução
              filmesFiltrados.push_back(filmeCinema);
              if(vetorCinemasAtualRepetido.find(cinema.Cinema_ID) == vetorCinemasAtualRepetido.end()){
                vetorCinemasAtual.push_back(cinema);
                vetorCinemasAtualRepetido.insert(cinema.Cinema_ID);
              }
            }
            if(runtime >= Tmin && runtime <= Tmax && !primeiraExecucao){ //bloco das execuções seguintes
              for(Filme filmeFilt : filmesFiltrados){
                if(filmeFilt.Cinema_ID == filmeCinema.Cinema_ID)
                  verifica = true;
              }
              if(verifica){
                vetorAuxFilmesFiltrados.push_back(filmeCinema);
                if(vetorAuxCinemasRepetidos.find(cinema.Cinema_ID) == vetorAuxCinemasRepetidos.end()){
                  vetorAuxCinemas.push_back(encontrarCinemaID(filmeCinema.Cinema_ID));
                  vetorAuxCinemasRepetidos.insert(filmeCinema.Cinema_ID);
                }
              }
            }


          break;
        }//fim do switch(acesso)
      }//fim do for de filmes

      //cinemasFiltrados.push_back(cinema);
      // cinemasRepetidos.insert(cinema.Cinema_ID); 
    }//fim do for

    // end = chrono::steady_clock::now();
    // cout << "Tempo Cinemas: " << endl;
    // printExecutionTime(begin, end);

    if(acesso == 6){ //significa que não retornou o cinema encontrado
      cout << "---------- Filtragem por Nome ------------\n\n";
      cout << "\t\tCinema não encontrado" << endl << endl;
      return;
    }


    if(primeiraExecucao || acesso == 0){
      primeiraExecucao = false;
    }else{
      vetorCinemasAtual.clear();
      copiarVetorCine(vetorCinemasAtual, vetorAuxCinemas); //vetorCinemasAtual = vetorAuxCinemas
      vetorAuxCinemas.clear();
      filmesFiltrados.clear();
      copiarVetorFilme(filmesFiltrados, vetorAuxFilmesFiltrados); //filmesfiltrados = vetAuxFilmesFilt
      vetorAuxFilmesFiltrados.clear();
    }

    imprimirCinemas (vetorCinemasAtual, filmesFiltrados, controle);
  }

  void criarVetorDistancia(long x, long y, vector<Cinema> &vetorCinemasAtual, vector<Filme> &filmesFiltrados, bool &controle, bool &primeiraExecucao){

    Cinema cinema;
    int tam;

    if(primeiraExecucao)
      tam = vetorCinemas.size();
    else
      tam = vetorCinemasAtual.size();

    for(int i=0; i < tam; i++){

      if(primeiraExecucao)
        cinema = vetorCinemas[i];
      else
        cinema = vetorCinemasAtual[i];

      Distancia d;
      d.Cinema_ID = cinema.Cinema_ID;
      d.Coordenada_X = cinema.Coordenada_X;
      d.Coordenada_Y = cinema.Coordenada_Y;
      long cx = cinema.Coordenada_X;
      long cy = cinema.Coordenada_Y;
      d.distancia = calcularDistancia(cx, cy, x, y);

      vetorDistancia.push_back(d);
    }

    if(primeiraExecucao)
      primeiraExecucao = false;

    quicksortVetorDistancia(vetorDistancia,0,vetorDistancia.size()-1);
    controle = true;
    reordenarVetorCinemasAtual(vetorCinemasAtual);
    imprimirCinemas(vetorCinemasAtual, filmesFiltrados, controle);
  }

  void limparVetor(){
    vetorCinemas.clear();
  }

  ~Cinemas(){
    limparVetor();
  }
};

#endif