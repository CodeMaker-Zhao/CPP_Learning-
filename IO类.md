### 8.1	IO类

IO对象无拷贝或赋值，进行IO操作的函数通常只能以引用方式传递和返回流，读写IO对象会改变其状态，因此传递和返回引用不能是const的。

ifstream从一个给定文件读取数据，ofstream向一个给定文件写入数据，fstream可以读写给定文件。

接受一个iostream类型引用参数的函数，可以用一个对应的fstream或sstream类型来调用。

文件模式，ifstream关联的文件默认以in模式打开，ofstream关联的文件默认以输出模式打开并截断文件。