#include <string>

typedef char byte;

class Nota {
	private:
		enum acidentes {bemol=-1, normal=0, sustenido=1};
		std::string diatonica;
		int oitava;
		char nome;
		acidentes semitom;
		int indiceDiatonica();
		int midiOitava();
		void setNome(char t);
		void setSemitom(char st);
	public:
		Nota(std::string nota);
		Nota(byte midi);
		byte toMidi();
		Nota* proximoTom(byte dif);
		bool operator==(const Nota& n);
};
