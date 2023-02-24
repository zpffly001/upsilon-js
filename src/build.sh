


# quickjs-bindsqlite.c ---> quickjs-bindsqlite.o
gcc -c -fPIC -o quickjs-bindsqlite.o quickjs-bindsqlite.c -I../deps/sqlite3 -I../deps/quickjs


#quickjs-bindsqlite.so
gcc -shared -o qjsbindsqlite.so quickjs-bindsqlite.o ../lib/quickjs/quickjs.o -lsqlite3 -L../lib/sqlite3