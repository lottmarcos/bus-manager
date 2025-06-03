#include <iostream>
#include <vector>
#include "services/OnibusService.hpp"
#include "ParadaService.hpp"
#include "Database.hpp"

using namespace std;

class Main {
public:
    Main(Database &db) : onibusService(db), paradaService(db) {}

    void menu() {
        int choice;
        do {
            cout << "------------------------------------------------------------------------------------\n";
            cout << "MENU" << endl;
            cout << "------------------------------------------------------------------------------------\n";
            cout << "1. Adicionar Ônibus\n";
            cout << "2. Listar Ônibus\n";
            cout << "3. Atualizar Ônibus\n";
            cout << "4. Deletar Ônibus\n";
            cout << "------------------------------------------------------------------------------------\n";
            cout << "5. Adicionar Parada\n";
            cout << "6. Listar Paradas\n";
            cout << "7. Atualizar Parada\n";
            cout << "8. Deletar Parada\n";
            cout << "------------------------------------------------------------------------------------\n";
            cout << "9. Sair\n";
            cout << "Escolha: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    system("clear");
                    adicionarOnibus();
                    break;
                case 2:
                    system("clear");
                    listarOnibus();
                    break;
                case 3:
                    system("clear");
                    atualizarOnibus();
                    break;
                case 4:
                    system("clear");
                    deletarOnibus();
                    break;
                case 5:
                    system("clear");
                    adicionarParada();
                    break;
                case 6:
                    system("clear");
                    listarParadas();
                    break;
                case 7:
                    system("clear");
                    atualizarParada();
                    break;
                case 8:
                    system("clear");
                    deletarParada();
                    break;
                case 9:
                    cout << "Encerrando...\n";
                    break;
                default:
                    cout << "Opção inválida!\n";
            }
        } while (choice != 9);
    }

private:
    OnibusService onibusService;
    ParadaService paradaService;

    void adicionarOnibus() {
        string placa;
        int num_assentos;
        double velocidade_media, valor_km;

        cout << "Digite a placa: ";
        cin >> placa;
        cout << "Digite o número de assentos: ";
        cin >> num_assentos;
        cout << "Digite a velocidade média (km/h): ";
        cin >> velocidade_media;
        cout << "Digite o valor por km (R$): ";
        cin >> valor_km;

        Onibus onibus(placa, num_assentos, velocidade_media, valor_km);
        if(onibusService.adicionarOnibus(onibus)){
            cout << "Ônibus adicionado\n";
        }
    }

    void listarOnibus() {
        cout << "ONIBUS:" << endl;
        cout << "------------------------------------------------------------------------------------\n";
        vector<Onibus> onibusList = onibusService.listarTodosOnibus();
        for (const auto &onibus : onibusList) {
            cout << "ID: " << onibus.getId() << ", Placa: " << onibus.getPlaca()
                      << ", Assentos: " << onibus.getNumAssentos()
                      << ", Velocidade: " << onibus.getVelocidadeMedia()
                      << ", Valor/km: " << onibus.getValorKm() << "\n";
        }
    }

    void atualizarOnibus() {
        listarOnibus();
        int id;
        cout << "Digite o ID do ônibus para atualizar: ";
        cin >> id;

        Onibus* onibus = onibusService.buscarOnibusPorId(id);
        if (onibus) {
            string placa;
            int num_assentos;
            double velocidade_media, valor_km;

            cout << "Digite a nova placa: ";
            cin >> placa;
            cout << "Digite o novo número de assentos: ";
            cin >> num_assentos;
            cout << "Digite a nova velocidade média: ";
            cin >> velocidade_media;
            cout << "Digite o novo valor por km: ";
            cin >> valor_km;

            onibus->setPlaca(placa);
            onibus->setNumAssentos(num_assentos);
            onibus->setVelocidadeMedia(velocidade_media);
            onibus->setValorKm(valor_km);

            onibusService.atualizarOnibus(*onibus);
            cout << "Ônibus adicionado\n";
            delete onibus;
        } else {
            cout << "Ônibus não encontrado!\n";
        }
    }

    void deletarOnibus() {
        listarOnibus();
        int id;
        cout << "Digite o ID do ônibus para deletar: ";
        cin >> id;
        onibusService.deletarOnibus(id);
        cout << "Ônibus deletado\n";
    }

    void adicionarParada() {
        string nome;
        double distancia_partida;

        cout << "Digite o nome da parada: ";
        cin >> nome;
        cout << "Digite a distância de partida (km): ";
        cin >> distancia_partida;

        Parada parada(nome, distancia_partida);
        paradaService.adicionarParada(parada);
        cout << "Parada adicionada\n";
    }

    void listarParadas() {
        cout << "PARADAS:" << endl;
        cout << "------------------------------------------------------------------------------------\n";
        vector<Parada> paradaList = paradaService.listarTodasParadas();
        for (const auto &parada : paradaList) {
            cout << "ID: " << parada.getId() << ", Nome: " << parada.getNome()
                      << ", Distância: " << parada.getDistanciaPartida() << "\n";
        }
    }

    void atualizarParada() {
        listarParadas();
        int id;
        cout << "Digite o ID da parada para atualizar: ";
        cin >> id;

        Parada* parada = paradaService.buscarParadaPorId(id);
        if (parada) {
            string nome;
            double distancia_partida;

            cout << "Digite o novo nome da parada: ";
            cin >> nome;
            cout << "Digite a nova distância de partida: ";
            cin >> distancia_partida;

            parada->setNome(nome);
            parada->setDistanciaPartida(distancia_partida);

            paradaService.atualizarParada(*parada);
            cout << "Parada atualizada\n";
            delete parada;
        } else {
            cout << "Parada não encontrada!\n";
        }
    }

    void deletarParada() {
        listarParadas();
        int id;
        cout << "Digite o ID da parada para deletar: ";
        cin >> id;
        paradaService.deletarParada(id);
        cout << "Parada deletada\n";
    }
};

int main() {
    Database db("bus_manager.sqlite");  
    Main app(db);
    app.menu();
    return 0;
}
