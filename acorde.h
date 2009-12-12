#include <string>
#include <vector>
#include <regex.h>

#include "nota.h"
#include "intervalos.h"

typedef char byte;

class Acorde {
	private:
		std::string cifra;
		regmatch_t parser[3];
		byte numNotas;
		Nota* raiz;
		std::vector<byte> acorde;
		void triade();
		void tetrade();
		void diminuta();
		void aumentada();
		void menor();
		void maior();
		bool valida();
	public:
		Acorde(std::string c);
		Nota* getNota(byte n);
		Nota** getNotas();
};
