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

![Figure_1](https://user-images.githubusercontent.com/2964258/132262641-1447c047-f2eb-4fb2-a471-793835a84718.png)

QuadTree also can be applied to image compression, as in this example:

![qt_compress_4](https://user-images.githubusercontent.com/2964258/133005737-ba11f535-c936-4de2-adf1-5b54f6232e24.png)
