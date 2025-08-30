# The Clockwise Spiral Rule 顺时针螺旋法则

## scene1 困惑的C/C++声明 Confusing C/C++ declarations

在C/C++中，对于简单的变量声明，可以一目了然理解它的含义。比如一个指向int的指针，一个大小为N的double数组以及一个返回float的函数。但是如果是嵌套结构的变量声明，是不是让人有点头晕目眩？

这里给大家介绍一种快速准确读懂这种复杂变量声明的含义的方法——**顺时针螺旋移动法**（Clockwise Spiral Rule）。

## scene 2 顺时针螺旋移动法 Clockwise Spiral Rule

顺时针螺旋移动法有三个步骤：

第一步以变量名作为螺旋的中心 (**Center on the variable name**)

第二步**以顺时针方向螺旋移动 (Move in a spiral clockwise direction)**，遇到方括号（数组）、圆括号（函数）和星号（指针）时，将其翻译成对应的英文或中文：比如

空方括号`[]`和方括号N`[N]`表示"array of size N of..." (**一个大小为N的...数组**)

圆括号`()` 表示 "function returning..." (**一个返回...的函数**)

星号`*` 表示"pointer to..." (**一个指向...的指针**)

第三步始终记得要先解析完括号内的所有内容再跳出括号。**重复步骤二和步骤三，直到所有符号都被解析完毕。** 

- `[]` 或 `[N]` -> "array of size N of..." (一个大小为N的...数组)
- `()` -> "function returning..." (**一个返回...的函数**)
- `*` -> "pointer to..." (**一个指向...的指针**)

## scene 3 顺时针螺旋移动法实例 Cases for Clockwise Spiral Rule

### **`int *foo[5]; `**

我们以左边变量foo的声明为例子说明顺时针螺旋移动法的操作步骤

**首先找到螺旋中心，即变量名**: `foo`

此时的位置的英语自然语义就是 foo is... 巴拉巴拉 

对应中文 foo是

接着顺时针螺旋移动 遇到 方括号5`[5]`。这是一个数组。

此时的英语自然语义就是 foo is an array of size 5 of 巴拉巴拉，

对应的中文语义就是 foo 是一个大小为5的数组...

接着再顺时针螺旋移动 遇到星号 `*`。这是一个指针。

此时的自然语义就是 foo is an array of size 5 of pointers to 巴拉巴拉

对应的中文就是 foo 是一个大小为5的数组，其元素是指向...

**最后，螺旋移动遇到类型**: `int`

那么完整的英语自然语义就是 foo is an array of size 5 of pointers to int.

相应的中文就是`foo` 是一个包含5个元素的数组，数组的每个元素都是一个指向 `int` 类型的指针。

我们用代码验证一下此法判断声明的正确性。

可以看到，`foo` 是一个包含5个元素的数组，数组的每个元素都是一个指向 `int` 类型的指针（指针数组）。

打印结果显示可以通过指针访问并修改指向的值。

### **`int (*bar)[5]; `**

再看一个括号改变优先级的声明

**首先找到螺旋中心，即变量名**: `bar`

此时的位置的英语自然语义就是 bar is... 巴拉巴拉 

由于被括号括住，顺时针螺旋移动先遇到星号 。这是一个指针。

此时的英语自然语义就是 bar is a pointer to  巴拉巴拉，

对应的中文语义就是 bar是一个指针，它指向...

跳出括号后，再顺时针螺旋移动遇到方括号5。这是一个数组。

此时的英语自然语义就是 bar is a pointer to an array of size 5 of 巴拉巴拉

对应的中文语义就是 bar是一个指针指向一个大小为5的数组

**最后，螺旋移动遇到类型**: `int`

那么完整的英语自然语义就是 bar is a pointer to an array of size 5 of ints.

相应的中文就是`bar` 是一个指针，它指向一个**一个大小为5的数组**，该数组的元素是**int**

我们用代码验证一下此法判断声明的正确性。

可以看到，`bar` 是一个指针，它指向一个包含5个 `int` 类型元素的数组（数组指针）。

打印结果显示bar指向一维数组的首地址，可通过该首地址访问数组内的元素

## scene 4 顺时针螺旋移动法自测 Self-assessment of the Clockwise Spiral Rule

### **`int *(*var[5])(void);`**

现在你是不是已经熟练掌握顺时针螺旋移动法了，那就用封面的例子自测一下吧～

**第一步：找到变量名**

`var` 是我们的起点。

> "var is..." (var 是...)

**第二步：向右移动，遇到 `[]`**

我们遇到了 `[5]`。这代表一个数组。

> "var is an array of size 5 of..." (var 是一个大小为5的数组...)

**第三步：继续螺旋移动（向左），遇到 `\*`**

我们遇到了 `*`。这代表一个指针。

> "foo is an array of size 5 of pointers to..." (foo 是一个大小为5的数组，其元素是指向...的指针)

**第四步：跳出括号，向右移动，遇到 `()`**

我们遇到了 `(void)`。这代表一个函数。

> "foo is an array of size 5 of pointers to a function returning..." (foo 是一个大小为5的数组，其元素是指向...的指针，这个指针指向一个函数，该函数返回...)

**第五步：继续螺旋移动（向左），遇到 `\*`**

我们又遇到了一个 `*`。还是一个指针。

> "foo is an array of size 5 of pointers to a function returning a pointer to..." (foo 是一个大小为5的数组，其元素是指向...的指针，这个指针指向一个函数，该函数返回一个指向...的指针)

**第六步：继续向左，遇到 `int`**

最后，我们遇到了基本类型 `int`。

> "foo is an array of size 5 of pointers to a function returning a pointer to an int." (**最终解读：foo 是一个包含5个元素的数组，数组的每个元素都是一个指针，该指针指向一个函数，这个函数没有参数 (void)，并返回一个指向 int 类型的指针。**)

### `int (*(*bar)[])();`

**第一步：找到变量名**

起点是 `bar`。

> "bar is..." (bar 是...)

**第二步：**

我们遇到了 `*`。

> "bar is a pointer to..." (bar 是一个指向...的指针)

**第三步：跳出内层括号**

我们遇到了 `[]`。这是一个没有指定大小的数组。

> "bar is a pointer to an array of unspecified size of..." (bar 是一个指针，它指向一个大小未指定的数组，该数组的元素是...)

**第四步：继续螺旋移动 (向左)**

我们遇到了外层的 `*`。

> "bar is a pointer to an array of unspecified size of pointers to..." (bar 是一个指针，它指向一个大小未指定的数组，该数组的元素是指向...的指针)

**第五步：继续螺旋移动 (向右)**

我们遇到了 `()`。这是一个函数。

> "bar is a pointer to an array of unspecified size of pointers to a function taking unspecified arguments returning..." (bar 是一个指针，它指向一个大小未指定的数组，该数组的元素是指向...的指针，这些指针指向一个函数，该函数返回...)

**第六步：最后向左移动**

我们遇到了类型 `int`。

> "bar is a pointer to an array of unspecified size of pointers to a function taking unspecified arguments returning an int."

## scene 5 const声明 declarations with const

最后我们再利用顺时针螺旋法则梳理一下四个与const相关的常量声明。

这四类常量声明无论是工程还是面试都常有涉及。分析流程和之前完全一致，动画展示了分析细节，这里不再口头赘述。

需要注意三点

第一点：T const 和 const T是等价的，其中T表示任意的基本数据类型(int double char等)

第二点：const和*号同时存在的声明中，假设变量名为p，如果const在星号的左边，则表示\*p是一个不可改变的内容，即不能修改所指向的内容但可以修改p指向的地址；如果const在星号的右边，则表示p是一个不可改变的内容，即不能修改p指向的地址但可以修改\*p的内容。如果星号的左右都有const，则表示既不能修改指向的地址也不能修改所指向的内容。

第三点：引用的底层通常也是常量指针，对于编译器而言，const int &和const int * const通常也是等价的，对于C++，偏向于使用引用而不是后者。

|                     类型                     |        含义        |   能否修改指向    | 能否修改所指内容 |
| :------------------------------------------: | :----------------: | :---------------: | :--------------: |
|    `int const&` / `const int&` (常量引用)    |   指向常量的引用   | 否 (引用天生不能) |        否        |
|           `int* const` (常量指针)            |   指针本身是常量   |        否         |        能        |
| `int const*` / `const int*` (指向常量的指针) |   指向常量的指针   |        能         |        否        |
|   `int const* const` / `const int* const`    | 指向常量的常量指针 |        否         |        否        |



###  `int const& A` / `const int& A` 

A is a reference to a const int.

`x` 是一个引用，它指向一个常量整数

### `int* const B`

B is a const pointer to an int.

B是一个常量指针，它指向一个int

### `int const* C` / `const int* C`

C是一个指针，它指向一个**常量 `int`**。

C is a pointer to a const int.

### `int const* D` / `const int* const D`

D 是一个常量指针，它指向一个**常量 `int`**。

D is a const pointer to a const int.



## scene 6 参考博客 referenced blogs

本次视频主要参考了两个外网博客，第一个博客介绍了顺时针螺旋移动法，第二个博客则给出C/C++声明和相应的英语自然语义之间的转换。本次分享我整合归纳了这两个博客中的精华部分，感兴趣的同学可以再自行浏览一下这两个博客的细节。尤其是第二个博客，对于英语不太好的程序员应该会有帮助，其他关于英语提升的方法论，也可以参考我的雅思分享。

