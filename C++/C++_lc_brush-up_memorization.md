# C++\_lc\_brush-up\_memorization

## ASCII码

只需要记住下面三个字符的ASCII码，它们是各自区间的“起点”：

- **'0' = 48** (数字的起点)
- **'A' = 65** (大写字母的起点)
- **'a' = 97** (小写字母的起点)
- 大小写字母之间的差值是 **32** (`'a' - 'A' = 97 - 65 = 32`)。

B的ASCII码是 65 + (2 - 1) = 66

W的ASCII码是 65 + (23 - 1) = 87

## 溢出判断

判断一个以科学记数法表示的数是否会导致 `int` 类型溢出：

关键阈值：大约 $2×10^9$ (二十亿)

**C++:** `int` 通常是 32 位有符号整数。其范围大约是 $-2×10^9$ 到 $2×10^9$(更精确地说是 $[−2^{31},2^{31}−1]$，即 [−2147483648,2147483647])。

判断一个以科学记数法表示的数是否会导致 `long long` 类型溢出：

关键阈值：大约 $9×10^{18}$ 

* `10^9 * 10^9 = 10^{18}`，两个 `int` 最大值的乘积正好在 `long long` 的范围内。

## C++容器类的通用方法

1. **构造、析构与赋值 (Construction, Destruction, and Assignment)**

|         方法／操作符          | 描述                                                         |  通用性  |
| :---------------------------: | ------------------------------------------------------------ | :------: |
|         `Container()`         | 默认构造函数。创建一个空的容器。                             | 所有容器 |
|      `Container(other)`       | 拷贝构造函数。创建 other 的一个副本。                        | 所有容器 |
| `Container(std::move(other))` | 移动构造函数（C++ 11）。接管 other 的资源， other 进入有效但未指定状态。 | 所有容器 |
|     `Container{a, b, c}`      | 初始化列表构造函数（C++ 11）。用 `{...}` 中的元素初始化容器。 | 所有容器 |
|        `~Container()`         | 析构函数。销毁容器及其所有元素。                             | 所有谷器 |
|      `operator=(other)`       | 拷贝赋值。将 other 的内容复制到当前容器。                    | 所有容器 |
| `operator=(std::move(other))` | 移动赋值（C++ 11）。接管 other 的资源。                      | 所有容器 |

当然。C++ 标准库（STL）的容器设计得非常出色，它们共享一套丰富的通用接口（方法），这使得学习和使用它们变得更加容易，并且是泛型编程的基石。

以下是 C++ 容器中最核心和通用的方法，按功能分类进行说明。

------



### 1. 构造、析构与赋值 (Construction, Destruction, and Assignment)

这些方法负责容器的生命周期管理和内容复制/移动。

|          方法/操作符          |                             描述                             |    通用性    |
| :---------------------------: | :----------------------------------------------------------: | :----------: |
|         `Container()`         |               默认构造函数。创建一个空的容器。               | **所有容器** |
|      `Container(other)`       |            拷贝构造函数。创建`other`的一个副本。             | **所有容器** |
| `Container(std::move(other))` | 移动构造函数 (C++11)。接管`other`的资源，`other`进入有效但未指定状态。 | **所有容器** |
|     `Container{a, b, c}`      | 初始化列表构造函数 (C++11)。用 `{...}` 中的元素初始化容器。  | **所有容器** |
|        `~Container()`         |               析构函数。销毁容器及其所有元素。               | **所有容器** |
|      `operator=(other)`       |          拷贝赋值。将`other`的内容复制到当前容器。           | **所有容器** |
| `operator=(std::move(other))` |            移动赋值 (C++11)。接管`other`的资源。             | **所有容器** |



### 2. 容量与大小 (Capacity and Size)

这些方法用于查询容器中有多少元素。

|     方法     |                         描述                         |    通用性    |
| :----------: | :--------------------------------------------------: | :----------: |
|  `empty()`   | 检查容器是否为空。**（推荐使用此方法检查是否为空）** | **所有容器** |
|   `size()`   |                返回容器中元素的数量。                | **所有容器** |
| `max_size()` |         返回容器理论上能容纳的最大元素数量。         | **所有容器** |



### 3. 迭代器 (Iterators)

迭代器是访问容器元素的通用指针式接口，是 STL 算法的基石。

|          方法           |                            描述                            |           通用性           |
| :---------------------: | :--------------------------------------------------------: | :------------------------: |
|   `begin()` / `end()`   |        返回指向容器第一个元素和“尾后”位置的迭代器。        |        **所有容器**        |
|  `cbegin()` / `cend()`  | (C++11) `const`版本的 `begin/end`，返回 `const_iterator`。 |        **所有容器**        |
|  `rbegin()` / `rend()`  | 返回指向容器反向序列的第一个元素和“尾后”位置的反向迭代器。 | **序列容器和有序关联容器** |
| `crbegin()` / `crend()` |           (C++11) `const`版本的 `rbegin/rend`。            |          **同上**          |



### 4. 修改器 (Modifiers)

这些方法用于改变容器的内容。其中一些方法名称通用，但用法可能因容器类型而异。

|     方法      |                             描述                             |        通用性        |
| :-----------: | :----------------------------------------------------------: | :------------------: |
|   `clear()`   |            移除容器中的所有元素，使其大小变为 0。            |     **所有容器**     |
| `swap(other)` | 将当前容器的内容与另一个同类型容器 `other` 的内容进行交换。效率极高。 |     **所有容器**     |
| `insert(...)` |                在指定位置插入一个或多个元素。                | **通用，但用法各异** |
| `erase(...)`  |                     移除一个或多个元素。                     | **通用，但用法各异** |



### 5. 元素访问 (Element Access)

这些方法用于获取容器中的单个元素。

|   方法    |            描述            |                    通用性                    |
| :-------: | :------------------------: | :------------------------------------------: |
| `front()` |  返回对第一个元素的引用。  |               **所有序列容器**               |
| `back()`  | 返回对最后一个元素的引用。 | `vector`, `list`, `deque`, `string`, `array` |

**注意**: `std::map` 和 `std::set` 等关联容器没有 `front()` 和 `back()` 方法。要访问它们的第一个元素，应使用迭代器 `container.begin()`。

### 6. **容器的insert函数**

|                  容器类型                  |    核心特性    |   `insert()` 返回值    |
| :----------------------------------------: | :------------: | :--------------------: |
|                `set`, `map`                |  有序，键唯一  | `pair<iterator, bool>` |
|      `unordered_set`, `unordered_map`      |  无序，键唯一  | `pair<iterator, bool>` |
|           `multiset`, `multimap`           | 有序，键可重复 |       `iterator`       |
| `unordered_multiset`, `unordered_multimap` | 无序，键可重复 |       `iterator`       |
|         `vector`, `deque`, `list`          |    序列容器    |       `iterator`       |



## `std::unordered_map`

```C++
#include <unordered_map>

// 声明
unordered_map<KeyType, ValueType> map_name;

// 插入元素
map_name[key] = value;  // 或
map_name.insert({key, value});  // 或
map_name.insert(make_pair(key, value));

// 访问元素
ValueType val = map_name[key];  // 注意：如果key不存在，会创建它并赋默认值

// 检查键是否存在
if (map_name.find(key) != map_name.end()) { /* 键存在 */ }
if (map_name.count(key) > 0) { /* 键存在 */ }

// 删除元素
map_name.erase(key);

// 元素个数
int size = map_name.size();
```

当使用**下标运算符 `[]`** 来访问一个不存在的键（key）时，这个键会被**自动插入**到 map 中，并且其对应的值（value）会被**值初始化（value-initialized）**。对于 `int` 这种基本数据类型，值初始化的结果就是 **`0`**。

只想**查询**一个键是否存在而不希望修改 map 时，应该使用 `.find()` 或 `.count()` 方法。如果你确定一个键应该存在，并且希望在它不存在时得到一个错误，那么应该使用 `.at()` 方法，因为它会抛出异常。

## 与map相关的迭代器

在C++中，当你遍历一个存储键值对（key-value pairs）的关联式容器时，比如 `std::map` 或 `std::unordered_map`，解引用（dereference）迭代器得到的并不是一个单一的值，而是一个 `std::pair` 对象。这个 `std::pair` 对象包含了键和值。`it->first` 指向这个键值对的**键（key）**。`it->second` 指向这个键值对的**值（value）**。这里的 `it->first` 是 `(*it).first` 的语法糖。

```C++
#include <iostream>
#include <map>
#include <string>

int main() {
    // 创建一个 map，键是 string (商品)，值是 double (价格)
    std::map<std::string, double> price_list;

    // 添加商品和价格
    price_list["苹果"] = 5.5;
    price_list["香蕉"] = 3.0;
    price_list["樱桃"] = 20.0;

    // 1. 经典用法：使用迭代器遍历 map
    std::cout << "--- 价格清单 (使用迭代器) ---\n";
    for (auto it = price_list.begin(); it != price_list.end(); ++it) {
        // it->first  是键 (商品名)
        // it->second 是值 (价格)
        std::cout << it->first << ": " << it->second << " 元" << std::endl;
    }

    // 2. 现代 C++ 更常见的用法：基于范围的 for 循环
    std::cout << "\n--- 价格清单 (使用范围for循环) ---\n";
    for (const auto& item : price_list) {
        // item 是一个 const std::pair<const std::string, double>&
        // item.first  是键
        // item.second 是值
        std::cout << item.first << ": " << item.second << " 元" << std::endl;
    }

    // 3. 查找并访问
    auto search = price_list.find("苹果");
    if (search != price_list.end()) {
        std::cout << "\n查找商品: " << search->first << ", 价格: " << search->second << " 元" << std::endl;
        
        // 修改值
        search->second = 6.0; // 苹果涨价了
        std::cout << "苹果的新价格: " << search->second << " 元" << std::endl;
    }

    return 0;
}
```



## `std::vector`

在C++的STL容器中，当你声明一个容器对象后，即使不进行显式赋值，它也已经是一个完全初始化的对象。这是C++语言的设计特点，也是STL容器的标准行为。

1. **默认构造函数的作用**：当你声明一个STL容器如`vector<int> v;`时，这会调用该容器的默认构造函数，创建一个空的但完全有效的容器对象。

2. **内存分配**：尽管容器内部没有元素，但容器对象本身已经分配了必要的内存来存储其内部数据结构（比如指针、大小计数器等）。

3. **可立即使用**：这些新声明的容器可以立即调用其所有成员函数，如`push_back()`、`insert()`、`size()`等。

4. 常见STL容器的默认状态：
   - `vector<T>` - 空数组 `[]`，大小为0
   - `list<T>` - 空链表，大小为0
   - `map<K,V>` - 空映射 `{}`，大小为0
   - `set<T>` - 空集合，大小为0
   - `queue<T>` - 空队列
   - `stack<T>` - 空栈
   - `deque<T>` - 空双端队列

5. **元素访问**：`front()` 和 `back()` 函数提供对容器中第一个和最后一个元素的**直接访问**。它们返回的是元素的**引用 (reference)**。这意味着你不仅可以读取该元素的值，还可以通过这个引用直接修改它。在**空容器**上调用 `front()` 或 `back()` 会导致**未定义行为 (undefined behavior)**。**`end()`**: 返回一个指向容器**尾端之后 (past-the-end)** 位置的迭代器。`end()`与 `begin()` (指向第一个元素的迭代器) 配合使用，来定义一个需要处理的元素区间 `[begin, end)`。

   因为 `end()` 返回的迭代器不指向任何实际元素，所以**绝对不能对它进行解引用 (dereference)** 操作（即不能使用 `*` 运算符）。

这与一些其他语言不同，在某些语言中，你必须显式初始化容器才能使用它们。C++的这种行为使得代码更简洁，也更符合**RAII (Resource Acquisition Is Initialization)** 原则，即资源获取即初始化的设计理念。

**创建和初始化**

```C++
// 创建空向量
vector<int> nums;

// 创建指定大小的向量，所有元素初始化为0
vector<int> nums(5, 0);  // {0, 0, 0, 0, 0}

// 使用初始化列表
vector<int> nums = {1, 2, 3, 4, 5};

// 创建二维向量（3行4列，全部初始化为0）
vector<vector<int>> matrix(3, vector<int>(4, 0));

// 从另一个向量复制
vector<int> nums2(nums);  // 复制 nums 的所有元素
```

**增加和访问元素**

```C++
vector<int> nums;

// 在末尾添加元素
nums.push_back(10);  // {10}
nums.push_back(20);  // {10, 20}

// 使用下标访问（从0开始）
int val = nums[0];  // 10
nums[1] = 25;       // 修改为 {10, 25}

// 使用at()方法（带边界检查）
int val2 = nums.at(1);  // 25

// 前后元素
int first = nums.front();  // 10
int last = nums.back();    // 25
```

`emplace_back` 作用也是在容器的末尾添加一个新元素。其核心特点是**就地构造 (in-place construction)**，即直接在容器的内存空间里创建这个元素，从而避免了不必要的临时对象的生成。这使得它在多数情况下比 `push_back` 更高效。

`emplace_back` 与 `push_back` 的最核心的区别在于新元素的创建方式。**`push_back`**: 这个函数接受一个**已经构造好的对象**（或一个临时对象）。然后，它将这个对象通过**拷贝 (copy)** 或**移动 (move)** 的方式放入容器的存储空间中。**`emplace_back`**: 这个函数接受的是用来**构造对象所需的参数**。它将这些参数直接转发给对象的构造函数，在容器的最终存储位置上「就地」把对象构建出来。 `emplace_back` 省去了创建临时对象以及后续拷贝/移动的中间步骤，对于复杂的对象，这能带来显著的性能提升。

当你手上只有**用于构造对象的原始参数**时，使用 **`emplace_back`**。它更直接，也通常更快。

```C++
// 参数是 "橘子" 和 30
my_vector.emplace_back("橘子", 30);
```

当你手上已经有一个**现成的对象**，希望将其副本或本身放入容器时，使用 **`push_back`**。

```C++
Item existing_item("葡萄", 40);
// 你已经有了对象，所以用 push_back
my_vector.push_back(existing_item); // 这里会拷贝对象
```

**删除元素**

```C++
vector<int> nums = {1, 2, 3, 4, 5};

// 删除末尾元素
nums.pop_back();  // {1, 2, 3, 4}

// 删除特定位置的元素
nums.erase(nums.begin() + 1);  // 删除索引1的元素，结果为 {1, 3, 4}

// 删除一个范围内的元素
vector<int> nums2 = {10, 20, 30, 40, 50};
nums2.erase(nums2.begin() + 1, nums2.begin() + 3);  // 删除索引1到2，结果为 {10, 40, 50}

// 清空所有元素
nums.clear();  // {}
```

**迭代**

```C++
vector<int> nums = {1, 2, 3, 4, 5};

// 使用索引
for (int i = 0; i < nums.size(); i++) {
    cout << nums[i] << " ";
}

// 使用范围for循环（C++11）
for (int num : nums) {
    cout << num << " ";
}

// 使用迭代器
for (auto it = nums.begin(); it != nums.end(); ++it) {
    cout << *it << " ";
}
```

**排序**

```C++
vector<int> nums = {5, 2, 8, 1, 9};

// 升序排序
sort(nums.begin(), nums.end());  // {1, 2, 5, 8, 9}

// 降序排序
sort(nums.begin(), nums.end(), greater<int>());  // {9, 8, 5, 2, 1}

// 自定义排序
sort(nums.begin(), nums.end(), [](int a, int b) {
    return abs(a) < abs(b);  // 按绝对值排序
});
```

##  `std::pair` 

```C++
#include <iostream>
#include <string>
#include <utility>  // std::pair, std::make_pair
#include <vector>
#include <map>

// ===================================================================
// 用法 2: 作为函数的返回值
// 函数模拟根据用户ID查找状态，返回一个包含查找结果(bool)和状态信息(string)的pair
// ===================================================================
std::pair<bool, std::string> getUserStatus(int userId) {
    if (userId == 101) {
        return std::make_pair(true, "用户在线");
    }
    return {false, "用户不存在或离线"}; // C++11风格的返回
}

int main() {
    std::cout << "--- 1. 基本创建与访问 ---\n";
    auto book = std::make_pair("C++ Primer", 99.9);
    std::cout << "书名: " << book.first << ", 价格: " << book.second << std::endl;
    book.second = 89.9; // 修改价格
    std::cout << "修改后价格: " << book.second << std::endl;
    std::cout << "\n";

    // ===================================================================
    
    std::cout << "--- 2. 处理函数返回的 pair ---\n";
    auto status_pair = getUserStatus(101);
    if (status_pair.first) {
        std::cout << "查询结果: " << status_pair.second << std::endl;
    }
    std::cout << "\n";
    
    // ===================================================================

    std::cout << "--- 3. 在 std::map 中的应用 ---\n";
    std::map<std::string, int> city_population;
    // 使用 make_pair, emplace, 和列表初始化来插入数据
    city_population.insert(std::make_pair("北京", 2189));
    city_population.emplace("上海", 2487);
    city_population["广州"] = 1867; // 更简洁的插入/更新方式
    
    std::cout << "遍历城市人口 (单位: 万人):\n";
    for (const auto& city_pair : city_population) {
        std::cout << "  " << city_pair.first << "的人口是 " << city_pair.second << " 万\n";
    }
    std::cout << "\n";

    // ===================================================================

    std::cout << "--- 4. 在 std::vector 中的应用 ---\n";
    std::vector<std::pair<std::string, std::string>> file_attributes;
    file_attributes.emplace_back("file1.txt", "Read-Only");
    file_attributes.emplace_back("document.docx", "Read-Write");

    std::cout << "遍历文件属性:\n";
    for (const auto& file_pair : file_attributes) {
        std::cout << "  文件名: " << file_pair.first << ", 属性: " << file_pair.second << std::endl;
    }
    std::cout << "\n";

    // ===================================================================

    std::cout << "--- 5. C++17 结构化绑定的优雅用法 ---\n";
    // 用于基本 pair
    auto [book_name, price] = book;
    std::cout << "结构化绑定获取书名: " << book_name << ", 价格: " << price << std::endl;

    // 用于函数返回值
    auto [found, status_message] = getUserStatus(404);
    if (!found) {
        std::cout << "结构化绑定获取查询结果: " << status_message << std::endl;
    }

    // 用于遍历 map
    std::cout << "使用结构化绑定遍历 map:\n";
    for (const auto& [city, population] : city_population) {
        std::cout << "  " << city << "的人口是 " << population << " 万\n";
    }
    
    // 用于遍历 vector
    std::cout << "使用结构化绑定遍历 vector:\n";
    for (const auto& [filename, attribute] : file_attributes) {
        std::cout << "  文件名: " << filename << ", 属性: " << attribute << std::endl;
    }

    return 0;
}
```

`std::pair`的默认比较遵循**字典序**规则：优先比较第一个成员（`first`），只有在第一个成员相等时，才会去比较第二个成员（`second`）。

## `std::sort`

`sort()`函数定义在`<algorithm>`头文件中，基本语法如下：

```C++
sort(first, last);  // 默认按升序排序
sort(first, last, comp);  // 使用自定义比较函数
```

**基本用法**

```C++
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

// 自定义比较函数
bool compare(int a, int b) {
    return a > b;  // 降序排序
}

// 用于排序的简单结构体
struct Person {
    string name;
    int age;
};

// 结构体比较函数
bool comparePersons(const Person& a, const Person& b) {
    if (a.age != b.age) {
        return a.age < b.age;  // 按年龄升序
    }
    return a.name < b.name;    // 年龄相同按名字字母顺序
}

int main() {
    // 1. 对普通数组排序
    int arr[] = {5, 2, 8, 1, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // 升序排序
    sort(arr, arr + n);
    
    cout << "升序排序数组: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 降序排序
    sort(arr, arr + n, greater<int>());
    
    cout << "降序排序数组: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 2. 对vector排序
    vector<int> vec = {5, 2, 8, 1, 9};
    
    // 升序排序
    sort(vec.begin(), vec.end());
    
    cout << "升序排序vector: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
    
    // 使用自定义比较函数
    sort(vec.begin(), vec.end(), compare);
    
    cout << "自定义函数降序排序: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
    
    // 3. 使用Lambda表达式
    vector<int> vec2 = {5, 2, 8, 1, 9};
    
    // 使用Lambda表达式进行降序排序
    sort(vec2.begin(), vec2.end(), [](int a, int b) {
        return a > b;
    });
    
    cout << "Lambda表达式降序排序: ";
    for (int num : vec2) {
        cout << num << " ";
    }
    cout << endl;
    
    // 4. 对结构体进行排序
    vector<Person> people = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 20},
        {"David", 25}
    };
    
    // 使用自定义比较函数排序
    sort(people.begin(), people.end(), comparePersons);
    
    cout << "结构体排序结果: " << endl;
    for (const Person& p : people) {
        cout << p.name << " - " << p.age << endl;
    }
    
    // 5. 使用Lambda表达式对结构体排序 (只按名字)
    sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
        return a.name < b.name;
    });
    
    cout << "Lambda表达式对结构体排序 (按名字): " << endl;
    for (const Person& p : people) {
        cout << p.name << " - " << p.age << endl;
    }
    
    // 6. 部分排序 (只排序vector的一部分)
    vector<int> vec3 = {5, 2, 8, 1, 9, 3, 7};
    
    // 只排序索引1到4的元素
    sort(vec3.begin() + 1, vec3.begin() + 5);
    
    cout << "部分排序结果: ";
    for (int num : vec3) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
```

* 普通数组的升序和降序排序
* vector的排序
* 使用自定义比较函数
* 使用Lambda表达式
* 结构体的排序
* 部分范围排序

## 常用数学函数

1. **绝对值**：`std::abs(x)`和 `std::fabs(x)`

2. **幂运算 (Power Functions)**:

   - `std::pow(base, exp)`: 计算 `base` 的 `exp` 次幂 (`base^exp`)。通常返回 `double`。
   - `std::sqrt(x)`: 计算 `x` 的平方根 (`√x`)。返回 `double`。
   - `std::cbrt(x)`: 计算 `x` 的立方根。返回 `double`。
   - `std::hypot(x, y)`: 计算 `sqrt(x*x + y*y)`，即直角三角形的斜边长，通常比手动计算更精确且能处理潜在的溢出。

3. **对数函数 (Logarithmic Functions)**:
   - `std::log(x)`: 计算自然对数 (`ln x`, 以 `e` 为底)。
   - `std::log10(x)`: 计算常用对数 (`lg x`, 以 `10` 为底)。
   - `std::log2(x)`: 计算以 `2` 为底的对数 (`lb x`)。

4. **三角函数 (Trigonometric Functions)**: (在几何相关题目中可能用到)

   - `std::sin(x)`, `std::cos(x)`, `std::tan(x)`: 计算正弦、余弦、正切 (参数 `x` 为弧度)。
   - `std::asin(x)`, `std::acos(x)`, `std::atan(x)`: 计算反正弦、反余弦、反正切。
   - `std::atan2(y, x)`: 计算 `y/x` 的反正切，但能根据 `x` 和 `y` 的符号确定正确的象限，返回值在 `[-π, π]`。非常有用。

5. **最大最小值 (Minimum and Maximum)**:
* std::min(a, b): 返回 a 和 b 中较小的一个。
* std::max(a, b): 返回 a 和 b 中较大的一个。
* std::min({a, b, c, ...}): (C++11 起) 返回初始化列表中最小的元素。
* std::max({a, b, c, ...}): (C++11 起) 返回初始化列表中最大的元素。

6. **内置类型的最大最小值**

**`<climits>` (整数限制)**:

- `INT_MAX`, `INT_MIN`
- `UINT_MAX`
- `LONG_MAX`, `LONG_MIN`
- `ULONG_MAX`
- `LLONG_MAX`, `LLONG_MIN` (需要 C++11 或支持 `long long` 的 C99)
- `ULLONG_MAX` (需要 C++11 或支持 `unsigned long long` 的 C99)
- `CHAR_MAX`, `CHAR_MIN`
- `SCHAR_MAX`, `SCHAR_MIN` (`signed char`)
- `UCHAR_MAX` (`unsigned char`)

**`<cfloat>` (浮点数限制)**:

- `FLT_MAX`, `FLT_MIN` (最小正规范化值), `-FLT_MAX` (最负值近似)
- `DBL_MAX`, `DBL_MIN` (最小正规范化值), `-DBL_MAX` (最负值近似)
- `LDBL_MAX`, `LDBL_MIN` (最小正规范化值), `-LDBL_MAX` (最负值近似)

## C++ 风格的显式类型转换 (Explicit Conversion / Casting)

* static_cast<new_type>(expression)

数值类型之间转换（`int` <-> `long long`, `int` <-> `double`, `float` <-> `double` 等）。

```C++
int a = 100000, b = 100000;
long long product = static_cast<long long>(a) * b; // 推荐
// long long product = (long long)a * b; // C风格也可以，但不推荐

int total = 10, count = 3;
double avg = static_cast<double>(total) / count;
int rounded_avg = static_cast<int>(avg + 0.5); // 简单四舍五入

char c = '5';
int digit = static_cast<int>(c - '0'); // 转换为数字 5

int num = 9;
char ch = static_cast<char>(num + '0'); // 转换为字符 '9'
```

* **字符串转数值：**

  - `std::stoi(str)`: 字符串转 `int`

  - `std::stol(str)`: 字符串转 `long`

  - `std::stoll(str)`: 字符串转 `long long`

  - `std::stof(str)`: 字符串转 `float`

  - `std::stod(str)`: 字符串转 `double`

  - `std::stold(str)`: 字符串转 `long double`

  - **注意：** 这些函数如果转换失败（如字符串包含非数字字符）或超出范围，会抛出异常 (`std::invalid_argument`, `std::out_of_range`)。在 LeetCode 中，有时题目保证输入有效，有时需要考虑异常处理（尽管不常见）。

```C++
#include <string>
#include <stdexcept>
#include <iostream>

std::string s_num = "12345";
std::string s_invalid = "abc";
try {
    int num = std::stoi(s_num); // num = 12345
    // int invalid_num = std::stoi(s_invalid); // 会抛出 std::invalid_argument
} catch (const std::invalid_argument& e) {
    std::cerr << "Invalid argument: " << e.what() << '\n';
} catch (const std::out_of_range& e) {
     std::cerr << "Out of range: " << e.what() << '\n';
}
```

* 数值转字符串：

```C++
#include <string>

int num = 123;
double pi = 3.14;
std::string s1 = std::to_string(num); // s1 = "123"
std::string s2 = std::to_string(pi);  // s2 = "3.140000" (精度可能因实现而异)
```

## `std::string`核心用法

1. **容量与访问 (Capacity & Access)**

```C++
// 假设 s 是一个 std::string 对象, 例如: std::string s = "LeetCode";
// std::string empty_s = "";

// size() / length()
unsigned int len = s.length(); // 或 s.size();

// empty()
bool isEmpty = s.empty();
bool isEmptyActually = empty_s.empty(); // true

// operator[] (不进行边界检查，假设索引有效)
char first_char = s[0];
char last_char = s[s.length() - 1];
s[0] = 'l'; // 修改字符

// at() (进行边界检查)
char char_at_1 = s.at(1);
// s.at(100); // 如果s长度小于100, 会抛出 std::out_of_range

// front() (假设 s 非空)
char f_char = s.front();

// back() (假设 s 非空)
char b_char = s.back();

// --- 输出示例 (仅为说明，实际代码段不含cout) ---
// std::cout << "Length: " << len << std::endl;
// std::cout << "Is s empty? " << isEmpty << std::endl;
// std::cout << "First char (s[0]): " << first_char << std::endl;
// std::cout << "Char at 1 (s.at(1)): " << char_at_1 << std::endl;
// std::cout << "Front char: " << f_char << std::endl;
// std::cout << "Back char: " << b_char << std::endl;
```

2. 修改器 (Modifiers)

```C++
// 假设 s1, s2 是 std::string 对象, 例如:
// std::string s1 = "hello";
// std::string s2 = "world";
// std::string s_build;

// operator+=
s_build += s1;         // s_build is now "hello"
s_build += " ";        // s_build is now "hello "
s_build += s2;         // s_build is now "hello world"
s_build += '!';        // s_build is now "hello world!"

// append()
std::string s_append = "start";
s_append.append(s1);                // s_append is "starthello"
s_append.append(" another", 0, 4);  // s_append is "starthello ano" (appends " ano")
s_append.append(3, '.');            // s_append is "starthello ano..."

// push_back()
std::string s_pb = "abc";
s_pb.push_back('d');   // s_pb is "abcd"

// pop_back() (C++11, 假设 s_pb 非空)
s_pb.pop_back();       // s_pb is "abc"

// insert()
std::string s_insert = "string";
s_insert.insert(0, "My_");      // s_insert is "My_string"
s_insert.insert(3, s1, 1, 2); // s_insert is "My_elstring" (inserts "el" from "hello" at index 3)

// erase()
std::string s_erase = "RemoveThis";
s_erase.erase(6, 4); // s_erase is "Remove" (removes "This")
// s_erase.erase(s_erase.begin() + 2); // s_erase is "Remve" (removes 'm')

// replace()
std::string s_replace = "Old value";
s_replace.replace(0, 3, "New"); // s_replace is "New value"
s_replace.replace(4, 5, s1);    // s_replace is "New hello" (replaces "value" with "hello")

// clear()
std::string s_clear = "not empty";
s_clear.clear();       // s_clear is ""

// swap()
std::string str_a = "Alpha";
std::string str_b = "Beta";
str_a.swap(str_b);     // str_a is "Beta", str_b is "Alpha"
```

3. 子串与比较 (Substrings & Comparison)

```C++
// 假设 main_s, s_comp1, s_comp2 是 std::string 对象, 例如:
// std::string main_s = "ThisIsAString";
// std::string s_comp1 = "IsA";
// std::string s_comp2 = "isa"; // for case-sensitive comparison
// std::string s_comp3 = "ThisIsAString";

// substr()
std::string sub = main_s.substr(4, 3);    // sub is "IsA" (starts at index 4, length 3)
std::string sub_to_end = main_s.substr(7); // sub_to_end is "String" (starts at index 7 to end)

// compare()
int result1 = s_comp1.compare(sub);             // result1 is 0 (equal)
int result2 = s_comp1.compare(s_comp2);         // result2 is < 0 ('I' vs 'i', lexicographically)
int result3 = s_comp2.compare(s_comp1);         // result3 is > 0

// 比较运算符 (更常用)
bool are_equal = (main_s == s_comp3);      // true
bool are_not_equal = (s_comp1 != s_comp2); // true
bool is_less = (s_comp2 < s_comp1);        // true ("isa" < "IsA" is false due to case, "IsA" < "isa" is true)
bool is_greater = (s_comp1 > "ABC");       // true
```

## 有序哈希表std::set

对于一个空的 `set` 或任何 C++ 容器，它的起始迭代器和末尾迭代器是相等的，即 `window.begin() == window.end()`

```cpp
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm> // For std::distance
#include <functional> // For std::greater

int main() {
    // --- 1. 声明和初始化 (Declaration & Initialization) ---
    std::cout << "--- 1. 声明和初始化 ---" << std::endl;
    std::set<int> s1; // 空 set
    std::set<std::string> s2 = {"apple", "banana", "cherry", "apple"}; // 初始化列表，"apple"只出现一次且有序
    std::set<int, std::greater<int>> s3 = {5, 1, 9, 3}; // 降序 set

    std::cout << "s2 (string set): ";
    for (const auto& str : s2) {
        std::cout << str << " "; // 输出: apple banana cherry
    }
    std::cout << std::endl;

    std::cout << "s3 (descending int set): ";
    for (int val : s3) {
        std::cout << val << " "; // 输出: 9 5 3 1
    }
    std::cout << std::endl << std::endl;


    // --- 2. 插入元素 (Inserting Elements) ---
    std::cout << "--- 2. 插入元素 ---" << std::endl;
    std::set<int> s_insert;
    auto result1 = s_insert.insert(20); // 插入 20
    s_insert.insert(10);
    auto result2 = s_insert.insert(20); // 尝试再次插入 20

    std::cout << "s_insert: ";
    for (int val : s_insert) {
        std::cout << val << " "; // 输出: 10 20
    }
    std::cout << std::endl;
    std::cout << "First insert (20): success? " << result1.second << ", iterator points to: " << *(result1.first) << std::endl;
    std::cout << "Second insert (20): success? " << result2.second << ", iterator points to: " << *(result2.first) << std::endl;
    std::cout << std::endl;


    // --- 3. 删除元素 (Erasing Elements) ---
    std::cout << "--- 3. 删除元素 ---" << std::endl;
    std::set<int> s_erase = {10, 20, 30, 40, 50};
    std::cout << "s_erase before erase: ";
    for (int val : s_erase) std::cout << val << " "; std::cout << std::endl;

    size_t erased_count = s_erase.erase(30); // 按值删除
    std::cout << "Erased 30, count: " << erased_count << ". s_erase: ";
    for (int val : s_erase) std::cout << val << " "; std::cout << std::endl;

    auto it_erase = s_erase.find(40);
    if (it_erase != s_erase.end()) {
        s_erase.erase(it_erase); // 按迭代器删除
        std::cout << "Erased element at iterator (was 40). s_erase: ";
        for (int val : s_erase) std::cout << val << " "; std::cout << std::endl;
    }
    std::cout << std::endl;


    // --- 4. 查找元素 (Finding Elements) ---
    std::cout << "--- 4. 查找元素 ---" << std::endl;
    std::set<int> s_find = {10, 20, 30};
    auto it_found = s_find.find(20);
    if (it_found != s_find.end()) {
        std::cout << "Found 20: " << *it_found << std::endl;
    } else {
        std::cout << "20 not found." << std::endl;
    }

    auto it_not_found = s_find.find(25);
    if (it_not_found == s_find.end()) {
        std::cout << "25 not found (iterator is s_find.end())." << std::endl;
    }
    std::cout << std::endl;


    // --- 5. 统计元素 (Counting Elements) ---
    std::cout << "--- 5. 统计元素 ---" << std::endl;
    std::cout << "Count of 20 in s_find: " << s_find.count(20) << std::endl; // 输出: 1
    std::cout << "Count of 25 in s_find: " << s_find.count(25) << std::endl; // 输出: 0

    // C++20 contains()
    #if __cplusplus >= 202002L
    std::cout << "s_find contains 30 (C++20)? " << std::boolalpha << s_find.contains(30) << std::endl;
    std::cout << "s_find contains 35 (C++20)? " << std::boolalpha << s_find.contains(35) << std::endl;
    #else
    std::cout << "(Skipping s.contains() example, requires C++20)" << std::endl;
    #endif
    std::cout << std::endl;


    // --- 6. 大小和判空 (Size and Emptiness) ---
    std::cout << "--- 6. 大小和判空 ---" << std::endl;
    std::cout << "s_find size: " << s_find.size() << std::endl;
    std::cout << "s_find empty? " << std::boolalpha << s_find.empty() << std::endl;

    std::set<int> s_empty;
    std::cout << "s_empty size: " << s_empty.size() << std::endl;
    std::cout << "s_empty empty? " << std::boolalpha << s_empty.empty() << std::endl;
    std::cout << std::endl;


    // --- 7. 清空 (Clear) ---
    std::cout << "--- 7. 清空 ---" << std::endl;
    std::set<int> s_clear = {1, 2, 3};
    std::cout << "s_clear before clear, size: " << s_clear.size() << std::endl;
    s_clear.clear();
    std::cout << "s_clear after clear, size: " << s_clear.size() << ", empty? " << s_clear.empty() << std::endl;
    std::cout << std::endl;


    // --- 8. 迭代 (Iteration) ---
    std::cout << "--- 8. 迭代 ---" << std::endl;
    std::set<int> s_iterate = {30, 10, 20};
    std::cout << "Range-based for loop: ";
    for (int val : s_iterate) {
        std::cout << val << " "; // 输出: 10 20 30
    }
    std::cout << std::endl;

    std::cout << "Iterator loop: ";
    for (std::set<int>::iterator it = s_iterate.begin(); it != s_iterate.end(); ++it) {
        std::cout << *it << " "; // 输出: 10 20 30
    }
    std::cout << std::endl;

    if (!s_iterate.empty()) {
        std::cout << "First element (begin): " << *s_iterate.begin() << std::endl;
        std::cout << "Last element (rbegin): " << *s_iterate.rbegin() << std::endl;
        // Alternative for last: std::cout << "Last element (--end): " << *(--s_iterate.end()) << std::endl;
    }
    std::cout << std::endl;


    // --- 9. lower_bound 和 upper_bound ---
    std::cout << "--- 9. lower_bound 和 upper_bound ---" << std::endl;
    std::set<int> s_bounds = {10, 20, 30, 40, 50};
    std::cout << "s_bounds: "; for(int x:s_bounds) std::cout << x << " "; std::cout << std::endl;

    // lower_bound: 第一个不小于 (>=) val 的元素
    auto lb1 = s_bounds.lower_bound(20); // 指向 20
    if (lb1 != s_bounds.end()) std::cout << "lower_bound(20): " << *lb1 << std::endl;

    auto lb2 = s_bounds.lower_bound(25); // 指向 30
    if (lb2 != s_bounds.end()) std::cout << "lower_bound(25): " << *lb2 << std::endl;

    auto lb3 = s_bounds.lower_bound(50); // 指向 50
    if (lb3 != s_bounds.end()) std::cout << "lower_bound(50): " << *lb3 << std::endl;

    auto lb4 = s_bounds.lower_bound(55); // 指向 s_bounds.end()
    if (lb4 == s_bounds.end()) std::cout << "lower_bound(55) is s_bounds.end()" << std::endl;

    // upper_bound: 第一个严格大于 (>) val 的元素
    auto ub1 = s_bounds.upper_bound(20); // 指向 30
    if (ub1 != s_bounds.end()) std::cout << "upper_bound(20): " << *ub1 << std::endl;

    auto ub2 = s_bounds.upper_bound(25); // 指向 30
    if (ub2 != s_bounds.end()) std::cout << "upper_bound(25): " << *ub2 << std::endl;

    auto ub3 = s_bounds.upper_bound(50); // 指向 s_bounds.end()
    if (ub3 == s_bounds.end()) std::cout << "upper_bound(50) is s_bounds.end()" << std::endl;

    auto ub4 = s_bounds.upper_bound(5); // 指向 10
    if (ub4 != s_bounds.end()) std::cout << "upper_bound(5): " << *ub4 << std::endl;
    std::cout << std::endl;
  
    // 使用upper_bound模拟：查找小于或等于 (<=) val 的最大元素
		int val_check1 = 25;
    // 查找 <= 25 的最大元素
    auto it_ub1 = s_bounds.upper_bound(val_check1); // it_ub1 指向 30 (第一个 > 25 的元素)
    if (it_ub1 != s_bounds.begin()) { // 确保前面有元素
        auto floor_it1 = std::prev(it_ub1); // floor_it1 指向 20
        std::cout << "floor(" << val_check1 << "): " << *floor_it1 << std::endl; // 输出: 20
    } else {
        std::cout << "No floor for " << val_check1 << " found." << std::endl;
    }
  
    // --- 10. 使用 bounds 统计范围内元素 ---
    std::cout << "--- 10. 使用 bounds 统计范围内元素 ---" << std::endl;
    // 统计范围 [20, 40] 内的元素 (即 20, 30, 40)
    int low_val = 20;
    int high_val = 40;
    auto range_start = s_bounds.lower_bound(low_val);
    auto range_end = s_bounds.upper_bound(high_val); // 第一个 > 40 的元素，即 50

    std::cout << "Elements in [" << low_val << ", " << high_val << "]: ";
    for (auto it_range = range_start; it_range != range_end; ++it_range) {
        std::cout << *it_range << " "; // 输出: 20 30 40
    }
    std::cout << std::endl;
    long count_in_range = std::distance(range_start, range_end);
    std::cout << "Count in range [" << low_val << ", " << high_val << "]: " << count_in_range << std::endl;

    return 0;
}
```

## `std::bitset`

C++ 中的 `std::bitset` 够存储和操作固定大小的位序列（0 或 1）。

### 1. **初始化**

```C++
#include <iostream>
#include <string>
#include <bitset>

int main() {
    // 默认构造 (全为 0)
    std::bitset<8> b1;
    std::cout << "b1 (default): " << b1 << std::endl; // b1: 00000000

    // 使用无符号长整型 (unsigned long long)
    std::bitset<8> b2(42);    // 42 的二进制是 00101010
    std::cout << "b2 (from 42): " << b2 << std::endl; // b2: 00101010

    std::bitset<4> b3(15);    // 15 的二进制是 1111
    std::cout << "b3 (from 15): " << b3 << std::endl; // b3: 1111

    std::bitset<4> b4(20);    // 20 的二进制是 10100，b4 只能存4位，取低4位
    std::cout << "b4 (from 20, size 4): " << b4 << std::endl; // b4: 0100

    // 使用字符串
    std::string s = "10110";
    std::bitset<5> b5(s);
    std::cout << "b5 (from string \"10110\"): " << b5 << std::endl; // b5: 10110

    std::bitset<8> b6(s); // 高位用0填充
    std::cout << "b6 (from string \"10110\", size 8): " << b6 << std::endl; // b6: 00010110

    std::bitset<3> b7(s); // 只取前3位 (实际上是字符串的前N位，如果字符串长于N)
                          // 或者整个字符串如果字符串短于N (高位补0)
                          // 对于bitset(string), 它会尝试转换整个字符串。
                          // 如果字符串长度 > N, 它会用字符串的最后 N 个字符。
                          // 如果字符串长度 < N, 它会用整个字符串，并在左边填充0.
                          // The behavior is: it uses the last N characters of the string if string.length() > N.
                          // If string.length() <= N, it uses the whole string, padding with '0's to the left.
                          // However, the constructor std::bitset<N>(const basic_string<...>&, pos, count) is different.
                          // The simple std::bitset<N>(str) tries to initialize from the whole string.
                          // Let's re-verify the behavior for b7 for clarity based on cppreference.
                          // For std::bitset<N>(str): If str.size() > N, it uses the N rightmost characters.
                          // If str.size() <= N, it uses all characters, padding with 0s on the left.
    std::string s_for_b7 = "101";
    std::bitset<3> b7_corrected(s_for_b7);
    std::cout << "b7_corrected (from string \"101\", size 3): " << b7_corrected << std::endl; // b7: 101

    std::string s_long_b7_test = "11101"; // length 5
    std::bitset<3> b7_test_long_str(s_long_b7_test); // Should take "101" (rightmost 3)
    std::cout << "b7_test_long_str (from string \"11101\", size 3): " << b7_test_long_str << std::endl; // b7_test_long_str: 101


    std::string s_long = "00110101101"; // length 11
    // From s_long, starting at index 2 ("110101101"), take 6 characters "110101"
    std::bitset<6> b8(s_long, 2, 6);
    std::cout << "b8 (from s_long, pos 2, count 6): " << b8 << std::endl; // b8: 110101

    // From "11110000", starting at index 4 ("0000"), take 4 characters "0000"
    std::bitset<4> b9("11110000", 4, 4);
    std::cout << "b9 (from \"11110000\", pos 4, count 4): " << b9 << std::endl; // b9: 0000

    return 0;
}
```

### 2. **访问和修改单个位**

```C++
#include <iostream>
#include <string>
#include <bitset>
#include <stdexcept> // For std::out_of_range

int main() {
    // operator[]
    std::bitset<8> bs_access("10101010");
    std::cout << "Initial bs_access: " << bs_access << std::endl;
    std::cout << "bs_access[0]: " << bs_access[0] << std::endl; // 最右边的位
    std::cout << "bs_access[1]: " << bs_access[1] << std::endl;
    std::cout << "bs_access[7]: " << bs_access[7] << std::endl; // 最左边的位

    bs_access[0] = 1; // 设置最右边的位为 1
    bs_access[7] = 0; // 设置最左边的位为 0
    std::cout << "bs_access after modification: " << bs_access << std::endl; // 00101011

    // set(pos, value)
    std::bitset<4> bs_set; // 0000
    std::cout << "Initial bs_set: " << bs_set << std::endl;
    bs_set.set(0);      // 设置第0位为1 -> 0001
    std::cout << "bs_set after set(0): " << bs_set << std::endl;
    bs_set.set(2, true);  // 设置第2位为1 -> 0101
    std::cout << "bs_set after set(2, true): " << bs_set << std::endl;
    bs_set.set(3, false); // 设置第3位为0 (如果之前是1) -> 0101 (无变化，因为本来就是0)
    std::cout << "bs_set after set(3, false): " << bs_set << std::endl;

    // reset(pos)
    std::bitset<4> bs_reset("1111");
    std::cout << "Initial bs_reset: " << bs_reset << std::endl;
    bs_reset.reset(1); // 将第1位清零 -> 1101
    std::cout << "bs_reset after reset(1): " << bs_reset << std::endl;
    bs_reset.reset(3); // 将第3位清零 -> 0101
    std::cout << "bs_reset after reset(3): " << bs_reset << std::endl;

    // flip(pos)
    std::bitset<4> bs_flip("1010");
    std::cout << "Initial bs_flip: " << bs_flip << std::endl;
    bs_flip.flip(0); // 翻转第0位 -> 1011
    std::cout << "bs_flip after flip(0): " << bs_flip << std::endl;
    bs_flip.flip(2); // 翻转第2位 -> 1111
    std::cout << "bs_flip after flip(2): " << bs_flip << std::endl;

    // test(pos)
    std::bitset<4> bs_test("1001");
    std::cout << "Initial bs_test: " << bs_test << std::endl;
    if (bs_test.test(0)) {
        std::cout << "Bit 0 of bs_test is set." << std::endl;
    }
    if (!bs_test.test(1)) {
        std::cout << "Bit 1 of bs_test is not set." << std::endl;
    }
    try {
        bs_test.test(4); // Accessing out of bounds
    } catch (const std::out_of_range& e) {
        std::cerr << "Exception for bs_test.test(4): " << e.what() << std::endl;
    }

    return 0;
}
```

### 3. **对所有位进行操作**

```C++
#include <iostream>
#include <string>
#include <bitset>

int main() {
    // set()
    std::bitset<4> bs_all_set; // 0000
    std::cout << "Initial bs_all_set: " << bs_all_set << std::endl;
    bs_all_set.set();         // 1111
    std::cout << "bs_all_set after set(): " << bs_all_set << std::endl;

    // reset()
    std::bitset<4> bs_all_reset("1010");
    std::cout << "Initial bs_all_reset: " << bs_all_reset << std::endl;
    bs_all_reset.reset();     // 0000
    std::cout << "bs_all_reset after reset(): " << bs_all_reset << std::endl;

    // flip()
    std::bitset<4> bs_all_flip("1100");
    std::cout << "Initial bs_all_flip: " << bs_all_flip << std::endl;
    bs_all_flip.flip();       // 0011
    std::cout << "bs_all_flip after flip(): " << bs_all_flip << std::endl;

    return 0;
}
```

### 4. **查询 `bitset` 状态**

```C++
#include <iostream>
#include <string>
#include <bitset>

int main() {
    // count()
    std::bitset<8> bs_count("10101100");
    std::cout << "bs_count: " << bs_count << std::endl;
    std::cout << "Number of set bits in bs_count: " << bs_count.count() << std::endl;

    // size()
    std::bitset<16> bs_size_demo;
    std::cout << "Size of bs_size_demo: " << bs_size_demo.size() << std::endl;
    std::cout << "Size of bs_count: " << bs_count.size() << std::endl;


    // any()
    std::bitset<4> bs_any1("0010");
    std::bitset<4> bs_any0("0000");
    std::cout << "bs_any1: " << bs_any1 << ", bs_any1.any(): " << bs_any1.any() << std::endl;
    std::cout << "bs_any0: " << bs_any0 << ", bs_any0.any(): " << bs_any0.any() << std::endl;

    // none()
    std::bitset<4> bs_none1("0010"); // same as bs_any1
    std::bitset<4> bs_none0("0000"); // same as bs_any0
    std::cout << "bs_none1: " << bs_none1 << ", bs_none1.none(): " << bs_none1.none() << std::endl;
    std::cout << "bs_none0: " << bs_none0 << ", bs_none0.none(): " << bs_none0.none() << std::endl;

    // all()
    std::bitset<4> bs_all1("1111");
    std::bitset<4> bs_all0("1101");
    std::cout << "bs_all1: " << bs_all1 << ", bs_all1.all(): " << bs_all1.all() << std::endl;
    std::cout << "bs_all0: " << bs_all0 << ", bs_all0.all(): " << bs_all0.all() << std::endl;

    return 0;
}
```

### 5. **位运算操作符**

```C++
#include <iostream>
#include <string>
#include <bitset>

int main() {
    std::bitset<4> b1("1100");
    std::bitset<4> b2("1010");
    std::cout << "b1: " << b1 << std::endl;
    std::cout << "b2: " << b2 << std::endl;

    // & (按位与 AND)
    std::bitset<4> result_and = b1 & b2; // 1000
    std::cout << "b1 & b2: " << result_and << std::endl;

    // | (按位或 OR)
    std::bitset<4> result_or = b1 | b2;   // 1110
    std::cout << "b1 | b2: " << result_or << std::endl;

    // ^ (按位异或 XOR)
    std::bitset<4> result_xor = b1 ^ b2; // 0110
    std::cout << "b1 ^ b2: " << result_xor << std::endl;

    // ~ (按位非 NOT)
    std::bitset<4> b_not_original("1100"); // Using a new variable to avoid confusion with b1
    std::bitset<4> result_not = ~b_not_original; // 0011
    std::cout << "~(" << b_not_original << "): " << result_not << std::endl;

    // << (左移), >> (右移)
    std::bitset<8> b_shift("00011010");
    std::cout << "b_shift original: " << b_shift << std::endl;
    std::bitset<8> result_lshift = b_shift << 2; // 01101000
    std::bitset<8> result_rshift = b_shift >> 2; // 00000110
    std::cout << "b_shift << 2: " << result_lshift << std::endl;
    std::cout << "b_shift >> 2: " << result_rshift << std::endl;

    // 复合赋值运算符
    std::bitset<4> b_assign("1100");
    std::cout << "b_assign initial: " << b_assign << std::endl;
    b_assign |= std::bitset<4>("0011"); // b_assign 变为 1111
    std::cout << "b_assign after |= \"0011\": " << b_assign << std::endl;

    b_assign &= std::bitset<4>("1010"); // b_assign (1111) &= 1010 -> 1010
    std::cout << "b_assign after &= \"1010\": " << b_assign << std::endl;

    b_assign ^= std::bitset<4>("1100"); // b_assign (1010) ^= 1100 -> 0110
    std::cout << "b_assign after ^= \"1100\": " << b_assign << std::endl;

    std::bitset<8> b_shift_assign("00001111");
    std::cout << "b_shift_assign initial: " << b_shift_assign << std::endl;
    b_shift_assign <<= 2; // 00111100
    std::cout << "b_shift_assign after <<= 2: " << b_shift_assign << std::endl;
    b_shift_assign >>= 3; // 00000111
    std::cout << "b_shift_assign after >>= 3: " << b_shift_assign << std::endl;

    return 0;
}
```

### 6. **转换**

```C++
#include <iostream>
#include <string>
#include <bitset>
#include <stdexcept> // For std::overflow_error

int main() {
    // to_string(zero, one)
    std::bitset<8> bs_to_str("00110101");
    std::cout << "bs_to_str: " << bs_to_str << std::endl;
    std::string str1 = bs_to_str.to_string();
    std::string str2 = bs_to_str.to_string('_', '#');
    std::cout << "to_string(): \"" << str1 << "\"" << std::endl;
    std::cout << "to_string('_', '#'): \"" << str2 << "\"" << std::endl;

    // to_ulong()
    std::bitset<8> bs_to_ul("00001101"); // 13
    std::cout << "bs_to_ul: " << bs_to_ul << std::endl;
    unsigned long ul = bs_to_ul.to_ulong();
    std::cout << "to_ulong(): " << ul << std::endl;

    std::bitset<32> bs_ul_max; // Max for unsigned long (assuming 32-bit ulong)
    bs_ul_max.set(); // All ones
    try {
        unsigned long ul_max_val = bs_ul_max.to_ulong();
        std::cout << "bs_ul_max (" << bs_ul_max.size() << " bits all set) to_ulong(): " << ul_max_val << std::endl;
    } catch (const std::overflow_error& e) {
        std::cerr << "For bs_ul_max (" << bs_ul_max.size() << " bits): " << e.what() << std::endl;
    }


    std::bitset<64> bs_ull_fits; // Fits in unsigned long long
    bs_ull_fits[63] = 1; // Set MSB for a large number
    bs_ull_fits[0] = 1;  // Set LSB
    std::cout << "bs_ull_fits: " << bs_ull_fits << std::endl;
    try {
        unsigned long long ull_fits_val = bs_ull_fits.to_ullong();
        std::cout << "bs_ull_fits to_ullong(): " << ull_fits_val << std::endl;
    } catch (const std::overflow_error& e) {
        std::cerr << "For bs_ull_fits: " << e.what() << std::endl;
    }


    // Example of overflow with to_ulong()
    // On most systems, unsigned long is 32 or 64 bits. std::bitset<N> N can be larger.
    // If N > (bits in unsigned long), to_ulong() can overflow if any bit beyond
    // the capacity of unsigned long is set.
    // Let's assume unsigned long is 32 bits for this test.
    // A bitset of 33 will cause overflow if bit 32 is set.
    const int ulong_bits = sizeof(unsigned long) * 8;
    std::cout << "unsigned long has " << ulong_bits << " bits on this system." << std::endl;

    std::bitset<ulong_bits + 1> bs_overflow_test;
    bs_overflow_test[ulong_bits] = 1; // Set the bit that is just outside ulong's range
    std::cout << "bs_overflow_test (size " << ulong_bits + 1 << "): " << bs_overflow_test << std::endl;
    try {
        unsigned long ul_err = bs_overflow_test.to_ulong();
        std::cout << "bs_overflow_test.to_ulong() (should not print if overflow): " << ul_err << std::endl;
    } catch (const std::overflow_error& e) {
        std::cerr << "Overflow error for bs_overflow_test.to_ulong(): " << e.what() << std::endl;
    }

    // to_ullong()
    std::bitset<36> bs_to_ull("101010101010101010101010101010101010"); // 36 bits
    std::cout << "bs_to_ull: " << bs_to_ull << std::endl;
    unsigned long long ull = bs_to_ull.to_ullong();
    std::cout << "to_ullong() example value: " << ull << std::endl;

    const int ullong_bits = sizeof(unsigned long long) * 8;
    std::cout << "unsigned long long has " << ullong_bits << " bits on this system." << std::endl;
    if (ullong_bits < 65) { // Only run overflow test if ullong is less than 65 bits
        std::bitset<65> bs_ull_overflow; // Could cause overflow if unsigned long long is 64 bits
        bs_ull_overflow[64] = 1; // Set the 65th bit (index 64)
        std::cout << "bs_ull_overflow (size 65): " << bs_ull_overflow << std::endl;
        try {
            unsigned long long ull_err = bs_ull_overflow.to_ullong();
            std::cout << "bs_ull_overflow.to_ullong() (should not print if overflow): " << ull_err << std::endl;
        } catch (const std::overflow_error& e) {
            std::cerr << "Overflow error for bs_ull_overflow.to_ullong(): " << e.what() << std::endl;
        }
    }


    return 0;
}
```

## C++20  `ranges::lower_bound` 

在一个已排序的数组中，它能以 O(log n) 的时间复杂度找到第一个**不小于**目标值的元素的位置。这个位置也就是该目标值如果不存在时，应该被插入的位置。

```cpp
#include <vector>
#include <algorithm>
#include <ranges>
#include <iterator>

int searchInsert(const std::vector<int>& nums, int target) {
    // 直接在 nums 上调用 ranges::lower_bound
    auto it = std::ranges::lower_bound(nums, target);
    // 计算迭代器距离，即为索引
    return std::distance(nums.begin(), it);
}
```

## C++ 20 `ranges::sort`

```C++
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9};
    std::ranges::sort(v); // No .begin() or .end() needed!
    for (int n : v) {
        std::cout << n << " "; // Prints: 1 1 3 4 5 9
    }
    std::cout << std::endl;
}

std::vector<int> v = {3, 1, 4, 1, 5, 9};
std::ranges::sort(v, std::ranges::greater()); // Use a standard library comparator
// v is now {9, 5, 4, 3, 1, 1}

struct Student {
    std::string name;
    int grade;
};

std::vector<Student> students = {{"Zoe", 88}, {"Alice", 95}, {"Bob", 92}};

// Sort students by their grade using a projection
// The empty {} is a placeholder for a custom comparator, which we aren't using
// &Student::grade不是引用，而是一个指向成员的指针
// 或者lambda表达式 [](const auto& student){ return student.grade}
std::ranges::sort(students, {}, &Student::grade);

// students is now sorted by grade: {Zoe, 88}, {Bob, 92}, {Alice, 95}
```

 **注意**：Lambda 作为一个函数（或指令），它被 `sort` 算法**重复调用**。每调用一次，`sort` 就会从 `students` 中取出一个不同的元素，作为参数传递给 Lambda。因此，`&Student::grade` 在每次调用中都指向了 `students` 里的一个新元素。

## `std::tuple`

`std::tuple` 是一个定义在头文件 `<tuple>` 中的模板类，可以看作是 `std::pair` 的泛化和扩展。`std::pair` 只能存储两个成员，而 `std::tuple` 可以存储**任意数量、任意类型**的成员。它主要用于将一组异构值捆绑成一个单一的对象。

```C++
#include <iostream>
#include <string>
#include <tuple> // 必须包含的头文件

// ===================================================================
// 用法 3: 作为函数的返回值
// 函数返回一个包含用户ID(int)、用户名(string)和是否为VIP(bool)的元组
// ===================================================================
std::tuple<int, std::string, bool> fetch_user_info(int user_id) {
    if (user_id == 1) {
        // 使用 C++11 的列表初始化返回
        return {1, "Admin", true}; 
    }
    // 使用 make_tuple 返回
    return std::make_tuple(0, "Guest", false);
}

int main() {
    std::cout << "--- 1. 如何创建 std::tuple ---\n";
    // 方法一：使用构造函数
    std::tuple<int, std::string, double> t1(1, "教科书", 99.9);
    // 方法二：使用辅助函数 std::make_tuple (更常用)
    auto t2 = std::make_tuple(2, "笔记本", 15.5);
    std::cout << "元组 t1 创建成功。\n";
    std::cout << "元组 t2 创建成功。\n";
    std::cout << "\n";

    // ===================================================================

    std::cout << "--- 2. 如何访问元组中的元素 ---\n";
    std::cout << "  a) 传统方式: std::get<index>()\n";
    // 读取元素
    std::cout << "    t1 的第一个元素: " << std::get<0>(t1) << std::endl;
    // 修改元素 (std::get 返回的是一个引用)
    std::get<1>(t1) = "C++ 程序设计教程";
    std::cout << "    t1 修改后的第二个元素: " << std::get<1>(t1) << std::endl;
    
    std::cout << "\n";
    
    std::cout << "  b) 现代 C++ (C++17) 方式: 结构化绑定\n";
    // 使用结构化绑定，直接解包到三个变量中
    auto [id, type, price] = t2;
    std::cout << "    通过结构化绑定获取 t2 的元素: ID=" << id << ", 类型=" << type << ", 价格=" << price << std::endl;
    std::cout << "\n";

    // ===================================================================

    std::cout << "--- 3. 处理函数返回的 tuple ---\n";
    // 使用结构化绑定接收函数返回值，非常清晰
    auto [user_id, user_name, is_vip] = fetch_user_info(1);
    if (user_id != 0) {
        std::cout << "  用户信息: " << user_name << (is_vip ? " (VIP用户)" : " (普通用户)") << std::endl;
    }
    std::cout << "\n";
    
    // ===================================================================

    std::cout << "--- 4. 辅助工具: std::tie 和 std::ignore ---\n";
    std::string name_from_tie;
    bool vip_status_from_tie;
    
    // 我们只想接收用户名和VIP状态，忽略ID
    std::tie(std::ignore, name_from_tie, vip_status_from_tie) = fetch_user_info(1);
    std::cout << "  使用 std::tie 只提取部分信息: \n";
    std::cout << "    用户名: " << name_from_tie << std::endl;
    std::cout << "    VIP状态: " << std::boolalpha << vip_status_from_tie << std::endl; // std::boolalpha 会将 true/false 输出为字符串

    return 0;
}
```

