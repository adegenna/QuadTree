Library for computing a quadtree data structure on unstructured 2D data.

Copyright 2021 by Anthony M. DeGennaro (ISC License).

**Installation**

```sh
cd [/PATH/TO/QuadTree]
mkdir build
cd build
cmake ../
make
```

**Example Driver**

```sh
cd [/PATH/TO/QuadTree]/build
./ex_rand

cd [/PATH/TO/QuadTree]/examples
python plot_qt.py
```

This example should compute a quadtree on noisy sinusoidal data:

![sinqt](https://user-images.githubusercontent.com/2964258/132142832-51bf6030-91fb-4fbb-8fb0-7461d8ded9c8.png)
