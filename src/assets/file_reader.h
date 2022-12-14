#pragma once

#include <string>
#include <fstream>

namespace assets {
    class FileReader {
    public:
        FileReader() = default;
        explicit FileReader(const std::string &filename);
        ~FileReader();

        FileReader(const FileReader &other) = delete;
        FileReader& operator=(const FileReader &other) = delete;

        void open_file(const std::string &filename);
        bool next_line(char *line, size_t size);
        bool next_line(std::string &line);

        bool end_of_file() const;
        std::string get_last_line() const;

        std::string get_file_content() const;
    private:
        std::string m_last_line;

        std::ifstream m_fs;
        int m_current_line_number;
    };
}