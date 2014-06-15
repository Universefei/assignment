Dynamic program for DNA sequeue alignment
=========================================

This is experiment export markdown file, you should see the report [here]()
rather than browsing this plain markdown file.

## personal info
* Name       : 费伦宙
* Student NO : 1303121797

## Platform
* OS         : Ubuntu 14.04
* CPU        : intel p7450
* Memory     : DDR3 1066hz 4G

## Introduction
This is a application of dynamic programming that divides problems to smaller 
ones, and the bigger problems ultilize the smaller ones' results. Recursivly, 
we can get final solution.

## Related work
* Analysis
* Coding
* Executing and Testing

## Algorithm

### Data structure
Using two 2-demension to store outcomes.
* dynamicMatrix     :  store dynamic result of all subproblems
* solutionMatrix    :  store symbals for visual analysis.

### Algorithm discription
Just using dynamic programming can solve this problem.

First handle the boundary situation of dynamic programming.
Then figure out other situation leverage the boundary situation and other solved
situation.

The boundary situation is dynamicMatrix\[maxverticalLength\]\[...\] and 
dynamicMatrix\[...\]\[maxHorizonalLength\]. Those data can filled with ease.

Then leverage subproblems, right, down and diagonal element in the matrix, which
are already solved, to find out which solution embrace the minimal penalty,
finally to get optimial alignment, and to fill corresponding solutionMatrix.

You can get in-depth perspective on the algorithm from the source code comments.

## Experiments & Discussion


## Conclusion
We can get the optimal alignment solution from the solutionMatrix output.

