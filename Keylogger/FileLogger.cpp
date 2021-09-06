#include "FileLogger.h"

namespace Keylogger {

bool FileLogger::open(IKeycodeMapper &mapper, std::string filename) {
	//_mapper = mapper;
	_stream.open(filename);
	
	return _stream.is_open();
}

void FileLogger::close() {
	_stream.close();
}

void FileLogger::logKeycode(int keycode, int state) {
	std::cout << keycode << " " << std::endl;
}

}
