/*************************************************************/

/*                                                          */

/* Starter file for a2                                      */

/*                                                          */

/* Author1 Name: Ayushi Sahu                                */

/* Student no.: 143789188                                   */

/*                                                          */

/*************************************************************/

//#include<bits/stdc++.h>

#include <string>

#include <utility>

#include <functional>

#include "mylist.h"



template <class TYPE>

class Table{

public:

Table(){}

virtual void update(const std::string& key, const TYPE& value)=0;

virtual bool remove(const std::string& key)=0;

virtual bool find(const std::string& key, TYPE& value)=0;

virtual int numRecords() const = 0;

virtual bool isEmpty() const = 0;

virtual int capacity() const = 0;

virtual ~Table(){}

};



template <class TYPE>

class SimpleTable:public Table<TYPE>{



struct Record{

TYPE data_;

std::string key_;

Record(const std::string& key, const TYPE& data){

key_=key;

data_=data;

}



};



Record** records_; //the table

int capacity_; //capacity of the array



void grow(){

Record** tmp=new Record*[capacity_*2 +1];

for(int i=0;i<capacity_;i++){

tmp[i]=records_[i];

}

for(int i=capacity_;i <capacity_*2+1;i++){

tmp[i]=nullptr;

}

delete[] records_;

records_=tmp;

capacity_*=2;

}

public:

SimpleTable(int capacity);

SimpleTable(const SimpleTable& rhs);

SimpleTable(SimpleTable&& rhs);

virtual void update(const std::string& key, const TYPE& value);

virtual bool remove(const std::string& key);

virtual bool find(const std::string& key, TYPE& value);

virtual const SimpleTable& operator=(const SimpleTable& rhs);

virtual const SimpleTable& operator=(SimpleTable&& rhs);

virtual ~SimpleTable();

virtual bool isEmpty() const{return numRecords()==0;}

virtual int numRecords() const;

virtual int capacity() const {return capacity_;}



};



template <class TYPE>

int SimpleTable<TYPE>::numRecords() const{

int rc=0;

for(int i=0;records_[i]!=nullptr;i++){

rc++;

}

return rc;

}







template <class TYPE>

SimpleTable<TYPE>::SimpleTable(int capacity): Table<TYPE>(){

records_=new Record*[capacity+1];

capacity_=capacity;

for(int i=0;i<capacity_+1;i++){

records_[i]=nullptr;

}

}



template <class TYPE>

SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs){

records_=new Record*[rhs.capacity_+1];

capacity_=rhs.capacity_;

for(int i=0;i<capacity_+1;i++){ 
records_[i]=nullptr;

}


for(int i=0;i<rhs.numRecords();i++){ 

update(rhs.records_[i]->key_,rhs.records_[i]->data_); 

}

}

template <class TYPE>

SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs){ 
 
capacity_=rhs.capacity_;

records_=rhs.records_;

rhs.records_=nullptr;

rhs.capacity_=0;

}



template <class TYPE>

void SimpleTable<TYPE>::update(const std::string& key, const TYPE& value){ 

int idx=-1;

int sz=numRecords();  

for(int i=0;i<sz;i++){   

if(records_[i]->key_ == key){

idx=i;

}

}

if(idx==-1){

if(numRecords() == capacity_){  

grow(); 

}

records_[numRecords()]=new Record(key,value); 

for(int i=numRecords()-1;i>0 && records_[i]->key_ < records_[i-1]->key_;i--){  

Record* tmp=records_[i];

records_[i]=records_[i-1];

records_[i-1]=tmp;

}



}

else{

records_[idx]->data_=value;

}



}



template <class TYPE>

bool SimpleTable<TYPE>::remove(const std::string& key){ 

int idx=-1;

int size=numRecords(); 

for(int i=0;i<size;i++){

if(records_[i]->key_ == key){

idx=i;

}

}

if(idx!=-1){



delete records_[idx]; 

for(int i=idx;i<numRecords()-1;i++){

records_[i]=records_[i+1]; 

}

records_[size-1]=nullptr;

return true;

}

else{

return false; 

}

}



template <class TYPE>

bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value){ 

int idx=-1;

for(int i=0;i<numRecords();i++){ 

if(records_[i]->key_ == key){

idx=i;

}

}

if(idx==-1)

return false;

else{

value=records_[idx]->data_;

return true;

}

}



template <class TYPE>

const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& rhs){ 

if(this!=&rhs){

if(records_){

while(numRecords() != 0){ 

remove(records_[0]->key_);

}

delete [] records_;

}

records_=new Record*[rhs.capacity_+1];

capacity_=rhs.capacity_;

for(int i=0;i<capacity_;i++){

records_[i]=nullptr;

}

for(int i=0;i<rhs.numRecords();i++){ 

update(rhs.records_[i]->key_,rhs.records_[i]->data_);

}



}

return *this;

}

template <class TYPE>

const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs){ 

if(records_){

while(numRecords() != 0){  

remove(records_[0]->key_); 

}

delete [] records_;

}

records_=rhs.records_;

capacity_=rhs.capacity_;

rhs.records_=nullptr;

rhs.capacity_=0;



return *this;

}

template <class TYPE>

SimpleTable<TYPE>::~SimpleTable(){  

if(records_){

int sz=numRecords();  

for(int i=0;i<sz;i++){

remove(records_[0]->key_);

}

delete [] records_;

}

}





template <class TYPE>

class ChainingTable:public Table<TYPE>{

struct Record{

TYPE value_;

std::string key_;

Record(const std::string& key, const TYPE& data){

key_=key;

value_=data;

}
};


int maxExpected=0;                                                         //capacity of the array
double maxLoadFactor=0;
int numRecord=0;                                                           //keeping track of number of records present in the table
DList<Record*> *HashTable;
public:
std::hash<std::string> hashFunction;

ChainingTable(int maxExpected, double maxLoadFactor);

ChainingTable(const ChainingTable& other);

ChainingTable(ChainingTable&& other);

virtual void update(const std::string& key, const TYPE& value);

virtual bool remove(const std::string& key);

virtual bool find(const std::string& key, TYPE& value);

virtual const ChainingTable& operator=(const ChainingTable& other);

virtual const ChainingTable& operator=(ChainingTable&& other);

virtual ~ChainingTable();

virtual bool isEmpty() const;

virtual int numRecords() const;

virtual int capacity() const;



};


//Constructor for creating a new table with the specified capacity and loadFactor
template <class TYPE>

ChainingTable<TYPE>::ChainingTable(int capacity,double maxLoadFactor): Table<TYPE>(){
maxExpected=capacity;
this->maxLoadFactor=maxLoadFactor;
HashTable = new DList<Record*>[maxExpected];
}


//Copy Constructor that takes the input as table reference and creates a copy
//of it along with all the data stored into the table
template <class TYPE>

ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other){
maxExpected=other.maxExpected;
numRecord=other.numRecord;
maxLoadFactor=other.maxLoadFactor;
HashTable = new DList<Record*>[maxExpected];
for(int i=0;i<maxExpected;i++){
    for(auto j:other.HashTable[i])   //todo
    {
        HashTable[i].push_back(j);
    }
  }
}



//Move Constructor that takes the input as table reference and moves the resources to the 
//current object without creating a copy of the table and then dereferncing the resource.
template <class TYPE>

ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other){
maxExpected=other.maxExpected;
numRecord=other.numRecord;
maxLoadFactor=other.maxLoadFactor;
HashTable=other.HashTable;
other.maxExpected=0;
other.maxLoadFactor=0;
other.numRecord=0;
other.HashTable=nullptr;

}


//update function to find the key-value pair in the table if exists then modify the value
//that specific key with the data passed into it else craete a new record into the table
template <class TYPE>

void ChainingTable<TYPE>::update(const std::string& key, const TYPE& value){
    TYPE value_temp;
    
//checking if the key-value pair exists in the table
bool isthere=ChainingTable::find(key,value_temp);

//if true then simply modify value/data of the key by using hasFunction to
//identify the index value of the key-value pair in the table
if(isthere){

auto hashvalue=hashFunction(key);
int index=hashvalue%maxExpected;
//running a loop to fetch the element in the table with the specific index
//when found, check if the key matches with the key passed in argument if
//true then modify the value of that element in the table
for(auto j:HashTable[index]){
    if(j->key_==key){
        HashTable[index].remove(j);
        HashTable[index].push_back(new Record(key,value));
        //j->value_=value;
        break;
    }
  }
}
//else if the key does not exists, then use the hasFunction to identify the 
//index of the element in the table and create a new record with the specified
//key and value, later incremented the number of records in the table
else{

auto hashvalue=hashFunction(key);
int index=hashvalue%maxExpected;
struct Record *temp=new Record(key,value);
HashTable[index].push_back(temp);
numRecord++;

//if the table is almost filled then grow the table by two times
//and set the values on the same using hashFunction and push_back functions
if((double)numRecord/maxExpected-maxLoadFactor>0.000001){
        DList<Record*>*tempTable = new DList<Record*>[2*maxExpected];
        for(int i=0;i<maxExpected;i++){
            for(auto j:HashTable[i])   //todo
            {
                auto hashvalue=hashFunction(j->key_);
                int index=hashvalue%(2*maxExpected);
                tempTable[index].push_back(j);
            }
         }
        delete [] HashTable;
        HashTable=tempTable;
        maxExpected=2*maxExpected;
     }

  }

}


//this removes the element from the table at a specific key
//the find fcuntion is again used to check the esistence of the element in the table
//if it exists then accessing the index value of it using hashFunction
//and calling the remove function again to make it a recursive function and then 
//decrementing the numRecord count
template <class TYPE>

bool ChainingTable<TYPE>::remove(const std::string& key){
    TYPE value;
   bool isthere=ChainingTable::find(key,value);
   if(isthere){
       auto hashvalue=hashFunction(key);
        int index=hashvalue%maxExpected;
        for(auto rec:HashTable[index]){
            if(rec->key_==key){
                HashTable[index].remove(rec);
                numRecord--;
                break;
            }
        }
       return true;
   }
return false;

}


//this function finds out element in the table with the specified key and value
//passed into the argument this also uses the hashFunction to find the index value
//of the element if the key was found then it stores the value from the table into the
//reference passed and returns true and false according to the check.
template <class TYPE>

bool ChainingTable<TYPE>::find(const std::string& key, TYPE& value){
auto hashvalue=hashFunction(key);
int index=hashvalue%maxExpected;
//check 
for(auto tmp : HashTable[index]){
    if(tmp->key_==key){
        value=tmp->value_;
        return true;
    }
}
return false;

}


//copy assignmnet operator function
template <class TYPE>

const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other){
for(int i=0;i<maxExpected;i++){
    for(auto j:HashTable[i]){
        delete j;
    }
}
delete [] HashTable;
HashTable = new DList<Record*>[other.maxExpected];
maxExpected=other.maxExpected;
numRecord=0;
maxLoadFactor=other.maxLoadFactor;
for(int i=0;i<maxExpected;i++){
    for(auto j:other.HashTable[i]){
        struct Record *temp=new Record(j->key_,j->value_);
        HashTable[i].push_back(temp);
        numRecord++;
    }
}
return *this;
}


//move assignment operator function
template <class TYPE>

const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other){
for(int i=0;i<maxExpected;i++){
    for(auto j:HashTable[i]){
        delete j;
    }
}
delete [] HashTable;
HashTable = new DList<Record*>[other.maxExpected];
maxExpected=other.maxExpected;
numRecord=other.numRecord;
maxLoadFactor=other.maxLoadFactor;
other.maxLoadFactor=0;
other.maxLoadFactor=0;
other.maxExpected=0;
other.numRecord=0;
for(int i=0;i<maxExpected;i++){
    for(auto j:other.HashTable[i]){
        HashTable[i].push_back(j);
    }
}
for(int i=0;i<maxExpected;i++){
    for(auto j:other.HashTable[i]){
     other.HashTable[i].pop_front();
    }
   
}
other.HashTable=nullptr;
return *this;

}


//destructor destroys all the nodes or elements in the table to free the memory
//by running a loop along all the entries in the table
template <class TYPE>

ChainingTable<TYPE>::~ChainingTable(){
for(int i=0;i<maxExpected;i++){
    for(auto j:HashTable[i]){
    HashTable[i].pop_front();
        //delete j;
    }
}
delete [] HashTable;
}


//this function checks whether the table is empty or not
//using the nuRecord counter
template <class TYPE>

bool ChainingTable<TYPE>::isEmpty() const {
if(numRecord==0){
    return true;
}
return false;

}


//this function returns the number of records that exist in the table
template <class TYPE>

int ChainingTable<TYPE>::numRecords() const {
return numRecord;

}


//this function returns the maximum amount of slots the table can have
template <class TYPE>

int ChainingTable<TYPE>::capacity() const {
return maxExpected;

}
