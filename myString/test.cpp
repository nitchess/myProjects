#include <iostream>
#include <stdio.h>
#include <cstring>

#include "mu_test.h"
#include "buffer.h"
#include "myString.h"
#include "stringException.h"

#define KMAG  "\x1B[35m"

using namespace std;

UNIT(Initializations)
    puts(KMAG"Let The Test Begin\n");
END_UNIT

UNIT(Buffer_from_size_1000)
    using namespace advcpp::implem;

    Buffer<char> * buf = new Buffer<char>(1000);

    std::cout << "Buffer Size: " << buf->size() << endl;
    std::cout << "Buffer Capacity: " << buf->capacity() << endl;

    buf->begin()[0] = ':';
    buf->begin()[1] = ')';

    cout << buf->begin() << endl;

    ASSERT_THAT(buf);
    delete buf;
END_UNIT


UNIT(Buffer_from_size_1MB)
    using namespace advcpp::implem;

    // ask mike about bad alloc catch for large number
    size_t allocSize = 50000000;

    Buffer<char> * buf = new Buffer<char>(allocSize);

    ASSERT_THAT(buf);
    std::cout << "Buffer Size: " << buf->size() << endl;
    std::cout << "Buffer Capacity: " << buf->capacity() << endl;

    allocSize = 100000000;
    buf->reserve(allocSize);

    allocSize = allocSize * 3 / 2;
    std::cout << "Buffer Size: " << buf->size() << endl;
    std::cout << "Buffer Capacity: " << buf->capacity() << endl;

    delete buf;
END_UNIT

UNIT(String_from_char)
    using namespace advcpp;
    
    MyString<char> * mstr = new MyString<char>("MyString<Char> Hello World");

    ASSERT_THAT(mstr);

    cout << "cStr: " << mstr->cStr() << endl;
    cout << "MyString Length: "<< mstr->length() << endl;

    cout << "String in [3]: " << (*mstr)[3] << endl;

    (*mstr)[3] = 'p';

    cout << "Now the string in [3] is : " << (*mstr)[3] << endl;
    cout << "cStr: " << mstr->cStr() << endl;

    delete mstr;
END_UNIT


UNIT(String_from_wchar)
    using namespace advcpp;
    
    wchar_t initfrom[64];
    wcscpy (initfrom, L"MyString<wchar_t> Hello World");

    MyString<wchar_t> * mstr = new MyString<wchar_t>(initfrom);

    ASSERT_THAT(mstr);

    wcout << "cStr: " << mstr->cStr() << endl;
    cout << "MyString Length: "<< mstr->length() << endl;
    wcout << "String in [3]: " << (*mstr)[3] << endl;

    delete mstr;
END_UNIT

UNIT(CTORS_and_UnaryAppendOp)
    using namespace advcpp;
    
    MyString<char> f("first");
    // Copy CTOR test
    MyString<char> s(f);
    // Assigment test
    s = "second";
    cout << "1cStr: " << s.cStr() << endl;
    
    f += s;
    cout << "String Length: "<< f.length() << endl;
    cout << "2cStr: " << f.cStr() << endl;

    f += "third";
    cout << "3cStr: " << f.cStr() << endl;

END_UNIT


UNIT(ToUpper_ToLower)
    using namespace advcpp;
    
    MyString<char> f("Or");

    wchar_t initfrom[64];
    wcscpy (initfrom, L"Erlich");
    MyString<wchar_t> s(initfrom);
    
    cout << toLowerCase(f).cStr() << endl;
    wcout << toLowerCase(s).cStr() << endl;

    cout << toUpperCase(f).cStr() << endl;
    wcout << toUpperCase(s).cStr() << endl;

    MyString<char> e(" Erlich");

    f = f + e;
    cout << f.cStr() << endl;

    f = "is it " + f;
    cout << f.cStr() << endl;

    f = f + "?";
    cout << f.cStr() << endl;

END_UNIT

UNIT(Equality_Operators)
    using namespace advcpp;

    MyString<char> rhs("Hello");
    MyString<char> lhs("Hola");

    ASSERT_THAT(rhs < lhs);
    ASSERT_THAT(rhs != lhs);
    ASSERT_THAT(!(rhs == lhs));

END_UNIT


TEST_SUITE(Buffer & MyString tests)
    TEST(Initializations)
    TEST(Buffer_from_size_1000)
    TEST(Buffer_from_size_1MB)
    TEST(String_from_char)
    TEST(String_from_wchar)
    TEST(CTORS_and_UnaryAppendOp)
    TEST(ToUpper_ToLower)
    TEST(Equality_Operators)
END_SUITE
