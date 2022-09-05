#include <iostream>
#include <fstream>
#include <vector>
#include "ArgumentManager.h"
#include <set>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <time.h>
#include <cmath>
using namespace std;


struct record{
  string id;
  string first;
  string last;
  string year;
  string month;
  string day;
  float gpa;
  record *next;
};
class linkedlist{
  private:
    record* head;

  public:
    linkedlist(){
      head = nullptr;
    }
    void addRecord(string line){
      vector<string> result;
      record *tmp = new record;
    
      int idpos = line.find("id:");
      idpos +=3;
      result.push_back(line.substr(idpos,7));
      
      int fpos = line.find("first:");
      fpos +=6;
      int q = line.find_first_of(',',fpos);
      result.push_back(line.substr(fpos,q-fpos));
    
      int lpos = line.find("last:");
      lpos +=5;
      int r = line.find_first_of(',',lpos);
      result.push_back(line.substr(lpos,r-lpos));
    
      int dpos = line.find("DOB:");
      dpos +=4;
      int s = line.find_first_of(',',dpos);
      result.push_back(line.substr(dpos,4));
      result.push_back(line.substr(dpos+5,2));
      result.push_back(line.substr(dpos+8,2));
    
      int pos = line.find("GPA:");
      pos += 4;
      result.push_back(line.substr(pos,3));
    
      tmp -> id = result[0];
      tmp -> first = result[1];
      tmp -> last = result[2];
      tmp -> year = result[3];
      tmp -> month = result[4];
      tmp -> day = result[5];
      string gpa = result[6];
      float f = stof(gpa);
      tmp -> gpa = f;
      tmp -> next = NULL;    
    
    

      if(head == nullptr){
          head = tmp;
          return;
      }
      record *fakehead = new record;
      fakehead -> next = head;
      record * prev = fakehead;
      record *cu = head;

      while(cu!=nullptr && cu->id < tmp -> id){
        prev = prev -> next;
        cu = cu -> next;
      }
      if(cu!=nullptr && cu -> id == tmp -> id){
        prev->next = tmp;
        tmp->next = cu->next;
        cu->next = nullptr;
        head = fakehead->next;
        return;
        
      }
      prev->next = tmp;
      tmp->next = cu;
      head = fakehead->next;
      return;

}

    
    void swap(record* a, record* b)
    {
      float tmp = a -> gpa;
      a -> gpa = b -> gpa;
      b-> gpa = tmp;
    
      string tmp1 = a -> year;
      a -> year = b -> year;
      b-> year = tmp1;
    
      string  tmp5 = a -> month;
      a -> month = b -> month;
      b-> month = tmp5;
      
      string  tmp6 = a -> day;
      a -> day = b -> day;
      b-> day = tmp6;
    
      string tmp2 = a -> id;
      a -> id = b -> id;
      b-> id = tmp2;
    
      string tmp3 = a -> first;
      a -> first = b -> first;
      b-> first = tmp3;
    
      string tmp4 = a -> last;
      a -> last = b -> last;
      b-> last = tmp4;
    }


    
    int data_compare(record *head, int index) {
      record *a = head;
      record *b = a -> next;
      while( b  != NULL)
      {
        if(index == 0){
          if (a->id > b->id) return(1);
          if (a->id < b->id) return(-1);
          return(0);
        }
        if(index ==4){
        if (a->year > b->year) return(1);
        if (a->year < b->year) return(-1);
    
        if (a->month > b->month) return(1);
        if (a->month < b->month) return(-1);
    
        if (a->day > b->day) return(1);
        if (a->day < b->day) return(-1);

        return(0);
        }
        if(index == 1){
          if (a->gpa > b->gpa) return(1);
          if (a->gpa < b->gpa) return(-1);
          return(0);
        }
        if(index == 2){
          if (a->first > b->first) return(1);
          if (a->first < b->first) return(-1);
          return(0);
        }
        if(index == 3){
          if (a->last > b->last) return(1);
          if (a->last < b->last) return(-1);
          return(0);
        }   
      }
      return 0;
    }
 
    void sort(int index)
    {
      int swapped;
      record *a;
      record *b = NULL;
      do{
        swapped = 0;
        a = head;
        while(a->next != b){
          int i = index;
          
          if(data_compare(a, i)==1){
            swap(a, a->next);
            swapped = 1;
          }
          a = a -> next;           
        }
        b = a;
        }
        while(swapped);
    }

    void deletedata(string id)
    {
        if(head != nullptr){
        while ((head->id).compare(id)==0)
          head = head->next;
        record *tmp = head;
        while (tmp->next != NULL)
        {
          if ((tmp->next->id).compare(id) == 0)
              tmp->next = tmp->next->next;
          else
              tmp = tmp->next;
        }
      }
}


void printList(string file){
  ofstream ofs;
  ofs.open(file);
  record *cu = head;
  record *tmp;
  record *fakehead = new record;
  record *prev = fakehead;
  if(cu==NULL){
    return;
  }
  

  while(cu->next!=NULL){

      ofs << "{id:" <<  setw(7) << setfill('0') << cu->id << ",first:" << cu->first
      << ",last:" << cu->last<< ",DOB:" << cu->year << '-' << setw(2) <<setfill('0')
      << cu->month << '-' << setw(2) << setfill('0') << cu->day << ",GPA:" << fixed
      <<setprecision(1) << cu->gpa << "}" << endl;
      cu = cu->next;
  }
      ofs << "{id:" <<  setw(7) << setfill('0') << cu->id << ",first:" << cu->first
      << ",last:" << cu->last<< ",DOB:" << cu->year << '-' << setw(2) <<setfill('0')
      << cu->month << '-' << setw(2) << setfill('0') << cu->day << ",GPA:" << fixed
      <<setprecision(1) << cu->gpa << "}" << endl;
}
};

int main(int argc, char* argv[]) {
    clock_t start;
    double duration;
    start = clock();
  
  ArgumentManager am(argc, argv);
  string infile = am.get("input");
  string outfile = am.get("output");
  string insort = am.get("sort");
  ifstream input(infile);
  ifstream sort(insort);
  ofstream output(outfile);

  string line;
  string sortline;
  record *head = nullptr;
  linkedlist list;

  if(input.is_open()){
    while(getline(input, line)){
      line.erase(remove_if(line.begin(), line.end(), (int(*)(int))iscntrl), line.end());
      line.erase(std::unique(line.begin(), line.end(),
                      [] (char a, char b) {return a == '\n' && b == '\n';}),
          line.end());
      if(line.length()==0 || line.length()==1)
          continue;
      else{
      size_t cut;
      size_t start = 0;
      if ((cut = line.find("delete",start)) != string::npos){
        string del_id = line.substr(7,13);
        list.deletedata(del_id);
        }
      else
        list.addRecord(line);
      }
      }
      
    
    list.sort(0);

  while(getline(sort, sortline)){
    sortline.erase(remove_if(sortline.begin(), sortline.end(), (int(*)(int))iscntrl), sortline.end());
      sortline.erase(std::unique(sortline.begin(), sortline.end(),
                  [] (char a, char b) {return a == '\n' && b == '\n';}),
      sortline.end());
    if(sortline.length()==0 || line.length()==1)
          continue;
    else{
    if(sortline.compare("id")==0)
      list.sort(0);
    if(sortline.compare("DOB")==0)
      list.sort(4);
    if(sortline.compare("first")==0)
      list.sort(2);
    if(sortline.compare("last")==0)
      list.sort(3);
    if(sortline.compare("GPA")==0)
      list.sort(1);
    }
    }

  list.printList(outfile);

  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << duration;

  }
  return 0;
  }
