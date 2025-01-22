#include "eigen/Eigen"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Eigen::MatrixXd readCSV(const std::string &filePath, int cols) {
    std::ifstream file(filePath);
    std::string line;
    std::vector<double> values;
    int rows = 0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        while (std::getline(ss, value, ',')) {
            values.push_back(std::stod(value));
        }
        ++rows;
    }

    Eigen::MatrixXd mat(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat(i, j) = values[i * cols + j];
        }
    }

    return mat;
}

int main() {
    std::string filePath = "data/anon_data.csv";
    int cols = 48;

    Eigen::MatrixXd x = readCSV(filePath, cols);

    // Standardization
    Eigen::Array<double, 1, Eigen::Dynamic> std_dev =
        ((x.rowwise() - x.colwise().mean()).array().square().colwise().sum() /
         (x.rows() - 1))
            .sqrt();
    Eigen::MatrixXd x_std =
        (x.rowwise() - x.colwise().mean()).array().rowwise() / std_dev;

    // Min-Max Normalization
    Eigen::MatrixXd x_min_max =
        (x.rowwise() - x.colwise().minCoeff()).array().rowwise() /
        (x.colwise().maxCoeff() - x.colwise().minCoeff()).array();

    // Mean Normalization
    Eigen::MatrixXd x_avg =
        (x.rowwise() - x.colwise().mean()).array().rowwise() /
        (x.colwise().maxCoeff() - x.colwise().minCoeff()).array();

    // Output normalized matrices
    std::cout << "Standardized Matrix:\n" << x_std << std::endl;
    std::cout << "Min-Max Normalized Matrix:\n" << x_min_max << std::endl;
    std::cout << "Mean Normalized Matrix:\n" << x_avg << std::endl;

    return 0;
}
