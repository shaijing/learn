#include "main.h"

int main() {
    void* handle = dlopen("./libshared.so", RTLD_LAZY);
    void (*share)(void);
    char* errorInfo;
    if (!handle) {
        fprintf(stderr, "Failed to load libsthc.so: %s\n", dlerror());
        return 1;
    }
    // 使用 dlsym
    // 函数，尝试解析新打开的对象文件中的符号。您将会得到一个有效的指向该符号的指针，或者是得到一个
    // NULL 并返回一个错误
    share = dlsym(handle, "sharedlib");
    errorInfo =
        dlerror();  // 调用dlerror方法，返回错误信息的同时，内存中的错误信息被清空
    if (errorInfo != NULL) {
        printf("Dlsym Error:%s.\n", errorInfo);
        return 0;
    }
    share();
    dlclose(handle);
    printf("Test\n");
    return 0;
}