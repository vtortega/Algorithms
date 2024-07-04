# Graph Faces Visualization

The problem approached here is to find the faces of a graph that is connect. The algorithm consists in checking, for each vertex of the graph, the edge that has the smallest angle clockwise or not, depending if its passing through the inside or outside of the edge. And that's the catch of the algorithm. We consider one edge equivalent to two half edges so that we only pass on each half edge once, so that the faces are formed correctly. That way we avoid appendixes too:

<img width="358" alt="Screenshot 2024-07-04 at 02 56 40" src="https://github.com/vtortega/Algorithms/assets/112141870/3d8e7e5b-b89c-4b62-8d99-ddc872ec44de">

This algorithm is not, by far, the best to find the faces. Its complexity can approach being exponential if a graph is fully connected and the algorithm starts checking the wrong edges. We cold have floating point problem with the radians of the angles too, but that's an easier problem to solve.
One upgrade that could be made to this algorithm is to sort the edges as it passes through them for the first time, so that the next vertex knows its angle already, but it would take more memory.

## Files

- `faces_finder.cpp`: A C++ program that reads the graph input and outputs all faces.
- `faces_ploter.py`(recent addition): A Python code that reads the same graph input summed with the `faces_finder` output and sequentially draws each face in separate plots, labeling which face it is.
- `examples_input.txt`

## Input Format

The input format for the C++ program is as follows:

1. The first line contains two integers, `N` and `M`, representing the number of vertices and edges of the input graph.
2. The next `N` lines each contain:
   - Two real numbers `xi` and `yi` representing the coordinates of vertex `i` in the Cartesian plane.
   - An integer `di`, the degree of vertex `i`.
   - `di` integers representing the neighbors of vertex `i`.

The output format fot the C++ program is as follows:

1. The first line contains two integers, `N` and `M`, representing the number of vertices and edges of the input graph.
2. The next `N` lines each contain:
   - Two real numbers `xi` and `yi` representing the coordinates of vertex `i` in the Cartesian plane.
   - An integer `di`, the degree of vertex `i`.
   - `di` integers representing the neighbors of vertex `i`.
3. The next `F` lines each describe a face:
   - An integer `si` representing the size of the `i-th` face.
   - `si` integers representing the vertices on the boundary of the face, in order.

The output format of the C++ code matches the input of the Python code so that you just need to get the output on input into the python program.

The input format for the python program is as follows:

1. The first line contains two integers, `N` and `M`, representing the number of vertices and edges of the input graph.
2. The next `N` lines each contain:
   - Two real numbers `xi` and `yi` representing the coordinates of vertex `i` in the Cartesian plane.
   - An integer `di`, the degree of vertex `i`.
   - `di` integers representing the neighbors of vertex `i`.
3. The next `F` lines each describe a face:
   - An integer `si` representing the size of the `i-th` face.
   - `si` integers representing the vertices on the boundary of the face, in order.

One example of a face outputed by `faces_ploter.py`:



The output format of the C++ code matches the input of the Python code so that you just need to get the output on input into the python program.

### Example Input of C++ program

    8 11\
    0 0 2 2 3\
    1 1 4 1 4 5 7\
    1 -1 5 1 4 5 6 7\
    2 0 2 2 3\
    4 0 3 2 3 6\
    4 -1.5 2 3 5\
    -3 0 3 2 3 8\
    -2 0 1 7\

### Example of Output of C++ program

    5\
    7 1 3 7 8 7 2 1\
    6 2 7 3 6 5 2\
    5 1 2 4 3 1\
    5 2 5 3 4 2\
    4 3 5 6 3\

### Example of Input for Python program

    8 11\
    0 0 2 2 3\
    1 1 4 1 4 5 7\
    1 -1 5 1 4 5 6 7\
    2 0 2 2 3\
    4 0 3 2 3 6\
    4 -1.5 2 3 5\
    -3 0 3 2 3 8\
    -2 0 1 7\
    5\
    7 1 3 7 8 7 2 1\
    6 2 7 3 6 5 2\
    5 1 2 4 3 1\
    5 2 5 3 4 2\
    4 3 5 6 3
