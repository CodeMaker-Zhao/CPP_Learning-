#ifndef PERSON
#define PERSON
#include <string>

class Person {
	friend std::istream& read(std::istream&, Person);
	friend std::ostream& print(std::ostream&, Person);
	friend Person& add(const Person&, const Person&);

public:
	std::string getName() const{
		return Name;
	}
	std::string getAddress() const{
		return Address;
	}
	Person& combine(const Person&);
	Person(const std::string &s,const std::string &a):Name(s),Address(a){}
	Person() = default;
private:
	std::string Name;
	std::string Address;
};

std::istream& read(std::istream& is, Person p) {
	is >> p.Address >> p.Name;
	return is;
}
std::ostream& print(std::ostream& os, Person p) {
	os << p.Address << p.Name;
	return os;
}
Person& Person::combine(const Person&) {

}
Person& add(const Person& p1, const Person& p2) {

}

#endif // !Person
#pragma once
