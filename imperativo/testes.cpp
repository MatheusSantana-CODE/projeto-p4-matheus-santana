#include <iostream>
#include <string>
#include <vector>
#include "irrigacao.h"

struct CasoTeste {
    std::string identificador;
    EntradaIrrigacao entrada;
    ResultadoAvaliacao resultadoEsperado;
    EstadoIrrigacao estadoEsperado;
    AcaoValvula acaoEsperada;
};

bool executarCaso(const CasoTeste& caso) {
    SaidaIrrigacao saida = avaliarIrrigacao(caso.entrada);

    bool aprovado = saida.resultado == caso.resultadoEsperado &&
                    saida.estadoResultante == caso.estadoEsperado &&
                    saida.acaoValvula == caso.acaoEsperada;

    std::cout << caso.identificador << ": "
              << (aprovado ? "APROVADO" : "REPROVADO") << '\n';

    if (!aprovado) {
        std::cout << "  Esperado: "
                  << resultadoParaTexto(caso.resultadoEsperado) << ", "
                  << estadoParaTexto(caso.estadoEsperado) << ", "
                  << acaoParaTexto(caso.acaoEsperada) << '\n';
        std::cout << "  Obtido:   "
                  << resultadoParaTexto(saida.resultado) << ", "
                  << estadoParaTexto(saida.estadoResultante) << ", "
                  << acaoParaTexto(saida.acaoValvula) << '\n';
    }

    return aprovado;
}

int main() {
    const int inicio = 30;
    const int interrupcao = 50;

    std::vector<CasoTeste> casos = {
        {"CN01", {20, inicio, interrupcao, SENSOR_NORMAL, true, PARADO, false}, SUCESSO, IRRIGANDO, ABRIR},
        {"CN02", {25, inicio, interrupcao, SENSOR_NORMAL, true, IRRIGANDO, false}, SUCESSO, IRRIGANDO, MANTER_ABERTA},
        {"CN03", {40, inicio, interrupcao, SENSOR_NORMAL, true, PARADO, false}, SUCESSO, PARADO, MANTER_FECHADA},
        {"CN04", {40, inicio, interrupcao, SENSOR_NORMAL, true, IRRIGANDO, false}, SUCESSO, IRRIGANDO, MANTER_ABERTA},
        {"CN05", {60, inicio, interrupcao, SENSOR_NORMAL, true, IRRIGANDO, false}, SUCESSO, PARADO, FECHAR},
        {"CN06", {70, inicio, interrupcao, SENSOR_NORMAL, true, PARADO, false}, SUCESSO, PARADO, MANTER_FECHADA},
        {"CN07", {20, inicio, interrupcao, SENSOR_NORMAL, false, IRRIGANDO, false}, SUCESSO, PARADO, FECHAR},
        {"CN08", {20, inicio, interrupcao, SENSOR_FALHA, true, IRRIGANDO, false}, RESULTADO_FALHA_SENSOR, FALHA_SENSOR, FECHAR},
        {"CN09", {20, inicio, interrupcao, SENSOR_NORMAL, true, FALHA_SENSOR, true}, SUCESSO, IRRIGANDO, ABRIR},
        {"CN10", {60, inicio, interrupcao, SENSOR_NORMAL, true, FALHA_SENSOR, false}, RESULTADO_FALHA_SENSOR, FALHA_SENSOR, FECHAR},

        {"CL01", {30, inicio, interrupcao, SENSOR_NORMAL, true, PARADO, false}, SUCESSO, IRRIGANDO, ABRIR},
        {"CL02", {50, inicio, interrupcao, SENSOR_NORMAL, true, IRRIGANDO, false}, SUCESSO, PARADO, FECHAR},
        {"CL03", {0, inicio, interrupcao, SENSOR_NORMAL, true, PARADO, false}, SUCESSO, IRRIGANDO, ABRIR},
        {"CL04", {100, inicio, interrupcao, SENSOR_NORMAL, true, IRRIGANDO, false}, SUCESSO, PARADO, FECHAR},

        {"CI01", {-1, inicio, interrupcao, SENSOR_NORMAL, true, PARADO, false}, ENTRADA_INVALIDA, PARADO, FECHAR},
        {"CI02", {101, inicio, interrupcao, SENSOR_NORMAL, true, IRRIGANDO, false}, ENTRADA_INVALIDA, PARADO, FECHAR},
        {"CI03", {40, 50, 30, SENSOR_NORMAL, true, PARADO, false}, ENTRADA_INVALIDA, PARADO, FECHAR}
    };

    int aprovados = 0;

    for (const CasoTeste& caso : casos) {
        if (executarCaso(caso)) {
            aprovados++;
        }
    }

    std::cout << "\nResumo: " << aprovados << " de " << casos.size()
              << " casos aprovados.\n";

    return aprovados == static_cast<int>(casos.size()) ? 0 : 1;
}

