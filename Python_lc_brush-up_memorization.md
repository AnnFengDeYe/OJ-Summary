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

