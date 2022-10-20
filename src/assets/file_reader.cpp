#include "file_reader.h"
#include "../logging.h"

#include <sstream>
#include <limits>

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

        m_current_line_number++;
        return true;
    }

    bool FileReader::next_line(std::string &line) {
        char char_line[128];
        if (m_fs.eof()) {
            return false;
        }

        m_fs.getline(char_line, sizeof(char_line));
        line = char_line;

        m_current_line_number++;
        return true;
    }

    std::string FileReader::get_file_content() const {
        std::stringstream ss;
        ss << m_fs.rdbuf();
        return ss.str();
    }

    void FileReader::go_to_previous_line() {
        go_to_line(m_current_line_number - 1);
    }

    void FileReader::go_to_line(int line_number) {
        m_fs.seekg(std::ios::beg);
        for(int i = 0; i < line_number - 1; ++i){
            m_fs.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }

        m_current_line_number = line_number;
    }

    bool FileReader::end_of_file() const {
        return m_fs.eof();
    }
}
