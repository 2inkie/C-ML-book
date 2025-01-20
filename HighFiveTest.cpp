#include "HighFive/include/highfive/H5DataSet.hpp"
#include "HighFive/include/highfive/H5DataSpace.hpp"
#include "HighFive/include/highfive/H5File.hpp"
#include <cstdint>
#include <vector>

// Test of high five, needs the library.

int main() {
    HighFive::File file(file_name, HighFive::File::ReadWrite |
                                       HighFive::File::Create |
                                       HighFive::File::Truncate);

    auto papers_group = file.createGroup("papers");

    for (const auto &paper : papers) {
        auto paper_group =
            papers_group.createGroup("paper_" + std::to_string(paper.id));

        std::vector<uint32_t> id = {paper.id};

        auto id_attr = paper_group.createAttribute<uint32_t>(
            "id", HighFive::DataSpace::From(id));
        id_attr.write(id);

        auto dec_attr = paper_group.createAttribute<std::string>(
            "preliminary_decision",
            HighFive::DataSpace::From(paper.preliminary_decision));
        dec_attr.write(paper.preliminary_decision);

        auto reviews_group = paper_group.createGroup("reviews");

        std::vector<size_t> dims = {3};
        std::vector<int32_t> values(3);

        for (const auto &r : paper.reviews) {
            auto dataset = reviews_group.createDataSet<int32_t>(
                std::to_string(r.id), HighFive::DataSpace(dims));
            values[0] = std::stoi(r.confidence);
            values[1] = std::stoi(r.evaluation);
            values[2] = std::stoi(r.orientation);
            dataset.write(values);
        }
    }

    HighFive::File file(file_name, HighFive::File::ReadOnly);
    auto papers_group = file.getGroup("papers");
    auto papers_names = papers_group.listObjectNames();

    return 0;
}
