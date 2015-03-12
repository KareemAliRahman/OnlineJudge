#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

string K; //pattern
vector<int> T;
int sp = 0;
int kp = 0;
int size_soFar = 0;
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
void KMPdfs(int x, vector<int> &T,int sp,int kp){
    int matches = 0;
    int last_size = size_soFar;
    size_soFar += nodes[x].s.size();
    while(sp < size_soFar)
    {
        while(kp != -1 && (kp == K.size() || K[kp] != nodes[x].s[sp-last_size])) kp = T[kp];
        kp++;
        sp++;
        if(kp == K.size()) ++matches;

    }
    answer += matches;
    
    for (int i = 0; i < nodes[x].sub_nodes.size(); ++i)
    {
        KMPdfs(nodes[x].sub_nodes[i],T,sp ,kp);
    }
    size_soFar -=nodes[x].s.size();
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

    vector<int> T(K.size() +1 ,-1);
    preKMP(K,T);
    KMPdfs(1,T,sp,kp);
    cout << answer << endl; 

    return 0;
}