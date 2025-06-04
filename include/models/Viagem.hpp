#include "Parada.hpp"
#include "Onibus.hpp"
#include "Data.hpp"

class Viagem {
    private:
        Parada *origem;
        Parada *destino;
        Onibus *onibus;
        int numAssentosLivres;
        Data data;

    public:
        // construtores
        Viagem(Data data);
        Viagem(Parada *origem, Parada *destino, Onibus *onibus, Data data);

        // outros metodos
        bool verificarDisponibilidade();
        bool incluiOTrecho(Parada *origem, Parada *destino); // verifica se a tentativa de reserva é valida pra viagem

        double calcularTempoViagemCompleta();
        double calcularTempoTrecho(Parada *origem, Parada *destino);
        
        void ocuparAssento();
        void desocuparAssento();

        // getteres e setteres
        Parada* getOrigem();
        void setOrigem(Parada *origem);

        Parada* getDestino();
        void setDestino(Parada *destino);

        int getNumAssentosLivres();
        void setNumAssentosLivres(int numAssentosLivres);

        Onibus* getOnibus();
        void setOnibus(Onibus *onibus);

        Data getData();
        void setData(Data data);
};