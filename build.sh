#!/bin/bash

g++ -ggdb --std=c++17 -fPIC -rdynamic -shared -o ./test-widget1.so ./test-widget1.cpp

g++ -ggdb --std=c++17 -fPIC -rdynamic -shared -o ./test-widget2.so ./test-widget2.cpp

g++ -ggdb --std=c++17 -rdynamic -o main main.cpp -ldl                            
