#include "include\csv.h"
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
// Read csv

template <std::size_t... Idx, typename T, typename R>
bool read_row_help(std::index_sequence<Idx...>, T &row, R &r) {
    return r.read_row(std::get<Idx>(row)...);
}

template <std::size_t... Idx, typename T>
void fill_values(std::index_sequence<Idx...>, T &row,
                 std::vector<double> &data) {
    data.insert(data.end(), {std::get<Idx>(row)...});
}

int main() {
    std::string filePath = "./data/anon_dem.csv";

    const uint32_t columnsNum = 48;
    io::CSVReader<columnsNum> csv_reader(filePath);
    std::vector<double> values;

    using RowType = std::array<double, 48>;
    RowType row;

    try {
        bool done = false;
        while (!done) {
            done = !read_row_help(
                std::make_index_sequence<std::tuple_size<RowType>::value>{},
                row, csv_reader);
            if (!done) {
                fill_values(std::make_index_sequence<columnsNum>{}, row,
                            values);
            }
        }
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}
