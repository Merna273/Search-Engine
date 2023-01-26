//
//  page.hpp
//  Analysis Project (Search Engine)
//
//  Created by Merna Abdelbadie on 02/11/2021.
//

#ifndef page_hpp
#define page_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
#include <map>
#include <set>
using namespace std;

class page
{
public:
    double impressions;
    double numOfClicks;
    double CTR;
    double PR;
    double score;
    string name;
    vector<string> keywords;
    void newScore();
    void CalcCTR();
    void CalcPR(double p);
    void readKeywords(int n);
    void getKeywords(int n);
    void setName(string n);
    void identifyImpressions(int n);
    void putBackToTheFile();
};

#endif /* page_hpp */
