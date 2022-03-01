/*
    Title: Set custom comparator
    Description: when you want to use a custom comparator in the set, 
    you must use the code below 
*/
struct CustomCompare{
    bool operator()(const int& lhs, const int& rhs) const{
        return lhs < rhs;
    }

    bool operator()(const Person& lhs, const Person& rhs) const{
        return lhs.getAge() < rhs.getAge();
    }
};

void SampleSetWithCustomCompare(){
    set<Person,CustomCompare> setOfPersons;

    setOfPersons.insert(Person("Person 1", 25));
    setOfPersons.insert(Person("Person 2", 16));
    setOfPersons.insert(Person("Person 3", 28));
    setOfPersons.insert(Person("Person 4", 9));

    for(set<Person,CustomCompare>::iterator it = setOfPersons.begin(); it!=setOfPersons.end(); ++it){
        cout << it->getName() << " , age : " << it->getAge()<< endl;
    }

}
