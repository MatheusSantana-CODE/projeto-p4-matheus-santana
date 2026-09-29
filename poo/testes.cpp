#include <iostream>
#include <string>
#include <vector>
#include "modelo.h"

struct CasoTeste {
    std::string id;
    int umidade;
    int inicio;
    int interrupcao;
    bool sensorNormal;
    bool habilitado;
    EstadoIrrigacao estadoAnterior;
    bool reinicializar;
    TipoResultado resultadoEsperado;
    EstadoIrrigacao estadoEsperado;
    AcaoValvula acaoEsperada;
};

bool executar(const CasoTeste& caso) {
    SensorUmidade sensor(caso.umidade, caso.sensorNormal);
    ValvulaIrrigacao valvula(caso.estadoAnterior == EstadoIrrigacao::Irrigando);
    ConfiguracaoLimites limites(caso.inicio, caso.interrupcao);
    ControladorIrrigacao controlador(sensor, valvula, limites,
                                     caso.estadoAnterior, caso.habilitado);

    const ResultadoControle obtido = controlador.processar(caso.reinicializar);
    const bool aprovado = obtido.tipo == caso.resultadoEsperado &&
                          obtido.estado == caso.estadoEsperado &&
                          obtido.acao == caso.acaoEsperada;

    std::cout << caso.id << ": " << (aprovado ? "APROVADO" : "REPROVADO") << '\n';
    if (!aprovado) {
        std::cout << "  Esperado: " << paraTexto(caso.resultadoEsperado) << ", "
                  << paraTexto(caso.estadoEsperado) << ", "
                  << paraTexto(caso.acaoEsperada) << '\n';
        std::cout << "  Obtido:   " << paraTexto(obtido.tipo) << ", "
                  << paraTexto(obtido.estado) << ", "
                  << paraTexto(obtido.acao) << '\n';
    }
    return aprovado;
}

int main() {
    const int inicio = 30;
    const int interrupcao = 50;
    using E = EstadoIrrigacao;
    using A = AcaoValvula;
    using R = TipoResultado;

    const std::vector<CasoTeste> casos = {
        {"CN01",20,inicio,interrupcao,true,true,E::Parado,false,R::Sucesso,E::Irrigando,A::Abrir},
        {"CN02",25,inicio,interrupcao,true,true,E::Irrigando,false,R::Sucesso,E::Irrigando,A::ManterAberta},
        {"CN03",40,inicio,interrupcao,true,true,E::Parado,false,R::Sucesso,E::Parado,A::ManterFechada},
        {"CN04",40,inicio,interrupcao,true,true,E::Irrigando,false,R::Sucesso,E::Irrigando,A::ManterAberta},
        {"CN05",60,inicio,interrupcao,true,true,E::Irrigando,false,R::Sucesso,E::Parado,A::Fechar},
        {"CN06",70,inicio,interrupcao,true,true,E::Parado,false,R::Sucesso,E::Parado,A::ManterFechada},
        {"CN07",20,inicio,interrupcao,true,false,E::Irrigando,false,R::Sucesso,E::Parado,A::Fechar},
        {"CN08",20,inicio,interrupcao,false,true,E::Irrigando,false,R::FalhaSensor,E::FalhaSensor,A::Fechar},
        {"CN09",20,inicio,interrupcao,true,true,E::FalhaSensor,true,R::Sucesso,E::Irrigando,A::Abrir},
        {"CN10",60,inicio,interrupcao,true,true,E::FalhaSensor,false,R::FalhaSensor,E::FalhaSensor,A::Fechar},
        {"CL01",30,inicio,interrupcao,true,true,E::Parado,false,R::Sucesso,E::Irrigando,A::Abrir},
        {"CL02",50,inicio,interrupcao,true,true,E::Irrigando,false,R::Sucesso,E::Parado,A::Fechar},
        {"CL03",0,inicio,interrupcao,true,true,E::Parado,false,R::Sucesso,E::Irrigando,A::Abrir},
        {"CL04",100,inicio,interrupcao,true,true,E::Irrigando,false,R::Sucesso,E::Parado,A::Fechar},
        {"CI01",-1,inicio,interrupcao,true,true,E::Parado,false,R::EntradaInvalida,E::Parado,A::Fechar},
        {"CI02",101,inicio,interrupcao,true,true,E::Irrigando,false,R::EntradaInvalida,E::Parado,A::Fechar},
        {"CI03",40,50,30,true,true,E::Parado,false,R::EntradaInvalida,E::Parado,A::Fechar}
    };

    int aprovados = 0;
    for (const CasoTeste& caso : casos) {
        if (executar(caso)) ++aprovados;
    }
    std::cout << "\nResumo: " << aprovados << " de " << casos.size()
              << " casos aprovados.\n";
    return aprovados == static_cast<int>(casos.size()) ? 0 : 1;
}
