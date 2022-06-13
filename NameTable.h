#ifndef NAMETABLE_INCLUDED
#define NAMETABLE_INCLUDED

#include <string>

class NameTableImpl;

class NameTable
{
  public:
    NameTable();
    ~NameTable();
    void enterScope();
    bool exitScope();
    bool declare(const std::string& id, int lineNum);
    int find(const std::string& id) const;
      // We prevent a NameTable object from being copied or assigned
    //overloaded copy constructor 
    NameTable(const NameTable&) = delete;
    //assignement operator
    NameTable& operator=(const NameTable&) = delete;

  private:
    //so basically you can change NameTable.slow.cpp as much as you want 
    NameTableImpl* m_impl;
};

#endif // NAMETABLE_INCLUDED
