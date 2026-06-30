#include <iostream>
#include <string>
using namespace std;

void getTables(string*& kw, int& kwCount, string*& op, int& opCount, char*& pc, int& pcCount) {
    static string keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "inline", "int", "long", "register", "restrict", "return", "short",
        "signed", "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while",
        "bool", "catch", "class", "delete", "false", "friend", "namespace",
        "new", "nullptr", "private", "protected", "public", "template",
        "this", "throw", "true", "try", "typename", "using", "virtual"
    };
    static int keywordsCount = sizeof(keywords) / sizeof(keywords[0]);

    static string operators[] = {
        "<<=", ">>=",
        "==", "!=", "<=", ">=", "&&", "||", "<<", ">>",
        "++", "--", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "->",
        "+", "-", "*", "/", "%", "=", "<", ">", "!", "&", "|", "^", "~", "?"
    };
    static int operatorsCount = sizeof(operators) / sizeof(operators[0]);

    static char punctuations[] = { '(', ')', '{', '}', '[', ']', ';', ',', '.', ':' };
    static int punctuationsCount = sizeof(punctuations) / sizeof(punctuations[0]);

    kw = keywords;
    kwCount = keywordsCount;
    op = operators;
    opCount = operatorsCount;
    pc = punctuations;
    pcCount = punctuationsCount;
}

bool isKeyword(const string& word) {
    string* kw; int kwCount; string* op; int opCount; char* pc; int pcCount;
    getTables(kw, kwCount, op, opCount, pc, pcCount);
    for (int j = 0; j < kwCount; j++)
        if (kw[j] == word)
            return true;
    return false;
}

bool isOperator(const string& word) {
    string* kw; int kwCount; string* op; int opCount; char* pc; int pcCount;
    getTables(kw, kwCount, op, opCount, pc, pcCount);
    for (int j = 0; j < opCount; j++)
        if (op[j] == word)
            return true;
    return false;
}

bool isPunctuation(char c) {
    string* kw; int kwCount; string* op; int opCount; char* pc; int pcCount;
    getTables(kw, kwCount, op, opCount, pc, pcCount);
    for (int j = 0; j < pcCount; j++)
        if (pc[j] == c)
            return true;
    return false;
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

void isValidIdentifier(string text) {
    int size = text.size();
    if (size == 0) {
        cout << " (Invalid)" << text << "\n";
        return;
    }
    if ((text[0] >= 'A' && text[0] <= 'Z') || (text[0] >= 'a' && text[0] <= 'z') || text[0] == '_') {
        for (int i = 1; i < size; i++) {
            if (!((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z')
                || (text[i] >= '0' && text[i] <= '9') || text[i] == '_')) {

                cout << " (Invalid): " << text << "\n";
                return;
            }
        }
        cout << " (Valid): " << text << "\n";
    }
    else {
        cout << " (Invalid): " << text << "\n";
    }
}

string scanQuoted(const string& s, int& i) {
    char quote = s[i];
    string val(1, s[i++]);
    int n = s.length();
    while (i < n && s[i] != quote) {
        if (s[i] == '\\' && i + 1 < n) val += s[i++];
        val += s[i++];
    }
    if (i < n) val += s[i++];
    return val;
}

void skipComment(const string& text, int& i) {
    int n = text.length();
    if (text[i + 1] == '*') {
        i += 2;
        while (i + 1 < n && !(text[i] == '*' && text[i + 1] == '/')) i++;
        i += 2;
    }
    else {
        while (i < n && text[i] != '\n') i++;
    }
}

const int MAX_WORDS = 10000;

int splitWords(const string& text, string words[]) {
    int count = 0;
    int i = 0, n = text.length();

    while (i < n && count < MAX_WORDS) {
        if (text[i] == ' ' || text[i] == '\t' || text[i] == '\n') {
            i++;
            continue;
        }
        if (i + 1 < n && text[i] == '/' && (text[i + 1] == '*' || text[i + 1] == '/')) {
            skipComment(text, i);
            continue;
        }
        if (text[i] == '"' || text[i] == '\'') {
            words[count++] = scanQuoted(text, i);
            continue;
        }
        string word = "";
        while (i < n && text[i] != ' ' && text[i] != '\t' && text[i] != '\n') {
            word += text[i++];
        }
        words[count++] = word;
    }
    return count;
}

bool isValidNumber(const string& word) {
    int dotCount = 0;
    for (char c : word) {
        if (c == '.') dotCount++;
        else if (!isDigit(c)) return false;
    }
    return dotCount <= 1;
}

void classify(const string& word) {
    char first = word[0];
    if (first == '"') {
        cout << "CONSTANT (string): " << word << "\n";
        return;
    }
    if (first == '\'') {
        cout << "CONSTANT (char): " << word << "\n";
        return;
    }

    if (isDigit(first)) {
        if (isValidNumber(word))
            cout << "CONSTANT (number): " << word << "\n";
        else
            cout << "INVALID TOKEN: " << word << "\n";
        return;
    }

    if (isLetter(first)) {
        if (word == "true" || word == "false") {
            cout << "CONSTANT (boolean): " << word << "\n";
        }
        else if (word == "nullptr" || word == "null") {
            cout << "CONSTANT (null): " << word << "\n";
        }
        else if (word == "mod" || word == "MOD") {
            cout << "OPERATOR (Modulo): " << word << "\n";
        }
        else if (word == "and" || word == "AND" ||
                 word == "or"  || word == "OR"  ||
                 word == "not" || word == "NOT") {
            cout << "OPERATOR (Logical): " << word << "\n";
        }
        else if (isKeyword(word)) {
            cout << "KEYWORD: " << word << "\n";
        }
        else {
            cout << "IDENTIFIER";
            isValidIdentifier(word);
        }
        return;
    }

    if (isOperator(word)) {
        cout << "OPERATOR: " << word << "\n";
        return;
    }

    if (word.size() == 1 && isPunctuation(first)) {
        cout << "PUNCTUATION: " << word << "\n";
        return;
    }

    cout << "UNKNOWN: " << word << "\n";
}

void tokenize(const string& text) {
    string words[MAX_WORDS];
    int count = splitWords(text, words);
    for (int i = 0; i < count; i++)
        classify(words[i]);
}

void input() {
    string text;
    cout << "Enter C/C++ code (press Enter on an empty line to finish):\n";
    string line;

    while (getline(cin, line)) {
        if (line.empty())
            break;
        text += line + "\n";
    }

    cout << "\n--- Start of Tokens ---\n\n";
    tokenize(text);
    cout << "\n--- End of Tokens ---\n";

    cout << "\nIf you want to test another code, press 1; any other key to exit.\n";
    int fl = 0;
    cin >> fl;
    if (fl == 1) {
        cin.ignore();
        input();
    }
    else {
        cout << "Exiting...\n";
    }
}

int main() {
    input();
    return 0;
}
