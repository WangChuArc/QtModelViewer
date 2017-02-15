#pragma once
#ifndef _TEST_CUBE_H_
#define _TEST_CUBE_H_

class TestCube
{
public:
    static constexpr float data[] =
    {
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f
    };

    static constexpr unsigned int index[] =
    {
        0, 1, 2,    2, 1, 3,
        2, 3, 6,    6, 3, 7,
        4, 6, 7,    4, 7, 5,
        4, 5, 0,    0, 5, 1,
        0, 2, 4,    4, 2, 6,
        3, 1, 7,    7, 1, 5
    };

    enum { BytesCount = sizeof(data), NodeCount = sizeof(data) / sizeof(data[0]) / 3 };
};

#endif // !_TEST_CUBE_H_

