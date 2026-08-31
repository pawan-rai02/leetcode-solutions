class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {

        if (!head || !head->next || !head->next->next)
            return {-1, -1};

        ListNode* first = head;
        ListNode* mid = head->next;
        ListNode* last = mid->next;

        int index = 2;

        vector<int> indices;

        while (last) {

            // local minimum
            if (first->val > mid->val && last->val > mid->val)
                indices.push_back(index);

            // local maximum
            else if (first->val < mid->val && last->val < mid->val)
                indices.push_back(index);

            first = mid;
            mid = last;
            last = last->next;

            index++;
        }

        // Need at least 2 critical points
        if (indices.size() < 2)
            return {-1, -1};

        int minDist = INT_MAX;
        int maxDist = indices.back() - indices.front();

        for (int i = 1; i < indices.size(); i++) {
            minDist = min(minDist, indices[i] - indices[i - 1]);
        }

        return {minDist, maxDist};
    }
};