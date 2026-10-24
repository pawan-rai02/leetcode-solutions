class Solution {
public:
    vector<int> cumMds = vector<int>(13, 0);

    int findDay(string& date) {
        int m = stoi(date.substr(0, 2));
        int d = stoi(date.substr(3, 2));

        return cumMds[m - 1] + d;
    }

    int countDaysTogether(string& arriveAlice, string& leaveAlice,
                          string& arriveBob, string& leaveBob) {

        int md[] = {31, 28, 31, 30, 31, 30,
                    31, 31, 30, 31, 30, 31};

        cumMds[1] = 0;

        for (int i = 1; i <= 12; i++) {
            cumMds[i] = cumMds[i - 1] + md[i - 1];
        }

        int aa = findDay(arriveAlice);
        int la = findDay(leaveAlice);

        int ab = findDay(arriveBob);
        int lb = findDay(leaveBob);

        int overlap = min(la, lb) - max(aa, ab) + 1;

        return max(0, overlap);
    }
};