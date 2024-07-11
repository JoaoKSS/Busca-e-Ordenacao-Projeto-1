#include <iostream>
#include <vector>
#include "Cinemas.h"
#include "Filmes.h"
#include "Interface.h"
#include <chrono>

using namespace std;

void printExecutionTime(chrono::steady_clock::time_point start, chrono::steady_clock::time_point end) {
    auto diff = end - start;
    cout << "Tempo de execução em segundos: " << chrono::duration <double, ratio<1>>(diff).count() << " s" << endl;
}


int main() {
  
  Filmes filme;
  Cinemas cinema;
  Interface interface;
  vector<Filme> vetorFilmesAtual;
  vector<Filme> vetorAux;  //vetor temporário como registrador
  vector<Filme> vetorAux2;
  vector <Cinema> cinemasFiltrados;
  vector <Cinema> vetorAuxCinemas;
  vector<Cinema> vetorCinemasAtual;
  
  string tconst, tipo, titulo, genero, nomeCinema;
  int anoInf, anoSup, limInf, limSup;
  long x, y;
  float Pmax;
  bool controleDistancia = false;

  //TESTES PRA FAZER EM CINEMAS: 
  // tipo = "tvEpisode"; //acesso = 0
  // genero = "Music"; //acesso = 1
  // nomeCinema = "Grand CineRoyal"; //acesso = 6
  // limInf = 5; //acesso = 2
  // limSup = 65;
  // Pmax = 11.80; //acesso = 3 
  // //(intervalo de anos acesso = 4) ou (ano específico acesso = 5)
  // anoInf = 2017; 
  // anoSup = 2018;
  
  int op,option,resp;
  bool controle, primeiraExecucao = true;
  chrono::steady_clock::time_point begin, end;

  interface.apresentarContinuar();
  
  do{
    interface.apresentarMenu();
    cin >> op;
    
    if(!op){
      interface.apresentarFimExecucao();
      break;
    }

    if(op == 1){
      controle = true;
      vetorAux.clear();

      while(controle){
        interface.apresentarMenuCinemas();
        cin >> option;

        switch(option){
          case 0:
            controle = false;  //interrompe o while de menu cinemas
          break;
          case 1:
            interface.apresentarMenuNome(nomeCinema);
            begin = chrono::steady_clock::now();
            cinema.encontrarCinemas(6, nomeCinema, tipo,  genero, limInf, limSup, Pmax , anoInf, anoSup, filme, controleDistancia, primeiraExecucao, cinemasFiltrados, vetorAuxCinemas, vetorAux, vetorAux2, vetorCinemasAtual);
            end = chrono::steady_clock::now();
            printExecutionTime(begin, end);
          break; 
          case 2:
            interface.apresentarOpcoesTipo();
            cin >> resp;
            interface.definirTipo(resp, tipo);
            if(resp == 0){
              break;
            }
            if(resp == 10){
              interface.apresentarMenuTipoCine(tipo);
            }
            begin = chrono::steady_clock::now();
            cinema.encontrarCinemas(0, nomeCinema, tipo,  genero, limInf, limSup, Pmax , anoInf, anoSup, filme, controleDistancia, primeiraExecucao, cinemasFiltrados, vetorAuxCinemas, vetorAux, vetorAux2, vetorCinemasAtual);
            end = chrono::steady_clock::now();
            printExecutionTime(begin, end);
          break;
          case 3:
            interface.apresentarOpcoesGenero();
            cin >> resp;
            interface.definirGenero(resp, genero);
            if(resp == 0) {
              break;
            }
            if(resp == 24){
              interface.apresentarMenuGeneroCine(genero);
            }  
            begin = chrono::steady_clock::now();
            cinema.encontrarCinemas(1, nomeCinema, tipo,  genero, limInf, limSup, Pmax , anoInf, anoSup, filme, controleDistancia, primeiraExecucao, cinemasFiltrados, vetorAuxCinemas, vetorAux, vetorAux2, vetorCinemasAtual);
            end = chrono::steady_clock::now();
            printExecutionTime(begin, end);
          break;
          case 4:
            interface.apresentarOpcoesDuracaoCine();
            cin >> resp;
            if(resp == 1){
              interface.apresentarMenuDuracaoEspecificaCine(limInf);
              begin = chrono::steady_clock::now();
              cinema.encontrarCinemas(7, nomeCinema, tipo,  genero, limInf, limSup, Pmax , anoInf, anoSup, filme, controleDistancia, primeiraExecucao, cinemasFiltrados, vetorAuxCinemas, vetorAux, vetorAux2, vetorCinemasAtual);
              end = chrono::steady_clock::now();
              printExecutionTime(begin, end);
            }else if(resp == 2){
              interface.apresentarMenuIntervaloDuracaoCine(limInf, limSup);
              begin = chrono::steady_clock::now();
            cinema.encontrarCinemas(2, nomeCinema, tipo,  genero, limInf, limSup, Pmax , anoInf, anoSup, filme, controleDistancia, primeiraExecucao, cinemasFiltrados, vetorAuxCinemas, vetorAux, vetorAux2, vetorCinemasAtual);
              end = chrono::steady_clock::now();
              printExecutionTime(begin, end);
            }
          break;
          case 5:
            interface.apresentarOpcoesAnoCine();
            cin >> resp;
            if(resp == 1){
              interface.apresentarMenuAnoEspecificoCine(anoInf);
              begin = chrono::steady_clock::now();
              cinema.encontrarCinemas(5, nomeCinema, tipo,  genero, limInf, limSup, Pmax , anoInf, anoSup, filme, controleDistancia, primeiraExecucao, cinemasFiltrados, vetorAuxCinemas, vetorAux, vetorAux2, vetorCinemasAtual);
              end = chrono::steady_clock::now();
              printExecutionTime(begin, end);
            }else if(resp == 2){
              interface.apresentarMenuIntervaloAnosCine(anoInf, anoSup);
              begin = chrono::steady_clock::now();
              cinema.encontrarCinemas(4, nomeCinema, tipo,  genero, limInf, limSup, Pmax , anoInf, anoSup, filme, controleDistancia, primeiraExecucao, cinemasFiltrados, vetorAuxCinemas, vetorAux, vetorAux2, vetorCinemasAtual);
              end = chrono::steady_clock::now();
              printExecutionTime(begin, end);
            }
          break;
          case 6:
            //(x,y) é a posição do usuário
            interface.apresentarMenuLocalizacao(x,y);
            begin = chrono::steady_clock::now();
            cinema.criarVetorDistancia(x, y, vetorCinemasAtual, vetorAux, controleDistancia, primeiraExecucao);
            end = chrono::steady_clock::now();
            
            cout << "[ Tempo gasto para ordenar ] ";
            printExecutionTime(begin, end);
          break;
          case 7:
            interface.apresentarMenuPrecoCine(Pmax);
            begin = chrono::steady_clock::now();
            cinema.encontrarCinemas(3, nomeCinema, tipo,  genero, limInf, limSup, Pmax , anoInf, anoSup, filme, controleDistancia, primeiraExecucao, cinemasFiltrados, vetorAuxCinemas, vetorAux, vetorAux2, vetorCinemasAtual);
            end = chrono::steady_clock::now();
            printExecutionTime(begin, end);
          break;
          case 8:
            cinema.mostrarCinemasEncontrados(vetorCinemasAtual, vetorAux, controleDistancia);
          break;
          case 9:
            cinema.retirarFiltros(vetorCinemasAtual, vetorAux, primeiraExecucao);
          break;
        }//fim do switch
        
        interface.apresentarContinuar();
        
      }//fim do while(controle)
    }//fim do (op == 1)
    
    if(op == 2){
      controle = true;
      
      while(controle){
        interface.apresentarMenuFilmes();
        cin >> option;

        switch(option){
          case 0:
            controle = false;  //interrompe o while de menu filmes
            break;
          case 1:
            interface.apresentarMenuTitulo(titulo);
            begin = chrono::steady_clock::now();
            filme.encontrarFilmes(2, vetorFilmesAtual, vetorAux, primeiraExecucao, tconst, tipo, titulo, anoInf, anoSup, limInf, limSup, genero);
            end = chrono::steady_clock::now();
            cout << endl;
            printExecutionTime(begin, end);
            break;
          case 2:  
            interface.apresentarOpcoesTipo();
            cin >> resp;
            interface.definirTipo(resp, tipo);
            if(resp == 0){
              break;
            }
            if(resp == 10){
              interface.apresentarMenuTipo(tipo);
            }
            begin = chrono::steady_clock::now();begin = chrono::steady_clock::now();
            filme.encontrarFilmes(1, vetorFilmesAtual, vetorAux, primeiraExecucao, tconst, tipo, titulo, anoInf, anoSup, limInf, limSup, genero);
            end = chrono::steady_clock::now();
            cout << endl;
            printExecutionTime(begin, end);
            break;
          case 3: 
            interface.apresentarOpcoesGenero();
            cin >> resp;
            interface.definirGenero(resp, genero);
            if(resp == 0) 
              break;
            if(resp == 24)
              interface.apresentarMenuGenero(genero);
            begin = chrono::steady_clock::now();
            filme.encontrarFilmes(5, vetorFilmesAtual, vetorAux, primeiraExecucao, tconst, tipo, titulo, anoInf, anoSup, limInf, limSup, genero);
            end = chrono::steady_clock::now();
            cout << endl;
            printExecutionTime(begin, end);
            break;
          case 4: 
            interface.apresentarOpcoesDuracao();
            cin >> resp;
            if(resp == 1){
              interface.apresentarMenuDuracaoEspecifica(limInf);
              begin = chrono::steady_clock::now();
              filme.encontrarFilmes(9, vetorFilmesAtual, vetorAux, primeiraExecucao, tconst, tipo, titulo, anoInf, anoSup, limInf, limSup, genero);
              end = chrono::steady_clock::now();
              cout << endl;
              printExecutionTime(begin, end);
            }else if(resp == 2){
              interface.apresentarMenuIntervaloDuracao(limInf, limSup);
              begin = chrono::steady_clock::now();
              filme.encontrarFilmes(7, vetorFilmesAtual, vetorAux, primeiraExecucao, tconst, tipo, titulo, anoInf, anoSup, limInf, limSup, genero);
              end = chrono::steady_clock::now();
              cout << endl;
              printExecutionTime(begin, end);
            }
            break;
          case 5: 
            interface.apresentarOpcoesAno();
            cin >> resp;
            if(resp == 1){
              interface.apresentarMenuAnoEspecifico(anoInf);
              begin = chrono::steady_clock::now();
              filme.encontrarFilmes(8, vetorFilmesAtual, vetorAux, primeiraExecucao, tconst, tipo, titulo, anoInf, anoSup, limInf, limSup, genero);
              end = chrono::steady_clock::now();
              cout << endl;
              printExecutionTime(begin, end);
            }else if(resp == 2){
              interface.apresentarMenuIntervaloAnos(anoInf, anoSup);
              begin = chrono::steady_clock::now();
              filme.encontrarFilmes(4, vetorFilmesAtual, vetorAux, primeiraExecucao, tconst, tipo, titulo, anoInf, anoSup, limInf, limSup, genero);
              end = chrono::steady_clock::now();
              cout << endl;
              printExecutionTime(begin, end);
            }
            break;
          case 6:
            cout << endl;
            filme.mostrarFilmesEncontrados(vetorFilmesAtual);
            break;
          case 7:
            filme.retirarFiltros(vetorFilmesAtual, primeiraExecucao);
            break;
          default:
            break;
        }//fim do switch

        interface.apresentarContinuar();
        
      }//fim do while(controle)

    }//fim do if(op==2)

    controle = true;
    
    if(op != 0 && op != 1 && op != 2)
      interface.apresentarOpcaoInvalida();
    
  }while(op);

  
  filme.limparVetor();
  cinema.limparVetor();
  vetorFilmesAtual.clear();
  vetorAux.clear();
  cinemasFiltrados.clear();
  vetorAuxCinemas.clear();
}