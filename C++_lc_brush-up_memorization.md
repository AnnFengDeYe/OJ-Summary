# C++\_lc\_brush-up\_memorization

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
