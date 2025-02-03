## Segment distance
### Calculate distance between two segmetns.
#### Usage
Takes 12 floating points numbers - coordinates of 2 segments (begin and end).
Write to output 1 number - distance between theese two segments.
```
.\segment_distance.exe 1 0 0  2 0 0   0 1 0  0 2 0
1.41421
```

### constexpr
Feel free to visit [constexpr branch](https://github.com/SmirnovBoris/SegmentDistance/tree/constexpr).

```c++
    constexpr point a{0., 0., 1.};
    constexpr point b{0., 0., 2.};
    constexpr sector s{a, b};
    static_assert(s.get_first_point().get_z() == 1.);

    constexpr sector t{point{1., 0., 0.}, point{2., 0., 0.}};

    constexpr scalar_type dist = geom::distance(s, t);
    constexpr scalar_type ans = 1.4142135623730951;
    static_assert(ans - TestFixture::eps < dist && dist < ans + TestFixture::eps);
```
