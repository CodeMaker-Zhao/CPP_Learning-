#ifndef CH_723
#define CH_723
#include<string>
class NoDefault {
public:
	NoDefault(int)
	{
		
	}
};
NoDefault no;
class C {
public:
	NoDefault nd;
	C(int i) :nd(i)
	{
	}
};

class Screen {
public:
	typedef std::string::size_type pos;
	Screen() = default;
	Screen(pos ht, pos wd) :height(ht), width(wd), contents(ht* wd, ' ') {}
	Screen(pos ht, pos wd, char c) :height(ht), width(wd), contents(ht* wd, c) {}
	char get() const { return contents[cursor]; }
	char get(pos ht, pos wd) const;
	Screen& set(char);
	Screen& set(pos, pos, char);
	Screen& move(pos r, pos c);
	Screen& display(std::ostream& os) { do_display(os);return *this; }
	const Screen display(std::ostream& os) const{ do_display(os);return *this; }
private:
	pos cursor = 0;
	pos width = 0, height = 0;
	std::string contents;
	void do_display(std::ostream& os) const { os << contents; }
};

inline Screen& Screen::set(char c) {
	contents[cursor] = c;
	return *this;
}

inline Screen& Screen::set(pos r, pos c, char ch) {
	contents[r * width + c] = ch;
	return *this;
}

inline char Screen::get(pos r, pos c) const {
	pos row = r * width;
	return contents[row + c];
}

inline Screen& Screen::move(pos r, pos c) {
	pos row = r * width;
	cursor = row + c;
	return *this;
}
#endif 
