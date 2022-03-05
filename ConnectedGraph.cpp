#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

// Element structure that holds each node in the graph
struct Element{
    int head; //value
    Element* tail; //pointer to next element

    Element(int h, Element* t){
        head = h;
        tail = t;
    }
};

// class that holds all elements
class Graph{
    private:
        Element *HNodes;
	int els; //root nodes

    public:
        // constructor
        Graph(int n){
            els = n;
            HNodes = (Element*) malloc(sizeof(Element) * (n - 1));
            for(int i = 0; i < n; i++){
                HNodes[i].head = i;
                HNodes[i].tail = nullptr;
            }
        }

        // add element to graph
        void add(int n, int v){
            
            // if its at the end, just add the element, else search for required node
            if(HNodes[n].tail == nullptr) HNodes[n].tail = new Element(v, nullptr);
            else{
                Element *node = &HNodes[n];
                do{
                    node = node->tail;
                } while(node->tail != nullptr);

                node->tail = new Element(v, nullptr);
            }
            // if its at the end, just add the element, else search for required node
            if(HNodes[v].tail == nullptr) HNodes[v].tail = new Element(n, nullptr);
            else{
                Element *node = &HNodes[v];
                do{
                    node = node->tail;
                } while(node->tail != nullptr);

                node->tail = new Element(n, nullptr);
            }

        }

        //removes connections between nodes 
        void remove(int n, int v){
            Element *pnode = &HNodes[n];
            Element *cnode = HNodes[n].tail;
            Element *rnode = &HNodes[v];
            Element *fnode = HNodes[v].tail;

            //checks for connection, removes node from adj list and stiches list back together.
            while (1){
                if(cnode->head == v){
                    if(cnode->tail != nullptr){
                        pnode->tail = cnode->tail;
                    }else{
                        pnode->tail = nullptr;
                    }
                    delete cnode;
                    break;
                } 
                if(cnode->tail != nullptr){
                    pnode = cnode;
                    cnode = pnode->tail;
                } else break;
            }
             while (1){
                if(fnode->head == v){
                    if(fnode->tail != nullptr){
                        rnode->tail = fnode->tail;
                    }else{
                        rnode->tail = nullptr;
                    }
                    delete fnode;
                    break;
                } 
                if(fnode->tail != nullptr){
                    rnode = fnode;
                    fnode = rnode->tail;
                } else break;
            }
        }

        //prints adjacency list view
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

        //implementation of recursive dfs algorithm
        void dfs(int v, int* mark, int* visited, int found){
            mark[v] = 1;
            Element* cnode = &HNodes[v];
            while (cnode->tail != nullptr){
                cnode = cnode->tail;
                if (mark[cnode->head] == 0 && cnode != nullptr) { 
                    visited[found++] = cnode->head;
                    dfs(cnode->head, mark, visited, found);               
                }
            }
        }

        //dfs overloader that initializes helper vars. Should be the one that's called.
        int* dfs(int v){ 
            int *mark = (int*) malloc(sizeof(int) * (els));
            int *visited = (int*) malloc(sizeof(int) * (els)); 
            for(int i = 0; i < els; i++) {
                mark[i] = 0;
                visited[i] = -1;
            }
	        visited[0] = v;
            dfs(v, mark, visited, 1);
            delete mark;

            return visited;
        }

        //calculates connected graphs
        void components(){
            for(int i = 0; i < els; i++){
                int* res = dfs(i);
                cout << i << ": ";
                int r = 0;
                cout << "{";
                //loops through dfs result until -1 terminator is encountered
                while (r < els && res[r] != -1){
                    cout << res[r++] << ", ";
                }
                cout << "\b\b}" << endl;

            }
        }

        int size(){
            return els;
        }

        Graph(){ };

        ~Graph(){}
};


int main(){
    string input;
    cout << "Please Enter Data: (Space between each number)" << endl;
    getline(cin, input);
    
    Graph g = Graph(atoi(&input[0]));
  
    for(int i = 2; i < input.length(); i += 4){
        if(atoi(&input[i]) != -1) { 
            if(atoi(&input[i]) < atoi(&input[0]) && atoi(&input[i + 2]) < atoi(&input[0]))  g.add(atoi(&input[i]), atoi(&input[i + 2]));
            else{
                cout << "Invalid Data ... STOP" << endl;
                exit(-1);
            }
           
        } else break;
    }

    cout << endl << "Direct Connections" << endl;
    g.prettyprint();

    cout << endl << "Result of DFS, with starting vertex of 2" << endl;
    int *search = g.dfs(2);
    for(int i = 0; i < g.size(); i++ ){
        int res = search[i];
        if(search[i] != -1){
            cout << search[i] << " ";
        }
    }
    cout << endl << endl;
    cout << "Connected Components" << endl;
    g.components();

    cout << endl;
    g.remove(1,3);
    g.remove(4,3);
    cout << "Direct Connections after removal of connection between {1,3} and {4,3}" << endl;
    g.prettyprint();

}
