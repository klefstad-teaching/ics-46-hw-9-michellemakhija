#include "ladder.h"
using namespace std;

void error(string word1, string word2, string msg) {
    cout << word1 << msg << word2 << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int stringLength1 = str1.size();
    int stringLength2 = str2.size();
    if (abs(stringLength1-stringLength2) > d) { return false; }
    
    int editsToWord = 0;
    int i, j;

    while (i < stringLength1 && j < stringLength2) {
        if (str1[i] != str2[j]) {
            editsToWord++;
            if (editsToWord > d) {return false;}
            if (stringLength1 > stringLength2) i++;
            else if (len1 < len2) j++;
            else { i++; j++; }
        }
        else {
            i++;
            j++;
        }
    }

    editsToWord += abs(len1 - i - (len2 - j));
    return edits <= d;
}
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        cout << error(begin_word, end_word, "are the same");
        return {};
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for(const string& word: word_list) {
            if(is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};
}
void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(in);
    if (!in) {
        cout << "file not loaded :(" << endl;
        return;
    }
    string word;
    while (in >> word) {
        for (char& c: word) {
            c = tolower(c);
        }
        word_list.insert(word);
    }
    in.close();
}
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "empty ladder" << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << " ";
    }
}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}