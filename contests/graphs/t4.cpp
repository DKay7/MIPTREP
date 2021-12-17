#include <bits/stdc++.h>

using namespace std;

int clStart, clEnd;
int n, m;
vector <vector <int> > g(100);
vector <int>  cl(100, 0);

int invert(int c){
    return c == 1 ? 2 : 1;
}

void dfs(int v, int c){
    cl[v] = c;
    for (int i = 0; i < g[v].size(); i++){
        int to = g[v][i];
        if (cl[to] == 0)
        {
            dfs(to, invert(c));
        }
        else if(cl[to] == c){
           cout << "NO";
           exit(0);
        }

    }
}

int main() {

    cin >> n;
    cin >> m;
    int a, b;
    for (int i = 0; i < m; i++){
        cin >> a;
        cin >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    clStart = -1;
    for (int i=0; i<n; ++i)
		if (cl[i] == 0)
			dfs(i, 1);


    cout << "YES" << endl;

    //system("pause");
    return 0;
}