namespace S1 {
    void foo() {}
    void foo1() {}
}

namespace S2 {
    void bar() {}
}

namespace S3 {
    void baz() {}
    void baz1() {}
}

int main() {
    S2::bar();

    using namespace S1;
    foo();
    foo1();

    using S3::baz;
    baz();

}

