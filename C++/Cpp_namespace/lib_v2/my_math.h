#pragma once
namespace MyLib {
    namespace v1 {
        int add(int a, int b);
    }

    inline namespace v2 {
        double add(double a, double b);
    }
}