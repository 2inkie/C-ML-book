#include "Shark\include\shark\Data\Csv.h"
#include "Shark\include\shark\Data\Dataset.h"

using namespace shark;

int main() {
    ClassificationDataset dataset;
    std::string filePathIN = "./data/iris_fix.csv";
    importCSV(dataset, filePathIN, LAST_COLUMN);

    std::size_t classes = numberOfClasses(dataset);
    std::cout << "Number of classes " << classes << std::endl;
    std::vector<std::size_t> sizes = classSizes(dataset);
    std::cout << "Class size: " << std::endl;

    for (auto cs : sizes) {
        std::cout << cs << std::endl;
    }

    std::size_t dim = inputDimension(dataset);
    std::cout << "Input dimension: " << dim << std::endl;
    return 0;
}