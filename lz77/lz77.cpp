#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <utility>

using std::string;
using std::list;
using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::setw;

const int window_size = 5;
const char eof_symbol = '\0';

struct Node {
    int offset;
    int length;
    char next;
};

struct BasicStringView {
    int begin;
    int end;
};

Node FindMatching(const string& s, BasicStringView buffer) {
    int max_offset = 0;
    int max_length = 0;
    for (int start = buffer.begin; start < buffer.end; ++start) {
        int buffer_length = buffer.end - start;
        vector<int> pi;
        pi.reserve(buffer_length);
        pi.push_back(0);
        // for (int i = buffer.begin; i < start; ++i) {
        //     cout << setw(4) << '-';
        // }
        for (int i = 1; i < buffer_length; ++i) {
            int j = pi.back();
            while (j > 0 && s[i + start] != s[j + start]) {
                j = pi[j - 1];
            }
            if (s[i + start] == s[j + start]) {
                ++j;
            }
            pi.push_back(j);
        }
        int length = 0;
        for (int i = buffer_length; i + start < s.size(); ++i) {
            int j = pi.back();
            while (j > 0 && s[i + start] != s[j + start]) {
                j = pi[j - 1];
            }
            if (s[i + start] == s[j + start]) {
                ++j;
            }
            int prev_pi = pi.back();
            pi.push_back(j);
            if (pi.back() < prev_pi) {
                break;
            }
            length += 1;
        }
        // for (int p : pi) {
        //     cout << setw(4) << p;
        // }
        // cout << endl;
        if (length > max_length) {
            max_length = length;
            max_offset = buffer.end - start;
        }
    }
    return {max_offset, max_length, eof_symbol};
}

// TODO: Pseudocode
list<Node> Encode(const string& s) {
    list<Node> answer;
    BasicStringView buffer = {0, 0};
    int pos = 0;
    while (pos < s.size()) {
        Node next_node = FindMatching(s, buffer);
//         offset, length = findMatching(buffer, pos);
//         shiftBuffer(length + 1);
//         answer.push({offset, length, s[pos]});
    }
    return answer;
}

string Decode(const list<Node>& encoded) {
    string answer;
    for (const Node& node: encoded) {
        if (node.length > 0) {
            int start = answer.size() - node.offset;
            for (int i = start; i < start + node.length; ++i) {
                answer.push_back(answer[i]);
            }
        }
        if (node.next != eof_symbol) {
            answer.push_back(node.next);
        }
    }
    return answer;
}

int main() {    
    const string s = "ababbabbabbabbbbbb";
    // const string s = "abacabacabad";
    const BasicStringView buffer = {0, 4};
    for (int i = 0; i < s.length(); ++i) {
        cout << setw(4) << i;
    }
    cout << endl;
    for (char c : s) {        
        cout << setw(4) << c;
    }
    cout << endl;
    const Node next_node = FindMatching(s, buffer);
    cout << "{" << next_node.offset << ", " << next_node.length << ", " << next_node.next << "}" << endl;

    // const list<Node> nodes_encoded = {{0, 0, 'a'}, {0, 0, 'b'}, {2, 1, 'c'}, {4, 7, 'd'}, {2, 1, 'c'}, {2, 1, eof_symbol}};
    // const string string_decoded = "abacabacabadaca";
    // const string answer_decoded = Decode(nodes_encoded);
    // cout << answer_decoded << endl;
    // if (answer_decoded == string_decoded) {
    //     cout << "OK" << endl;
    // } else {
    //     cout << "FAIL" << endl;
    // }
    return 0;
}