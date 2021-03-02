# Code Style

```c
int* i;
i = &x;
if(i == &x){
	// Do something
}

int* function(){
	return i;
}
```

`file.h`
```c
#ifndef FILE
#define FILE

void function_2();

#endif
```

`file.c`
```c
#include "file.h"

static void static_func();

...

void function_2(){
	// Code
}

static void static_func(){
	// More code
}
```


