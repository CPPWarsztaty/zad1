#include <iostream>
#include <cstdio>
#include <array>
#include <cstring>

std::string read(std::FILE* file) {
    std::string result;
    std::array<char, 1024> buffer{};

    size_t bytes = 0;
    while ((bytes = std::fread(buffer.data(), 1, buffer.size(), file)) == buffer.size()) {
        result.append(buffer.data(), buffer.size());
    }

    if (std::ferror(file)) {
        throw std::runtime_error("error while reading from file: " + std::string(strerror(errno)));
    }

    return result.append(buffer.data(), bytes);
}

void write(std::FILE* file, const std::string& data) {
    if (std::fwrite(data.data(), 1, data.size(), file) != data.size()) {
        throw std::runtime_error("error while writing to file: " + std::string(strerror(errno)));
    }
}

void toUpper(std::string& text) {
    for (auto& character: text) {
        character = static_cast<char>(toupper(character));
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <path to file>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    std::FILE* input = std::fopen(filename, "r");
    if (input == NULL) {
        std::cerr << "Could not open file: " << strerror(errno) << std::endl;
        return 1;
    }

    std::string text;

    try {
        text = read(input);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::fclose(input);

    toUpper(text);

    std::FILE* output = std::fopen(filename, "w");
    if (!output) {
        std::cerr << "Could not open file: " << strerror(errno) << std::endl;
        return 1;
    }

    try {
        write(output, text);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::fclose(output);

    return 0;
}