#include <QMainWindow>
#include <new>
#include <map>
#include <utility>
#include <cstring>

#include "map.h"

using namespace std;

Map::Map()
{
    fst = new(nothrow) int[default_N]{};
    pre = new(nothrow) int[default_M];
    to = new(nothrow) int[default_M];
    if(fst == NULL || pre == NULL || to == NULL)
        exit(-1);

    maxn = default_N; maxm = default_M;
    totn = 0; totm = 0;
}
Map::~Map()
{
    if(fst != NULL)
        delete[]fst;
    if(pre != NULL)
        delete[]pre;
    if(to != NULL)
        delete[]to;
}

int Map::Realloc_point()
{
    int *tmp = new(nothrow) int[maxn << 1]{};
    if(tmp == NULL)
        return ERROR;
    memcpy(tmp, fst, maxn * sizeof(int));
    maxn <<= 1;
    delete[]fst;
    fst = tmp;
    return OK;
}
int Map::Realloc_path()
{
    int *tmp1 = new(nothrow) int[maxm << 1];
    int *tmp2 = new(nothrow) int[maxm << 1];
    if(tmp1 == NULL || tmp2 == NULL)
        return ERROR;
    memcpy(tmp1, pre, maxm * sizeof(int));
    memcpy(tmp2, to, maxm * sizeof(int));
    maxm <<= 1;
    delete[]pre; delete[]to;
    pre = tmp1; to = tmp2;
    return OK;
}

int Map::add_point(const QString station)
{
    map<QString, int>::const_iterator it = hashtable.find(station);
    if(it != hashtable.end())
        return ERROR;

    int flag = OK;
    if(totn + 1 ==maxn)
        flag = Realloc_point();
    if(flag == ERROR)
        return ERROR;

    hashtable.insert(make_pair(station, ++totn));
    return OK;
}
int Map::add_path(const int u, const int v)
{
    int flag = OK;
    if(totm + 1 ==maxm)
        flag = Realloc_path();
    if(flag == ERROR)
        return ERROR;
    to[++totm] = v; pre[totm] = fst[u]; fst[u]=totm;
    return OK;
}

int Map::exist(const QString station)
{
    map<QString, int>::const_iterator it = hashtable.find(station);
    if(it == hashtable.end())
        return 0;
    else
        return 1;
}
int Map::get_id(const QString station)
{
    map<QString, int>::const_iterator it = hashtable.find(station);
    if(it == hashtable.end())
        return -1;
    else
        return it->second;
}

int *Map::get_shortest_path(const QString Ss, const QString Tt)
{
    map<QString, int>::const_iterator itS = hashtable.find(Ss);
    map<QString, int>::const_iterator itT = hashtable.find(Tt);
    if(itS == hashtable.end() || itT == hashtable.end())
        return NULL;

    int S = itS->second;
    int T = itT->second;

    int *Q = new(nothrow) int[maxn]{};
    int *fro = new(nothrow) int[maxn]{};
    if(Q == NULL || fro == NULL)
        return NULL;

    int l = 0, r = 1; Q[0] = S;
    while(l < r && Q[l] != T)
    {
        int u =Q[l++];
        for(int k = fst[u]; k; k = pre[k])
        {
            int v = to[k];
            if(fro[v])
                continue;
            fro[v] = u; Q[r++] = v;
            if(v == T)
                break;
        }
    }
    if(Q[l] != T)
    {
        delete[]Q;
        return NULL;
    }

    delete[]Q;
    int *path_point = new(nothrow) int[maxn + 1]{};
    if(path_point == NULL)
        return NULL;

    int cnt = 0;
    for(int i = T; i != S; i = fro[i])
        path_point[++cnt] = i;
    path_point[++cnt] = S;
    path_point[++cnt] = -1;
    return path_point;
}
