#include "examples.h"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <list>
#include <set>
#include <unordered_set>
#include <forward_list>
#include <iterator>
#include <string>
#include <utility>

using namespace std;

void vector_example(){
    vector<int> myvec;
	int i;
	for(i=0;i<5;i++)
		myvec.push_back(i);
	for(i=0;i<5;i++)
		cout<<myvec[i]<<" ";

	int exsize=myvec.size();
	int excap=myvec.capacity();

    cout<<endl<<"Vector size="<<exsize<<endl;
	cout<<"Vector capacity="<<excap<<endl;
	cout<<endl<<"Data to be added exceeds vector capacity"<<endl;

	for(i=exsize;i<2*excap;i++)
		myvec.push_back(i);

	cout<<"Vector size="<<myvec.size()<<endl;
	cout<<"Vector capacity="<<myvec.capacity()<<endl;	
	
    cout<<endl<<"Data is being added to vector"<<endl;
    myvec.push_back(i+1);

    cout<<"Vector size="<<myvec.size()<<endl;
	cout<<"Vector capacity="<<myvec.capacity()<<endl;

	while(!myvec.empty()){
		cout<<myvec.back()<<" ";
		myvec.pop_back();
	}

}

void stack_example(){
    stack<int> stack;
	
    for(int i=0;i<5;i++)
		stack.push(i);
	
    while(!stack.empty()){
		cout<<stack.top()<<endl;
		stack.pop();
	}

}

void queue_example(){
	
    queue<int> myq;
	
    for(int i=0;i<5;i++)
		myq.push(i);
	
    while(!myq.empty()){
		cout<<myq.front()<<endl;
		myq.pop();
	}

}

void pqueue_example(){
    priority_queue<int> mypq;

	mypq.push(30);
	mypq.push(100);
	mypq.push(25);
	mypq.push(40);
 	while (!mypq.empty()){	 
         cout << " " << mypq.top()<<endl;
		 mypq.pop();
	}

}

void map_example(){
	map<string, string> strMap;
	strMap["Monday"]    = "1";
	strMap["Tuesday"]   = "2";
	strMap["Wednesday"] = "3";
	strMap["Thursday"]  = "4";
	strMap["Friday"]    = "5";
	strMap["Saturday"]  = "6";

	strMap.insert(pair<string, string>("Sunday", "7"));
	while(!strMap.empty()){
		cout<<strMap.begin()->first<<" "
			<<strMap.begin()->second<<endl;
		strMap.erase(strMap.begin());
	}

}

void iterator_example(){
	list<int> myl;	
	for(int i=0;i<5;i++)
		myl.push_back(i);
	list<int>::iterator myit;
	for(myit=myl.begin();myit!=myl.end();myit++)
		cout<<*myit<<endl;

	list<int>::reverse_iterator myrit;
	for(myrit=myl.rbegin();myrit!=myl.rend();myrit++)
		cout<<*myrit<<endl;

}

void list_example(){
	list <int> list1; 
  	forward_list<char> list2;

	list2.assign({'a', 'b', 'c'});
  
  	for (int i = 0; i < 10; ++i) 
        list1.push_back(i * 2); 

	list1.reverse(); 
	list<int>::iterator it; 
    for(it = list1.begin(); it != list1.end(); ++it) 
        cout << *it << " "; 
    cout << endl; 

	list1.sort(); 
    for (int&i : list1)
        cout << i << " ";
    cout << endl;


	list2.assign({'a', 'b', 'c'});
  
    for (char&ch : list2)
        cout << ch << " ";
    cout << endl;

	list2.assign(10, 'x');

	for (char&ch : list2)
        cout << ch << " ";
    cout << endl;
}

void set_example(){
	set<int> set1;
 
	for(int i=1;i<10;i++)
    	set1.insert(i*10);
	set1.insert(50); 
    set1.insert(10);
 
    for (const int i : set1)
        cout << i << " ";
    cout << endl;
 
    set<int> set2(set1.begin(), set1.end());
 
    for (const int i : set2)
        cout << i << " ";
    cout << endl;
 
 	set2.erase(80);
    set2.erase(set2.begin(), set2.find(40));
    for (const int i : set2)
        cout << i << " ";
    cout << endl;

    cout << *set1.lower_bound(60) << endl;
    cout << *set1.upper_bound(60) << endl;
}

void unordered_set_map_example(){
    unordered_set<string> set1 ; 

    set1.insert("tolga") ; 
    set1.insert("ovatman") ; 
    set1.insert("blg223") ; 
    set1.insert("123412") ; 
    set1.insert("data structures") ; 
      
    for (string s : set1)
        cout << s << " ";
    cout << endl;

	unordered_map<string, int> map1; 
  
    map1["Tolga"] = 1980; 
    map1["Duygu"] = 1985; 
    map1["Teoman"] = 2020; 
  
	//auto keywrod might be used as well
    for (pair<string, int> x : map1) 
      cout << x.first << " " << x.second << endl; 
}

void wfreq_example(){
   	FILE *myfile= fopen( "some_text.txt", "r" );
	if(!myfile){
        cout << "File cannot be opened"<<endl;
        return;
    }			
	char word[100];
	map <string,int> freq; 
	while(!feof(myfile)){
		fscanf(myfile,"%s",word);		
		freq[word]++;
	}
	fclose(myfile); 
    multimap<int,string> freq_rev;
    map<string,int>::iterator it;
    for(it=freq.begin();it!=freq.end();it++)
        freq_rev.insert(make_pair(it->second,it->first));

    multimap <int,string>::reverse_iterator myit;
    int count;
    for (myit=freq_rev.rbegin(),count=0;count<10;myit++,count++)
	    cout<<(*myit).second<<" "<<(*myit).first<<endl;

}




