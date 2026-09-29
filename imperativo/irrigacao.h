#ifndef IRRIGACAO_H
#define IRRIGACAO_H

#include <string>

enum EstadoIrrigacao {
    PARADO,
    IRRIGANDO,
    FALHA_SENSOR
};

enum EstadoSensor {
    SENSOR_NORMAL,
    SENSOR_FALHA
};

enum AcaoValvula {
    ABRIR,
    MANTER_ABERTA,
    FECHAR,
    MANTER_FECHADA
};

enum ResultadoAvaliacao {
    SUCESSO,
    RESULTADO_FALHA_SENSOR,
    ENTRADA_INVALIDA
};

// Agrupa os valores recebidos em uma avaliacao. Nao possui metodos.
struct EntradaIrrigacao {
    int umidade;
    int limiteInicio;
    int limiteInterrupcao;
    EstadoSensor sensor;
    bool sistemaHabilitado;
    EstadoIrrigacao estadoAnterior;
    bool reinicializar;
};

// Agrupa as saidas observaveis definidas pelo contrato semantico.
struct SaidaIrrigacao {
    ResultadoAvaliacao resultado;
    EstadoIrrigacao estadoResultante;
    AcaoValvula acaoValvula;
    std::string mensagem;
};

bool entradaValida(const EntradaIrrigacao& entrada, std::string& motivoErro);
SaidaIrrigacao avaliarIrrigacao(const EntradaIrrigacao& entrada);

std::string estadoParaTexto(EstadoIrrigacao estado);
std::string acaoParaTexto(AcaoValvula acao);
std::string resultadoParaTexto(ResultadoAvaliacao resultado);

#endif

