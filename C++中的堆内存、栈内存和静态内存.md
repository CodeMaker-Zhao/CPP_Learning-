# C++中的堆内存、栈内存和静态内存

C++中的空间主要分为三类，堆内存、栈内存和静态内存，其中静态内存用来存储全局对象（定义在任何函数之外的对象）、局部static对象、类static数据成员，栈内存用于保存定义在函数之内的非static对象。静态内存和栈内存中的对象，所占用的空间都是由编译器自动的创建和销毁的。而除此之外，还有一种内存，是由我们来动态分配的，它就是**堆内存**。堆内存中的对象由我们手动创造，并且需要我们手动**delete**，如果忘记delete就会造成内存泄漏的情况。

下面的例子是在侯捷老师的C++课程中所举的，在这里我还是通过这个例子来说明内存的分配。我们创建两个类，分别是Complex和String，他们的定义如下。

```c++
class Complex{
public:
  Complex(int r=0,int v=0):ri(r),vi(v){};
private:
  int ri=0,vi=0;
}
class String{
public:
  String(const char* str=0){
  	if (str){
        s_data = new char[strlen(str)+1];
        strcpy(s_data,str);
    }else{
        s_data = new char[1];
        *s_data = '\0';
    }
  }
  ~String();
private:
  char * my_data;
}

```

这里主要为了说明原理，先不对拷贝构造、拷贝赋值和析构函数进行声明。

当我们在函数中动态分配一段内存给我们的对象时。

```c++
int main(){
  /*这样四个指针都是指向堆内存的，他们在堆内存上根据类的大小而获得内存的，其中new的过程分为三步，第一步是在堆内存中创建指定大小的内存空间，此时调用了operator new，在new操作符中由调用了malloc函数进行空间的分配，第二步是将返回的空间由void*转化为指定类型指针，第三步是调用类的构造函数进行初始化。*/
	Complex * ci = new Complex();
  String * si = new String();
  Complex * cm = new Complex[10];
  String * sm = new String[10];
  
  delete ci;
  delete si;
  delete [] cm;
  delete [] sm;
  /*delete过程分为两部，第一步是调用析构函数，如int这种内置类型没有析构函数，而很多类的对象都有自己的析构函数，第二步是释放内存，调用operator delete，在delete操作符中调用free()函数，释放内存。*/
}
```

  分配动态数组和单个对象的区别主要有以下几个部分，对于动态数组，用**new typename [N]**进行动态空间分配，删除时也要配合**delete []**，这是一定要牢记在心的。那为什么要这么做呢？这是因为在**new [N]**时分配了至少N个大小为类大小的空间给象，**delete[]**在告诉编译器我们要删除的是多个空间，而不是一个。而**delete**和**delete[]**在释放内存的步骤是没有什么区别的，都是将对象所指的堆内存进行释放，区别就是在第一步，delete调用一次析构函数，而delete[]调用N次析构函数。

当我们用delete和delete[]处理指向Complex类对象的指针时，其实是没有什么区别的，因为int类型的数没有析构函数，所以还是成功的释放了内存。但是对于String类就不一样了，如果我们使用delete,那么只调用了一次析构函数，剩下的没有调用析构函数，下面给出String类的析构函数。

```c++
String::~String(){
  delete [] s_data;
}
```

在析构函数中我们delete了s_data指针，对它所指的内存进行了释放。

所以如果我们使用delete sm而不是delete [] sm，那么在整个过程中只调用了一次析构函数，剩下9个s_data指针所指向的堆内存都没有正确的进行释放，这里借用一下侯老师的图，更方便理解。![截屏2020-11-19 下午3.51.09](/Users/zhaoliqun/Library/Application Support/typora-user-images/截屏2020-11-19 下午3.51.09.png)

所以说错误使用delete和delete[]并不是delete的指针内存没有进行释放，而是指针所指空间内的**指向其他堆内存的指针没有正确的释放。**

在听完侯老师的课之后，我又自己瞎想了一下，写了下面的一段代码。

```c++
using namespace  std;
class Node{
public:
    int i=1;
    ~Node(){
        cout<<"dx"<<endl;
    }
};
class s{
public:
    s(){
        Node fnode;
        n = &fnode;
    }
    Node* n;
};
int main(){
    s* ps = new s[10];
    cout<<ps->n->i;
}
/*result=
dx
dx
dx
dx
dx
dx
dx
dx
dx
dx
1
*/
```

在我的认知中，最后一段代码应该出问题，因为我将n指向了一个局部变量，但是最后的结果却是如上图所示。经过在网上查找资料，我按照自己的理解来解释一下整个过程。

编译器会如何处理这段**s* ps = new s[10]**语句呢，首先编译器在堆内存中给分配了储存10个s类对象的空间，再转化为s的指针类型，赋值给ps，最后调用10次s的构造函数，此时构造函数是被压入栈中，上面的fnode都是在栈中创建的，当fnode离开了这个构造函数的作用域后，就直接调用它的析构函数。

为什么析构函数明明被调用了但是我们仍然能通过n访问到i呢？

此时我们的n指向的是栈内存中的一段空间，打个比方说，你通过n获得了栈内存中的一段空间，此时n就是你的钥匙，空间就是你的房子，在你重新访问之前，编译器可以对你所指的空间进行覆盖，它可以把这个房子里面所有的家具都换掉，但是如果它没有覆盖这段空间，你就可以重新非法的进入这个房子，而这个房子里面的家具跟你出去的时候还是一样的。C++完全可以把你用过的栈空间全部清零，但是没有必要这样做，因为这样做会花费额外的时间。

C++允许你这样做，但这并不意味着这样做是对的，这种未定义的行为是所有行为中最为危险的。



参考来源：1、侯捷 C++面向对象高级编程 https://www.bilibili.com/video/BV14s411E772?t=2411&p=8

​					2、Stackoverflow 

​					https://stackoverflow.com/questions/6441218/can-a-local-variables-memory-be-accessed-outside-its-scope

