# Sliced or Copied?

#### Output
```
--===# B #===--
B ctor
  b.x: 0
  b.x: 3
  b.x: 8
B copy ctor
D convert ctor
x: 8
D destructor
B destructor
  b.x: 8
  b.x: 8
B destructor

--===# const B #===--
B assign ctor 1
  b.x: 1
B copy ctor
D convert ctor
x: 1
D destructor
B destructor
  b.x: 1
  b.x: 1
B destructor

--===# D #===--
B ctor
D ctor
x: 0
x: 3
x: 8
x: 11
x: 16
D destructor
B destructor

--===# const D #===--
B assign ctor 9
D assign ctor 9
  b.x: 9
x: 9
  b.x: 9
x: 9
  b.x: 9
D destructor
B destructor
```

## Conclusion

Passing by reference slices.
