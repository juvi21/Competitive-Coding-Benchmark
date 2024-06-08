#include <iostream>
#include <set>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> songs(n);
    for (int i = 0; i < n; i++) {
        std::cin >> songs[i];
    }

    std::set<int> unique_songs;
    int left = 0, right = 0;
    int max_length = 0;

    while (right < n) {
        if (unique_songs.find(songs[right]) == unique_songs.end()) {
            unique_songs.insert(songs[right]);
            max_length = std::max(max_length, right - left + 1);
            right++;
        } else {
            unique_songs.erase(songs[left]);
            left++;
        }
    }

    std::cout << max_length << std::endl;
    return 0;
}