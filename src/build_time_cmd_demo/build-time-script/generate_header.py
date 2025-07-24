
import os
header_content = \
"""
#ifndef CPPLAB_MYCLASS_H
#define CPPLAB_MYCLASS_H
class MyClass {
public:
    int value;

    MyClass(int value);
};
#endif //CPPLAB_MYCLASS_H
"""

print(f"[py] Working dir is {os.getcwd()}")
with open("include/MyClass.h", "w") as f:
    f.write(header_content)
    f.write("\n")

print("[py] done.")