#include "Manager.h"

using namespace ClassProject;

int main(int argc, char *argv[]) {
    Manager manager1;

    BDD_ID a_id = manager1.createVar("a");
    BDD_ID b_id = manager1.createVar("b");
    BDD_ID c_id = manager1.createVar("c");
    BDD_ID d_id = manager1.createVar("d");
    BDD_ID a_or_b_id = manager1.or2(a_id, b_id);
    BDD_ID c_and_d_id = manager1.and2(c_id, d_id);
    manager1.and2(a_or_b_id,c_and_d_id);

    manager1.printUniqueTable();

}

