#include <iostream>
#include "person.h"

int main()
{
    Person person1(Person::MALE, "E");
    Person person2(Person::FEMALE, "W");
    Person person3(Person::MALE, "DeJun");
    Person person4(Person::MALE, "Wang");
    Person person5(Person::MALE, "grands");
    Person person6(Person::FEMALE, "Wan");
    Person person7(Person::FEMALE, "Hou");

    Person person8(Person::MALE, "uncle");
    Person person9(Person::MALE, "MJ");
    Person person10(Person::MALE, "Wang2");

    Person person11(Person::MALE, "uncle1");
    Person person12(Person::MALE, "MJ1");


    std::cout << "Person 1 - Name: " << person1.name << ", Sex: " << (person1.sex == Person::MALE ? "MALE" : "FEMALE") << std::endl;
    std::cout << "Person 2 - Name: " << person2.name << ", Sex: " << (person2.sex == Person::MALE ? "MALE" : "FEMALE") << std::endl;

    
    bool addC = person3.addChild(&person2);
    //bool checkC = person3.hasChild(&person2);
    bool addC1 = person3.addChild(&person1);
    //person3.removeAllChildren();
    bool checkC1 = person3.hasChild(&person1);
    bool checkRC = person3.hasChild(&person2);
    bool setAnc = person3.setFather(&person4);
    bool setAnc1 = person3.setFather(&person10);    // reset father
    bool setGran = person5.setFather(&person1);
    bool setSib = person6.setMother(&person7);
    bool setSib1 = person6.setFather(&person3);

    bool setUnc = person8.setFather(&person10);
    bool setCousin = person8.addChild(&person9);

    bool setUnc1 = person11.setFather(&person10);
    bool setCousin1 = person11.addChild(&person12);

    People anc;
    person5.getAncestors(anc);

    People dec;
    person10.getDescendants(dec);

    People sib;
    person1.getSiblings(sib);

    People cous;
    person9.getCousins(cous);

    std::cout << "Ancestors of gran:" << std::endl;
    for (const Person* ancestor : anc) {
        std::cout << ancestor->name << std::endl;
    }

    std::cout << "Decen of Wang2:" << std::endl;
    for (const Person* decen : dec) {
        std::cout << decen->name << std::endl;
    }

    std::cout << "siblings of: E" << std::endl;
    for (const Person* sibling : sib) {
        std::cout << sibling->name << std::endl;
    }

    std::cout << "cousins of: MJ" << std::endl;
    for (const Person* cousins  : cous) {
        std::cout << cousins->name << std::endl;
    }


    //bool r1 = person1.removeChild(&person2);
    //checkRC = person1.hasChild(&person2);

    //bool addC1 = person3.addChild(&person2);
    //bool checkC1 = person3.hasChild(&person1);

    std::cout << addC << std::endl;
    //std::cout << checkC << std::endl;
    std::cout << addC1 << std::endl;
    std::cout << checkC1 << std::endl;
    //std::cout << removeC << std::endl;
    std::cout << checkRC << std::endl;
    //std::cout << r1 << std::endl;
    //std::cout << addC1 << std::endl;
    //std::cout << checkC1 << std::endl;

    Person p2f = *person2.getFather();
    std::cout << "Person 2 - Name: " << p2f.name << ", Sex: " << (p2f.sex == Person::MALE ? "MALE" : "FEMALE") << std::endl;
    std::cout << "Author: " << Person::getAuthor() << std::endl;

    /*
    
    bool success = person2.setFather(&person3);
    Person p2f = *person2.getFather();
    std::cout << "Person 3 - Name: " << p2f.name << ", Sex: " << (p2f.sex == Person::MALE ? "MALE" : "FEMALE") << std::endl;
    if (success)
    {
        std::cout << "Father of person2 set successfully." << std::endl;
    }
    else
    {
        std::cout << "Failed to set the father of person2." << std::endl;
    }
    bool nullF = person2.setFather(NULL);
    if (nullF)
    {
        std::cout << "Father of person2 set successfully." << std::endl;
    }
    else
    {
        std::cout << "Failed to set the father of person2." << std::endl;
    }
   
    

    // This test will fail if no father because h file provided returns a nullptr;
    //Person p2ff = *person2.getFather();
    //std::cout << "Person 3 - Name: " << p2ff.name << ", Sex: " << (p2ff.sex == Person::MALE ? "MALE" : "FEMALE") << std::endl;
    
    success = person2.setFather(NULL);
    //p2f = *person2.getFather();
    //Person p2ff = *person2.getFather();
    //std::cout << "Person 3 - Name: " << p2ff.name << ", Sex: " << (p2ff.sex == Person::MALE ? "MALE" : "FEMALE") << std::endl;

    if (success)
    {
        std::cout << "Father of person2 set successfully." << std::endl;
    }
    else
    {
        std::cout << "Failed to set the father of person2." << std::endl;
    }
   
    */
    return 0;
}
