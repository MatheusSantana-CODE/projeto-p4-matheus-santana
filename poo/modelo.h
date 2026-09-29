#ifndef MODELO_H
#define MODELO_H

#include <string>

enum class EstadoIrrigacao { Parado, Irrigando, FalhaSensor };
enum class AcaoValvula { Abrir, ManterAberta, Fechar, ManterFechada };
enum class TipoResultado { Sucesso, FalhaSensor, EntradaInvalida };

struct ResultadoControle {
    TipoResultado tipo;
    EstadoIrrigacao estado;
    AcaoValvula acao;
    std::string mensagem;
};

class ConfiguracaoLimites {
private:
    int limiteInicio_;
    int limiteInterrupcao_;

public:
    ConfiguracaoLimites(int limiteInicio, int limiteInterrupcao);

    int limiteInicio() const;
    int limiteInterrupcao() const;
    bool valida() const;
};

class SensorUmidade {
private:
    int umidade_;
    bool funcionando_;

public:
    SensorUmidade(int umidade = 0, bool funcionando = true);
    void atualizar(int umidade, bool funcionando);
    int lerUmidade() const;
    bool funcionando() const;
};

class ValvulaIrrigacao {
private:
    bool aberta_;

public:
    explicit ValvulaIrrigacao(bool aberta = false);
    void executar(AcaoValvula acao);
    bool aberta() const;
};

class ControladorIrrigacao {
private:
    SensorUmidade& sensor_;
    ValvulaIrrigacao& valvula_;
    ConfiguracaoLimites limites_;
    EstadoIrrigacao estado_;
    bool habilitado_;

    ResultadoControle concluir(TipoResultado tipo,
                               EstadoIrrigacao novoEstado,
                               AcaoValvula acao,
                               const std::string& mensagem);

public:
    ControladorIrrigacao(SensorUmidade& sensor,
                        ValvulaIrrigacao& valvula,
                        const ConfiguracaoLimites& limites,
                        EstadoIrrigacao estadoInicial = EstadoIrrigacao::Parado,
                        bool habilitado = true);

    ResultadoControle processar(bool reinicializar = false);
    void habilitar();
    void desabilitar();
    void definirEstadoParaTeste(EstadoIrrigacao estado);
    EstadoIrrigacao estado() const;
    bool habilitado() const;
};

std::string paraTexto(EstadoIrrigacao estado);
std::string paraTexto(AcaoValvula acao);
std::string paraTexto(TipoResultado resultado);

#endif
