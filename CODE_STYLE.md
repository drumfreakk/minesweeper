# Code Style

`include/file.h`
```c
#ifndef FILE_H
#define FILE_H

void external_func(int x);

int* i = NULL;

#endif
```

`src/file.c`
```c
#include "file.h"

static int* static_func();

void external_func(int x){
	if(i == &x){
		// Code
	}
}

int* void static_func(){
	// More code
}
```


