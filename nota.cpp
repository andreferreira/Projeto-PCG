#include "nota.h"

void Nota::setNome(char t) {
	if (t >= 'A' && t <= 'G')
		nome = t;
}

void Nota::setSemitom(char st) {
	switch(st) {
	case ' ':
		semitom = normal; break;			
	case 'b':
		semitom = bemol; break;
	case '#':
		semitom = sustenido; break;
	}
}

Nota::Nota(byte midi) {
	oitava = (midi / 12) - 1;
	int tom = midi % 12;
	if (diatonica[tom] != ' ') {
		nome = diatonica[tom];
		semitom = normal;
	} else {
		nome = diatonica[tom-1];
		semitom = sustenido;
	}
}
	
Nota::Nota(std::string nota) {
	switch(nota.size()) {
	case 1:
		setSemitom(' '); break;
	case 2:
		setSemitom(nota[1]); break;
	}
	setNome(nota[0]);
}
	
int Nota::indiceDiatonica() {
	int i = diatonica.find(nome);
	byte B = 11;
	byte C = 0;
	
	switch(semitom) {
	case bemol:
		return (nome != 'C') ? i-1 : B; // Cb = B
	case sustenido:
		return (nome != 'B') ? i+1 : C; // B# = C
	default:
		return i;
	}		
}
	
int Nota::midiOitava() {
	return 12*(oitava+1);
}

byte Nota::toMidi() {
	return (byte)(midiOitava() + indiceDiatonica());
}

Nota* Nota::proximoTom(byte dif) {
	int novoIndice = (indiceDiatonica()+dif) % 12;
	return new Nota((byte)(midiOitava()+novoIndice));
}

bool Nota::operator==(const Nota& n) {
	return toMidi() == ((Nota) n).toMidi();
}
