#include <fstream>
#include <regex>

using namespace std;

int main() {
    string filePathIN = "./data/iris.data";
    string filePathOUT = "./data/iris_fix.csv";

    ifstream data_stream(filePathIN);
    string data_string((istreambuf_iterator<char>(data_stream)),
                       istreambuf_iterator<char>());
    data_string = regex_replace(data_string, regex("Iris-setosa"), "1");
    data_string = regex_replace(data_string, regex("Iris-versicolor"), "2");
    data_string = regex_replace(data_string, regex("Iris-virginica"), "3");
    ofstream out_stream(filePathOUT);
    out_stream << data_string;

    return 0;
}