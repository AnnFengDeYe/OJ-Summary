# C++左值/右值

## scene 1 引例：减少对象复制的开销

假设你现在需要为美图秀秀开发一个滤镜功能。

即为一张具有千万像素的数码照片应用各种艺术效果，比如锐化、复古、灰度。

一个直接的想法是接口函数接受原始图像数据后 `original_photo`，创建一个它的拷贝副本`copy_image`，在这个副本上进行计算，把每个彩色像素都转换成相应的艺术效果`final_image`。

我们站在计算机的角度思考一下内存开销。假设原始的5000万像素照片对应的内存区域为A，这个区域就是一个很大的内存占用。

复制一张照片就意味着在内存中开辟一块新的空间，然后把5000万个像素的数据，一个接一个地从旧位置拷贝到新位置。这是一个非常耗时、耗费资源的操作。

然而这还只是第一步。当函数**返回**这张照片时，为了把它交给主程序，系统很可能又会创建另一个**临时副本**，这导致了第二次同样昂贵的拷贝！仅仅是一个滤镜，我们就把一张巨大的照片至少拷贝了两遍。内存区域ABC只是内存地址不同，地址对应的内容完全一样。

为了规避重复拷贝带来的性能开销，现代C++的策略不再是暴力的内存拷贝，而是利用左值右值及其引用实现的移动语义直接进行资源交接。

与其损耗系统资源开辟一个新的内存用来拷贝，不如直接将其内部存着的几千万像素数据的归属权直接拿走据为已有。这个「拿走」的过程，几乎是瞬时的。它不涉及任何数据的复制，仅仅是像交换一张名片一样，改变了对那块内存数据的所属权。

------

## scene 2 左值和右值 lvalues && rvalues

为了理解这种资源交接的策略，我们必须先理解C++ 中的左值和右值的概念。

**左值（rvalue，left-hand side）**指的是一个指向特定内存的具有名称的值，即**具名对象**。比如声明的变量，都是左值。**如果一个值有名字，那么它就是左值。**

**右值（rvalue，right-hand side）** 指的是那些临时的、短暂的表达式或值，生命周期较短，它们没有一个稳定、可识别的内存地址。右值通常代表一个计算的中间结果、一个字面量，或一个即将被销毁的临时对象。**凡是临时的、即用即弃的值，就是右值。**

```C++
int a = 1;
int b = 2;
int c = a + b;
```

比如变量a,b,c都是左值，数字1和2都是没有名字的字面值，因此是右值， 而`a+b`的结果也是右值，因为它是临时的中间值，没有名字和固定的内存地址。

根据是否存在特定的内存地址，可以使用取地址运算符&判断左值右值，可以取地址的值是左值，不可以取地址的值是右值。指针pa，pb，pc是可以打印内存地址的，但是对字面值1取地址& 则会给出报错cannot take the address of an rvalue

```c++
#include <iostream>

int main() {
    int a = 1;
    int b = 2;
    int c = a + b;

    auto *pa = &a, *pb = &b;
    std::cout << pa << std::endl << pb << std::endl;
    std::cout << ++pa << std::endl << pb;
}
```

再来看一个经典例子：

```C++
#include <iostream>

int x = 1;

int get_val() {
    return x;
}

void set_val(int val) {
    x = val;
}

int main() {
    x++;
    ++x;
    int y = get_val();
    set_val(2);

//    auto *p = &x++;
//    auto *q = &++x;
}
```

x++和++x都是自增操作，但是却是不同的值类别。其中x++是右值，因为在后置++操作中编译器首先会生成一份x值的临时复制，然后才对x递增，最后返回的是没有自加之前的那个临时副本。而++x则不同，它是直接对x递增后马上返回其自身，所以++x是一个左值。如果对它们实施取地址操作，就会发现++x的取地址操作可以编译成功，而对x++取地址就会报错。并且，由于++x是一个变量，因此是可以赋值操作的，但是x++作为一个右值，赋值就会出错。

再来看get_val函数，该函数返回了一个全局变量x，虽然变量x是一个左值（因为它有名字 x）但是它经过函数返回以后变成了一个右值。原因和x++类似，在函数返回的时候编译器并不会返回x本身，而是返回x的临时复制，所以对get_val取地址也会编译失败。对于set_val函数，该函数接受一个参数并且将参数的值赋值到x中。在main函数中调用set_val(2);实参2是一个右值，但是进入函数之后形参val却变成了一个左值，可以对val使用取地址符，所以**函数形参一定是左值**，因为它是一个有名字的变量，**如果一个值有名字，那么它就是左值**。

```C++
void set_val(int val) {
		int *p = &val;
    x = val;
}
```

有一个特例需要注意：

```c++
  auto *p = &"annfeng";
```

通常字面量都是右值，但是字符串字面量是一个左值，可以对字符串字面量取地址，说明其是左值。这是因为字符串字面量在C++中是一个**常量**字符数组，编译器会将字符串字面量存储到程序的**只读数据段**中，这个区域的数据从程序开始运行到结束都一直存在，并且每个字符串字面量在**只读数据段**都有一个独一无二的、固定的地址。

-------

## scene 3 左值引用 lvalue references

使用指针可以对左值取地址，但是指针的指向的位置是可以被任意修改，这一定程度增加了内存泄漏的风险。

```C++
#include <iostream>

int main() {
    int x = 0;
    auto *px = &x;
    std::cout << px << std::endl;
    std::cout << ++px << std::endl;
}
```

为了使C++在一定程度上脱离危险的指针，左值引用提供了解决方案，同时既有指针的高效率（底层采用指针实现），又有值传递的简洁语法。左值引用的常见场景在于希望函数能修改传入的参数。使用指针可以做到左值引用一样的效果，但引用提供了更清晰、更安全的方案。

来看一个经典的值交换的例子。

```C++
#include <iostream>

void swap_ptr(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void swap_ref(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

int main() {
    int a = 1, b = 2, c = 3, d = 4;
    swap_ptr(&a, &b);
    std::cout << "After swap_ptr: "<< a << " " << b << std::endl;

    swap_ref(c, d);
    std::cout << "After swap_ref: "<< c << " " << d << std::endl;
}
```

可以看到，引用版本的函数体和调用代码都比指针版本更简洁，且引用的对象名永远都是原对象的别名，不允许存在空引用也不允许重新绑定在别的变量上，而指针则可以存在悬空或者修改所指向地址的可能。注意，（引用版本的值交换）x = y的意思是：将别名 `y` 所代表的变量的值，赋给别名 `x` 所代表的变量。

利用左值引用来实现的交换函数中，都是非常量左值的引用，非常量左值的引用对象必须是左值，但是常量左值引用不仅可以引用左值还能引用右值。

```C++
#include <iostream>

int main() {
    int &a = 7;
    const int &b = 11;
}
```

被绑定的右值的生命周期会得到延长。引用绑定右值目前似乎并没有看到什么实际价值，但是常量左值引用的真正用途在于**复制构造函数（Copy Constructor）**和**复制赋值运算符（Copy Assignment Operator）**的形参。

```C++
#include <iostream>

class X {
public:
    X() {
        std::cout << "Default constructor called." << std::endl;
    }

    X(const X& other) {     // 复制构造函数
        std::cout << "Copy constructor called." << std::endl;
    }

    X& operator=(const X& other) {     // 复制赋值运算符
        std::cout << "Copy assignment operator called." << std::endl;
        return *this;
    }
    ~X() {}
};

X make_x() {
    std::cout << "--- Entering make_x function ---" << std::endl;
    return X(); // 创建并返回一个 X 的临时对象 注意：这里现代编译器会使用 RVO (返回值优化)
}

int main() {
    std::cout << "1. X x1;" << std::endl;
    X x1; // 调用默认构造函数

    std::cout << "\n2. X x2(x1);" << std::endl;
    X x2(x1); // 调用复制构造函数

    std::cout << "\n3. X x3(make_x());" << std::endl;
    X x3(make_x()); // 调用 make_x() 函数来初始化 x3

    std::cout << "\n4. x3 = make_x();" << std::endl;
    x3 = make_x();

    return 0;
}
```

来看一个类的定义的例子：为了更加直观的演示常量左值引用在类中的应用方式，这里需要添加命令行参数-fno-elide-constructors来禁用RVO返回值优化后，这是因为gcc的RVO优化会减少复制构造函数的调用。

我们看一下这段代码的运行结果，其中X x3(make_x());会调用一次默认构造函数和两次复制构造函数，默认构造函数在make_x函数内部调用，调用后在make_x()返回时会第一次调用复制构造函数，第二次是`main`函数拿到了函数返回的结果，X x3(...)会调用第二次复制构造函数。同理，x3 = make_x();则会调用一次默认构造函数，一次复制构造函数，一次拷贝赋值构造函数。

那么这里的**复制构造函数（Copy Constructor）**和**复制赋值运算符（Copy Assignment Operator）**为什么要使用常量左值引用呢？

首先，常量形参则意味着被引用的对象不能被修改，这也符合被复制的值（**x1和make_x()的返回值**）不应该被修改的自然语义。其次

**对于复制构造函数`X(const X&)`**：如果它的参数不是引用，而是按值传递 `X(X other)`。当调用这个构造函数时，比如 声明一个类型为 `X` 的对象 `x3`，并用 `x1` 对其进行初始化`X x3(x1);`，为了将 `x1` 传递给 `other`，需要先为 `other` 创建一个 `x1` 的副本。但如何创建副本呢？又需要调用复制构造函数！这就导致了**无限递归**，程序会因栈溢出而崩溃。因此，复制构造函数的参数**必须**是引用类型。

**对于复制赋值运算符 `X& operator=(const X&)`：** 虽然在这里使用值传递不会导致无限递归，但每次赋值都需要先拷贝一个临时对象，然后再从这个临时对象拷贝到 `*this`，也就是通过 `*this` 来访问和修改左边对象的数据成员，但这完全是没必要的开销。使用引用可以直接操作原始对象，避免了这次多余的拷贝。

-------

## scene 4 右值引用和移动语义 rvalues ref && move semantics

既然有左值引用，是不是也会有右值引用呢？有的 兄弟

在左值引用声明中，需要在类型后添加一个符号与&，而右值引用则是在类型后添加两个符号与

```c++
#include <iostream>

int main() {
    int a = 0;
    int &b = a;
    int &&c = 2;

    std::cout << "value of lvalue reference: " << b <<std::endl;
    std::cout << "value of rvalue reference: " << c <<std::endl;
}
```

上一节可以发现，C++中很多操作都会产生临时的、没有名字的“右值”对象，比如函数的**按值返回**，表达式计算的**中间结果**。左值引用并不能规避对象拷贝的开销，但是右值引用可以实现C++11中最核心的**移动语义**，从而在处理临时对象时，用高效的资源窃取（移动语义）取代昂贵的深度拷贝，极大地提升程序性能。

```C++
#include <iostream>
#include <vector>
#include <chrono>
#include <cstring>

class X {
private:
    char* image; // 模拟一个昂贵的资源
    static const size_t IMAGE_SIZE = 2048; // 2KB大小

public:
    // 默认构造函数：分配资源
    X() {
//         std::cout << "Default constructor." << std::endl;
        image = new char[IMAGE_SIZE];
    }

    // 析构函数：释放资源
    ~X() {
        delete[] image;
    }

    // ------------------- 拷贝语义 -------------------

    // 1. 复制构造函数 (昂贵的深度拷贝)
    X(const X& other) {
        std::cout << "Copy constructor (expensive deep copy)." << std::endl;
        image = new char[IMAGE_SIZE];
        memcpy(this->image, other.image, IMAGE_SIZE); // 逐字节复制数据
    }

    // 2. 复制赋值运算符 (昂贵的深度拷贝)
    X& operator=(const X& other) {
        std::cout << "Copy assignment (expensive deep copy)." << std::endl;
        if (this == &other) {
            return *this;
        }
        delete[] image; // 释放旧资源
        image = new char[IMAGE_SIZE];
        memcpy(this->image, other.image, IMAGE_SIZE); // 复制新资源
        return *this;
    }

    // ------------------- 移动语义 -------------------

    // 3. 移动构造函数 (高效的资源窃取)
    X(X&& other) noexcept {
//        std::cout << "Move constructor (cheap pointer swap)." << std::endl;
        this->image = other.image; // 1. 偷走源对象的指针
        other.image = nullptr;     // 2. 将源对象指针置空，避免它析构时释放资源
    }

    // 4. 移动赋值运算符 (高效的资源窃取)
    X& operator=(X&& other) noexcept {
        std::cout << "Move assignment (cheap pointer swap)." << std::endl;
        if (this == &other) {
            return *this;
        }
        delete[] image; // 释放自己的旧资源
        this->image = other.image; // 1. 偷走源对象的指针
        other.image = nullptr;     // 2. 将源对象指针置空
        return *this;
    }
};

// 一个返回大量 X 对象的函数
std::vector<X> make_bunch_of_x(size_t count) {
    std::vector<X> vec;
    vec.reserve(count); // 预分配内存，避免vector扩容时的额外开销
    for (size_t i = 0; i < count; ++i) {
        vec.push_back(X()); // push_back 会创建临时对象，触发移动或拷贝
    }
    return vec;
}

int main() {
    const size_t NUM_OBJECTS = 1000;
    auto start_move = std::chrono::high_resolution_clock::now();

    // make_bunch_of_x 返回一个右值 (临时vector)
    // 将其赋值给 images 会触发 vector 的移动构造函数
    // vector 的移动构造函数会逐个移动其内部的 X 对象，调用 X 的移动构造函数
    std::vector<X> images = make_bunch_of_x(NUM_OBJECTS);

    auto end_move = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_move = end_move - start_move;

    std::cout << "\nRESULT WITH MOVE: Vector has " << images.size() << " objects." << std::endl;
    std::cout << "TIME TAKEN: " << duration_move.count() << " ms\n" << std::endl;

    return 0;
}
```

现在，来看一下引入右值引用，即移动语义之后的代码（代码背景为引例中的图像处理）。相比于拷贝语义，移动语义不再是将被复制的对象原封不动的拷贝一遍，而是直接将作为右值的临时对象直接拿走，将原来的被复制的对象内容直接掏空。

需要注意的是，如果传入的实参是左值，那么编译器只会使用拷贝语义下的构造函数，如果参数是一个右值时，编译器会优先选择移动构造函数，也可以选择拷贝构造函数。

| 传入的实参类型              | 匹配 `X(const X&)` | 匹配 `X(X&&)` | 最终调用的函数   |
| --------------------------- | ------------------ | ------------- | ---------------- |
| **左值** (e.g., `X x1`)     | **完美匹配**       | 匹配失败      | **复制构造函数** |
| **右值** (e.g., `make_x()`) | 可用匹配           | **完美匹配**  | **移动构造函数** |

我们可以比较一下拷贝语义和移动语义的性能，保留移动语义时会优先调用移动构造函数和移动赋值运算符；当注释掉移动语义部分的代码后，编译器会自动调用拷贝语义下的代码。可以发现，移动语义比拷贝语义节省了更多的时间开销，且这个节省的开销会和被移动对象的大小成正相关。

注意到移动语义的代码需要noexcept关键字，这个关键字的作用是什么呢？试想这样一种情况，如果移动数据容器中的某部分数据时，`X`的移动构造函数**抛出了异常**，此时数据容器中的数据就可能一部分元素在新内存，一部分元素在旧内存。 容器中的数据已经损坏，无法回滚到初始状态！而noexcept则告诉编译器已经百分之百确定移动操作不会抛出异常的情况下，编译器才敢使用移动构造函数。否则，为了安全，如果没有使用noexcept声明异常安全，编译器宁愿选择慢一点的拷贝语义。

------

## scene5 左值的移动语义 move semantics for lvalues

既然右值可以通过移动语义减少开销，那么左值能否实现移动语义呢？可以的，兄弟。

我们已经知道，右值引用只能绑定右值，如果尝试绑定左值,会导致编译错误，但是可以通过static_cast将其强制转换为右值引用。强制右值引用转换不会改变变量a的生命周期和内存地址，但是可以让左值也能使用移动语义。右值引用也相当于被引用对象的别名，这一点和左值引用是一样的，即无论是左值引用还是右值引用，**引用即别名**，**一旦绑定，不可更改。**

注意，为了防止数据的意外丢失，左值是不能被【隐式】移动的。但程序员可以通过 `std::move` 将左值【显式地】转换为右值引用，从而允许编译器对其执行移动操作。

```C++
#include <iostream>

int main() {
    int a = 0;
    int &&b = static_cast<int &&>(a);

    std::cout << "Value of a: " << a << std::endl;
    std::cout << "Value of b: " << b << std::endl;

    std::cout << "Address of a (&a): " << &a << std::endl;
    std::cout << "Address of b (&b): " << &b << std::endl; // 给出它所引用的对象的地址

    b = 100; // 通过别名 b 修改值
    std::cout << "After b = " << b << ", a is now: " << a << std::endl; // a 的值也变了

    return 0;
}
```

试想这样一个代码场景，视频博主「安枫的叶」想要修改他的名字。

代码定义了一个string对象，初始值为"安枫的叶"。在使用左值的拷贝语义后，uploader_name对象中的内容不会有任何变化。

然而在移动语义的场景下，代码明确表示不再需要 uploader_name 的内容了，将uploader_name中的内容交接给 new_name，std::move函数将左值 uploader_name 转换为右值引用，移动后，uploader_name 中的内容就像被“掏空”一样。

std::move的底层实现其实也就是static_cast的强制类型转换，表达式std::move(uploader_name)返回值是一个右值。被移动后的对象处于“有效但未指定”的状态。对string对象来说通常是空字符串。不应该再依赖一个被移动后的对象的值，但可以给这个对象赋新值。

```C++
#include <iostream>
#include <string>
#include <vector>
#include <utility> // 必须包含 <utility> 才能使用 std::move

int main() {
    std::string uploader_name = "安枫的叶";

    // 场景1：拷贝左值
    std::string uploader = uploader_name;
    std::cout << "After copy:" << std::endl;
    std::cout << "  uploader: " << uploader << std::endl;
    std::cout << "  uploader_name: " << uploader_name << std::endl;

    std::cout << "-------------------------" << std::endl;

    // 场景2：从左值移动
    std::string new_name = std::move(uploader_name);

    std::cout << "After move:" << std::endl;
    std::cout << "  new_name: " << new_name << std::endl;
    std::cout << "  uploader_name: " << uploader_name << std::endl;
    
    uploader_name = "Ann Feng";
    std::cout << "uploader name after re-assignment: " << uploader_name << std::endl;
}
```



------

## scene6 值类别总结 value categories

最后，我们来总结一下前面所讲的全部内容

首先是左值和右值的基本概念

**如果一个值有名字，那么它就是左值。**即左值都是有名字的实体。

**凡是临时的、即用即弃的值，就是右值。**右值是没有名字的临时值。

为了减少拷贝所带来的额外内存开销，C++ 11之后引入了移动语义。C++ 11中，具有名字和能否移动是两个独立的属性。用横纵坐标表示值的属性，横轴是值是否具有名字，纵轴为是否可以移动。

移动语义移动的是【右值】所代表的对象的资源，因此右值一定是可以被移动的，坐标系右上角既是右值又不能移动的格子是不可能的。**右值**主要有两种来源：一个天生临时的**【纯右值】**，比如函数返回值或临时对象。另外一个是被 `std::move` 显式转换过的**【左值】**，而这个左值也是有名字的，但是在被转换后，`std::move`的返回值是一个右值，又称为将亡值xvalue，x是expire的意思。而一个天生临时的**【纯右值】**又称为pure right value（pure rvalue）。

pure right value和xvalue一起被称为rvalue。而lvalue和xvalue一起则被称为generalized left value（generalized lvalue）。

作为程序员，我们不太需要知道这些专业术语的细分。只需要知道不能直接应用移动语义的是左值，可以移动的是右值就可以了。

接着，我们介绍了左值引用和右值引用。注意，无论是左值引用 `&` 还是右值引用 `&&`，引用的本质都是一个**别名（alias）**。它不是一个新对象，它只是一个已存在对象的另一个名字，因此，左值引用和右值引用都是左值。

OK，以上就是移动语义 左值右值及其引用的全部内容了，如果大家觉得不错的话希望能给个一键三连，这对我真的很重要。有什么疑问或者其他想看的内容都可以在评论区留言，我们下期再见！

