#include <iostream>
#include <list>
#include <string>

using std::string;
using std::list;
using std::cout;
using std::endl;

const int window_size = 5;

struct Node {
    int offset;
    int length;
    char next;
};

// TODO: Pseudocode
// list<Node> encode(string s) {
//     list<Node> answer;
//     int pos = 0;
//     string buffer;
//     while (pos < s.size()) {
//         offset, length = findMatching(buffer, pos);
//         shiftBuffer(length + 1);
//         answer.push({offset, length, s[pos]});
//     }
//     return answer;
// }

string Decode(list<Node> encoded) {
    string answer;
    for (const Node& node: encoded) {
        if (node.length > 0) {
            int start = answer.size() - node.offset;
            for (int i = start; i < start + node.length; ++i) {
                answer.push_back(answer[i]);
            }
        }
        answer.push_back(node.next);
    }
    return answer;
}

int main() {
    const list<Node> nodes_encoded = {{0, 0, 'a'}, {0, 0, 'b'}, {2, 1, 'c'}, {4, 7, 'd'}, {2, 1, 'c'}, {2, 1, '$'}};
    const string string_decoded = "abacabacabadaca$";
    const string answer_decoded = Decode(nodes_encoded);
    cout << answer_decoded << endl;
    if (answer_decoded == string_decoded) {
        cout << "OK" << endl;
    }
    return 0;
}