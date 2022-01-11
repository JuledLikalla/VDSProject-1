#include <iostream>
#include <iomanip>
#include <string>
#include "Manager.h"
#include <algorithm>

using namespace ClassProject;

int main(int argc, char *argv[]) {
    Manager manager1;

    BDD_ID a_id = manager1.createVar("a");
    BDD_ID b_id =manager1.createVar("b");
    BDD_ID c_id =manager1.createVar("c");
    BDD_ID d_id =manager1.createVar("d");
    BDD_ID a_or_b_id = manager1.or2(a_id, b_id);
    BDD_ID c_and_d_id = manager1.and2(c_id, d_id);
    BDD_ID f_id = manager1.and2(a_or_b_id,c_and_d_id);

        cout
                << endl
                << left
                << setw(10)
                << "ID"
                << left
                << setw(10)
                << "Label"
                << left
                << setw(10)
                << "High"
                << left
                << setw(10)
                << "Low"
                << setw(10)
                << "Top Var"
                << endl;

        for (auto & i : manager1.uniqueTable) {
            cout
                    << left
                    << setw(10)
                    << i.id
                    << left
                    << setw(10)
                    << i.label
                    << left
                    << setw(10)
                    << i.high
                    << left
                    << setw(10)
                    << i.low
                    << setw(10)
                    << i.topVar
                    << endl;
        }
    set<BDD_ID> nodes_root;
    cout << "Nodes reacheabe from root: "<<endl;
    manager1.findNodes(a_or_b_id,nodes_root);
    int i =0;

    for (auto it = nodes_root.begin(); it !=nodes_root.end(); ++it){
        cout <<"Node " << i++<<": " <<*it<<endl;
    }
    cout<<endl;


    set<BDD_ID> vars_of_root;
    cout << "Variables reacheabe from root: "<<endl;
    manager1.findVars(f_id,vars_of_root);
    int j =0;

   for (auto it1 = vars_of_root.begin(); it1 !=vars_of_root.end(); ++it1){
       cout <<"TopVar " << j++<<": " <<*it1<<endl;
    }
   cout<<endl;


}

