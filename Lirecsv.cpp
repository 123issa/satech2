#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

#include "Lirecsv.hpp"

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;
using std::istringstream;

float** Lirecsv::loadCSV(const string& path) {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    

    std::cout << "Hello World!";
    string filename(path);
    string file_contents;
    std::map<int, std::vector<string>> csv_contents;
    char delimiter = ',';
   

    

    istringstream sstream(ss.str());
    std::vector<string> items;
    string record;

    int counter = 0;
    while (std::getline(sstream, record)) {
        istringstream line(record);
        while (std::getline(line, record, delimiter)) {
            items.push_back(record);
        }

        csv_contents[counter] = items;
        items.clear();
        counter += 1;
    }
    int rows =  csv_contents.size();
    int cols = csv_contents[0].size();
    cout<<rows<< " "<<cols; 
    cout << "array size: " << csv_contents.size() << endl;
    float**  csv_cont;
    float l=240;
    float c=320;


    float tempo;
    csv_cont = new float*[240];
    for (int i=0;i<240;i++){
        csv_cont[i] = new float[320];
        for (int j=0;j<320;j++) {
            float temp = ::atof(csv_contents [i][j].c_str());
            csv_cont[i][j]=temp/10;
            

        }
       
    }

    
    return csv_cont;

    
   
}