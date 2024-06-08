#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    TrieNode* suffixLink;
    TrieNode* outputLink;
    vector<int> patternIndices;
};

class AhoCorasick {
public:
    AhoCorasick(const vector<string>& patterns) {
        root = new TrieNode();
        buildTrie(patterns);
        buildSuffixAndOutputLinks();
    }

    vector<int> search(const string& text, int k) {
        vector<int> occurrences(k, 0);
        TrieNode* currentNode = root;

        for (int i = 0; i < text.size(); ++i) {
            char c = text[i];

            while (currentNode != root && currentNode->children.find(c) == currentNode->children.end()) {
                currentNode = currentNode->suffixLink;
            }

            if (currentNode->children.find(c) != currentNode->children.end()) {
                currentNode = currentNode->children[c];
            } else {
                currentNode = root;
            }

            TrieNode* tempNode = currentNode;
            while (tempNode != root) {
                for (int index : tempNode->patternIndices) {
                    occurrences[index]++;
                }
                tempNode = tempNode->outputLink;
            }
        }

        return occurrences;
    }

private:
    TrieNode* root;

    void buildTrie(const vector<string>& patterns) {
        for (int i = 0; i < patterns.size(); ++i) {
            const string& pattern = patterns[i];
            TrieNode* currentNode = root;

            for (char c : pattern) {
                if (currentNode->children.find(c) == currentNode->children.end()) {
                    currentNode->children[c] = new TrieNode();
                }
                currentNode = currentNode->children[c];
            }

            currentNode->patternIndices.push_back(i);
        }
    }

    void buildSuffixAndOutputLinks() {
        queue<TrieNode*> q;
        root->suffixLink = root;
        q.push(root);

        while (!q.empty()) {
            TrieNode* currentNode = q.front();
            q.pop();

            for (auto& child : currentNode->children) {
                char c = child.first;
                TrieNode* childNode = child.second;

                TrieNode* tempNode = currentNode->suffixLink;
                while (tempNode != root && tempNode->children.find(c) == tempNode->children.end()) {
                    tempNode = tempNode->suffixLink;
                }

                if (tempNode->children.find(c) != tempNode->children.end() && tempNode->children[c] != childNode) {
                    childNode->suffixLink = tempNode->children[c];
                } else {
                    childNode->suffixLink = root;
                }

                if (childNode->suffixLink->patternIndices.empty()) {
                    childNode->outputLink = childNode->suffixLink->outputLink;
                } else {
                    childNode->outputLink = childNode->suffixLink;
                }

                q.push(childNode);
            }
        }
    }
};

int main() {
    string text;
    cin >> text;

    int k;
    cin >> k;

    vector<string> patterns(k);
    for (int i = 0; i < k; ++i) {
        cin >> patterns[i];
    }

    AhoCorasick ac(patterns);
    vector<int> result = ac.search(text, k);

    for (int count : result) {
        cout << count << endl;
    }

    return 0;
}
