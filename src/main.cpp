#include <iostream>
#include <fstream>

#include "state.h"
#include "fsm.h"

void t1(){
    fsm::State s1("s1"), s2("s2");
    std::vector<fsm::State> states = {s1, s2};
    std::vector<int> alphabet = {0, 1};
    fsm::State &final_state = s2;
    std::vector<fsm::State> final_states = {final_state};
    fsm::State &initial_state = s1;
    std::vector<std::vector<fsm::State>> transition_table = {
            {states[0], states[1]},
            {states[1], states[1]},
    };
    fsm::FSM<int> machine(states, alphabet, initial_state, final_states, transition_table);
    std::cout << "is in final state: " << machine.is_in_final_state() << std::endl;
    machine.transition(0);
    std::cout << "is in final state: " << machine.is_in_final_state() << std::endl;
    machine.transition(1);
    std::cout << "is in final state: " << machine.is_in_final_state() << std::endl;
    std::cout << "Current state: " << machine.get_current_state() << std::endl;
    std::cout << "Restarting" << std::endl;
    machine.restart();
    std::cout << "Current state: " << machine.get_current_state() << std::endl;

    fsm::State s3("s3");
    machine.add_state(s3);
    machine.add_transition_rule(s3, alphabet[0], s1);
    machine.add_transition_rule(s3, alphabet[1], s2);

    machine.set_initial_state(s3);
    machine.transition(1);
    std::cout << "Current state: " << machine.get_current_state() << std::endl;
    std::cout << "is in final state: " << machine.is_in_final_state() << std::endl;
}

void t2(){
    fsm::State s1("s1"), s2("s2"), s3("s3"), s4("s4"), s5("s5");
    std::vector<fsm::State> states1 = {s1, s2, s3};
    std::vector<fsm::State> states2 = {s4, s5};

    std::vector<int> alphabet = {0, 1};

    fsm::State &initial_state1 = s1, &initial_state2 = s4;
    fsm::State &final_state1 = s3, &final_state2 = s5;

    std::vector<fsm::State> final_states1 = {final_state1};
    std::vector<fsm::State> final_states2 = {final_state2};

    std::vector<std::vector<fsm::State>> transition_table1 = {
            {states1[2], states1[1]},
            {states1[2], states1[0]},
            {states1[1], states1[2]},
    };
    std::vector<std::vector<fsm::State>> transition_table2 = {
            {states2[0], states2[1]},
            {states2[1], states2[0]}
    };

    fsm::FSM<int> machine1(states1, alphabet, initial_state1, final_states1, transition_table1);
    fsm::FSM<int> machine2(states2, alphabet, initial_state2, final_states2, transition_table2);

    std::cout << (machine1 & machine2) << std::endl;
}

void t3() {
    fsm::State s1("s1"), s2("s2"), s3("s3"), s4("s4");
    std::vector<fsm::State> states1 = {s1, s2};
    std::vector<fsm::State> states2 = {s3, s4};

    std::vector<int> alphabet = {0, 1, 2};

    fsm::State &initial_state1 = s1, &initial_state2 = s3;
    fsm::State &final_state1 = s2, &final_state2 = s4;

    std::vector<fsm::State> final_states1 = {final_state1};
    std::vector<fsm::State> final_states2 = {final_state2};

    std::vector<std::vector<fsm::State>> transition_table1 = {
            {states1[0], states1[1], states1[1]},
            {states1[0], states1[0], states1[1]}
    };
    std::vector<std::vector<fsm::State>> transition_table2 = {
            {states2[0], states2[0], states2[1]},
            {states2[0], states2[1], states2[0]}
    };

    fsm::FSM<int> machine1(states1, alphabet, initial_state1, final_states1, transition_table1);
    fsm::FSM<int> machine2(states2, alphabet, initial_state2, final_states2, transition_table2);

    std::cout << (machine1 & machine2) << std::endl;
}

void t4(){
    fsm::State s1("s1"), s2("s2"), s3("s3"), s4("s4"), s5("s5"), s6("s6");
    std::vector<fsm::State> states1 = {s1, s2, s3};
    std::vector<fsm::State> states2 = {s4, s5, s6};

    std::vector<int> alphabet = {0, 7};

    fsm::State &initial_state1 = s1, &initial_state2 = s4;
    fsm::State &final_state1 = s3, &final_state2 = s6;

    std::vector<fsm::State> final_states1 = {final_state1};
    std::vector<fsm::State> final_states2 = {final_state2};

    std::vector<std::vector<fsm::State>> transition_table1 = {
            {states1[1], states1[0]},
            {states1[2], states1[0]},
            {states1[2], states1[2]}
    };
    std::vector<std::vector<fsm::State>> transition_table2 = {
            {states2[0], states2[1]},
            {states2[0], states2[2]},
            {states2[2], states2[2]}
    };

    fsm::FSM<int> machine1(states1, alphabet, initial_state1, final_states1, transition_table1);
    fsm::FSM<int> machine2(states2, alphabet, initial_state2, final_states2, transition_table2);

    std::cout << machine1.evaluate("07007") << std::endl;  // Recognises words containing "00".
    std::cout << machine2.evaluate("07707") << std::endl;  // Recognises words containing "77".
    std::cout << !machine2.evaluate("77007") << std::endl;  // Recognises words NOT containing "77".

    // Recognises words containing "00" OR "77".
    std::cout << (machine1 | machine2).evaluate("07070") << std::endl;
    std::cout << (machine1 | machine2).evaluate("77070") << std::endl;

    // Recognises words containing "00" AND NOT "77".
    std::cout << (machine1 & !machine2).evaluate("700770") << std::endl;
    std::cout << (machine1 & !machine2).evaluate("070070") << std::endl;
}

void t5() {

    fsm::FSM<int> m1, m2;

    std::cin >> m1 >> m2;

    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;

    std::cout << (m1 | m2);
}

void t6() {
    fsm::FSM<int> m1, m2;

    std::ifstream f1("m1.txt");
    std::ifstream f2("m2.txt");

    f1 >> m1;
    f2 >> m2;

    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;

    std::cout << (m1 | m2);
}

void t7() {
    fsm::FSM<int> m1("m1.txt"), m2;

    m1.toTXT("m1Test.txt");
    m2.fromTXT("m1Test.txt");

    //these should be the same.
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
}

template <typename T>
void loadMachine(fsm::FSM<T>& m1) {
    char fileName[21];
    unsigned option;

    do {
        std::cout << "1. Load machine from .txt file.\n";
        std::cout << "2. Make machine from console.\n";
        std::cout << "Choose option: ";
        std::cin >> option;
    } while (option > 2);
   
    if (option == 1) {
        std::cout << "\nEnter name of .txt file: ";
        std::cin >> fileName;

        m1.fromTXT(fileName);
    }
    else if (option == 2) {

        std::cout << "\n";
        std::cin >> m1;
    }
}

template <typename T>
void saveFile(fsm::FSM<T>& m) {
    char fileName[21];
    std::cout << "Enter name of the save file: ";
    std::cin >> fileName;

    m.toTXT(fileName);
}

template <typename T>
void recogWord(fsm::FSM<T>& m) {
    char word[21];

    std::cout << "Enter word: ";
    std::cin >> word;

    if (m.evaluate(word)) {
        std::cout << word << " is reccognised my the machine! :)\n";
    }
    else {
        std::cout << word << " is NOT reccognised my the machine.\n";
    }
}

template <typename T>
void userIO() {
    unsigned option = 1;
    fsm::FSM<T> m1, m2;

    loadMachine(m1);

    while (option) {
        std::cout << "\n======================\n\n";
        std::cout << "1. Load another machine.\n";
        std::cout << "2. Evaluate word.\n";
        std::cout << "3. Make complement.\n";
        std::cout << "4. Make union.\n";
        std::cout << "5. Make intersection.\n";
        std::cout << "6. Print on console.\n";
        std::cout << "7. Save to file.\n";
        std::cout << "0. Exit.\n";
        std::cout << "Choose option: ";
        std::cin >> option;

        switch (option)
        {
        case 0:
            break;
        case 1:
            std::cout << "\n======================\n\n";
            loadMachine(m1);
            break;
        case 2:
            std::cout << "\n";
            recogWord(m1);
            break;
        case 3:
            m1 = !m1;
            break;
        case 4:
            std::cout << "\n======================\n\n";
            std::cout << "Enter second machine.\n";
            loadMachine(m2);
            m1 = m1 | m2;
            break;
        case 5:
            std::cout << "\n======================\n\n";
            std::cout << "Enter second machine.\n";
            loadMachine(m2);
            m1 = m1 & m2;
            break;
        case 6:
            std::cout << "\n" << m1;
            break;
        case 7:
            saveFile(m1);
            break;
        default:
            std::cout << "Invalid option! ;(\n";
            break;
        }
    }
}

void demo() {
    
    unsigned option;
    std::cout << "======== Menu ========\n";
    do {
        std::cout << "1. Int.\n";
        std::cout << "2. Char.\n";
        std::cout << "Choose data type for the machine: ";
        std::cin >> option;
    } while (option > 2);

    std::cout << "\n======================\n\n";

    if (option == 1) { userIO<int>(); }
    if (option == 2) { userIO<char>(); }

}

int main() {

    //t1();
    //t2();
    //t3();
    //t4();
    ////t5();
    //t6();
    //t7();
    demo();


    return 0;
}
