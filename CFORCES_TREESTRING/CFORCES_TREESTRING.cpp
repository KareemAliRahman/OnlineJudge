 /*
 * C++ Program to Implement Knuth–Morris–Pratt Algorithm (KMP)
 */
#include <iostream>
#include <string>
#include <vector>
 #include <set>
using namespace std;


int answer = 0;
struct Node{
    int name;
    string s;
    vector<int> sub_nodes;
};

int MAX = 100001;
vector<Node> nodes(100001);


// struct Node_index{
//     int node;
//     int index;
//     bool operator<(const Node_index& rhs) const {
//       if(node > rhs.node){
//         return false;
//       }
//       else if(node < rhs.node){
//         return true;
//       }else{
//         return index < rhs.index;
//       }
//     }
//     bool operator>(const Node_index& rhs) const {
//       if(node < rhs.node){
//         return false;
//       }
//       else if(node > rhs.node){
//         return true;
//       }else{
//         return index > rhs.index;
//       }
//     }
// };

// struct Match{
//     Node_index ni1;
//     Node_index ni2;
//     bool operator<(const Match& rhs) const {
//         if(ni1 > rhs.ni1){
//             return false; 
//         }else if(ni1 < rhs.ni1){
//             return true;
//         }else{
//             return ni2< rhs.ni2;
//         }
//     }
//     bool operator>(const Match& rhs) const {
//         if(ni1 < rhs.ni1){
//             return false; 
//         }else if(ni1 > rhs.ni1){
//             return true;
//         }else{
//             return ni2> rhs.ni2;
//         } 
//     }
// };

//set<Match> matches;

// vector<int> KMP1(string K, string S)
// {
//         vector<int> T(K.size() + 1, -1);
//     vector<int> matches;
 
//         if(K.size() == 0)
//         {
//             matches.push_back(0);
//             return matches;
//         }
//     for(int i = 1; i <= K.size(); i++)
//     {
//         int pos = T[i - 1];
//         while(pos != -1 && K[pos] != K[i - 1]) pos = T[pos];
//         T[i] = pos + 1;
//     }
 
//     int sp = 0;
//     int kp = 0;
//     while(sp < S.size())
//     {
//         while(kp != -1 && (kp == K.size() || K[kp] != S[sp])) kp = T[kp];
//         kp++;
//         sp++;
//         if(kp == K.size()) matches.push_back(sp - K.size());
//     }
 
//     return matches;
// }




// int KMP2(string K, string S)
// {
//     vector<int> T(K.size() + 1, -1);
//     int matches = 0;
 
//     if(K.size() == 0)
//     {
//         return matches;
//     }
//     for(int i = 1; i <= K.size(); i++)
//     {
//         int pos = T[i - 1];
//         while(pos != -1 && K[pos] != K[i - 1]) pos = T[pos];
//         T[i] = pos + 1;
//     }
 
//     int sp = 0;
//     int kp = 0;
//     while(sp < S.size())
//     {
//         while(kp != -1 && (kp == K.size() || K[kp] != S[sp])) kp = T[kp];
//         kp++;
//         sp++;
//         if(kp == K.size()) ++matches;
//     }
 
//     return matches;
// }

// void KMP(string K, string S)
// {
//     vector<int> T(K.size() + 1, -1);
//     int matches = 0;
 
//     if(K.size() == 0)
//     {
//         //return matches;
//     }
//     for(int i = 1; i <= K.size(); i++)
//     {
//         int pos = T[i - 1];
//         while(pos != -1 && K[pos] != K[i - 1]) pos = T[pos];
//         T[i] = pos + 1;
//     }
 
//     int sp = 0;
//     int kp = 0;
//     while(sp < S.size())
//     {
//         while(kp != -1 && (kp == K.size() || K[kp] != S[sp])) kp = T[kp];
//         kp++;
//         sp++;
//         if(kp == K.size()) ++matches;
//     }
 
//     //return matches;
// }

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
    // int sp = 0;
    // int kp = 0;
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

    // int diff = S.size() - nodes[x].s.size();
    // S = S.substr(0,diff);
}

// void dfs(vector<Node> &nodes,int x,string &s_sofar, string &pattern){
//     s_sofar += nodes[x].s;
//     if(nodes[x].sub_nodes.empty()){
//         KMP(pattern,s_sofar);
//     }
//     for (int i = 0; i < nodes[x].sub_nodes.size(); ++i)
//     {
//         dfs(nodes,nodes[x].sub_nodes[i],s_sofar, pattern);
//     }

//     int diff = s_sofar.size() - nodes[x].s.size();
//     s_sofar = s_sofar.substr(0,diff);
//}
 
int main()
{
    cin.sync_with_stdio(false);

    int n;
    cin >> n;

    //nodes(n+1);
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

    string pattern;
    cin >> pattern;

    string S = "";
    vector<int> T(pattern.size() +1 ,-1);
    preKMP(pattern,T);
    int sp = 0;
    int kp = 0;
    KMPdfs(1,S,pattern,T,sp,kp);
    cout << answer << endl;

    
    return 0;

}