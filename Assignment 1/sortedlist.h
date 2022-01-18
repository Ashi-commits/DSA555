/*******************************************************************/
/*                                                                 */
/*  A1 Part 2: SortedList starter file                             */
/*                                                                 */
/*  version 1.1: fixed class declaration to include merge          */
/*                                                                 */
/*  Author1 Name: Amasia Nalbandian                                */
/*      - class/function list                                      */
/*  Author2 Name: <name here>                                      */
/*      - class/function list                                      */
/*                                                                 */
/*******************************************************************/

#include <iostream>
template <typename T>

class SortedList{
	// This is the node struct declared to stay private within the list. 
	struct Node{

		T data_;
		Node* next_;
		Node* prev_;

		Node(const T& data=T{},Node* nx=nullptr,Node* pr=nullptr){
			data_ = data;
			next_ = nx;
			prev_ = pr;	
		}
	};
	Node* front_;	// points to the first sentinel
	Node* back_;	// points to last sentinel
	int m_size = 0; // the size of the elements in a list, excluding sentinels.


public:
	// Const iterator class used to return iterators which must not be changed.
	class const_iterator{
		Node* curr_;
		friend class SortedList;
		const_iterator(Node* n) {
			curr_=n;
		}
	public:
		//const_iterator constructor, will set the curr_ iterator to null
		const_iterator(){ 
			curr_=nullptr;
		}

		// the below prefix and postfix operators will allow us to move through the list using iterators.
		//prefix iterator increment operator function
		const_iterator& operator++(){
			curr_=curr_->next_;
			return *this;
		}

		//postfix iterator increment operator for functions
		const_iterator operator++(int){
			const_iterator startNode = *this;
			curr_=curr_->next_;
			return startNode;
		}

		//prefix iterator decrement operator function
		const_iterator& operator--(){
			if (curr_) {
				curr_ = curr_->prev_;
			} 
			return *this;
		}

		//postfix iterator decrement operator function
		const_iterator operator--(int){ 
			const_iterator startNode = *this;	
			curr_ = curr_->prev_;	
			
			return startNode;
		}

		// this returns true if the current iterator is equal to another iterator.
		bool operator==(const_iterator rhs){
			return curr_==rhs.curr_ ;
		}
		
		// this returns true if the current iterator is not equal to another iterator.
		bool operator!=(const_iterator rhs){
			return curr_!=rhs.curr_ ;
		}
		
		// Operator will return a reference to the data in the current iterator 
		const T& operator*()const{
			return curr_->data_;
		}
	};
	// This is the iterator class, which will allow us to get through the list one node at a time.
	class iterator:public const_iterator{
		friend class SortedList;
		iterator(Node* n): const_iterator(n){}	//implementation of inheritance, every iterator is a type of const iterator, not other way around.
	public:
		iterator():const_iterator(){}
		//prefix increment operator function
		iterator& operator++(){
			this->curr_ = this->curr_->next_;
			return *this;
		}
                //postfix increment operator function
		iterator operator++(int){
			iterator startNode = *this;
			this->curr_=this->curr_->next_;
			return startNode;
		}
		//prefix decrement operator function
		iterator& operator--(){
			this->curr_ = this->curr_->prev_;
			return *this;
		}
		
		//postfix decrement operator function
		iterator operator--(int){                 // postfix 1 2 3 4, if curr = 1, we return 1 but set curr to 2.
			iterator startNode = *this;
			this->curr_ = this->curr_->prev_;
			return startNode;
		}

		//dereferencing operator function
		// returns a reference to data at the current iterator.
		T& operator*(){
			return this->curr_->data_;
		}
		//dereferencing operator function
		// returns a CONST reference to the data in the iterator.
		const T& operator*()const{
			return this->curr_->data_;
		}
	};
	SortedList();
	~SortedList();
	SortedList(const SortedList& rhs);
	SortedList& operator=(const SortedList& rhs);
	SortedList(SortedList&& rhs);
	SortedList& operator=(SortedList&& rhs);
	
	// returns an iterator object to the first node in the list.
	// this does NOT return the front sentinel
	iterator begin() {
		return iterator(front_->next_);
	};
	// returns an iterator object to the last node in the list.
	// this does NOT return the back sentinel
	iterator end() {
		return iterator(back_);
	};
	// returns a constant iterator object to the first node in the list.
	// this does NOT return the front sentinel
	const_iterator cbegin() const{ 
		return const_iterator(front_->next_);
	}
	// returns an iterator object to the last node in the list.
	// this does NOT return the back sentinel
	const_iterator cend() const{
		return const_iterator(back_);
	}
	
	iterator insert(const T& data);
	iterator search(const T& data);
	const_iterator search(const T& data) const;
	iterator erase(iterator it);
	void merge(SortedList& other);
	bool empty() const;
	int size() const;
	void display() const;
};

// Constructor for the sorted list. This will handle the creation of a new list by creating the front and back sentinels,
// and pointing these sentinel to one another. 
template <typename T>
SortedList<T>::SortedList(){
	// creates an instance of front_ and back_ to use as sentinels
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;

}

// Destructor for the sortedList, this will ensure all the nodes are deleted first, and then delete the sentinels
// to leave an empty list.
template <typename T>
SortedList<T>::~SortedList(){
	while(!empty()){
		// delete each node using remove() using iterator.
		if (front_->next_ != back_) {
			Node* temp = front_->next_->next_; // pts to second node.
			delete front_->next_;
			front_->next_ = temp;	
			m_size--;
		}
	}
	delete front_;
	delete back_;
}


template <typename T>
SortedList<T>::SortedList(const SortedList& rhs){
	//copy constructor

	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
	// deep copy of all nodes
	for (const_iterator it=rhs.cbegin(); it != rhs.cend(); it++) {
		this->insert(*it);
	}

}

template <typename T>
SortedList<T>& SortedList<T>::operator=(const SortedList& rhs){
	//copy assignment function
	while(!empty()){
		// delete each node using remove() using iterator.
		if (front_->next_ != back_) {
			Node* temp = front_->next_->next_; // pts to second node.
			delete front_->next_;
			front_->next_ = temp;	
			m_size--;
		}
	}
	delete front_;
	delete back_;


	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
	// deep copy of all nodes
	for (const_iterator it=rhs.cbegin(); it != rhs.cend(); it++) {
		this->insert(*it);
	}

	return *this;
}

// As this object list empty during a move constructor, we call the assignment to handle the move.
template <typename T>
SortedList<T>::SortedList(SortedList&& rhs){
	//move constructor
	*this=rhs;
}

template <typename T> 
SortedList<T>& SortedList<T>::operator=(SortedList&& rhs){
	//move assignment operator function
	//deleting the current object's nodes
	while(!empty()){
		// delete each node using remove() using iterator.
		if (front_->next_ != back_) {
			Node* temp = front_->next_->next_; // pts to second node.
			delete front_->next_;
			front_->next_ = temp;	
			m_size--;
		}
	}
	delete front_;
	delete back_;

	// Swapping the sentinels around so that we can achieve O(1)
	back_=rhs.back_;
	front_=rhs.front_;
	m_size = rhs.m_size;

	// setting the sentinels to nullptr after move and delete.
	rhs.back_ = nullptr;
	rhs.front_= nullptr;

	return *this;
}


template <typename T>
typename SortedList<T>::iterator SortedList<T>::insert(const T& data){

	//creating a new node with the data passed in argument
	
	iterator nn = iterator(new Node(data, nullptr, nullptr));
	m_size++;
	//checking for the current object's linked list if its empty
	//if true setting up the note as the first data node into the linked list
	if (front_->next_ == back_) 
	{
		front_->next_ = nn.curr_;
		nn.curr_->prev_ = front_;
		back_->prev_ = nn.curr_;
		nn.curr_->next_ = back_;
	}
	else
	{
		//else running an iterator loop to check for the right position of the node
		//as it is a sorted list the newly created node must be set into sorted order
		for (iterator it = begin(); it != end(); it++)
		{
			if (*nn < *it )
			{ 
				it.curr_->prev_->next_ = nn.curr_;
				nn.curr_->prev_ = it.curr_->prev_;
				nn.curr_->next_ = it.curr_;
				it.curr_->prev_ = nn.curr_;
				return nn;
			}
		}  
		//if the node could not find the position then setting it onto the last position
		//in the linked list
		back_->prev_->next_ = nn.curr_;
		nn.curr_->prev_ = back_->prev_;
		nn.curr_->next_ = back_;
		back_->prev_ = nn.curr_;

	}

	return nn;
}

template <typename T>
typename SortedList<T>::iterator SortedList<T>::search(const T& data){

	for (iterator it = begin(); it != end(); it++){   //iterator loop runs accross the linked list to match the data passed into
		                                          //parameter with the data in the linked list, if found returns the iterator else
		if (*it == data)                          //else returns nullptr
		{
			return it;
		}
	}
	return end();
}

template <typename T>
typename SortedList<T>::const_iterator SortedList<T>::search(const T& data) const{

	for (const_iterator it = cbegin(); it != cend(); it++) {   //iterator loop runs accross the linked list to match the data passed into
		                                                   //parameter with the data in the linked list, if found returns the iterator else
                if (*it == data)                                   //else returns nullptr
                {    	
                	return it;
                }
            }
            return cend();

        }

template <typename T>
        typename SortedList<T>::iterator SortedList<T>::erase(iterator it){

    iterator next= iterator(it.curr_->next_);                         //creating two node pointers to point in the same location that
	// iterator hold = iterator(it.curr_);	// another object to hold on to the iterator reference

	                                   // is passed into the parameter as iterator


	if (it != end() && it!=begin())            //checking if the pointer does not point to to the first and last data
	{                                   
		it.curr_->prev_->next_=it.curr_->next_;
		it.curr_->next_->prev_=it.curr_->prev_;                                      //data node if true then setting the pointers
	}
	else if(it == begin()){                                        //else if its the fisrt data node then setting the pointers
		front_->next_ = it.curr_->next_;
		it.curr_->next_->prev_ = front_;
	}
	else{                                                                       //else it will be the last node, so setting up the pointers
		back_->prev_ = it.curr_->prev_;
		it.curr_->prev_->next_ = back_;
	}
	
	m_size--;
	delete it.curr_;
	return next;
}

// Merge operator will look through two lists, "thisList" and "otherList" using the iterators created, and 
// will look for the correct space to insert the otherList node into thisList- ONE node at a time.
template <typename T>
void SortedList<T>::merge(SortedList& other){
	// create the instances of iterator and set to point to first node in the list.
	iterator thisList = this->begin();
	iterator otherList = other.begin();

	// run this loop until one list ends. 
	while (otherList != other.end() && thisList != end()){	
		// if thisList is lower or equal to the node in the other list, we incremenent the iterator to check the
		// next element.
		if( *thisList < *otherList || *thisList == *otherList){ 	// IF :checks that curr < other		
			thisList++;
		}
		else {	
			// otherwise we need to insert the node from the otherList into thisList
			//first I create the link between the otherNode previous and thisList.
			otherList.curr_->prev_= thisList.curr_->prev_;
			thisList.curr_->prev_->next_ = otherList.curr_;
			
			// next I have to increase the iterator here to not lose my node in the otherList. 
			// at the same time I deal with the size of the lists, incrementing one, while decrementing the other.
			otherList++;
			other.m_size--;
			this->m_size++;
			
			// Next I make sure to tie the front of the otherList to point to what WAS the second node in the list.
			// now is the current iterator after line 390. 			
			other.front_->next_ = otherList.curr_;
			otherList.curr_->prev_ = other.front_;

			// Lastly, I take care of the current iterator connecting to the new node I have just added into thisList.
			thisList.curr_->prev_= thisList.curr_->prev_->next_;
			thisList.curr_->prev_->next_=thisList.curr_;
		}
	}

	// once one of the lists reaches the end, we don't care about theList being empty... if it somehow does. BUT
	// we need to make sure that the rest of the otherList is attached right at the end of thisList, so we link the
	// front of the otherList to the back of thisList
	if (otherList != other.end()) {
		// This check makes sure that if the iterator moved past the last node to the back sentinel, we will point it back to the 
		// last element so I can succesfully attach the back of thisList to the otherList.
		if(thisList== back_) {
			thisList--;
		}
		// Linking the end of thisList to the front of theOtherList
		thisList.curr_->next_ = otherList.curr_;
		otherList.curr_->prev_=thisList.curr_;
		this->back_->prev_ = other.back_->prev_;
		this->back_->prev_->next_= back_;
		m_size += other.m_size; // adding the remaining size to thisList
	}
	// these are my safeguards to ensure I return other.m_size as 0, and that the sentinels point to one another. 
	other.m_size = 0;	
	other.front_->next_ = other.back_;
	other.back_->prev_ = other.front_;
}


template <typename T> bool SortedList<T>::empty() const{              //if the size of the current object's linked list is 0 it returns true else false
return m_size == 0 ? true : false;
}

template <typename T>
int SortedList<T>::size() const{                //returns the size of current object's linked list
return m_size; 
}

template <typename T>
void SortedList<T>::display() const {                       //running an iterator loop to print the data from the current object's linked list
for (iterator it = begin(); it != end(); it++){
	std::cout << *it << std::endl;
}
}

