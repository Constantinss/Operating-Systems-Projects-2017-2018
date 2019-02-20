#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

std::map<string, int>mp_values;

template<typename K, typename V>
bool findByValue(std::vector<K> & vec, std::map<K, V> mapOfElemen, V value)
{
	int c = 0;
	bool bResult = false;
	auto it = mapOfElemen.begin();
	// Iterate through the map
	while(it != mapOfElemen.end())
	{
		// Check if value of this entry matches with given value
		if(it->second == value)
		{ 
			c++;
			// Yes found
			if(c >= 2)
			{
				bResult = true;
				// Push the key in given map
			}
				vec.push_back(it->first);
			
		}
		// Go to next entry in map
		it++;
	}
	return bResult;
}

// Insert keys and values into collection
void insert_mp(std::vector<string> &v){
	for (int i = 0; i < v.size(); i+=2)
	{
		int num = atoi(v[i+1].c_str());
		
		if(mp_values.find(v[i]) == mp_values.end() ){

			mp_values.insert(pair<string, int>( v[i], num ));

		}else{

			mp_values.find(v[i])->second += atoi(v[i+1].c_str());
		
		}
	}
}

// Remove white space in input
size_t split(const string &txt, std::vector<string> &str, char ch){
	size_t pos = txt.find(ch);
	size_t init = 0;
	str.clear();

	while(pos != std::string::npos){
			str.push_back(txt.substr(init, pos - init));
			init = pos + 1;

			pos = txt.find(ch, init);
	}

	str.push_back( txt.substr( init, std::min( pos, txt.size() ) - init + 1 ) );

	return str.size();
}

int main(int argc, char const *argv[])
{
	string str;
	while(true){
		std::vector<std::string> v;
		getline(cin, str);

		// Will end after insert q
		if(str == "q")
			break;
		
		split(str, v, ' ');
		insert_mp(v);
	}
	
	// This section is for the ouput
	std::vector<int> arr;
	for(std::map<string,int>::iterator itr = mp_values.begin(); itr != mp_values.end(); ++itr){

		vector<string> vec;
		bool result = findByValue(vec, mp_values, itr->second);

		if(std::find(arr.begin(), arr.end(), itr->second) == arr.end()){
		 if(result == true){
			
				int i;
				for (i = 0; i < vec.size() - 1; ++i)
				{
			
					cout << vec[i] << ", ";
				}

			    cout << vec[i++] << " : " << itr->second << endl;
			
		 }else{
			
	    	cout << itr->first << ": " << itr->second << '\n';
		
		 }
		 arr.push_back(itr->second);
		}
		
	}
	

	return 0;
}