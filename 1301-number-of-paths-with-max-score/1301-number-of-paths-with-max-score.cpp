class Solution {
public:
    int MOD = 1e9 + 7;
    int f(int x, int y, vector<string>& board, vector<vector<int>>& total_ways,
          vector<vector<int>>& score) {
        // Out of bounds, or obstacle
        if (x < 0 || y < 0 || board[x][y] == 'X') {
            return -1;
        }
        // Reached 'E'
        if (x == 0 && y == 0 && board[x][y] == 'E') {
            total_ways[x][y] = 1;
            return score[x][y] = 0;
        }

        if (score[x][y] != -2) {
            return score[x][y];
        }

        // Try in all 3 directions
        // Up
        int up_score = f(x - 1, y, board, total_ways, score);
        // Left
        int left_score = f(x, y - 1, board, total_ways, score);
        // Up-left => diagonal
        int diag_score = f(x - 1, y - 1, board, total_ways, score);

        int best_score = max({up_score, left_score, diag_score});

        // No path is possible
        if (best_score == -1) {
            total_ways[x][y] = 0;
            return score[x][y] = -1;
        }

        int cnt_ways = 0;
        int up_ways = (x > 0) ? total_ways[x - 1][y] : 0;
        int left_ways = (y > 0) ? total_ways[x][y - 1] : 0;
        int diag_ways = (x > 0 && y > 0) ? total_ways[x - 1][y - 1] : 0;

        // For score from each of the three directions,
        // if it mathces the best score, include no of ways to reach that also
        if (best_score == up_score) {
            cnt_ways = (cnt_ways + up_ways) % MOD;
        }
        if (best_score == left_score) {
            cnt_ways = (cnt_ways + left_ways) % MOD;
        }
        if (best_score == diag_score) {
            cnt_ways = (cnt_ways + diag_ways) % MOD;
        }
        total_ways[x][y] = cnt_ways % MOD;

        // Add the current cells value also
        if (isdigit(board[x][y])) {
            best_score += board[x][y] - '0';
        }
        return score[x][y] = best_score;
    }

    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        vector<vector<int>> total_ways(n, vector<int>(n, 0));
        vector<vector<int>> score(n, vector<int>(n, -2)); // -2 = not computed

        int max_score = f(n - 1, n - 1, board, total_ways, score);
        if (max_score == -1) {
            return {0, 0};
        }
        return {max_score, total_ways[n - 1][n - 1]};
    }
};