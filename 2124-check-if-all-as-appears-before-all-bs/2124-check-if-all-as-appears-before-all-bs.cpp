class Solution {
public:
    bool checkString(string& s) {
        
        bool bseen = false;
        bool aseen = false;

        for(char &c : s){
            if(c == 'b')
                bseen = true;

            else if(c == 'a'){
                if(bseen == true)
                    return false;
                else 
                    aseen = true;
            }
        }

        return true;
    }
};