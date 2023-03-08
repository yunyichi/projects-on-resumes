/*
Yunyi Chi
CS 5330 Computer Vision Project 3
this class includes a csv writer and reader
*/

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <string>
#include <iostream>
#include "csv_writter.h"
/*
write database to a csv file, the database includes a string vector of names
 and a vector of features vectors
*/
void write_csv(std::vector<std::string> &v1, std::vector<std::vector<double>> &v2) {
    std::ofstream file("data.csv");
    if (file.is_open()) {
        for (int i = 0; i < v1.size(); i++) {
            file << v1[i] << ",";
            std::vector<double> temp = v2[i];
            for (int n = 0; n < temp.size(); n++) {
                file << temp[n];
                if (n != temp.size() - 1) {
                    file << ", ";
                }
            }
            file << "\n";
        }
        file.close();
    }
}

/*
load database from a csv file, the database includes a string vector of names
 and a vector of features vectors
*/
void read_csv(std::vector<std::string>& v1, std::vector<std::vector<double>>& v2) {
    std::ifstream file("data.csv");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            std::getline(ss, item, ',');
            v1.push_back(item);
            std::vector<double> temp;
            while (std::getline(ss, item, ',')) {
                temp.push_back(std::stod(item));
            }
            v2.push_back(temp);
        }
        file.close();
    }
}
