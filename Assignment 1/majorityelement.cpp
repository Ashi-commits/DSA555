/*******************************************************************/
/*                                                                 */
/*  A1 Part 3: Majority Element starter file                       */
/*                                                                 */
/*  Author1 Name: <name here>                                      */
/*      - function list                                            */
/*  Author2 Name: <name here>                                      */
/*      - function list                                            */
/*                                                                 */
/*******************************************************************/
bool findCandidate(int array[],int& candidate, int sz);
bool majorityElement(const int arr[], int& majority, int sz);

bool majorityElement(const int arr[], int& majority, int sz){
    bool majorityExists = false;
    int arrCpy[sz];
    int occurence=0;
    //copy array
    for (int i = 0; i < sz; i++) {
        arrCpy[i] = arr[i];
    }

    // call to findCandidate
    if (findCandidate(arrCpy, majority, sz)) {
        // check that it is the majority element
        for(int i = 0; i < sz; i++){
            if(arr[i] == majority) {
                occurence++;
            }
        }
        majorityExists = occurence > (sz/2) ? true : false;
    }


    return majorityExists;

}

//this functions finds the possible candidats for the majority element
//this will take the input array and compare the consecutive elements in the
//array (like in pairs) and if the elements are same then it stores into another
//array named 'data'
bool findCandidate(int array[],int& candidate, int sz){
    bool candidateExists; 
    if(sz==0){
        return false;
    }

    if(sz==1){
        candidate=array[0];
        return true;
    }


    int data[sz];
    int i=0,j=0;
    while(i<sz/2){                               //running a while loop to check the elements of the pair of equality
                                                 //if found then storing it into the newly created array 'data'
        if(array[2*i]==array[2*i+1]){
            data[j]=array[2*i];
            j++;
        }
        i++;
    }
    if(j==0){                                     //here we check if are no matching elements in the
                                                  //pair then check if the array contains odd number of elements
        if(sz%2==1){
            data[j]=array[sz-1];                  //if true then se the data into the 'data' array
            j++;
        }
    }
    bool ans=findCandidate(data,candidate,j);
    //calling the findCandidate function to iterate,
    //this cycle goes on until the possible candidate is found
    //if the size of array is odd number after completed all the iterations
    //then we will set the possible candidate and return the result of the function
    if(ans==false){
        if(sz%2==1){
            candidate=array[sz-1];
            ans=true;
        }
    }
    return ans;
}
