
# MultiSet Class

## Overview

The `MultiSet` class represents a multiset of numbers in the range `[0, n]`, where `n` is defined during initialization. Each number can occur in the multiset a maximum of `2^k - 1` times, where `k` specifies the number of bits allocated for storing the count of each number.

This implementation is optimized for memory efficiency and supports various operations for managing and manipulating multisets.

---

## Features

### 1. Add a Number
Add a number to the multiset. If the number is already at its maximum count (`2^k - 1`), it cannot be incremented further.

### 2. Count Occurrences
Retrieve the number of times a specific number appears in the multiset.

### 3. Print All Numbers
Print all numbers that exist in the multiset along with their respective counts.

### 4. Print Memory Representation
Display the internal memory representation of the multiset, showcasing how the counts are stored.

### 5. Serialization/Deserialization
Save the multiset to a binary file for persistence and load it back into memory when needed.

### 6. Intersection/Difference
Perform set operations such as:
- **Intersection**: Find the common elements between two multisets and their minimum occurrences.
- **Difference**: Subtract the counts of one multiset from another.

### 7. Complement
Compute the complement of the multiset. If a number appears `p` times, it will appear `2^k - 1 - p` times in the complement.

---

## Example Usage

### Initialization
```python
# Create a MultiSet with a range of 0 to 10 and up to 3 bits for storing counts
ms = MultiSet(n=10, k=3)
```

### Adding Numbers
```python
ms.add(1)
ms.add(1)
ms.add(2)
```

### Checking Occurrences
```python
print(ms.count(1))  # Output: 2
print(ms.count(2))  # Output: 1
print(ms.count(3))  # Output: 0
```

### Printing Numbers
```python
ms.print_all()
# Output:
# Number: 1, Count: 2
# Number: 2, Count: 1
```

### Printing Memory Representation
```python
ms.print_memory()
# Example Output: [2, 1, 0, 0, 0, 0, 0, 0, 0, 0]
```

### Serialization/Deserialization
```python
# Save the current state of the multiset to a binary file
ms.serialize("multiset.dat")

# Load the state from the binary file
ms2 = MultiSet.deserialize("multiset.dat")
```

### Complement of the MultiSet
```python
ms_complement = ms.complement()
ms_complement.print_all()
# Output (assuming k=3):
# Number: 1, Count: 5
# Number: 2, Count: 6
# Number: 3, Count: 7
```

### Intersection and Difference
```python
# Create another multiset
ms2 = MultiSet(n=10, k=3)
ms2.add(1)
ms2.add(2)
ms2.add(2)

# Intersection
ms_intersection = ms.intersection(ms2)
ms_intersection.print_all()
# Output:
# Number: 1, Count: 1
# Number: 2, Count: 1

# Difference
ms_difference = ms.difference(ms2)
ms_difference.print_all()
# Output:
# Number: 1, Count: 1
# Number: 2, Count: 0
```

---

## Implementation Notes

- **Memory Efficiency**: The multiset is stored using an array, where each index corresponds to a number, and the value at the index is its count.
- **Count Constraints**: The count for any number cannot exceed `2^k - 1` to ensure memory efficiency and predictable behavior.
- **Binary File Format**: Serialization stores the multiset as a compact binary representation for efficient storage and retrieval.

---

## Constraints

1. **Range**: Numbers are limited to the range `[0, n]`.
2. **Maximum Count**: A number can appear at most `2^k - 1` times.
3. **Optimized Memory**: The implementation uses only the necessary memory to store counts.
