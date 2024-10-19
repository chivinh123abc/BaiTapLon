#include <iostream>
#include "vattu.cpp"
#pragma once
using namespace std;

struct VatTuStack
{
    DanhSachVatTu arr[500];
    int sp;

    VatTuStack()
    {
        sp = -1;
    }

    bool isEmpty()
    {
        return sp == -1;
    }

    bool isFull()
    {
        return sp == 499;
    }

    void push(DanhSachVatTu node)
    {
        if (!isFull())
        {
            arr[++sp] = node;
        }
        else
        {
            cout << "Stack overflow!";
        }
    }

    DanhSachVatTu pop()
    {
        if (!isEmpty())
        {
            return arr[sp--];
        }
        else
        {
            cout << "Stack underflow!";
            return nullptr;
        }
    }

    DanhSachVatTu peek()
    {
        if (!isEmpty())
        {
            return arr[sp];
        }
        else
        {
            return nullptr;
        }
    }
};
