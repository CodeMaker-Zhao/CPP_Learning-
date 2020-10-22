### 3.1	命令空间的Using声明

每个using声明引入命令空间的一个成员，**位于头文件中的代码，一般来说不应该使用using声明**，因为这样头文件的内容会拷贝到引用他的其他文件当中，可能会产生一些意想不到的错误。

### 3.2	String

string表示可变长的字符序列，使用前必须在头文件中include，并且string是标准库中的一部分。初始化分为**直接初始化**和**拷贝初始化**两种。直接初始化一般使用括号或者花括号的方式进行，拷贝初始化是把等号右侧的值拷贝到新创建的对象中去。一次性创建多个对象一般使用直接初始化的方式，用拷贝初始化会比较复杂。

```c++
string s1 = "hiya";
string s1(10,'c');
string s1{"hiya"};
string s1 = string(10,'c');
```

cin读入输入内容到字符串中，会忽略字符串前半部分的空白，直到读到字符才开始计数，再次读到空白就会结束。

```c++
#include <string>
using std::string;
string s;
cin>>s;//输入"   Machine Learning"，s=“Machine”
```

使用get line()方法读入，会读到换行符终止，不会忽略空格。getline(is,s)表示从is中读入一行赋给s，返回is。

string.size()返回一个string::size_type类型的数，表示字符串中字符数。

```c++
string s;
decltype(s.size()) ;
```

string对象进行比较时，如果两者完全相同，则相等，如果两者长度不同，一个string对象内容和在另外一个string对象上对应位置相同，则第一个string小于第二个string.字符上相同位置内容不同，则string对象相比按照第一个不同位的比较结果来看。

字符串与字符字面值相加时，字符字面值会转化为**字符串对象**，但是要确保加号左右至少有一个字符串对象。

### 3.3	范围For语句

```c++
for(auto c : ci){

}
```

ci是一个可迭代的序列，c是序列中中的一个变量，每次迭代会重置c。当把string对象放入范围for语句中，可以把字符串中每一个字符输出出来。**如果想要改变string对象中的字符，要用引用类型定义循环变量。**

```c++
for(auto &c: ci){

}
```

### 3.4	标准库类型vector

vector是一组对象的集合，其中所有的对象都是相同的。要使用vector，也需要引入它的头文件

```c++
#include <vector>
using std::vector;
```

vector是一个类模版，模版本身不是类或者函数，可以将模板看作为编译器生成类或函数编写的一份说明，编辑器根据模板创建类或函数的过程称为**实例化**。对vector对象进行初始化时，有几点说明，第一，使用拷贝初始化时，只能提供一个初始值，第二，如果提供的是一个类内初始值，则只能使用拷贝初始化或花括号初始化，第三，如果提供的是初始元素值的列表，则只能放在花括号里面进行初始化，不能放在圆括号。

```c++
vector<int> ivec;
vector<string> svec;
vector<vector<int>> file;//file的元素是vector对象
```

**vector是模板而不是类型，由vector生成的类型必须包含vector中元素的类型**。

```c++
vector<int> ivec(10,-1);//创建一个包含10个-1的容器
vector<string> svec(10,"hi")//创建一个包含10个hi的容器
vector<int> ivec2(ivec);//把ivec拷贝到ivec2
vector<int> ivec3(5);//创建一个包含5个int类型对象，每个都初始化为0
vector<int> ivec4{10,1};//两个int对象，一个10，一个1
vector<string> ivec5{10,"string"};//10个string对象，当花括号中的内容无法转化为相映类型时，
```

vector对象使用push_back方法进行添加对象，**在范围for循环体内部，不能对vector对象添加元素。**

**“==”操作符，vector可以用，数组不可以用**

使用范围for循环，改变循环变量值时需要用&引用。