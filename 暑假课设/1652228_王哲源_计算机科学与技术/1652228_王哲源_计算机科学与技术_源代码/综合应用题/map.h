#ifndef MAP_H
#define MAP_H

#define default_N 100
#define default_M 500

#define OK      1
#define ERROR   0

#include <QMainWindow>
#include<string>
#include<map>

using namespace std;

class Map
{
public:
    int *fst, *pre, *to;
    int totn, totm;
    map<QString, int> hashtable;

    Map();
    ~Map();

    int add_point(const QString);
    int add_path(const int, const int);

    int exist(const QString);
    int get_id(const QString);

    int *get_shortest_path(const QString, const QString);
private:
    int maxn, maxm;

    int Realloc_point();
    int Realloc_path();
};

#endif // MAP_H
