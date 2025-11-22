# Cpp_namespaces

## scene1 命名空间起源



```cpp
#include <iostream>

int main() { // using namespace 指令
    using namespace std;
    cout << "Hello, World!" << std::endl;
}
```

或

```cpp
#include <iostream>

int main() { // using 声明
    using std::cout;
    cout << "Hello, World!" << std::endl;
}
```

或

```cpp
#include <iostream>

int main() { // 完全限定名称
    std::cout << "Hello, World!" << std::endl;
}
```

你一定看到过C++ 打印Hello world的多种不同写法

这里反复出现的 `std`，就是 `cout` 对象所在的命名空间。它向编译器声明，`cout` 这一标识符定义在 C++ 自带的「标准命名空间」（Standard, `std`）内。

所谓命名空间（Namespace），是 C++ 提供的一种代码组织机制，用于**防止命名冲突**。它将函数、变量、类等标识符封装在各自的逻辑范围内。

比如，这里的`foo` 和 `bar` 命名空间都定义了 `magic_number`。借助命名空间，`foo::magic_number` 和 `bar::magic_number` 被视为两个完全独立的实体，因此可以共存且互不干扰。

```C++
#include <iostream>

namespace foo {
    constexpr int magic_number = 42; 
}

namespace bar {
    constexpr float magic_number = 3.14;
}

int main() {
    std::cout << foo::magic_number << '\n';
    std::cout << bar::magic_number << '\n';
}
```

你可能会疑惑，为什么作为C++的师祖，C语言却不采用命名空间的管理方式。(人)

因为C语言被设计为一种小而美Small and refined的可移植汇编语言，追求简洁、高效、贴近硬件，把解决命名冲突的责任**交给了程序员**，而不是语言本身。(人)

比如C语言的命名常采用添加前缀的方式，所有C的标准库的函数都遵循了这种约定，比如字符串库以str开头，文件IO库则以f开头，标准流开头则是std

C++则被设计用来构建大而杂Large and cluttered的软件系统，这类项目往往包含海量的文件和第三方库，极易造成“全局命名污染”。命名空间的引入从语言本身解决了命名冲突问题，因为这允许使用更为简洁的名称，而不是不断的添加前缀。(人)

对于命名空间，C++自带的标准命名空间为std，著名的第三方库boost，以及在计算机视觉领域的开源库OpenCV的命名空间为cv。





## scene2 基本语法

可以使用关键字namespace来声明和定义一个命名空间的内容，比如在命名空间S1中声明和定义了foo和foo1函数，在S2中则是bar函数，S3则是baz和baz1函数。

要访问命名空间内的成员，标准方式是使用作用域解析运算符 `::`，例如 `S2::bar()`。此外，C++ 提供了两种 `using` 机制。第一种是 **`using` 指令**，语法为 `using namespace namespace_name;`如 `using namespace S1;`。它将命名空间如 `S1`中的所有成员名称引入到当前作用域，允许直接调用 `foo()`和`foo1()`。

第二种是 **`using` 声明**，语法为 `using namespace_name::member_name;`如 `using S3::baz;`。它仅将特定的成员，如 `baz`引入当前作用域，允许直接使用 `baz`，而无需 `S3::` 前缀，但是你也只能访问baz，其他没有导入的成员，比如baz1是不可以访问的。

```cpp
namespace S1 {
    void foo() {}
}

namespace S2 {
    void bar() {}
}

int main() {
    using namespace S1;
    foo();
    
    S2::bar();
}
```



## scene 3 嵌套命名空间

在C++工程代码中，嵌套命名空间（Nested Namespaces）在管理大型项目时可以提供更加清晰的逻辑层次结构。嵌套命名空间允许像创建文件目录一样，对代码进行逻辑上的分组和分层。 （人）

比如，游戏引擎开发初期通常采用扁平的命名空间结构。随着项目规模扩张，为构建清晰的层次化架构，就会引入**嵌套命名空间**。嵌套命名空间通过逻辑分组与访问控制，精确界定模块边界，如有效隔离渲染与物理子系统，从而提升代码的可维护性与协作效率。

当嵌套层级过深时，C++17 提供了嵌套命名空间语法糖，允许利用 `::` 运算符在单行内声明多层命名空间，从而避免了代码的过度缩进。

```cpp
namespace GameEngine {
    class Renderer;
    class PhysicsBody;
    class Texture;
    class Shader;
    class RigidBody;
    class Collider;
    class BoundingBox;
}
```



```cpp
namespace GameEngine {
    namespace Rendering { // 渲染相关的类
        class Renderer;
        class Texture;
        class Shader;
        class Material;
    }

    namespace Physics { // 物理相关的类
        class PhysicsBody;
        class RigidBody;

        namespace Colliders { // 物理模块下的碰撞检测子模块
            class Collider;
            class BoundingBox;
            class SphereCollider;
        }
    }
}
```



```C++
namespace GameEngine {
    namespace Physics {
        namespace Colliders {
            class BoundingBox { /* ... */ };
        }
    }
}
```



```C++
namespace GameEngine::Physics::Colliders {
    class BoundingBox { /* ... */ };
} // 对应三个命名空间
```

## scene 4 inline命名空间

inline可以和namespace组合使用。(人)

inline namespace将命名空间内部的成员**自动提升**至其父命名空间的作用域中，使其可以直接被父命名空间访问。

```cpp
namespace MyLib {
    inline namespace v1 {
        int add(int a, int b);
    }
}
```

比如，命名空间内部成员add函数就可以直接通过 `MyLib::add` 来访问，**同时 `MyLib::v1::add` 这种全限定名的访问方式依然有效**。

引入 `inline namespace` 的可见性提升机制，其工程价值并非运行时的代码优化，而是为了实现动态库的**无缝版本迭代与 ABI 向后兼容**。（人）

假设这样一个代码场景，存量客户端 `app_v1` 依赖旧版库提供的整型运算接口 `add(int)`，而增量客户端 `app_v2` 需要新增的浮点运算能力`add(double)`。此时，库的开发者可以在新版动态库中利用 `inline namespace` 将浮点接口设为默认导出版本，同时在非内联命名空间中保留旧版整型实现。此时仅需删除旧的并用新的动态库进行同名替换，未重新编译的 `app_v1` 依然能通过链接器准确查找到被保留的旧版符号，从而实现无感运行；而 `app_v2` 则能在不破坏既有业务稳定性的前提下，直接链接至被提升的新版默认接口。

```
cp libMyLib_v2.dylib libMyLib_v1.dylib    
```

```
./app_v1            
```

这里省略动态库的构建过程，可以在我的github直接使用提供的 CMake 脚本进行构建。这里只需要知道**动态库** 是符号的**提供者**(函数的实现)，而 **执行体** 是符号的**使用者****(函数的调用)。app_v1（存量）和app_v2（增量）是作为客户端的执行体，Mylib_v1和Mylib_v2分别是他们所需要的动态库，需求更新后，新的动态库(MyLib_v2)同时满足了存量客户端和增量客户端的需求。更多关于动态链接详细内容可参考往期分享。



```cpp
// my_library/v1/include/math.h
namespace MyLib {
    // 一个 v1.0 的函数
    int add(int a, int b) { return a + b; }
}
```

现在，你想发布 `v2.0`。你决定对 `add` 函数进行重大“改进”，比如为了演示，你把它改成了浮点数（这是一个会破坏 ABI 的变更）：

```cpp
// my_library/v2/include/math.h
namespace MyLib {
    // v2.0 的不兼容更改
    double add(double a, double b) { return a + b; }
}
```

所有用 `v1.0` 编译的旧程序，如果现在尝试链接 `v2.0` 的库，链接器会失败（或在运行时崩溃）。因为它们期望的 `int add(int, int)` 符号（函数签名）找不到了。

你被迫告诉所有用户：“升级到 v2.0，你必须重新编译你的所有代码！”

```cpp
// my_library/v2/include/math.h
namespace MyLib {

    // v1.0 的代码，原封不动
    namespace v1 {
        int add(int a, int b) { return a + b; }
    }

    // v2.0 的新代码，标记为 inline
    inline namespace v2 {
        double add(double a, double b) { return a + b; }
    }
}
```





## scene 5 3个Tips

以上就是namespace的所有内容了，最后给大家总结三个命名空间在工程应用中简单又实用的建议：(人)

* 第一、不要在头文件（`.h` 或 `.hpp`）的顶层使用 `using namespace ...;` 指令。这会污染所有包含该头文件的文件。

* 第二、在实现文件 (`.cpp`) 中，优先使用完全限定名称，比如可以使用`std::vector` 或`using std::vector;`，而不是 `using namespace std;`

* 第三、在 .cpp 文件中，对于仅限于该文件内部使用的辅助函数或变量，使用匿名命名空间包裹，而不是将其暴露在全局。使用匿名命名空间内部的成员时，直接在当前代码文件调用即可，无须任何前缀。
