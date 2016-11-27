#include <iostream>
#include <iomanip>
#include <exception>
#include "PDF.h"

Wicher::PDF::Entry::Entry() {}
Wicher::PDF::Entry::Entry(std::string name, std::string type, std::vector<int> ids, std::string comment) : name(name), type(type), ids(ids), comment(comment){}
Wicher::PDF::EntryGen::EntryGen(){}

void Wicher::PDF::EntryGen::append(int id, std::string name, std::string type){
	Entry e;
	bool found = false;
	for(std::vector<Entry>::iterator iter = this->entries.begin(); iter != this->entries.end() && !found; ++iter){
		e = *iter;
		if(e.type == type){
			found = true;
			break;
		}
	}
	e.ids.push_back(id);
	if(!found){
		e.type = type;
		e.name = name;
		this->entries.push_back(e);
	}
}

std::vector<Wicher::PDF::Entry> & Wicher::PDF::EntryGen::get_entries(){
	return this->entries;
}