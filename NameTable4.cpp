// NameTable.cpp

// This is a correct but inefficient implementation of
// the NameTable functionality.
#include <iostream>
#include "NameTable.h"
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <functional> //hash function
using namespace std;

  // This class does the real work of the implementation.
const int HASH_TABLE_SIZE = 20000;
class NameTableImpl
{
  public:
    NameTableImpl(int hash_table_size):m_hashsize(hash_table_size){
        m_table.resize(m_hashsize);
    }
    void enterScope();
    bool exitScope();
    bool declare(const string& id, int lineNum);
    int find(const string& id) const;
  private:
    struct Info{
        Info(string id, int lineNum, int scopeNum): m_id(id), m_lineNum(lineNum), m_scopeNum(scopeNum) {}
        string m_id; //this is the key
        int m_lineNum;
        int m_scopeNum;
    };
    vector<list<Info>> m_table;
    vector<Info> m_data;
    size_t findHash(const string &key) const;
    int m_scope = 0;
    int m_hashsize;

};
size_t NameTableImpl::findHash(const string &key) const{
    return hash<string>{} (key) % HASH_TABLE_SIZE;
}


int NameTableImpl::find(const string& id) const{
    if (id.empty())
        return -1;
    
    size_t vect_index = findHash(id);
    
    //empty bucket
    if (m_table[vect_index].empty())
        return -1;
    //iterate from the back to the front, so the first one that fits the condition will be returned, which is the one with the greatest lineNum
    
    for (list<Info>::const_reverse_iterator it = m_table[vect_index].rbegin(); it != m_table[vect_index].rend(); ++it) {
        if (it->m_id == id && it->m_scopeNum <= m_scope)
        {
            return it->m_lineNum;
        }
    }
    return -1;

    
}

bool NameTableImpl::declare(const string& id, int lineNum)
{
    if (id.empty())
        return false;
    
    size_t hash_num = findHash(id);

    //check if you can add it first
    for (std::list<Info>::reverse_iterator it = m_table[hash_num].rbegin(); it != m_table[hash_num].rend(); ++it)
    {
        if (it->m_id == id && it->m_scopeNum == m_scope)
        {
            return false;
        }
    }
    Info info(id, lineNum, m_scope);
    m_table[hash_num].push_back(info);
    m_data.push_back(info);
    return true;
}
  
void NameTableImpl::enterScope()
{
    m_scope++;
}

bool NameTableImpl::exitScope()
{
    if (m_scope == 0)
        return false;
    
    int index = m_data.size()-1;
    while (m_data[index].m_scopeNum == m_scope)
    {
        int hash_val = findHash(m_data[index].m_id);
        if (m_table[hash_val].back().m_scopeNum == m_scope)
        {
            m_table[hash_val].pop_back();
            m_data.pop_back();
        }
        index--;
    }
    m_scope--;
    return true;
}





//*********** NameTable functions **************

// For the most part, these functions simply delegate to NameTableImpl's
// functions.

NameTable::NameTable()
{
    m_impl = new NameTableImpl(HASH_TABLE_SIZE);
}

NameTable::~NameTable()
{
    delete m_impl;
}

void NameTable::enterScope()
{
    m_impl->enterScope();
}

bool NameTable::exitScope()
{
    return m_impl->exitScope();
}

bool NameTable::declare(const string& id, int lineNum)
{
    return m_impl->declare(id, lineNum);
}

int NameTable::find(const string& id) const
{
    return m_impl->find(id);
}


