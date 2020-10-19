### 2.6	constexpr和常量表达式

常量表达式（const expression）指值不会改变并且在编译过程就能得到计算结果的表达式。一个对象是不是常量表达式由**数据类型和初始值**有关。有些时候需要用到常量表达式。

将变量声明为constexpr类型以便编译器来验证变量的值是否是一个常量表达式。**声明为constexpr的一定是常量表达式，而且必须用常量表达式初始化。**

```c++
constexpr int mf = 20;
constexpr int limit = mf + 1;
constexpr int sz = size();//只有当size是一个constexpr函数时才是一条正确的声明语句
```

​	constexpr声明指针时，指针的初始值必须是nullptr或者0，或者地址不变的变量。而在函数体内的变量地址会改变，所以要求变量必须在函数体外声明。

### 2.7	类型别名

两种方法进行类型别名的声明，一种是typeof ，一种是using.

```c++
typeof double wages;//wages是double的同义词
typeof wages zlq,*p;//zlq是double的同义词，p是double *的同义词
using SI = Sales_item;
```

当对引用和指针使用别名时，要额外注意

```c++
typeof char *pstring;
const pstring p;//p是指向字符变量的常量指针。
```

不能理解为指向常量字符的指针，pstring已经规定是指向字符的指针，而加了const就是对指针的修饰了。

### 2.8	auto和decltype

auto可以使我们不知道初始化值的类型就对一个变量进行初始化过程，通过初始值来推断变量的类型。在使用时应注意，一条语句中声明多个变量时，他们的初始基本数据类型应该一致。

```c++
auto i = 0,*sz = &i;//正确，都是int修饰
auto s = 0,pi = 3.14;//错误，一个int，一个double
```

当用auto进行初始化时，会忽略顶层const，保留底层const

```c++
int i = 0;
const int ci = i，&cr = ci;
auto b = ci;//b是int型
auto c = cr;//c是int型
auto d = &i;//d是int型指针
auto e = &ci;//e是指向整形常量的指针
```

如果希望推断出来是顶层const,需要在auto前加const。

对引用类型，顶层常量属性依然保留。**对初始值绑定一个引用，此时的常量就不是顶层常量了。**

```c++
auto &g = ci;//正确，整型常量引用
auto &h = 42;//错误
const auto &j = 42;//正确
```

decltype可以返回操作数的数据类型，decltype处理顶层const和引用与auto不同，如果用的表达式一个变量，直接返回该变量类型（包括顶层const和引用）

不是一个变量的情况，返回表达式结果对应的类型。如果是解引用操作，直接得到引用类型。

```c++
const int i = 0, &r = i;
decltype(i) x = 1;//x是const int类型
decltype(r) r1 = i;//r1是const int&类型
const int *p = &i;
decltype(*p) c = i//对指针进行解引用，得到的是指向的对象，const int&指针
```

并且要注意的是，如果给表达式加一个括号，就会得到引用类型。

### 2.9	编写头文件

在不同的文件中使用同一个类，就要保证类的定义一致，所以类通常被定义在头文件中。确保头文件多次包含仍然能够正常工作的技术就是**预处理器**，在编译前进行执行的一段程序，可以部分改变编写的程序。C++还有一项预处理功能是**头文件保护符**，它基于预处理变量，通过**#ifndef**查询是否没定义，**#ifdef**查询是否定义了，为真时都执行到#endif处结束，通过**#define**将一个名字设定为预处理变量。

```c++
#ifndef SALES
#define SALES
#inclue <string>
struct Sales_data{
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
#endif
```

