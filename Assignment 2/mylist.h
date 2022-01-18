/*******************************************************/
/*                                                     */
/*  Put your linked list code from A1/lab3/lab4 into   */
/*  this file                                          */
/*                                                     */
/*******************************************************/


/************************************************************/
/*  Lab 4				                    */
/*  				                            */
/*     Nasme: Ayushi Sahu   	                            */
/*     Student no.: 143789188                               */
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
	void push_back(const T& data);
    void remove(const T& data);
    void pop_front();
    void pop_back();
	~DList();

	class const_iterator{
	        friend class DList;
		Node* curr_;
        	const DList* theList_;
		const_iterator(Node* n, const DList* list){
			curr_=n;
			theList_=list;
		}
	public:
		const_iterator(){
			theList_=nullptr;
			curr_=nullptr;
		}
		//in this function checks the existance of the curr_ pointer of the
		//current object and if its true it increments the pointer to point
		//onto next node and returns the current object
		const_iterator operator++(){
			if(this->curr_){
				this->curr_=this->curr_->next_;
			}
			return *this;
                }
		//in this function checks the existance of the curr_ pointer of the
		//current object and if its true it increments the pointer to point
		//onto next node and returns the previous object
		const_iterator operator++(int){
			const_iterator old=*this;
			if(this->curr_){
				this->curr_=this->curr_->next_;
			}
			return old;
                 }

		//in this function checks the existance of the curr_ pointer of the
		//current object and if its true it decrements the pointer to point
		//onto previous node, else it will set the pointer to the back of the
		//linked list and returns the current object
		const_iterator operator--(){
			if (this->curr_){
				this->curr_=this->curr_->prev_;
			}
			else{
				this->curr_=this->theList_->back_;
			}
			return *this;
		}

		//in this function checks the existance of the curr_ pointer of the
		//current object and if its true it decrements the pointer to point
		//onto previous node, else it will set the pointer to the back of the
		//linked listand returns the previous object
		const_iterator operator--(int){
                 const_iterator old=*this;
			if (this->curr_){
				this->curr_=this->curr_->prev_;
			}
			else{
				this->curr_=this->theList_->back_;
			}
			return old;
                 }

		//this function will check for the same iterator from
		//parameter and the current iterator
		bool operator==(const_iterator rhs){
				return theList_==rhs.theList_ && curr_==rhs.curr_;
		}

		//this function will check for the different iterator from
		//parameter and the current iterator
		bool operator!=(const_iterator rhs){
				return theList_!=rhs.theList_ || curr_!=rhs.curr_;
		}

		//this function will return the data stored in the current object
		const T& operator*()const{
			return this->curr_->data_;
		}
	};

	class iterator:public const_iterator{
	    friend class DList;
            iterator(Node* n, const DList* list):const_iterator(n, list){}
	    public:

		iterator():const_iterator(){}

		//in this function checks the existance of the curr_ pointer of the
		//current object and if its true it increments the pointer to point
		//onto next node and returns the current object
		iterator operator++(){
			if(this->curr_){
				this->curr_=this->curr_->next_;
			}
			return *this;
		}

		//in this function checks the existance of the curr_ pointer of the
		//current object and if its true it increments the pointer to point
		//onto next node and returns the previous object
		iterator operator++(int){
			iterator old=*this;
				if(this->curr_){
					this->curr_=this->curr_->next_;
				}
				return old;
		}

		//in this function checks the existance of the curr_ pointer of the
		//current object and if its true it decrements the pointer to point
		//onto previous node, else it will set the pointer to the back of the
		//linked list and returns the current object
		iterator operator--(){
			if(this->curr_){
				this->curr_=this->curr_->prev_;
			}
			else{
				this->curr_=this->theList_->back_;
			}
			return *this;
		}

		//in this function checks the existance of the curr_ pointer of the
		//current object and if its true it decrements the pointer to point
		//onto previous node, else it will set the pointer to the back of the
		//linked list and returns the previous object
		iterator operator--(int){
			iterator old=*this;
			if(this->curr_){
				this->curr_=this->curr_->prev_;
			}
			else{
				this->curr_=this->theList_->back_;
			}
			return old;
		}

		//this fucntion returns the data stored in the current object
               T& operator*(){
			return this->curr_->data_;
		}
		//this fucntion returns the data stored in the current object
		const T& operator*()const{
			return this->curr_->data_;
		}
	};

	//this function sets the node pointer to point at the beginning
	//and current object in the linked list
	const_iterator cbegin() const{
		return const_iterator(front_, this);
	}
	//this function sets the node pointer to point at the beginning
	//and current object in the linked list
	iterator begin(){
		return iterator(front_, this);
	}
	//this function sets the node pointer to point at the nullptr/back->next_
	//and current object in the linked list
	const_iterator cend() const{
		return const_iterator(nullptr, this);
	}
	//this function sets the node pointer to point at the nullptr/back->next_
	//and current object in the linked list
	iterator end(){
		return iterator(nullptr, this);
	}
};



//this function creates deletes the node present at the position of
//front_ node in the double linked list.
template <typename T>
void DList<T>::pop_front(){
	Node* rm;
	//if the current node is not nullptrn then point a newly created
	//pointer to the current node and reset the pointers of the node based on 
	//condition for deletion of the node pointed by newly created pointer.
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

//this function deletes the node present at the position of
//back_ node in the double linked list.
template <typename T>
void DList<T>::pop_back(){
	Node* rm;
	//if the current node is not nullptrn then point a newly created
	//pointer to the current node and reset the pointers of the node based on 
	//condition for deletion of the node pointed by newly created pointer.
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

//this function deletes the node present at the position of
//back_ or fron_ node in the double linked list by checking the data
//reference passed into the argument
template <typename T>
void DList<T>::remove(const T& data){

    if(front_==nullptr){
        return;
    }
 
	//if the data refernce passed in matches to the data of front_ or back_ node then
	//I am simply calling the respective pop functions
		if(front_->data_==data){
			pop_front();
		}
		else if(back_->data_==data){
			pop_back();
		}
	//else I am resetting the node pointers and creating a new pointer to delete the node
	//matching the data reference passed into the argument.
        else{
        Node* rm=front_;
        while(rm!=back_){
            if(rm->data_==data){
                rm->prev_->next_=rm->next_;
                rm->next_->prev_=rm->prev_;
                delete rm;
                return;
            }
            rm=rm->next_;
        }
	}
    
}


//this functions checks for special cases and creates new node
//for every data entry and place it in front position of the double linked list.
template <typename T>
void DList<T>::push_back(const T& data){
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

//Sentinel
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
	~Sentinel();

	class const_iterator{
		friend class Sentinel;
		Node* curr_;
		const_iterator(Node* n){
			curr_=n;
		}
	public:
		const_iterator(){
			curr_=nullptr;
		}
		//this function sets the current object's cur__ pointer to
		//point at the next node in the linked list and returns
		//the current object
		const_iterator operator++(){
			curr_=curr_->next_;
			return *this;
		}
		//this function sets the current object's cur__ pointer to
		//point at the next node in the linked list and returns
		//the previous object which was without any changes
		const_iterator operator++(int){
			const_iterator old=*this;
			curr_=curr_->next_;
			return old;
		}

		//this function sets the current object's cur__ pointer to
		//point at the previous node in the linked list and returns
		//the current object
		const_iterator operator--(){
                   curr_=curr_->prev_;
			return *this;
                }
		//this function sets the current object's cur__ pointer to
		//point at the previous node in the linked list and returns
		//the previous object which was without any changes
		const_iterator operator--(int){
                  const_iterator old=*this;
			curr_=curr_->prev_;
			return old;
                }
		//this function will check for the same iterator from
		//parameter and the current iterator
		bool operator==(const_iterator rhs){
			return curr_==rhs.curr_;
		}
		//this function will check for the different iterator from
		//parameter and the current iterator
		bool operator!=(const_iterator rhs){
			return curr_!=rhs.curr_;
		}
		//this function returns the data stored in the current object
		const T& operator*() const{
			return curr_->data_;
		}
	};

	class iterator:public const_iterator{
		friend class Sentinel;
		iterator(Node* n):const_iterator(n){
		}
	        public:
		iterator():const_iterator(){}

		//this function sets the current object's cur__ pointer to
		//point at the next node in the linked list and returns
		//the current object
                iterator operator++(){
	           this->curr_=this->curr_->next_;
			return *this;
		}
		//this function sets the current object's cur__ pointer to
		//point at the next node in the linked list and returns
		//the previous object which was without any changes
		iterator operator++(int){
                  iterator old=*this;
			this->curr_=this->curr_->next_;
			return old;
                }
		//this function sets the current object's cur__ pointer to
		//point at the previous node in the linked list and returns
		//the current object
		iterator operator--(){
                  this->curr_=this->curr_->prev;
			return *this;
                }
		//this function sets the current object's cur__ pointer to
		//point at the previous node in the linked list and returns
		//the previous object which was without any changes
		iterator operator--(int){
                   iterator old=*this;
			this->curr_=this->curr_->prev_;
			return old;
                }
		//this function returns the data stored in the current object
		T& operator*(){
			return this->curr_->data_;
		}
		//this function returns the data stored in the current object
		const T& operator*()const{
			return this->curr_->data_;
		}
	};

	//this function sets the node pointer to point at the first data
	//sentinel of the linked list
	const_iterator cbegin() const{
		return const_iterator(front_->next_);
	}
	//this function sets the node pointer to point at the first data
	//sentinel of the linked list
	iterator begin(){
		return iterator(front_->next_);
	}
	//this function sets the node pointer to point at the back sentinel
	//of the linked list
	const_iterator cend() const{
		return const_iterator(back_);
	}
	//this function sets the node pointer to point at the back sentinel
	//of the linked list
	iterator end(){
		return iterator(back_);
	}
};

//this functions creates new node for every data entry and place
//it next to the front node's position in the double linked list
template <typename T>
void Sentinel<T>::push_front(const T& data){
		Node* nn = new Node(data,front_->next_,front_);
		front_->next_->prev_=nn;
		front_->next_=nn;
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
