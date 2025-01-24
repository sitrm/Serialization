#include "../include/core.h"

bool Core::Util::isLittleEndian()
{
	// 0x00 0x00 0x00 0000 0101   32 ���� = 4 �����   - LE 
	// 0000 0101 0x00 0x00 0x00  -  BE
	int8_t a = 5;
	std::string result = std::bitset<8>(a).to_string();
	if (result.back() == '1')
		return true;
	return false;

}

void Core::Util::save(const char* file, std::vector<int8_t> buffer){
	std::ofstream out;
	out.open(file);

	for (size_t i = 0; i < buffer.size(); i++) {
		out << buffer[i];
	}

	out.close();
}

void Core::Util::retrivenNsave(ObjectModel::Root* root)
{
	//доставать имя - паковать в буфер - сохранять в файл

	int16_t iterator = 0;
	std::vector<int8_t> buffer(root->getSize());
	std::string name = root->getName().substr(0, root->getName().length()).append(".ttc");  // вытаскиваем имя

	root->pack(&buffer, &iterator);  // пакуем 	

	save(name.c_str(), buffer);       // сохраянем в файл
}




