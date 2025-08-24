# Python_lc\_brush-up\_memorization

## {} [] ()

```python
# 字典初始化

dict1 = {} # 使用花括号
dict2 = dict() # 使用 dict() 函数

# 元组初始化
tuple1 = () # 使用圆括号
tuple2 = tuple() # 使用 tuple() 函数

# 列表初始化
list1 = [] # 使用方括号
list2 = list() # 使用 list() 函数  
```

## range

三种形式 (`range(stop)`, `range(start, stop)`, `range(start, stop, step)`)

```python
# --- range() 三种形式的简洁示例 ---

n = 7
start = 2
stop = 5
step = -2

# 1. range(stop) -> 0 到 stop-1
print(f"range({n}): \t\t {list(range(n))}")

# 2. range(start, stop) -> start 到 stop-1
print(f"range({start}, {stop}): \t {list(range(start, stop))}")

# 3. range(start, stop, step) -> 从 start 到 stop (不含) 按 step 步进
# 示例：从 n-1 (6) 反向到 0 (stop=-1), 步长 -2
print(f"range({n-1}, -1, {step}): {list(range(n-1, -1, step))}")
```

输出：

```
range(7):          [0, 1, 2, 3, 4, 5, 6]
range(2, 5):       [2, 3, 4]
range(6, -1, -2): [6, 4, 2, 0]
```



## **生成器表达式 (generator expression)** 

生成器表达式的语法是 `(expression for item in iterable if condition)`，它创建一个**迭代器 (iterator)**，而不是像列表推导式那样直接在内存中创建一个完整的列表。这使得它具有**惰性求值 (lazy evaluation)** 和 **内存高效** 的特点，在处理大数据或只需要迭代一次的场景中特别有用。

1. **聚合计算 (Aggregation)**:

* 与 `sum()` 结合：计算满足条件的元素的总和或数量。

```python
# 计算列表中所有偶数的平方和
nums = [1, 2, 3, 4, 5]
sum_of_squares = sum(x*x for x in nums if x % 2 == 0) # sum(4, 16) -> 20

# 统计字符串中元音字母的数量 
s = "leetcode"
vowel_count = sum(1 for char in s if char in 'aeiou') # sum(1, 1, 1, 1) -> 4
```

* 与 `min()` / `max()` 结合：查找满足条件的元素的最小值或最大值，而无需创建中间列表。

```python
# 找到列表中非零元素的最小绝对值
nums = [1, -2, 0, 3, -1]
min_abs_val = min(abs(x) for x in nums if x != 0) # min(1, 2, 3, 1) -> 1
```

2. **条件判断 (Condition Checking)**:

与 `any()` 结合：判断序列中**是否存在**至少一个满足条件的元素。它会短路，一旦找到满足条件的元素就立即返回 `True`，非常高效。

```python
# 判断列表中是否有负数
nums = [1, 2, -3, 4]
has_negative = any(x < 0 for x in nums) # True
```

与 `all()` 结合：判断序列中**是否所有**元素都满足条件。它也会短路，一旦找到不满足条件的元素就立即返回 `False`。

```python
# 判断是否所有数字都大于0
nums = [1, 2, 3, 4]
all_positive = all(x > 0 for x in nums) # True
```

3. **数据筛选与转换 (Filtering & Transformation)**:

作为其他函数的输入：生成器可以作为参数传递给 `list()`, `set()`, `tuple()`, `dict()`, `"".join()` 等函数，用于创建新的集合或进行转换。

```python
# 获取字符串中所有字母的小写形式，并去重
paragraph = "Hello, World! 123"
unique_letters = set(c.lower() for c in paragraph if c.isalpha()) # {'h', 'e', 'l', 'o', 'w', 'r', 'd'}

# 将数字列表转换为字符串
digits = [1, 2, 3]
num_str = "".join(str(d) for d in digits) # "123"
```



## enumerate

`enumerate()` 的核心功能是将任何可迭代对象（如列表、元组或字符串）转换为一系列配对，每对包含：

* 一个计数值（通常表示位置或索引）
* 原始可迭代对象中的元素

### 1. 基本语法

最基础的用法是在循环中同时获取索引和元素：

```python
# 基本形式
for index, value in enumerate(iterable):
    # 使用 index 和 value 进行操作

# 实际示例
nums = [10, 20, 30, 40]
for i, num in enumerate(nums):
    print(f"索引 {i}: 值 {num}")
```

### 2. 自定义起始索引

默认情况下，`enumerate()` 从 0 开始计数，但你可以指定不同的起始值：

```python
# 从1开始计数
for i, value in enumerate(iterable, start=1):
    # 此时 i 从 1 开始

# 从任意数字开始
for i, value in enumerate(iterable, start=10):
    # 此时 i 从 10 开始
```

### 3. 与切片结合使用

常用于跳过第一个元素或仅处理部分序列：

```python
# 跳过第一个元素，索引依然从1开始对应
nums = [10, 20, 30, 40, 50]
for i, num in enumerate(nums[1:], 1):
    # i=1 对应 num=20，i=2 对应 num=30，依此类推
    print(f"索引 {i}: 值 {num}")
```

### 4. 在列表推导式中使用

结合列表推导式可以高效筛选或转换带索引的元素：

```python
# 筛选满足条件的索引
indices = [i for i, x in enumerate(nums) if x > 0]

# 根据索引和值创建新的结构
result = [(i, x) for i, x in enumerate(nums) if condition]

# 在列表推导式中使用自定义起始索引
result = [(i, x) for i, x in enumerate(nums, 1) if condition]
```

### 5. 与 `zip()` 结合使用

处理多个序列时非常有用：

```python
# 同时遍历多个列表并获取索引
names = ["Alice", "Bob", "Charlie"]
scores = [95, 87, 92]
for i, (name, score) in enumerate(zip(names, scores)):
    print(f"#{i+1}: {name} 得分 {score}")

# 配合自定义起始索引
for i, (name, score) in enumerate(zip(names, scores), 1):
    print(f"#{i}: {name} 得分 {score}")
```



## len

### len() 函数的基本使用

`len()` 函数可以返回不同数据类型的长度：

- 字符串：返回字符串中字符的数量
- 列表、元组、集合：返回元素的数量
- 字典：返回键值对的数量

```python
def solution(nums):
    for i in range(len(nums)):
        # 通过索引访问元素
        # 这在需要同时访问元素索引和值时很有用
```



```python
def max_subarray(nums):
    dp = [0] * len(nums)  # 创建一个与输入数组同样长度的 DP 数组
    dp[0] = nums[0]
    # ...
```



## zip

`zip()` 函数能够将多个可迭代对象（如列表、元组、字符串等）的元素聚合起来，创建一个迭代器，该迭代器生成的结果元组中，第 i 个元组包含了来自每个输入可迭代对象的第 i 个元素。当最短的可迭代对象耗尽时，`zip()` 就会停止。

**1. 并行迭代多个可迭代对象**

这是 `zip()` 最核心和最常见的用途。当你需要同时处理来自不同列表或序列的对应元素时，`zip()` 非常方便。

```python
list1 = [1, 2, 3]
list2 = ['a', 'b', 'c']
list3 = [True, False, True]

for num, char, boolean_val in zip(list1, list2, list3):
    print(f"Number: {num}, Character: {char}, Boolean: {boolean_val}")
# 输出:
# Number: 1, Character: a, Boolean: True
# Number: 2, Character: b, Boolean: False
# Number: 3, Character: c, Boolean: True
```

**2. 创建字典**

如果一个列表包含键，另一个列表包含对应的值，`zip()` 可以轻松地将它们组合成一个字典。

```python
keys = ['name', 'age', 'city']
values = ['Alice', 30, 'New York']

my_dict = dict(zip(keys, values))
print(my_dict)
# 输出: {'name': 'Alice', 'age': 30, 'city': 'New York'}
```

**3. 解压序列 (Unzipping) / 矩阵转置**

与打包相反，`zip()` 结合星号操作符 `*` 可以用来“解压”一个已经打包好的序列。这个技巧常用于矩阵转置。

```python
zipped_data = [(1, 'a'), (2, 'b'), (3, 'c')]
numbers, letters = zip(*zipped_data)

print(numbers)  # 输出: (1, 2, 3)
print(letters)  # 输出: ('a', 'b', 'c')

# 矩阵转置示例
matrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

# zip([1, 2, 3], [4, 5, 6], [7, 8, 9])
transposed_matrix = [list(row) for row in zip(*matrix)]
# zip() 函数会从它接收的每个参数（在这里是三个列表）中依次取出相同索引位置的元素，并将它们组合成一个元组 (tuple)。这个过程会持续进行，直到最短的输入可迭代对象耗尽。在这个例子中，所有输入列表长度相同。
print(transposed_matrix)
# 输出: [[1, 4, 7], [2, 5, 8], [3, 6, 9]]
```

**4. 处理不等长的可迭代对象**

默认情况下，`zip()` 会在最短的可迭代对象耗尽时停止。

```python
list_a = [1, 2, 3, 4, 5]
list_b = ['x', 'y', 'z']

for item_a, item_b in zip(list_a, list_b):
    print(item_a, item_b)
# 输出:
# 1 x
# 2 y
# 3 z
```

如果你需要处理所有元素，即使可迭代对象的长度不同，可以使用 `itertools.zip_longest()`，它可以让你指定一个 `fillvalue` 来填充较短序列的缺失值。

```python
from itertools import zip_longest

list_a = [1, 2, 3, 4, 5]
list_b = ['x', 'y', 'z']

for item_a, item_b in zip_longest(list_a, list_b, fillvalue=None):
    print(item_a, item_b)
# 输出:
# 1 x
# 2 y
# 3 z
# 4 None
# 5 None
```

**5. 与 `enumerate` 结合使用**

有时你可能既需要索引，又需要并行迭代的元素。这时可以将 `enumerate` 与 `zip` 结合。

```python
names = ["Alice", "Bob", "Charlie"]
scores = [85, 90, 78]

for index, (name, score) in enumerate(zip(names, scores)):
    print(f"Rank {index + 1}: {name} - {score}")
# 输出:
# Rank 1: Alice - 85
# Rank 2: Bob - 90
# Rank 3: Charlie - 78
```

## dict

基于哈希表实现的快速键值对操作。

1. **初始化字典**

```python
# 空字典
d1 = {}
d2 = dict()

#直接初始化
d3 = {"name": "LeetCode", "year": 2024, "type": "platform"}

# 使用 fromkeys (所有键具有相同初始值)
keys = ['a', 'b', 'c']
d4 = dict.fromkeys(keys, 0)  # {'a': 0, 'b': 0, 'c': 0}

# 字典推导式
nums = [1, 2, 3]
d5 = {x: x*x for x in nums} # {1: 1, 2: 4, 3: 9}
d6 = {key: value for key, value in zip(keys, nums)} # {'a': 1, 'b': 2, 'c': 3}
```

2. **访问和修改元素**

```python
my_dict = {"count": 5, "char": 'a'}

# 通过键访问值 (若键不存在，会引发 KeyError)
current_count = my_dict["count"]

# 使用 get(key, default_value) 安全访问 (推荐，避免 KeyError)
# 若键不存在，返回 default_value (默认为 None)
char_value = my_dict.get("char")            # 'a'
non_existent_value = my_dict.get("id", None) # None
frequency = my_dict.get("word_freq", 0)   # 0 (如果 "word_freq" 不存在)

# 添加或修改键值对
my_dict["new_key"] = "new_value"   # 添加新键值对
my_dict["count"] = 10              # 修改已存在键的值

# 使用 setdefault(key, default_value)
# 若键存在，返回其值；若不存在，插入键并设其值为 default_value，然后返回 default_value
# 常用于确保键存在，特别是当值为列表或集合等需要后续修改时
my_dict.setdefault("tags", []).append("algorithms")
my_dict.setdefault("count", 0) # "count" 已存在，其值不变，返回 10

# 使用 update() 合并字典或可迭代的键值对
my_dict.update({"char": 'b', "language": "Python"})
my_dict.update([("items", [3,4,5]), ("version", 1.0)])
```

3. **删除元素**

```python
delete_dict = {"a": 1, "b": 2, "c": 3, "d": 4}

# 使用 del (若键不存在，会引发 KeyError)
del delete_dict["a"]

# 使用 pop(key, default_value)
# 删除键并返回其值。若键不存在且未提供 default_value，引发 KeyError。
# 若提供了 default_value，则键不存在时返回 default_value。
value_b = delete_dict.pop("b")                 # value_b 为 2
value_z = delete_dict.pop("z", "Not Found")  # value_z 为 "Not Found"

# popitem(): 删除并返回一个任意的 (键, 值) 对 (Python 3.7+ 为 LIFO)。
# 若字典为空，引发 KeyError。
if delete_dict: # 确保非空
    last_item = delete_dict.popitem()

# clear(): 清空字典中所有项
delete_dict.clear()
```

4. **检查键是否存在**

```python
check_dict = {"name": "LeetCode", "year": 2024}

# 使用 'in' 和 'not in' (最高效且 Pythonic 的方式)
is_name_present = "name" in check_dict      # True
is_age_present = "age" in check_dict        # False
is_year_absent = "year" not in check_dict   # False
```

5. **遍历字典**

```python
traverse_dict = {"apple": 3, "banana": 1, "cherry": 5}

# 遍历键 (默认迭代行为)
for key in traverse_dict:
    # value = traverse_dict[key]
    pass # 对 key 或 traverse_dict[key] 进行操作

# 遍历键 (显式使用 .keys())
for key in traverse_dict.keys():
    pass # 操作 key

# 遍历值 (使用 .values())
for value in traverse_dict.values():
    pass # 操作 value

# 遍历键值对 (使用 .items() - LeetCode 中非常常用)
for key, value in traverse_dict.items():
    pass # 同时操作 key 和 value
```

6. **字典的长度和复制**

```python
len_copy_dict = {"a": 10, "b": 20, "c": 30}

# 长度 (键值对数量)
num_items = len(len_copy_dict) # 3

# 浅拷贝 (Shallow Copy) - 创建一个新的字典，其键是原始键的副本，值是原始值的引用
# 对于不可变值（数字、字符串、元组）没问题
# 若值为可变对象（列表、其他字典），修改副本中的可变对象会影响原始字典
copied_dict1 = len_copy_dict.copy()
copied_dict2 = dict(len_copy_dict)

# 深拷贝 (Deep Copy) - 若字典包含嵌套的可变对象，且希望副本完全独立
import copy
# nested_dict = {"key1": "value1", "key2": [1, 2, 3]}
# deep_copied_dict = copy.deepcopy(nested_dict)
# deep_copied_dict["key2"].append(4) # nested_dict["key2"] 不会改变
```

## collections

### collections.Counter

`Counter` 是一个字典的子类，用于统计可哈希对象的出现次数。它非常适合用来快速统计字符、数字或任何其他可哈希元素的频率。

```python
from collections import Counter

# 初始化
c1 = Counter('leetcode')
print(f"c1: {c1}") # 输出: c1: Counter({'e': 3, 'l': 1, 't': 1, 'c': 1, 'o': 1, 'd': 1})

c2 = Counter(['a', 'b', 'a', 'c', 'b', 'a'])
print(f"c2: {c2}") # 输出: c2: Counter({'a': 3, 'b': 2, 'c': 1})

c3 = Counter(a=3, b=2, c=1)
print(f"c3: {c3}") # 输出: c3: Counter({'a': 3, 'b': 2, 'c': 1})

# 访问计数
print(f"Count of 'e' in c1: {c1['e']}")  # 输出: Count of 'e' in c1: 3
print(f"Count of 'z' in c1: {c1['z']}")  # 输出: Count of 'z' in c1: 0

# 增加/更新计数
c1.update('leet')
print(f"c1 after update('leet'): {c1}")
# 输出: c1 after update('leet'): Counter({'e': 5, 'l': 2, 't': 2, 'c': 1, 'o': 1, 'd': 1})

c1['c'] += 1
print(f"c1 after c1['c'] += 1: {c1}")
# 输出: c1 after c1['c'] += 1: Counter({'e': 5, 'l': 2, 't': 2, 'c': 2, 'o': 1, 'd': 1})

# 获取元素
elements_list = list(c1.elements())
print(f"Elements of c1: {elements_list}") # 输出会比较长，例如: ['l', 'l', 'e', 'e', 'e', 'e', 'e', ...]

# 最常见的元素
most_common_c1 = c1.most_common(2)
print(f"Two most common in c1: {most_common_c1}") # 输出: Two most common in c1: [('e', 5), ('l', 2)]

# 算术运算
cnt1 = Counter(a=2, b=1, x=5) # Adding 'x' for distinctness in subtraction
cnt2 = Counter(a=1, b=3, y=2) # Adding 'y' for distinctness
print(f"cnt1: {cnt1}")
print(f"cnt2: {cnt2}")

print(f"cnt1 + cnt2: {cnt1 + cnt2}") # 加法，计数相加
print(f"cnt1 - cnt2: {cnt1 - cnt2}") # 减法，保留正数计数 (b will be 1-3=-2, so not shown)
print(f"cnt2 - cnt1: {cnt2 - cnt1}")
print(f"cnt1 & cnt2: {cnt1 & cnt2}") # 交集，取最小计数
print(f"cnt1 | cnt2: {cnt1 | cnt2}") # 并集，取最大计数
```

### collections.deque

`deque` (double-ended queue) 是一种类似列表的容器，支持在两端进行快速的添加（append）和弹出（pop）操作 (O(1) 时间复杂度)。它非常适合实现队列（FIFO）和栈（LIFO）。

```python
from collections import deque

# 初始化
d_empty = deque()
print(f"Empty deque: {d_empty}")

d_list = deque([1, 2, 3, 4])
print(f"Deque from list: {d_list}")

d_str = deque('leetcode')
print(f"Deque from string: {d_str}")

d_maxlen = deque(maxlen=3) # 创建一个固定最大长度的deque
print(f"Deque with maxlen=3: {d_maxlen}")

# 从右端添加/删除
d_list.append(5)
print(f"After append(5): {d_list}")
item_pop = d_list.pop()
print(f"Popped item from right: {item_pop}, deque: {d_list}")

# 从左端添加/删除
d_list.appendleft(0)
print(f"After appendleft(0): {d_list}")
item_popleft = d_list.popleft()
print(f"Popped item from left: {item_popleft}, deque: {d_list}")

# 扩展
d_list.extend([6, 7])
print(f"After extend([6, 7]): {d_list}")
d_list.extendleft([-1, -2]) # 注意顺序: -2 会在 -1 的左边
print(f"After extendleft([-1, -2]): {d_list}") #  deque([-2, -1, 1, 2, 3, 4, 6, 7])

# 旋转
d_rotate = deque([1, 2, 3, 4, 5])
print(f"Original for rotation: {d_rotate}")
d_rotate.rotate(2)  # 向右旋转2个位置
print(f"After rotate(2): {d_rotate}") # deque([4, 5, 1, 2, 3])
d_rotate.rotate(-1) # 向左旋转1个位置
print(f"After rotate(-1): {d_rotate}") # deque([5, 1, 2, 3, 4])

# 访问元素
print(f"First element of d_rotate: {d_rotate[0]}")
print(f"Last element of d_rotate: {d_rotate[-1]}")

# 最大长度 (如果设置了)
d_maxlen.append(1)
d_maxlen.append(2)
d_maxlen.append(3)
print(f"d_maxlen after 3 appends: {d_maxlen}") # deque([1, 2, 3], maxlen=3)
d_maxlen.append(4)
print(f"d_maxlen after 4th append: {d_maxlen}") # deque([2, 3, 4], maxlen=3)
d_maxlen.appendleft(0)
print(f"d_maxlen after appendleft(0): {d_maxlen}") # deque([0, 2, 3], maxlen=3)
```

### collections.defaultdict

`defaultdict` 是字典 (`dict`) 的一个子类，它在字典中查找一个不存在的键时，会为这个键提供一个默认值，而不会引发 `KeyError`。你需要提供一个工厂函数（如 `int`、`list`、`set` 等）在创建 `defaultdict` 时，当访问不存在的键时，该工厂函数会被调用来生成默认值。

```python
from collections import defaultdict

# 初始化
# 当键不存在时，默认值为 0
dd_int = defaultdict(int)
# 当键不存在时，默认值为一个空列表 []
dd_list = defaultdict(list)
# 当键不存在时，默认值为一个空集合 set()
dd_set = defaultdict(set)
# 使用 lambda 定义更复杂的默认值
dd_custom = defaultdict(lambda: "N/A")

# 访问/赋值
dd_list['fruits'].append('apple')
dd_list['fruits'].append('banana')
dd_list['vegetables'].append('carrot')
print(f"dd_list: {dd_list}")
# 输出: dd_list: defaultdict(<class 'list'>, {'fruits': ['apple', 'banana'], 'vegetables': ['carrot']})

print(f"dd_int['count'] (before assignment): {dd_int['count']}") # 输出: 0
dd_int['count'] += 1
print(f"dd_int['count'] (after increment): {dd_int['count']}") # 输出: 1
print(f"dd_int: {dd_int}") # defaultdict(<class 'int'>, {'count': 1})

print(f"dd_set['items'] (before add): {dd_set['items']}") # 输出: set()
dd_set['items'].add('item1')
print(f"dd_set: {dd_set}") # defaultdict(<class 'set'>, {'items': {'item1'}})

print(f"dd_custom['missing_key']: {dd_custom['missing_key']}") # 输出: N/A
print(f"dd_custom: {dd_custom}") # defaultdict(<function <lambda> at ...>, {'missing_key': 'N/A'})
```

