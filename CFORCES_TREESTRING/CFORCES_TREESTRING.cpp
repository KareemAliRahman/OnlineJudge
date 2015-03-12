 /*
 * C++ Program to Implement Knuth–Morris–Pratt Algorithm (KMP)
 */
#include <iostream>
#include <string>
#include <vector>
 #include <set>
using namespace std;

string K; //pattern
vector<int> T;
int sp = 0;
int kp = 0;
string S;




int answer = 0;
struct Node{
    int name;
    string s;
    vector<int> sub_nodes;
};

int MAX = 100001;
vector<Node> nodes(100001);



// K is the pattern and T is the failure array
void preKMP(string K, vector<int> &T){
    //vector<int> T(K.size() +1 ,-1);
    if(K.size() == 0){
        return;
    }
    for(int i = 1; i <= K.size(); i++)
    {
        int pos = T[i - 1];
        while(pos != -1 && K[pos] != K[i - 1]) pos = T[pos];
        T[i] = pos + 1;
    }
    return;
}

//S is the string so far, K is the pattern string
void KMPdfs(int x,string S, string K, vector<int> &T,int sp,int kp){
    S += nodes[x].s;
    int matches = 0;
    while(sp < S.size())
    {
        while(kp != -1 && (kp == K.size() || K[kp] != S[sp])) kp = T[kp];
        kp++;
        sp++;
        if(kp == K.size()) ++matches;
    }
    answer += matches;
    if(nodes[x].sub_nodes.empty()){
        return;
    }
    for (int i = 0; i < nodes[x].sub_nodes.size(); ++i)
    {
        KMPdfs(nodes[x].sub_nodes[i],S, K,T,sp ,kp);
    }

 }
int main()
{
    cin.sync_with_stdio(false);

    int n;
    cin >> n;
    Node root;
    root.s = "";
    nodes[1] = root;

    for (int i = 2; i <= n; ++i)
    {
        int new_x;
        string new_s;
        cin >> new_x;
        cin >> new_s;
        nodes[new_x].sub_nodes.push_back(i);
        nodes[i].s = new_s;
    }

    //string pattern;
    cin >> K;

    string S = "";
    vector<int> T(K.size() +1 ,-1);
    preKMP(K,T);
    KMPdfs(1,S,K,T,sp,kp);
    cout << answer << endl; 

    return 0;
}