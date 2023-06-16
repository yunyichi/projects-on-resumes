/*
Yunyi Chi
CS 5330 Computer Vision Project 3
this is the header file for csv_writter.cpp
*/
using namespace std;

/*
write database to a csv file, the database includes a string vector of names
 and a vector of features vectors
*/
void write_csv( std::vector<std::string> &v1, std::vector<std::vector<double>> &v2);
/*
load database from a csv file, the database includes a string vector of names
 and a vector of features vectors
*/
void read_csv(std::vector<std::string> &v1, std::vector<std::vector<double>> &v2);
