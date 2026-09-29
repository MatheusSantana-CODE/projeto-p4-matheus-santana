#include "modelo.h"

ConfiguracaoLimites::ConfiguracaoLimites(int limiteInicio, int limiteInterrupcao)
    : limiteInicio_(limiteInicio), limiteInterrupcao_(limiteInterrupcao) {}

int ConfiguracaoLimites::limiteInicio() const { return limiteInicio_; }
int ConfiguracaoLimites::limiteInterrupcao() const { return limiteInterrupcao_; }

bool ConfiguracaoLimites::valida() const {
    return limiteInicio_ >= 0 && limiteInicio_ <= 100 &&
           limiteInterrupcao_ >= 0 && limiteInterrupcao_ <= 100 &&
           limiteInicio_ < limiteInterrupcao_;
}

SensorUmidade::SensorUmidade(int umidade, bool funcionando)
    : umidade_(umidade), funcionando_(funcionando) {}

void SensorUmidade::atualizar(int umidade, bool funcionando) {
    umidade_ = umidade;
    funcionando_ = funcionando;
}

int SensorUmidade::lerUmidade() const { return umidade_; }
bool SensorUmidade::funcionando() const { return funcionando_; }

ValvulaIrrigacao::ValvulaIrrigacao(bool aberta) : aberta_(aberta) {}

void ValvulaIrrigacao::executar(AcaoValvula acao) {
    if (acao == AcaoValvula::Abrir || acao == AcaoValvula::ManterAberta) {
        aberta_ = true;
    } else {
        aberta_ = false;
    }
}

bool ValvulaIrrigacao::aberta() const { return aberta_; }

ControladorIrrigacao::ControladorIrrigacao(
    SensorUmidade& sensor,
    ValvulaIrrigacao& valvula,
    const ConfiguracaoLimites& limites,
    EstadoIrrigacao estadoInicial,
    bool habilitado)
    : sensor_(sensor),
      valvula_(valvula),
      limites_(limites),
      estado_(estadoInicial),
      habilitado_(habilitado) {}

ResultadoControle ControladorIrrigacao::concluir(
    TipoResultado tipo,
    EstadoIrrigacao novoEstado,
    AcaoValvula acao,
    const std::string& mensagem) {
    estado_ = novoEstado;
    valvula_.executar(acao);
    return {tipo, estado_, acao, mensagem};
}

ResultadoControle ControladorIrrigacao::processar(bool reinicializar) {
    const int umidade = sensor_.lerUmidade();

    if (!limites_.valida()) {
        return concluir(TipoResultado::EntradaInvalida, EstadoIrrigacao::Parado,
                        AcaoValvula::Fechar,
                        "O limite de inicio deve ser menor que o de interrupcao e ambos devem estar entre 0 e 100.");
    }

    if (umidade < 0 || umidade > 100) {
        return concluir(TipoResultado::EntradaInvalida, EstadoIrrigacao::Parado,
                        AcaoValvula::Fechar,
                        "A umidade deve estar entre 0 e 100.");
    }

    if (!sensor_.funcionando()) {
        return concluir(TipoResultado::FalhaSensor, EstadoIrrigacao::FalhaSensor,
                        AcaoValvula::Fechar,
                        "Falha no sensor. A valvula deve permanecer fechada.");
    }

    if (!habilitado_) {
        const AcaoValvula acao = estado_ == EstadoIrrigacao::Irrigando
                                     ? AcaoValvula::Fechar
                                     : AcaoValvula::ManterFechada;
        return concluir(TipoResultado::Sucesso, EstadoIrrigacao::Parado, acao,
                        "Sistema desabilitado pelo usuario.");
    }

    if (estado_ == EstadoIrrigacao::FalhaSensor && !reinicializar) {
        return concluir(TipoResultado::FalhaSensor, EstadoIrrigacao::FalhaSensor,
                        AcaoValvula::Fechar,
                        "O sistema aguarda reinicializacao apos a falha.");
    }

    if (umidade <= limites_.limiteInicio()) {
        const AcaoValvula acao = estado_ == EstadoIrrigacao::Irrigando
                                     ? AcaoValvula::ManterAberta
                                     : AcaoValvula::Abrir;
        return concluir(TipoResultado::Sucesso, EstadoIrrigacao::Irrigando, acao,
                        "Umidade baixa. A irrigacao deve permanecer ativa.");
    }

    if (umidade >= limites_.limiteInterrupcao()) {
        const AcaoValvula acao = estado_ == EstadoIrrigacao::Irrigando
                                     ? AcaoValvula::Fechar
                                     : AcaoValvula::ManterFechada;
        return concluir(TipoResultado::Sucesso, EstadoIrrigacao::Parado, acao,
                        "Umidade suficiente. A irrigacao deve ficar parada.");
    }

    if (estado_ == EstadoIrrigacao::Irrigando) {
        return concluir(TipoResultado::Sucesso, EstadoIrrigacao::Irrigando,
                        AcaoValvula::ManterAberta,
                        "Faixa intermediaria. A irrigacao permanece ativa.");
    }

    return concluir(TipoResultado::Sucesso, EstadoIrrigacao::Parado,
                    AcaoValvula::ManterFechada,
                    "Faixa intermediaria. A irrigacao permanece parada.");
}

void ControladorIrrigacao::habilitar() { habilitado_ = true; }
void ControladorIrrigacao::desabilitar() { habilitado_ = false; }

void ControladorIrrigacao::definirEstadoParaTeste(EstadoIrrigacao estado) {
    estado_ = estado;
}

EstadoIrrigacao ControladorIrrigacao::estado() const { return estado_; }
bool ControladorIrrigacao::habilitado() const { return habilitado_; }

std::string paraTexto(EstadoIrrigacao estado) {
    switch (estado) {
        case EstadoIrrigacao::Parado: return "PARADO";
        case EstadoIrrigacao::Irrigando: return "IRRIGANDO";
        case EstadoIrrigacao::FalhaSensor: return "FALHA_SENSOR";
    }
    return "ESTADO_DESCONHECIDO";
}

std::string paraTexto(AcaoValvula acao) {
    switch (acao) {
        case AcaoValvula::Abrir: return "ABRIR";
        case AcaoValvula::ManterAberta: return "MANTER_ABERTA";
        case AcaoValvula::Fechar: return "FECHAR";
        case AcaoValvula::ManterFechada: return "MANTER_FECHADA";
    }
    return "ACAO_DESCONHECIDA";
}

std::string paraTexto(TipoResultado resultado) {
    switch (resultado) {
        case TipoResultado::Sucesso: return "SUCESSO";
        case TipoResultado::FalhaSensor: return "FALHA_SENSOR";
        case TipoResultado::EntradaInvalida: return "ENTRADA_INVALIDA";
    }
    return "RESULTADO_DESCONHECIDO";
}
