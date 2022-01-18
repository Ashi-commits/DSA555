/************************************************************/
/*  Lab 3 header                                            */
/*                                                          */
/*   Name: Ayushi Sahu                                      */
/*   Student no.: 143789188                                 */
/*                                                          */
/************************************************************/

#include <iostream>

template <typename T>
class DList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	DList(){
		front_=nullptr;
		back_=nullptr;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	void reversePrint() const;
	~DList();
};

//this functions checks for special cases and creates new node
//for every data entry and place it in front position of the double linked list.
template <typename T>
void DList<T>::push_front(const T& data){
		Node* nn=new Node(data);
		if(front_!=nullptr){
			nn->next_=front_;
			front_->prev_=nn;
		}
		else{
			back_=nn;
		}
		front_=nn;
}

//this functions checks for special cases and creates new node for every
//data entry and place it in last position of the double linked list.
template <typename T>
void DList<T>::push_back(const T& data){
	Node* nn=new Node(data);
	if(back_!=nullptr){
		nn->prev_=back_;
		back_->next_=nn;
	}
	else{
		front_=nn;
	}
	back_=nn;
}

//this function creates deletes the node present at the position of
//front_ node in the double linked list.
template <typename T>
void DList<T>::pop_front(){
	Node* rm;
	if(front_!=nullptr){
		rm = front_;
		front_ = rm->next_;
		if(front_!=nullptr){
			front_->prev_=nullptr;
		}
		else{
			back_=nullptr;
		}
		delete rm;
	}

}

//this function creates deletes the node present at the position of
//back_ node in the double linked list.
template <typename T>
void DList<T>::pop_back(){
	Node* rm;
	if(back_!=nullptr){
		rm = back_;
		back_ = rm->prev_;
		if(back_!=nullptr){
			back_->next_=nullptr;
		}
		else{
			front_=nullptr;
		}
		delete rm;
	}

}

template <typename T>
void DList<T>::print() const{
	Node* curr=front_;
	while(curr!=nullptr){
		std::cout << curr->data_ << " ";
		curr=curr->next_;
	}
	if(!front_){
		std::cout << "empty list";
	}
	std::cout << std::endl;
}

template <typename T>
void DList<T>::reversePrint() const{
	Node* curr=back_;
	while(curr!=nullptr){
		std::cout << curr->data_ << " ";
		curr=curr->prev_;
	}
	if(!back_){
		std::cout << "empty list";
	}
	std::cout << std::endl;
}

//this destructor deletes the nodes from the linked list until
//the list is empty and points to nullptr, this does not only empties
//the data but it also deletes the existance of the node in the list
//to prevent memory leakage.
template <typename T>
DList<T>::~DList(){
	Node* del=front_;
	while(front_!=nullptr){
		del=front_;
		front_=del->next_;
		delete del;
	}
}

template <typename T>
class Sentinel{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	Sentinel(){
		front_=new Node();
		back_=new Node();
		front_->next_=back_;
		back_->prev_=front_;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
	void reversePrint() const;
	~Sentinel();
};

//this function creates new node for every data entry and place it in
//between the sentinel nodes after front_ node of the double linked list.
template <typename T>
void Sentinel<T>::push_front(const T& data){
	Node* nn = new Node(data,front_->next_,front_);
	front_->next_->prev_=nn;
	front_->next_=nn;
}

//this function creates new node for every data entry and place it in
//between the sentinel nodes before back_ node of the double linked list.
template <typename T>
void Sentinel<T>::push_back(const T& data){
	Node* nn = new Node(data,back_,back_->prev_);
	back_->prev_->next_=nn;
	back_->prev_=nn;
}

//this function creates deletes the node present after the front_
//node between the sentinel nodes in the double linked list.
template <typename T>
void Sentinel<T>::pop_front(){
	//if its an empty list... note that it means
	//front sentinel's next node is the back sentinel
	if(front_->next_!=back_){
		Node* rm = front_->next_;
		Node* B = rm ->next_;
		front_->next_= B;
		B->prev_=front_;
		delete rm;
	}
}

//this function creates deletes the node present before the back_
//node between the sentinel nodes in the double linked list.
template <typename T>
void Sentinel<T>::pop_back(){
	if(front_!=back_->prev_){
		Node* rm = back_->prev_;
		Node* B = rm ->prev_;
		back_->prev_= B;
		B->next_=back_;
		delete rm;
	}
}

template <typename T>
void Sentinel<T>::print() const{
	Node* curr=front_->next_;
	while(curr!=back_){
		std::cout << curr->data_ << " ";
		curr=curr->next_;
	}
	if(front_->next_==back_){
		std::cout << "empty list";
	}
	std::cout << std::endl;
}

template <typename T>
void Sentinel<T>::reversePrint() const{
	Node* curr=back_->prev_;
	while(curr!=front_){
		std::cout << curr->data_ << " ";
		curr=curr->prev_;
	}
	if(back_->prev_==front_){
		std::cout << "empty list";
	}
	std::cout << std::endl;
}

//this destructor deletes the nodes from the linked list until
//the list is empty and points to nullptr, this does not only empties
//the data but it also deletes the existance of the node in the list
//to prevent memory leakage.
template <typename T>
Sentinel<T>::~Sentinel(){
	Node* del=front_;
	while(front_!=nullptr){
		del=front_;
		front_=del->next_;
		delete del;
	}
}
