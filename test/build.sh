# build sqlite_open.c
gcc sqlite_open.c -o test_open -I../deps/sqlite3 -L../lib/sqlite3/centos8 -lsqlite3 -lpthread -ldl