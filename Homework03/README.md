# Partial Function Task

## Task Description

We need to implement an **abstract base class** `PartialFunction` that maps 32-bit integers to 32-bit integers. This class must include:

1. **A method to check if the function is defined at a given point.**
2. **A method to compute the function's result for a given input.**

### Derived Classes of `PartialFunction`

1. **Criterion-Based Partial Function**:
   - Takes a function in the constructor, which, for a given input, returns a tuple:
     - Whether the function is defined for that input.
     - If defined, the function's result.

2. **Maximum of Partial Functions**:
   - Takes multiple partial functions in the constructor.
   - The result is defined at a given point only if **all** input functions are defined at that point.
   - The result is the maximum of the results from the input functions.

3. **Minimum of Partial Functions**:
   - Similar to "Maximum," but the result is the **minimum** of the results from the input functions.

---

## Input File Format (`func.dat`)

1. The file starts with two **16-bit unsigned integers**:
   - `N`: Maximum 32.
   - `T`: Determines the type of function. Possible values for `T`:

### Function Types (`T`):

| **T** | **Description**                                                                                 |
|-------|-------------------------------------------------------------------------------------------------|
| **0** | 2N integers follow (`arg1, ..., argN, res1, ..., resN`). Function defined only for given arguments. |
| **1** | N integers follow. The function is undefined for these values and returns `x` for all others.     |
| **2** | N integers follow. Function returns `1` for these values and `0` otherwise. Defined for all `x`.  |
| **3** | N null-terminated strings follow. Each string is a path to a binary file. Their **maximum** defines the function. |
| **4** | N null-terminated strings follow. Each string is a path to a binary file. Their **minimum** defines the function. |

---

## Example File Structure

### `func.dat`:
```
3 3
first.dat
second.dat
third.dat
```

### `first.dat`:
```
7 0
0 1 2 3 5 6 7
0 3 3 3 4 4 0
```

### `second.dat`:
```
2 1
3 5
```

### `third.dat`:
```
4 2
0 5 6 7
```

---

## Example Program Execution

**Input:**  
`a = 0, b = 10`

**Expected Output:**
```
f(0) = 1   f(1) = 3   f(2) = 3   f(6) = 6   f(7) = 7
```
