#include <iostream>
#include <limits>
#include "irrigacao.h"

int lerInteiro(const std::string& mensagem) {
    int valor;

    while (true) {
        std::cout << mensagem;
        if (std::cin >> valor) {
            return valor;
        }

        std::cout << "Entrada invalida. Digite um numero inteiro.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool lerSimNao(const std::string& mensagem) {
    char resposta;

    while (true) {
        std::cout << mensagem << " (s/n): ";
        std::cin >> resposta;

        if (resposta == 's' || resposta == 'S') {
            return true;
        }
        if (resposta == 'n' || resposta == 'N') {
            return false;
        }

        std::cout << "Opcao invalida. Responda com s ou n.\n";
    }
}

void exibirSaida(const SaidaIrrigacao& saida) {
    std::cout << "\nResultado: " << resultadoParaTexto(saida.resultado) << '\n';
    std::cout << "Estado resultante: " << estadoParaTexto(saida.estadoResultante) << '\n';
    std::cout << "Acao da valvula: " << acaoParaTexto(saida.acaoValvula) << '\n';
    std::cout << "Mensagem: " << saida.mensagem << "\n\n";
}

void exibirMenu() {
    std::cout << "1 - Processar leitura de umidade\n";
    std::cout << "2 - Alterar limites\n";
    std::cout << "3 - Habilitar ou desabilitar sistema\n";
    std::cout << "0 - Encerrar\n";
}

int main() {
    int limiteInicio = 30;
    int limiteInterrupcao = 50;
    bool sistemaHabilitado = true;
    EstadoIrrigacao estadoAtual = PARADO;
    bool executando = true;

    std::cout << "Sistema de Gerenciamento de Irrigacao Inteligente\n";
    std::cout << "Implementacao imperativa em C++\n\n";

    while (executando) {
        std::cout << "Estado atual: " << estadoParaTexto(estadoAtual) << '\n';
        std::cout << "Sistema habilitado: " << (sistemaHabilitado ? "SIM" : "NAO") << '\n';
        std::cout << "Limites: inicio=" << limiteInicio
                  << " interrupcao=" << limiteInterrupcao << "\n\n";

        exibirMenu();
        int opcao = lerInteiro("Escolha: ");

        switch (opcao) {
            case 1: {
                EntradaIrrigacao entrada;
                entrada.umidade = lerInteiro("Umidade do solo (0 a 100): ");
                entrada.limiteInicio = limiteInicio;
                entrada.limiteInterrupcao = limiteInterrupcao;
                entrada.sensor = lerSimNao("O sensor esta funcionando normalmente?")
                                     ? SENSOR_NORMAL
                                     : SENSOR_FALHA;
                entrada.sistemaHabilitado = sistemaHabilitado;
                entrada.estadoAnterior = estadoAtual;
                entrada.reinicializar = estadoAtual == FALHA_SENSOR
                                            ? lerSimNao("Deseja reinicializar o sistema?")
                                            : false;

                SaidaIrrigacao saida = avaliarIrrigacao(entrada);

                // Atribuicao que modifica o estado mantido entre as iteracoes.
                estadoAtual = saida.estadoResultante;
                exibirSaida(saida);
                break;
            }

            case 2:
                limiteInicio = lerInteiro("Novo limite de inicio: ");
                limiteInterrupcao = lerInteiro("Novo limite de interrupcao: ");
                std::cout << "Limites atualizados. A validade sera verificada na proxima leitura.\n\n";
                break;

            case 3:
                sistemaHabilitado = !sistemaHabilitado;
                std::cout << "Sistema "
                          << (sistemaHabilitado ? "habilitado" : "desabilitado")
                          << ".\n\n";
                break;

            case 0:
                executando = false;
                break;

            default:
                std::cout << "Opcao inexistente.\n\n";
        }
    }

    std::cout << "Programa encerrado.\n";
    return 0;
}

