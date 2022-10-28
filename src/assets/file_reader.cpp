#include "file_reader.h"
#include "../logging.h"

#include <sstream>

namespace assets {
    FileReader::FileReader(const std::string &filename) {
        open_file(filename);
    }

    FileReader::~FileReader() {
        m_fs.close();
    }

    void FileReader::open_file(const std::string &filename) {
        m_fs.open(filename);
        if (!m_fs.is_open())
            THROW_ERROR("IO ERROR, could not open filename %s", filename);
    }

    bool FileReader::next_line(char *line, const size_t size) {
        if (m_fs.eof()) {
            return false;
        }

        m_fs.getline(line, size);

        m_last_line = line;
        return true;
    }

    bool FileReader::next_line(std::string &line) {
        char char_line[128];
        if (m_fs.eof()) {
            return false;
        }

        m_fs.getline(char_line, sizeof(char_line));
        line = char_line;
        m_last_line = char_line;

        return true;
    }

    std::string FileReader::get_file_content() const {
        std::stringstream ss;
        ss << m_fs.rdbuf();
        return ss.str();
    }

    bool FileReader::end_of_file() const {
        return m_fs.eof();
    }

    std::string FileReader::get_last_line() const {
        return m_last_line;
    }
}
