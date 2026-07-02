class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {

        sort(points.begin(), points.end());

int prevS = points[0][0];
int prevE = points[0][1];
int arrows = 1;

for (int i = 1; i < points.size(); i++) {
    int currS = points[i][0];
    int currE = points[i][1];

    if (currS <= prevE) {
        prevS = max(prevS, currS);
        prevE = min(prevE, currE);
    } else {
        prevS = currS;
        prevE = currE;
        arrows++;
    }
}return arrows;
    }
};