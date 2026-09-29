#include <iostream>
#include <limits>
#include <string>
#include "modelo.h"

int lerInteiro(const std::string& mensagem) {
    int valor;
    while (true) {
        std::cout << mensagem;
        if (std::cin >> valor) return valor;
        std::cout << "Entrada invalida. Digite um numero inteiro.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool lerSimNao(const std::string& mensagem) {
    char resposta;
    while (true) {
        std::cout << mensagem;
        std::cin >> resposta;
        if (resposta == 's' || resposta == 'S') return true;
        if (resposta == 'n' || resposta == 'N') return false;
        std::cout << "Opcao invalida. Responda com s ou n.\n";
    }
}

int main() {
    SensorUmidade sensor;
    ValvulaIrrigacao valvula;
    ConfiguracaoLimites limites(30, 50);
    ControladorIrrigacao controlador(sensor, valvula, limites);

    std::cout << "Sistema de Gerenciamento de Irrigacao Inteligente\n";
    std::cout << "Implementacao orientada a objetos em C++\n\n";

    while (true) {
        std::cout << "Estado: " << paraTexto(controlador.estado()) << '\n';
        std::cout << "1 - Processar leitura\n";
        std::cout << "2 - Habilitar sistema\n";
        std::cout << "3 - Desabilitar sistema\n";
        std::cout << "0 - Encerrar\n";

        const int opcao = lerInteiro("Escolha: ");
        if (opcao == 0) break;

        if (opcao == 2) {
            controlador.habilitar();
            std::cout << "Sistema habilitado.\n\n";
            continue;
        }
        if (opcao == 3) {
            controlador.desabilitar();
            std::cout << "Sistema desabilitado.\n\n";
            continue;
        }
        if (opcao != 1) {
            std::cout << "Opcao invalida.\n\n";
            continue;
        }

        const int umidade = lerInteiro("Umidade do solo (0 a 100): ");
        const bool sensorNormal = lerSimNao("O sensor esta funcionando? (s/n): ");
        const bool reiniciar = controlador.estado() == EstadoIrrigacao::FalhaSensor
                                   ? lerSimNao("Reinicializar apos a falha? (s/n): ")
                                   : false;

        sensor.atualizar(umidade, sensorNormal);
        const ResultadoControle resultado = controlador.processar(reiniciar);

        std::cout << "Resultado: " << paraTexto(resultado.tipo) << '\n';
        std::cout << "Estado: " << paraTexto(resultado.estado) << '\n';
        std::cout << "Acao: " << paraTexto(resultado.acao) << '\n';
        std::cout << "Mensagem: " << resultado.mensagem << "\n\n";
    }
    return 0;
}
