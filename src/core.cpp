#include "core.h"


bool Core::Util::isLittleEndian(uint8_t a)
{
	// 0x00 0x00 0x00 0000 0101   32 ???? = 4 ?????   - LE 
	// 0000 0101 0x00 0x00 0x00  -  BE

	std::string result = std::bitset<8>(a).to_string();
	if (result.back() == '1')
		return true;
	return false;

}

void Core::Util::save(const char* file, std::vector<int8_t> buffer) {
	std::ofstream out;
	out.open(file);

	for (size_t i = 0; i < buffer.size(); i++) {
		out << buffer[i];
	}

	out.close();
}


std::vector<int8_t> Core::Util::load(const char* path)
{	
	std::ifstream in(path, std::ios::binary);

	std::vector<int8_t> result((std::istreambuf_iterator<char>(in)), (std::istreambuf_iterator<char>()));
	return result;
}


void Core::Util::retrivenNsave(ObjectModel::Root* root)
{


	int16_t iterator = 0;
	std::vector<int8_t> buffer(root->getSize());
	std::string name = root->getName().substr(0, root->getName().length()).append(".ttc");  

	root->pack(&buffer, &iterator);  

	save(name.c_str(), buffer);       
}




