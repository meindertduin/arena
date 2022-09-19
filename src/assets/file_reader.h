#pragma once

#include <string>
#include <fstream>

namespace assets {
    class FileReader {
    public:
        FileReader(const std::string &filename);
        ~FileReader();

        FileReader(const FileReader &other) = delete;
        FileReader& operator=(const FileReader &other) = delete;

        void open_file(const std::string &filename);
        bool next_line(char *line, size_t size);
        bool next_line(std::string &line);

        std::string get_file_content() const;
    private:
        std::ifstream fs;
    };
}