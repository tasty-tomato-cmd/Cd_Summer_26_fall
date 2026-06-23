#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <string>

using namespace std;

void solve1(string text) {
    bool isNumCons = true;
    
    for (int i = 0; i < text.size(); i++) {
        int asciiVal = (int)text[i];

        if (asciiVal < 48 || asciiVal > 57) { 
            isNumCons = false;
            break;
        }
    }
    
    if (isNumCons) {
        cout << "Valid numeric constant!" << "\n";
    }
    
    else {
        cout << "Invalid numeric constant." << "\n";
    }
}

void solve2(string text) {
    char ops[] = {'+', '-', '*', '/', '%', '='};
    
    int num_ops = sizeof(ops) / sizeof(ops[0]); 
    int operator_count = 1;

    for (int i = 0; i < text.size(); i++) {
        for (int j = 0; j < num_ops; j++) {
            if (text[i] == ops[j]) { 
                cout << "operator" << operator_count << ": " << text[i] << "\n";
                operator_count++;
                break;
            }
        }
    }

    if (operator_count == 1) {
        cout << "No operators found." << "\n";
    }
}

void solve3(string text, int startIndex) {
    string comment = text.substr(startIndex);
    int size = comment.size();

    if (size >= 2 && comment[0] == '/' && comment[1] == '/') {
        cout << "//single line comment" << "\n";
    }
    else if (size >= 4 && comment[0] == '/' && comment[1] == '*' && comment[size-1] == '/' && comment[size-2] == '*') {
        cout << "/*multiple line comment*/" << "\n";
    }
    else {
        cout << "Given expression is not a valid comment." << "\n";
    }
}

void remove(string text) {
    int index = -1;
    
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == '/') {
            index = i;
            break; 
        }
    }

    if (index == -1) {
        cout << "Given expression is not a valid comment." << "\n";
    } 
    else {
        solve3(text, index);
    }
}

void solve4(string text) {
    int size = text.size();

    if (size == 0) {
        cout << "Invalid identifier" << "\n";
        return;
    }
    
    if ((text[0] >= 'A' && text[0] <= 'Z') || (text[0] >= 'a' && text[0] <= 'z') || text[0] == '_') {
        for (int i = 1; i < size; i++) {
            if (!((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z') 
                || (text[i] >= '0' && text[i] <= '9') || text[i] == '_')) {
                
                cout << "Invalid identifier" << "\n";
                
                return;
            }
        }
        
        cout << "Valid identifier" << "\n";
    }

    else {
        cout << "Invalid identifier" << "\n";
    }
}

void solve5() {
    int totalElements;
    cout << "Enter the number of elements: ";
    cin >> totalElements;
    if (totalElements <= 0) {
        cout << "Invalid number of elements." << endl;
        return;
    }

    double arr[totalElements];
    cout << "Enter " << totalElements << " numbers:" << endl;
    for (int i = 0; i < totalElements; i++) {
        cout << "Element " << i + 1 << ": ";
        cin >> arr[i];
    }
    
    double sum = 0;
    for (int i = 0; i < totalElements; i++) {
        sum += arr[i];
    }

    double avg = sum / totalElements;
    cout << "The average of the elements is: " << avg << endl;
}

void solve6() {
    int totalElements;
    cout << "Enter the number of elements: ";
    cin >> totalElements;
    
    if (totalElements <= 0) {
        cout << "Invalid number of elements." << endl;
        return;
    }
    
    double arr[totalElements];
    cout << "Enter " << totalElements << " numbers:" << endl;
    for (int i = 0; i < totalElements; i++) {
        cin >> arr[i];
    }
    
    sort(arr, arr + totalElements);
    
    double minVal = arr[0];
    double maxVal = arr[totalElements - 1];
    cout << "Minimum value: " << minVal << endl;
    cout << "Maximum value: " << maxVal << endl;
}

void solve7(string s1, string s2) {
    string s3 = s1 + " " + s2;

    cout << "fullname: " << s3 << "\n";
}

int main() {
    string text;
    cout << "Task-1: Enter your constant: ";
    getline(cin, text);
    solve1(text);

    cout << "Task-2: Enter your expression: ";
    getline(cin, text);
    solve2(text);

    cout << "Task-3: Enter your comment: ";
    getline(cin, text);
    remove(text);

    cout << "Task-4: Enter your input: ";
    getline(cin, text);
    solve4(text);
    
    cout << "Task-5: ";
    solve5();

    cout << "Task-6: ";
    solve6();

    cout << "Task-7: " << "\n";
    string str1;
    string str2;
    cout << "\n\nEnter the firstname: ";
    cin >> str1;
    cout << "Enter the lastname: ";
    cin >> str2;
    solve7(str1, str2);

    return 0;
}
