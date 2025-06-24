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

当使用**下标运算符 `[]`** 来访问一个不存在的键（key）时，这个键会被**自动插入**到 map 中，并且其对应的值（value）会被**值初始化（value-initialized）**。对于 `int` 这种基本数据类型，值初始化的结果就是 **`0`**。

只想**查询**一个键是否存在而不希望修改 map 时，应该使用 `.find()` 或 `.count()` 方法。如果你确定一个键应该存在，并且希望在它不存在时得到一个错误，那么应该使用 `.at()` 方法，因为它会抛出异常。

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

## bitset

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

