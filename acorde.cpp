#include "acorde.h"

Acorde::Acorde(std::string c): cifra(c) {
	if (!valida())
		return;
	
	regoff_t i = parser[0].rm_so;
	regoff_t l = parser[0].rm_eo;
	raiz = new Nota(cifra.substr(i, l-i));

	switch(numNotas) {
	case 3:
		triade(); break;
	case 4:
		tetrade(); break;
	}
}

void Acorde::tetrade() {
	regoff_t i = parser[1].rm_so;
	regoff_t l = parser[1].rm_eo;
	std::string tom = cifra.substr(i, l-i);
	
	if (tom.size() == 0)
		return;
	switch(tom[0]) {
		case '/':
			maior();
			if (tom.size() == 1)
				acorde.push_back(SETIMA);
			else
				acorde.push_back(SETIMA_MAIOR);
			break;
		case '-':
			menor();
			if (tom.size() == 2)
				acorde.push_back(SETIMA);
			else
				acorde.push_back(SETIMA_MAIOR);
			break;
		case '+':
			aumentada();
			if (tom.size() == 2)
				acorde.push_back(SETIMA);
			else
				acorde.push_back(SETIMA_MAIOR);
			break;
		case '_':
			diminuta();
			if (tom.size() == 2)
				acorde.push_back(SETIMA);
			else
				acorde.push_back(SETIMA_DIMINUTA);
			break;
		case 'm':
			acorde.push_back(TERCEIRA_MAIOR);
			acorde.push_back(QUINTA_DIMINUTA);
			acorde.push_back(SETIMA);
			break;
	}
}

void Acorde::triade() {
	regoff_t i = parser[1].rm_so;
	if (i == -1) {
		maior();
	} else {
		char tom = cifra[i];
		switch(tom) {
		case '-':
			menor(); break;
		case '+':
			aumentada(); break;
		case '_':
			diminuta(); break;
		}
	}
}

void Acorde::diminuta() {
	acorde.push_back(TERCEIRA_MENOR);
	acorde.push_back(QUINTA_DIMINUTA);
}

void Acorde::aumentada() {
	acorde.push_back(TERCEIRA_MAIOR);
	acorde.push_back(QUINTA_AUMENTADA);
}

void Acorde::menor() {
	acorde.push_back(TERCEIRA_MENOR);
	acorde.push_back(QUINTA);
}

void Acorde::maior() {
	acorde.push_back(TERCEIRA_MAIOR);
	acorde.push_back(QUINTA);
}

bool Acorde::valida() {
	regex_t triade, tetrade;
	
	regcomp(&triade, "^([A-G][#b]?)([+\\-_])?$", 0);
	if (regexec(&triade, cifra.c_str(), 2, parser, 0) == 0) {
		numNotas = 3;
		return true;
	}
	
	regcomp(&tetrade, "^([A-G][#b]?)([+\\-]?/M?|_/m?|m5/)?7$", 0);
	if (regexec(&tetrade, cifra.c_str(), 2, parser, 0) == 0) {
		numNotas = 4;
		return true;
	}

	return false;
}

Nota* Acorde::getNota(byte n) {
	return (n == 0) ? raiz : raiz->proximoTom(acorde[n]);
}

Nota** Acorde::getNotas() {
	Nota** notas = new Nota*[numNotas];
	notas[0] = raiz;
	for (int i = 1; i < numNotas; ++i)
		notas[i] = raiz->proximoTom(acorde[i-1]);
	return notas;
}
