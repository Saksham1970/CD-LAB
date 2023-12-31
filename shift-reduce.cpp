#include <iostream>
#include <cstring>
using namespace std;

int z = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stk[15], act[10];

void check() {
    strcpy(ac, "REDUCE TO E -> ");
    for (z = 0; z < c; z++) {
        if (stk[z] == '4') {
            cout << ac << "4";
            stk[z] = 'E';
            stk[z + 1] = '\0';
            cout << "\n$" << stk << "\t" << a << "$\t";
        }
    }
    for (z = 0; z < c - 2; z++) {
        if (stk[z] == '2' && stk[z + 1] == 'E' && stk[z + 2] == '2') {
            cout << ac << "2E2";
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            cout << "\n$" << stk << "\t" << a << "$\t";
            i = i - 2;
        }
    }
    for (z = 0; z < c - 2; z++) {
        if (stk[z] == '3' && stk[z + 1] == 'E' && stk[z + 2] == '3') {
            cout << ac << "3E3";
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            cout << "\n$" << stk << "\t" << a << "$\t";
            i = i - 2;
        }
    }
    return; // return to main
}

int main() {
    cout << "GRAMMAR is -\nE->2E2 \nE->3E3 \nE->4\n";
    strcpy(a, "32423");
    c = strlen(a);
    strcpy(act, "SHIFT");
    cout << "\nstack \t input \t action";
    cout << "\n$\t" << a << "$\t";
    for (i = 0; j < c; i++, j++) {
        cout << act;
        stk[i] = a[j];
        stk[i + 1] = '\0';
        a[j] = ' ';
        cout << "\n$" << stk << "\t" << a << "$\t";
        check();
    }
    check();
    if (stk[0] == 'E' && stk[1] == '\0')
        cout << "Accept\n";
    else //else reject
        cout << "Reject\n";
}


