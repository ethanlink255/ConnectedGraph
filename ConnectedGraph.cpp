#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

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
	int els; //root nodes

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

            if(HNodes[v].tail == nullptr) HNodes[v].tail = new Element(n, nullptr);
            else{
                Element *node = &HNodes[v];
                do{
                    node = node->tail;
                } while(node->tail != nullptr);

                node->tail = new Element(n, nullptr);
            }

        }

        void remove(int n, int v){
            Element *pnode = &HNodes[n];
            Element *cnode = HNodes[n].tail;
            Element *rnode = &HNodes[v];
            Element *fnode = HNodes[v].tail;

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

             while (1){
                if(fnode->head == v){
                    rnode->tail = nullptr;
                    delete fnode;
                    break;
                } 
                if(fnode->tail != nullptr){
                    rnode = cnode;
                    cnode = rnode->tail;
                } else break;
            }
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

        void dfs(int v, int* mark, int* visited, int found){
            mark[v] = 1; //BIG BAD
            Element* cnode = &HNodes[v];
            while (cnode->tail != nullptr){
                cnode = cnode->tail;
                if (mark[cnode->head] == 0 && cnode != nullptr) { 
                    visited[found++] = cnode->head;
                    dfs(cnode->head, mark, visited, found);               
                }
            }
        }

        int* dfs(int v){ 
            int *mark = (int*) malloc(sizeof(int) * (els));
            int *visited = (int*) malloc(sizeof(int) * (els));    //this
            for(int i = 0; i < els; i++) {
		mark[i] = 0;
		visited[i] = -1;
	    }
	    visited[0] = v;
            dfs(v, mark, visited, 1);
            delete mark;

            return visited;
        }

/*        void components(){
		for(int i = 0; i < els; i++){
		/*	int* res = dfs(i);
			cout << i << ": ";
			int r = 0;
			while (r < els && res[r] != -1){
				cout << res[r++];
			}
			cout << endl;

		}
        }*/

        int size(){
            return els;
        }



        Graph(){ };
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

    g.prettyprint();

    cout << "Result of DFS, with starting vertex of 2" << endl;
    int *search = g.dfs(2);
    for(int i = 0; i < g.size(); i++ ){
        cout << search[i] << " ";
    }

//    g.components();

    cout << endl;
}
