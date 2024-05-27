#pragma once

#include <algorithm>
#include <bit>
#include <fstream>
#include <string_view>

namespace image_processor::io {

class Reader {
public:
    explicit Reader(std::string_view filename);

    template <typename T>
    T Read();

    // std::cin >> a;
    // int i
    // be_reader >> i;
    // const auto i2 = be_reader.Read()
    template <typename T>
    Reader& operator>>(T& i);

private:
    std::ifstream stream_;
};

template <typename T>
T Reader::Read() {
    char buffer[sizeof(T)];
    stream_.read(buffer, sizeof(buffer));

    return *reinterpret_cast<T*>(buffer);
}

template <typename T>
Reader& Reader::operator>>(T& i) {
    i = Read<T>();
    return *this;
}

}  // namespace image_processor::io
