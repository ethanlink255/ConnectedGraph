#include <iostream>

using namespace std;

struct Element{
    int head;
    Element* tail;

    Element(int h, Element* t){
        head = h;
        tail = t;
    }
};

class Graph{
    private: 
        Element *HNodes;
        int els;
    public: 
        Graph(int n){
            els = n;
            HNodes = (Element*) malloc(sizeof(Element) * (n - 1));
            for(int i = 0; i < n; i++){
                HNodes[i].head = i;
                HNodes[i].tail = nullptr;
            }
        }

        void add(int n, int v){
            if(HNodes[n].tail == nullptr) HNodes[n].tail = new Element(v, nullptr);
            else{
                Element *node = &HNodes[n];
                do{
                    node = node->tail;
                } while(node->tail != nullptr);

                node->tail = new Element(v, nullptr);
            }
            els++;
        }

        void remove(int n, int v){
            Element *pnode = &HNodes[n];
            Element *cnode = HNodes[n].tail;

            while (1){
                if(cnode->head == v){
                    pnode->tail = nullptr;
                    delete cnode;
                    break;
                } 
                if(cnode->tail != nullptr){
                    pnode = cnode;
                    cnode = pnode->tail;
                } else break;
            }
            els--;
        }

        void prettyprint(){
            for(int i = 0; i < els; i++){
                cout << i << ": ";
                Element *cnode = &HNodes[i];
                while(cnode->tail != nullptr){
                    cnode = cnode->tail;
                    cout << cnode->head << " ";

                }
                cout << endl;
                
            }
        }

        void components(int v){
            int mark[els];
            int parent[els];

            for (int v = 0; v < els; v++){
                parent[v] = -1;
            }

            for(int v = 0; v < els; v++){
                if(mark[v] = 0){
                    dfs(v); //Not real
                }
            }
        }

        Graph(){ }; //defawt constwuctor *uwu* don't touch XD
};


int main(){
    string input;
    cout << "Please Enter Data: (Space between each number)" << endl;
    getline(cin, input);
    
    Graph g = Graph(atoi(&input[0]));

    for(int i = 2; i < input.length(); i += 4){
        if(input[i] != -1) g.add(atoi(&input[i]), atoi(&input[i + 2]));  
    }

    g.prettyprint();
}