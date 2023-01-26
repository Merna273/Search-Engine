//
//  page.cpp
//  Analysis Project (Search Engine)
//
//  Created by Merna Abdelbadie on 02/11/2021.
//

#include "page.hpp"
void page::newScore()
{
    score =  (0.4 * PR + ((1 - (0.1 - impressions)/(1 +0.1 * impressions)) * PR +  ((0.1 * impressions)/(1+ 0.1 * impressions)) * CTR) * 0.6);
}
void page::CalcCTR()
{
    CTR = (numOfClicks/impressions)*100.0;
}

void page::CalcPR(double p)
{
    PR = p;
}
 void page::getKeywords(int n)
 {
   cout << this->name << endl;
   for(int i = 0; i < n; i++)
    cout << keywords[i] << endl;
   
 }
 void page::readKeywords(int n)
 {
   keywords.resize(10);
      ifstream in;
  in.open("keyword");
  if(in.fail())
    {
      cout << "fail to open file" << endl;
      exit(9);
    }
  int i = 0;
  int j = 0;
  int k = 0;
  while(in)
  {
    string line;
    if(!getline(in, line)) break;
    istringstream ss(line);
    while(ss)
    {
      string str;
      if(!getline(ss,str, ',')) break;
      if(i == n)
      {
        if(k == 0)
        {
          name = str;
          k++;
        }
        else
        {
          keywords.at(j) = str;
          j++;
        }
      }
    }
    i++;
  }
    in.close();
 }
 void page::identifyImpressions(int n)
 {
   ifstream in;
  in.open("impressions");
  if(in.fail())
    {
      cout << "fail to open file" << endl;
      exit(9);
    }
  int i = 0;
  int k = 0;
  while(in)
  {
    string line;
    if(!getline(in, line)) break;
    istringstream ss(line);
    while(ss)
    {
      string str;
      if(!getline(ss,str, ',')) break;
     
      if(i == n)
    {
      if(k == 0)
      {
        k++;
      }
      else if (k == 1)
      {
        impressions = stoi(str);
        k++;
      }
       else if (k == 2)
      {
        numOfClicks = stoi(str);
        k++;
      }
       else if (k == 3)
      {
        k++;
      }
       else if (k == 4)
      {
        score = stod(str);
        k++;
      }
    }
  }
  i++;
}
in.close();
 }
 void page::putBackToTheFile()
 {
   ofstream to;
   to.open("impressions", ios::app);
   to << name << "," << to_string(impressions) << "," << to_string(numOfClicks) << "," << to_string(PR) << "," << to_string(score) << endl;
 }
