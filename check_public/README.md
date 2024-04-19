Stavar Laurentiu-Cristian, Grupa 322CC
Homework 1 PA
--------------------------------------------------------------------------------

Total implementation time: ~16h

1. servere.cpp:
   
- Complexity: O(n * (log n)), where n = number of servers.
- Explanation:
  - For every server, read the power and cost.
  - After, do a binary search for the final answer, in (-inf, max(power)).
    - Check if all the absolute values, are positive.
    - If they aren't continue searching in the left side.
    - Absolute values are |X - cost[i]| == power[i] - current_solution.
    - For every ecuation like the one above compute the interval 
    of solutions.
    - Intersect all the intervals computed, to find the solution interval.
    - If the solution interval is'nt a valid one, continue searching 
    in the left side.
    - If the solution interval is a valid one, save the solution as the 
    current best one and continue searching in the right side.

1. colorare.cpp
- Complexity: O(n * (log n)), where n = number of zones.
- Explanation:
  - Read the number of zones and iterate trough each one.
  - Read the number of rectangles in the current zone and the zone type.
  - Append the first rectangle in the zone to the painting.
    - If's the first rectangle in the painting then initiate the 
    solution properly => 6 for Horizontal and 3 for Vertical.
    - If the previous zone was a HORIZONTAL one, then update the 
    solution properly => new_solution = (solution * 3) % MOD.
    - If the previous zone was a VERTICAL one, then update the 
    solution properly => new_solution = (solution * 2) % MOD.
    - Update prev_zone_type and the number of rectangles.
  - Append the rest of the rectangles to painting.
    - If the zone type is Horizontal 
    => new_solution = (solution * fast_pow(3, rectangles, MOD)) % MOD.
    - If the zone type is Vertical
    => new_solution = (solution * fast_pow(2, rectangles, MOD)) % MOD.

1. compresie.cpp
- Complexity: O(n + m), where n = size of the first array
                                m = size of the second array
- Explanation:
  - Read the two arrays.
  - Compute the sum of elements for both arrays.
  - If the sums are not equal => there is no solution.
  - Else take two pointers, one in "a" and one in "b".
  - If the current element in "a" is greater than the current element
  in "b", then compress "b" by making b[index] += b[index++ - 1].
  - If the current element in "b" is greater than the current element
  in "a", then compress "a" by making a[index] += a[index++ - 1].
  - Else the current element in both "a" and "b" is the same so we
  found a new element in the solution and we can skip to the next
  element in both of the two arrays.

4. criptat.cpp
- Complexity: O(n * (m + (log n))), where n = number of words
                                m = size of the longest word
- Explanation:
  - Read all the words.
  - Get all the unique characters from "words" array to form 
  the alphabet.
  - For each character in the alphabet, we will consider it the 
  dominant character.
    - Compute the number of dominant characters for each word.
    - Populate the vector of word details (the actual word, number of 
    dominant chars, length, ratio = number of dominant chars / length).
    - Sort the words by the ratio.
    - Compute the maximum length of the password that can be formed
    by concatenating the words in the order given by the sorted
    vector, choosing the words that keep true the condition
    num_of_dominant_chars > length / 2.
    - Update the maximum length
  
5. oferta.cpp
- Complexity: O(n), where n = number of prices
- Explanation:
  - Read the products prices.
  - Compute the base cases for dp.
  - Using dp, compute the minimum amount of money needed to 
  buy the first i products.
  - For the recurention formula, we take the minimum value of the
  three cases:
    a. Take the current product with full price .
        => dp[i - 1] + prices[i - 1]
    b. Take products i - 1 and product i together, and get the 50% 
    discount for the cheapest of them.
        => dp[i - 2] + min(prices[i - 1], prices[i - 2]) / 2.0 +
        max(prices[i - 1], prices[i - 2])
    c. Take products i - 2, i - 1, i together, and get full discount
    on the cheapest one.
        => dp[i - 3] + prices[i - 3] + prices[i - 2] + prices[i - 1] -
        min(prices[i - 3], min(prices[i - 2], prices[i - 1]))
  - Return the solution => dp[n].
