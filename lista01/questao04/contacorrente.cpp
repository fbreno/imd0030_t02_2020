#include "contacorrente.hpp"

#include <iomanip>

using std::setfill;
using std::setw;
using std::fixed;
using std::setprecision;
using std::left;
using std::right;

ContaCorrente::ContaCorrente(string agencia, string numero, 
			double saldo, tcTipo tipo, double limite):
			agencia(agencia), numero(numero),
			saldo(saldo), tipo(tipo), limite(limite) {}

ContaCorrente::~ContaCorrente() {}

string 
ContaCorrente::getAgencia() const {
	return this->agencia;
}

string 
ContaCorrente::getNumero() const {
	return this->numero;
}

double 
ContaCorrente::getSaldo() const {
	return this->saldo;
}

tcTipo 
ContaCorrente::getTipo() const {
	return this->tipo;
}

double 
ContaCorrente::getLimite() const {
	return this->limite;
}

vector<Movimentacao*> 
ContaCorrente::getHistorico() const {
	return this->historico;
}

bool ContaCorrente::processarMovimentacao(Movimentacao* nova){
	if (nova->getTipo()==tmCredito) {
		this->saldo += nova->getValor();
		this->historico.push_back(nova);
		return true;
	} else if (nova->getTipo()==tmDebito) {
		if ((this->saldo + this->limite) >= nova->getValor()) {
			this->saldo -= nova->getValor();
			this->historico.push_back(nova);
			return true;
		}
	}
	return false;
}

ostream& operator<< (ostream& o, ContaCorrente& cc) {
	o << setfill(' ') << setw(10) << cc.agencia
		<< setfill(' ') << setw(10) << cc.numero
		<< right << setfill(' ') << setw(15) 
		<< fixed << setprecision(2) << cc.saldo
		<< setfill(' ') << setw(15)
		<< fixed << setprecision(2) << cc.limite;
	return o;
}

bool 
ContaCorrente::operator==(const ContaCorrente& outro) const {
	return (this->numero == outro.numero);
}