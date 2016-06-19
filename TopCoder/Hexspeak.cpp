#include<bits/stdc++.h>
using namespace std;
class Hexspeak{
    public:
    	 string decode(long long ciphertext)
             {
             		char arr[16];
             		memset(arr,'n', sizeof(arr));
             		stringstream stream;
             		stream << hex << ciphertext;
             		string str ( stream.str());
					bool found = false;
             		for(int i=0;i< str.length(); i++)
                       {
                        if(str.at(i) == '1')
                            str.at(i) = 'I';
                        else if(str.at(i) == '0')
                            str.at(i) == 'O';
                                
						else if(str.at(i) >= 97 && str.at(i) <= 102)
							str.at(i) = str.at(i) - 32;
						
						else
						{
							found = true;
							break;
						}
                        
                    }
					
					if(found== true)
						return "Error!"; 
						
						
					
           			return str;
             
             }
    
    
    
    
    };
	
int main()
{

	Hexspeak a;
	return 0;
}