#include "file_reader.h"
#include "../logging.h"

namespace assets {
    FileReader::FileReader(const std::string &filename) {
        open_file(filename);
    }

    FileReader::~FileReader() {
        fs.close();
    }

    void FileReader::open_file(const std::string &filename) {
        fs.open(filename);
        if (!fs.is_open())
            THROW_ERROR("IO ERROR, could not open filename %s", filename);
    }

    bool FileReader::next_line(char *line, const size_t size) {
        if (fs.eof()) {
            return false;
        }

        fs.getline(line, size);
        return true;
    }

    bool FileReader::next_line(std::string &line) {
        char char_line[128];
        if (fs.eof()) {
            return false;
        }

        fs.getline(char_line, sizeof(char_line));
        line = char_line;
        return true;
    }

}
