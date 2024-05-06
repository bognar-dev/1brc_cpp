# The One Billion Row Challenge:

Data Processing at Scale
What is the best way of processing a billion rows of data in the least amount of runtime?

## Author

NIKLAS STEFAN BOGNAR  
Comp. Sci. 203  
Algorithms and Data Structures  
[GitHub Repository](https://github.com/bognar-dev/1brc_cpp)

## 1. Introduction

Initially set up by Gunnar Morling, the One Billion Row Challenge (1BRC) [1] primarily targeted Java developers, tasking
them with evaluating a large temperature set of data. However, this study explores an attempt to approach this using the
C programming language. By adapting ideas from Java implementations and applying them to C, to investigate the
possibilities of C in effectively processing big datasets. The study investigates techniques and evaluates their success
in terms of runtime reduction.

## 2. Objective

## 3. Iterative Versions

### 1. BASELINE Linear Search (655.39s)

Linear search has an average Big-O notation of O(n), indicating that it runs in linear time. This algorithm traverses
the entire dataset sequentially until it finds the desired element, making it inefficient for large datasets as it
requires multiple passes through the list. In this implementation, each line of the dataset is read sequentially, and
then a linear search is performed to process the data. This approach is suboptimal as it entails both the sequential
reading of lines and subsequent linear search operations.

### 2. Hash Map  With Linear Probing (122.27s)

The hashmap implementation using linear probing[1] and the Bernstein hash[2] function exhibits different runtime
complexities based on the specific situation. On average, both insertion and search operations have a constant time
complexity, represented as O(1), assuming there are very few collisions. The effectiveness of the hashmap is derived
from the direct mapping of keys to their respective slots. However, in the event of a worst-case scenario with frequent
collisions, the runtime complexity of both insertion and search operations deteriorates to linear time, denoted as O(n).
This phenomenon happens when multiple attempts are needed to resolve collisions, resulting in the traversal of the full
hashmap. Consequently, the algorithm's efficiency relies heavily on the efficacy of the hash function and the
arrangement of components within the hashmap.

### 3. Custom double parsing (62.12s)

Other studies found that the native strod() implementation is slow[3]. The tests on 1 billion string to double
conversions reveal a significant improvement in performance with the custom parsing implementation. While the regular
parsing method took approximately 89.02 seconds to process the data, the custom parsing technique reduced the processing
time drastically to just 2.42 seconds. This enhancement translates to an speedup factor of about 36% in the separate
test, highlighting the efficiency gains achieved by adopting the custom parsing approach.

### 4. fread() in chunks (50.66s)

Instead of reading line by line, this approach improves performance by reading in the file in chunks using the fread()
function[4].

### 5. Loop Unrolling (46.05s)

Loop unrolling involves stretching loops in the source code to execute several iterations within a single loop
iteration. This reduces the overhead of loop control and enhances instruction-level parallelism. The programme optimises
performance and throughput by unrolling loops, efficiently utilising the processor's pipeline capabilities.. In
addition, loop unrolling improves the way memory is accessed, which reduces the number of cache misses and improves the
organisation of data, resulting in even greater performance improvements.
Reduced overhead in tight loops due to pre-calculated offsets. Possible increase in register usage, impacting
performance.

### 6. Parallelization (25.99s)

Threading is one of the most used techniques for reducing the runtime of big data processing tasks. Here it is
implemented by creating multiple threads to concurrently process chunks of data from a file. Each thread independently
calculates statistics for groups identified by keys, leveraging hashmaps and linear probing for efficient data
retrieval. Finally, the results from all threads are combined to generate the final aggregated output.
Amdahl's Law suggests that the speedup is bound by the sequential component of the program, stressing the requirement of
improving parallelizable operations. Gustafson's Law shows that the speedup can be considerable if the problem size
grows with the number of processors. In the case of processing a billion rows of data, the ideal size for attaining
maximum speedup relies on how efficiently the workload can be spread among the available processors.
P = proportion of the program for parallelisation.
𝑁 = number of processors available.

### 7. mmap()(18.79s)

The use of mmap() in the program can significantly improve performance by allowing the entire file to be mapped into
memory, avoiding the need for repeated disk reads and reducing I/O overhead. This optimization ensures faster data
access and processing, particularly beneficial when dealing with large datasets such as billions of rows, where disk I/O
operations can become a bottleneck. However, it's essential to find the optimal chunk size for mmap() to balance memory

## 4. Analysis

### Data Collection

Conducted experiments with varying file sizes: 1000, 10000, 100000, 1000000, 10000000, 100000000, and 1000000000 lines.
Recorded performance metrics for different algorithms to analyze runtime efficiency.

### Runtime Information

Analyzed runtime (in seconds) of each algorithm across different file sizes.
Compared the performance of linear search, hashmap, parse double, fread chunks, loop unrolling, parallelization, and
memory mapping techniques.

### Relative Speedup

Calculated the relative speedup for each optimization technique compared to the baseline (linear search).
Demonstrated the efficiency gains achieved by each optimization approach.

### Observations

Hashmap and parallelization demonstrated significant speedups across all file sizes.
For the largest dataset (1000000000 lines), hashmap achieved a runtime of 27.86 seconds, a speedup of 22.58x compared to
linear search.
Parallelization reduced runtime to 26 seconds, showing a 27.86x speedup.
Memory mapping optimized file access:
Memory mapping reduced runtime from 638.15 seconds (baseline) to 22.58 seconds, a 28.3x speedup for the largest dataset.

## 5. Results/Findings

- Optimization Impact:
    - Hashmap and parallelization led to substantial speedup compared to linear search.
    - Parse double and fread chunks enhanced data processing efficiency significantly.
    - Memory mapping improved file access time significantly.
- Effective Combination:
    - Utilizing hashmap with parse double, fread chunks, and parallelization yielded the best performance.
    - Synergistic combination of multiple optimization techniques showcased optimal performance gains.
- Scalability:
    - Algorithms demonstrated scalability with increasing dataset sizes.
    - Parallelization proved beneficial for larger datasets, indicating its relevance in handling big data efficiently.

## 6. Conclusion

The implementation of optimized algorithms and parallel processing techniques is crucial for improving runtime
efficiency in data processing tasks. The results of this study highlight the importance of algorithmic efficiency and
parallelism, highlighting their significant impact on the performance of data processing systems. By leveraging
optimized algorithms and parallel processing, organizations can achieve substantial improvements in runtime efficiency,
enabling faster and more effective data analysis and decision-making processes.

## References

1. AGRAWAL, Shraddha. 2024. ‘One Billion Rows Challenge in Golang’. ByteSizeGo [online]. Available
   at: https://www.bytesizego.com/blog/one-billion-row-challenge-go [accessed 6 May 2024].
2. DAVIDSON, Jack W and SANJAY JINTURKAR. 2001. ‘An Aggressive Approach to Loop Unrolling’. An Aggressive Approach to
   Loop Unrolling.
3. EPPSTEIN, David. 2024. ‘Linear Probing Made Easy’. 11011110.github.io [online]. Available
   at: https://11011110.github.io/blog/2011/10/13/linear-probing-made.html [accessed 6 May 2024].
4. GORAN VELKOSKI, MARJAN GUSEV and SASKO RISTOV. 2014. ‘The Performance Impact Analysis of Loop Unrolling’. The
   performance impact analysis of loop unrolling.
5. GRENNING, James W. 2011. Test Driven Development for Embedded C. Pragmatic Bookshelf.
6. GUSTAFSON, John L. 2007. ‘Amdahl’s Law’. web.archive.org [online]. Available
   at: https://web.archive.org/web/20070927040654/http://www.scl.ameslab.gov/Publications/Gus/AmdahlsLaw/Amdahls.html [accessed 6 May 2024].
7. HELLER, Steve. 2014. Efficient C/C++ Programming. Academic Press.
8. HORVATH, Adam. 2012. ‘Code Unwinding - Performance Is Far Away’. Adam Horvath’s blog [online]. Available
   at: https://blog.teamleadnet.com/2012/02/code-unwinding-performance-is-far-away.html [accessed 6 May 2024].
9. LEMIRE’S, Daniel. 2020. ‘Fast Float Parsing in Practice – Daniel Lemire’s Blog’. Daniel Lemire’s Blog [online].
   Available at: https://lemire.me/blog/2020/03/10/fast-float-parsing-in-practice/ [accessed 6 May 2024].
10. ‘Loop Unrolling - an Overview | ScienceDirect Topics’. n.d. www.sciencedirect.com [online]. Available
    at: https://www.sciencedirect.com/topics/computer-science/loop-unrolling#:~:text=Loop%20unrolling%20is%20a%20technique%20used%20to%20increase%20the%20number.
11. MORLING, Gunnar. 2024. ‘The One Billion Row Challenge’. www.morling.dev [online]. Available
    at: https://www.morling.dev/blog/one-billion-row-challenge/ [accessed 3 May 2024].
