#ifndef SALES_DATA
#define SALES_DATA
#include<string>
struct Sales_data;
std::istream& read(std::istream&, Sales_data&);//为了能够在类内定义含read的构造体
class Sales_data
{
	friend std::istream& read(std::istream&, Sales_data&);
	friend std::ostream& print(std::ostream&, const Sales_data&);
public:
	Sales_data(const std::string& s, unsigned n, double p) : bookNO(s), units_sold(n), revenue(p* n) { std::cout << "hello 0"; }
	Sales_data() :Sales_data(" ", 0, 0) { std::cout << "hello 1"; }
	Sales_data(std::istream& is) :Sales_data() { read(is, *this);std::cout << "hello 2"; }
	Sales_data(const std::string& s) :Sales_data(s, 0, 0) { std::cout << "hello 3"; };
	std::string isbn() const { return bookNO; };
	Sales_data& combine (const Sales_data&) ;
private:
	std::string bookNO;
	unsigned units_sold = 0;
	double revenue = 0.0;
	inline double avg_price() const;
};

inline double Sales_data::avg_price() const {
	return units_sold? revenue / units_sold:0;
}

Sales_data& Sales_data::combine(const Sales_data& rhs){
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs) {
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

std::istream& read(std::istream& is, Sales_data& sd) {
	double price = 0.0;
	is >> sd.bookNO >> sd.units_sold>>price;
	sd.revenue = price * sd.units_sold;
	return is;
}

std::ostream& print(std::ostream& os, const Sales_data& sd) {
	os << sd.bookNO <<" "<< sd.units_sold <<" "<< sd.revenue;
	return os;
}
#endif
