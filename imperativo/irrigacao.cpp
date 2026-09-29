#include "irrigacao.h"

bool entradaValida(const EntradaIrrigacao& entrada, std::string& motivoErro) {
    if (entrada.umidade < 0 || entrada.umidade > 100) {
        motivoErro = "A umidade deve estar entre 0 e 100.";
        return false;
    }

    if (entrada.limiteInicio < 0 || entrada.limiteInicio > 100 ||
        entrada.limiteInterrupcao < 0 || entrada.limiteInterrupcao > 100) {
        motivoErro = "Os limites devem estar entre 0 e 100.";
        return false;
    }

    if (entrada.limiteInicio >= entrada.limiteInterrupcao) {
        motivoErro = "O limite de inicio deve ser menor que o limite de interrupcao.";
        return false;
    }

    motivoErro.clear();
    return true;
}

SaidaIrrigacao avaliarIrrigacao(const EntradaIrrigacao& entrada) {
    SaidaIrrigacao saida;
    std::string motivoErro;

    // R01: a validacao possui a maior prioridade do contrato.
    if (!entradaValida(entrada, motivoErro)) {
        saida.resultado = ENTRADA_INVALIDA;
        saida.estadoResultante = PARADO;
        saida.acaoValvula = FECHAR;
        saida.mensagem = motivoErro;
        return saida;
    }

    // R02: qualquer falha atual do sensor leva ao estado seguro.
    if (entrada.sensor == SENSOR_FALHA) {
        saida.resultado = RESULTADO_FALHA_SENSOR;
        saida.estadoResultante = FALHA_SENSOR;
        saida.acaoValvula = FECHAR;
        saida.mensagem = "Falha no sensor. A valvula deve permanecer fechada.";
        return saida;
    }

    // R03: o comando de desabilitacao prevalece sobre a umidade.
    if (!entrada.sistemaHabilitado) {
        saida.resultado = SUCESSO;
        saida.estadoResultante = PARADO;
        saida.acaoValvula = entrada.estadoAnterior == IRRIGANDO
                                ? FECHAR
                                : MANTER_FECHADA;
        saida.mensagem = "Sistema desabilitado pelo usuario.";
        return saida;
    }

    // R04: uma falha anterior exige reinicializacao explicita.
    if (entrada.estadoAnterior == FALHA_SENSOR && !entrada.reinicializar) {
        saida.resultado = RESULTADO_FALHA_SENSOR;
        saida.estadoResultante = FALHA_SENSOR;
        saida.acaoValvula = FECHAR;
        saida.mensagem = "O sistema aguarda reinicializacao apos a falha.";
        return saida;
    }

    // R06: valor igual ao limite de inicio tambem inicia a irrigacao.
    if (entrada.umidade <= entrada.limiteInicio) {
        saida.resultado = SUCESSO;
        saida.estadoResultante = IRRIGANDO;
        saida.acaoValvula = entrada.estadoAnterior == IRRIGANDO
                                ? MANTER_ABERTA
                                : ABRIR;
        saida.mensagem = "Umidade baixa. A irrigacao deve permanecer ativa.";
        return saida;
    }

    // R07: valor igual ao limite de interrupcao tambem encerra a irrigacao.
    if (entrada.umidade >= entrada.limiteInterrupcao) {
        saida.resultado = SUCESSO;
        saida.estadoResultante = PARADO;
        saida.acaoValvula = entrada.estadoAnterior == IRRIGANDO
                                ? FECHAR
                                : MANTER_FECHADA;
        saida.mensagem = "Umidade suficiente. A irrigacao deve ficar parada.";
        return saida;
    }

    // R08: entre os limites, o estado operacional anterior e preservado.
    saida.resultado = SUCESSO;
    if (entrada.estadoAnterior == IRRIGANDO) {
        saida.estadoResultante = IRRIGANDO;
        saida.acaoValvula = MANTER_ABERTA;
        saida.mensagem = "Faixa intermediaria. A irrigacao permanece ativa.";
    } else {
        saida.estadoResultante = PARADO;
        saida.acaoValvula = MANTER_FECHADA;
        saida.mensagem = "Faixa intermediaria. A irrigacao permanece parada.";
    }

    return saida;
}

std::string estadoParaTexto(EstadoIrrigacao estado) {
    switch (estado) {
        case PARADO: return "PARADO";
        case IRRIGANDO: return "IRRIGANDO";
        case FALHA_SENSOR: return "FALHA_SENSOR";
    }
    return "ESTADO_DESCONHECIDO";
}

std::string acaoParaTexto(AcaoValvula acao) {
    switch (acao) {
        case ABRIR: return "ABRIR";
        case MANTER_ABERTA: return "MANTER_ABERTA";
        case FECHAR: return "FECHAR";
        case MANTER_FECHADA: return "MANTER_FECHADA";
    }
    return "ACAO_DESCONHECIDA";
}

std::string resultadoParaTexto(ResultadoAvaliacao resultado) {
    switch (resultado) {
        case SUCESSO: return "SUCESSO";
        case RESULTADO_FALHA_SENSOR: return "FALHA_SENSOR";
        case ENTRADA_INVALIDA: return "ENTRADA_INVALIDA";
    }
    return "RESULTADO_DESCONHECIDO";
}

