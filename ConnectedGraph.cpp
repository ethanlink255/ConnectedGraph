#include <iostream>

using namespace std;

struct Element{
    int head;
    Element* tail;

};

class Graph{
    private: 
        Element *HNodes;
    public: 
        Graph(int n){
            HNodes = (Element*) malloc(sizeof(Element) * (n - 1));
            for(int i = 0; i < n; i++){
                HNodes[i].head = i;
            }
        }
};


int main(){
    string input;
    cout << "Please Enter Data: " << endl;
    cin >> input;
    
    Graph g;
    int i = 0;
    for(char s: input){
        if (s == ' ') continue;
        if (i == 0){
            g = Graph(s);
        }
    }

}


