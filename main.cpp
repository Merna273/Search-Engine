//
//  main.cpp
//  Analysis Project (Search Engine)
//
//  Created by Merna Abdelbadie on 22/10/2021.
//

#include "page.hpp"

void readWebpages(page* p, int n);
void newSearch(page pages[], int x);
void openWebPage(vector<page>& p, page pg[], int n);
void returnToFile(page pages[], int x);

int main()
{
    ifstream in;
    int x = 0;
    //get no. of distinct webpages
    in.open("keyword");
    string line;
    while(!in.eof())
    {
        getline(in, line);
        x++;
    }
    cout << x << endl;
    in.close();
    //create pages
    page* pages = new page[x];

    readWebpages(pages, x);
    //get keywords and impressions for each page and store them
    for(int i = 0; i < x; i++)
    {
        pages[i].readKeywords(i);
        pages[i].identifyImpressions(i);
        pages[i].CalcCTR();
        pages[i].newScore();
    }
    string choice1 = "";
    do
    {
        cout << "Welcome!\n" << "What would you like to do?\n" << "1. New Search\n" << "2. Exit\n\n" << "Type your choice: ";
        getline(cin, choice1);
        if(choice1 == "2")
            exit(0);
        else if(choice1 == "1")
        {
          system("clear");
          newSearch(pages, x);
        }
        else
        {
            system("clear");
            cout << endl << "Please choose a valid choice\n" << endl;
        }
    }while(choice1 != "1" && choice1 != "2");
    cout << endl;
    return 0;
}
struct cmp {
  bool operator() (const page& p1, const page& p2)
  const {
    return (p1.score > p2.score || (p1.score == p2.score && p1.name < p2.name));
  }
};

void newSearch(page pages[], int x)
{
  string keyword;
  cout << "Please enter the keywords you want to search for:\n";
  getline(cin, keyword);
  istringstream ss(keyword);
  string word1, word2, word3, words;
  getline(ss, word1, ' ');
  getline(ss, word2, ' ');
  getline(ss, word3, ' ');
  string quotationWord = word1 + ' ' + word2;
  string finalWord = quotationWord.substr(1, quotationWord.size() - 2);
  set<page, cmp> webPagesOfFoundKeywords;
    for(int i = 0; i < x; i++)
    {
      for(int j = 0; j < pages[i].keywords.size(); j++)
      {
        
        if(word2 == "and" || word2 == "AND")
        {
          for(int k = 0; k < pages[i].keywords.size(); k++ )
         {
          if(word1 == pages[i].keywords.at(j) && word3 == pages[i].keywords.at(k))
            webPagesOfFoundKeywords.insert(pages[i]);
         }
        }
        else if(word2 == "or" || word2 == "OR")
        {
          if(word1 == pages[i].keywords.at(j) || word3 == pages[i].keywords.at(j))
            webPagesOfFoundKeywords.insert(pages[i]);
        }
        else if(word1[0] == '"' && word2[word2.size()-1]== '"')
        {
            if(finalWord == pages[i].keywords.at(j))
            {
              webPagesOfFoundKeywords.insert(pages[i]);
            }
        }
        else if (word2 != "" && word2 != "or" && word2 != "and" && word2 != "OR" && word2 != "AND")
        {
          if(word1 == pages[i].keywords.at(j) || word2 == pages[i].keywords.at(j))
            webPagesOfFoundKeywords.insert(pages[i]);
        }
        else if(word2 == "" && word3 == "")
        {
          if(keyword == pages[i].keywords.at(j))
            webPagesOfFoundKeywords.insert(pages[i]);
        }
      }
    }
    if(webPagesOfFoundKeywords.size() == 0)
    {
      cout << "Keyword not found please try again\n";
      newSearch(pages, x);
    }
    cout << "Search Results: " << endl;
    int ind = 1;
    for(const page& Page : webPagesOfFoundKeywords)
    {
      for(int j = 0; j < x; j++)
      {
        if(Page.name == pages[j].name)
        pages[j].impressions++;
      }
      cout << ind <<  ". " << Page.name << endl;
      ind++;
    }
    string choice2 = "";
    cout << "Would you like to:\n"  << "1. Choose a webpage to open\n" << "2. New Search\n" << "3. Exit\n" << endl;
    getline(cin, choice2);
    if(choice2 == "1")
    {
    vector<page> sortedWebPages(webPagesOfFoundKeywords.size());
    ind = 0;
    for (const page& Page : webPagesOfFoundKeywords) {
      sortedWebPages[ind] = Page;
      ind++;
    }
     openWebPage(sortedWebPages, pages, x);
    }
    else if(choice2 == "2")
    {
      system("clear");
      newSearch(pages, x);
    }
   else if(choice2 == "3")
    {
      returnToFile(pages, x);
      exit(0);
    }
}
void openWebPage(vector<page>& p, page pg[], int n)
{
  string nn;
  cout << "Please choose the webpage you would like to open:\n";
  getline(cin, nn);
  int num = stoi(nn);
  cout << "You are now viewing: " << p.at(num - 1).name << endl;
  p.at(num - 1).numOfClicks++;
  for(int i = 0; i < n; i++)
  {
    if(p.at(num - 1).name == pg[i].name)
    pg[i].numOfClicks++;
  }
  string choice3 = "";
  cout << "Do you want to:\n" << "1. Go back to webPages\n" << "2. New Search\n" << "3. Exit\n";
  getline(cin, choice3);
  if(choice3 == "1")
    {
      cout << "Search Results:\n";
      for(int i = 0; i < p.size(); i++)
        cout << (i + 1) << ". " << p.at(i).name << endl;
     string choice = "";
      cout << "Would you like to:\n"  << "1. Choose a webpage to open\n" << "2. New Search\n" << "3. Exit\n" << endl;
      getline(cin, choice);
      if(choice == "1")
    {
     openWebPage(p, pg, n);
    }
    else if(choice == "2")
    {
      system("clear");
     newSearch(pg, n);
    }
   else if(choice == "3")
    {
      system("clear");
      returnToFile(pg, n);
      exit(0);
    }
    }
    else if(choice3 == "2")
    {
      system("clear");
      newSearch(pg, n);
    }
   else if(choice3 == "3")
    {
      system("clear");
      returnToFile(pg, n);
      exit(0);
    }
}
void readWebpages(page* p, int n)
{
    ifstream in;
  in.open("webpage");
  map<string, int> haash;
  vector<pair<int,int>> links;
  vector<vector<int>> outGoing, inGoing;
  int id = 0;
  while(in)
  {
    string line;
    if(!getline(in, line)) break;
    int ind;
    for (int i = 0; i < line.size(); i++)
    {
      if (line[i] == ',')
      {
        ind = i;
        break;
      }
    }
    string web1 = line.substr(0, ind);
    string web2 = line.substr(ind + 1, line.size() - ind - 1);
    
    if (!haash.count(web1))
      haash[web1] = id++;
    if (!haash.count(web2))
      haash[web2] = id++;
    links.push_back(make_pair(haash[web1], haash[web2]));
  }
  outGoing.resize(id); inGoing.resize(id);
  for (int i = 0; i < links.size(); i++)
  {
    int u = links[i].first, v = links[i].second;
    // there is an edge from u to v
    outGoing[u].push_back(v); inGoing[v].push_back(u);
  }
  vector<double> pageRank(n, 1.0/(double)n);
  for(int i = 0; i < 100; i++)
  {
    double D = 0.15;
    for(int j = 0; j < n; j++)
    { // compute pageRank[j]
      double PR = 0;
      // sum all of pageranks of nodes in ingoing[j] and store in PR
      for(int k = 0; k < inGoing[j].size(); k++)
      {
        PR = PR +
        (pageRank[inGoing[j][k]])/(double)outGoing[inGoing[j][k]].size();
      }
      pageRank[j] = (1 - D) + D * PR;
      p[j].CalcPR(pageRank[j]);
      //cout << pageRank[j] << endl;
    }
  }
    in.close();
}
void returnToFile(page pages[], int x)
{
    ofstream out;
    out.open("impressions");
    out.clear();
    for(int i = 0; i < x; i++)
    {
      pages[i].CalcCTR();
      pages[i].newScore();
    }
    for(int i = 0; i < x; i++)
    {
      pages[i].putBackToTheFile();
    }
}
