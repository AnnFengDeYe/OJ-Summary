# C++\_lc\_brush-up\_memorization

## 溢出判断

判断一个以科学记数法表示的数是否会导致 `int` 类型溢出：

关键阈值：大约 $2×10^9$ (二十亿)

**C++:** `int` 通常是 32 位有符号整数。其范围大约是 $-2×10^9$ 到 $2×10^9$(更精确地说是 $[−2^{31},2^{31}−1]$，即 [−2147483648,2147483647])。

## unordered_map

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

## vector

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

## sort

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

