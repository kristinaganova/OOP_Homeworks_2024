
# Playlist 

Each song has the following properties:

- **Name**: Up to 64 characters
- **Duration**
- **Genre**: Can be a single genre or a combination of the following genres: Rock, Pop, Hip-Hop, Electronic, Jazz (e.g., Rock & Pop)
- **Content**: A sequence of up to 256 bytes, read from binary files.

The genre should be stored in a data structure/member that takes up no more than **1 byte**.

### Song Modifications
The content of a song can be modified in one of the following ways:

1. **Rhythm Creation**: Turn every k-th bit from the end into `1` (to create additional rhythm).
    - Example:  
    Input: `0100 0110 0100 0110`, `k=3`  
    Output: `0100 1111 0110 0110`

2. **Mixing Songs**: Combine two songs' contents by setting a bit to `1` if it is `1` in only one of the songs. If the bit is `1` in both, it is set to `0`. If the songs have different lengths, only as many bytes as the shorter song are mixed.
    - Example 1:  
      Song 1: `0110 0001`  
      Song 2: `0101 0101`  
      Result: `0011 0100`

    - Example 2:  
      Song 1: `0101 1010 0101 1010`  
      Song 2: `0111 0111`  
      Result: `0010 1101 0101 1010`

    - Example 3:  
      Song 1: `0111 0111`  
      Song 2: `0101 1010 0101 1010`  
      Result: `0010 1101`

### Playlist Functionalities
The playlist can contain up to **30 songs** and supports the following operations:

1. **Add a Song**: Add a song with a name, duration, genre, and content read from a binary file.
    - Genre is passed as a string (e.g., `"rp"` means Rock and Pop).

2. **Print Songs**: Print the songs in the playlist, showing:
    - Name
    - Duration in `hours:minutes:seconds`
    - Genre

3. **Search by Name**: Find a song by its unique name.

4. **Search by Genre**: Find all songs that include a specific genre.

5. **Sort by Duration**: Sort the songs based on their duration.

6. **Sort by Name**: Sort the songs alphabetically by their name.

7. **Modify a Song**: Modify the content of a song using the specified operations.

8. **Save a Song**: Save a song to a binary file.

## Example Usage

### Song Content (Binary File)
Example file contents:

- `song1.dat`: `“V”`  
  Binary: `0101 0110`

- `song2.dat`: `“Ua”`  
  Binary: `0101 0101 0110 0001`

### Code Example
```cpp
Playlist p;
p.add(“Song 2”, 0, 1, 55, “rp”, “song2.dat“);
p.add(“Song 1”, 0, 1, 5, “p”, “song1.dat“);

p.print(); 
// Song 2, 00:01:55, Pop&Rock
// Song 1, 00:01:05, Pop

p.sortByName();
p.print(); 
// Song 1, 00:01:05, Pop
// Song 2, 00:01:55, Pop&Rock

p.find(“Song 1”); 
// Song 1, 00:01:05, Pop

p.findGenre(‘p’);
// Song 1, 00:01:05, Pop
// Song 2, 00:01:55, Pop&Rock

p.findGenre(‘r’);
// Song 2, 00:01:55, Pop&Rock

p.mix(“Song 1”, “Song 2”);
p.save(“Song 1”, “song3.dat”);
// song3.dat content: “S” // 0000 0011
```

## Constraints
- A song name can contain a maximum of **64 characters**.
- Song content is up to **256 bytes**.
- The playlist can hold a maximum of **30 songs**.
- **Genre** information must take up **1 byte**.
