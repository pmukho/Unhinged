//main.cpp

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>

#include "RadixTree.h"

const std::string MEMBERS_FILE    = "members.txt";
const std::string TRANSLATOR_FILE = "translator.txt";

//bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);

//int main() {
//    //MemberDatabase mdb;
//    //if (!mdb.LoadDatabase(MEMBERS_FILE))
//    //{
//    //    std::cout << "Error loading " << MEMBERS_FILE << std::endl;
//    //    return 1;
//    //}
//    //AttributeTranslator at;
//    //if (!at.Load(TRANSLATOR_FILE))
//    //{
//    //    std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
//    //    return 1;
//    //}
//
//    //while (findMatches(mdb, at))
//    //    ;
//
//    //std::cout << "Happy dating!" << std::endl;
//}

//bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
//{
//      // Prompt for email
//    std::string email;
//    const PersonProfile* pp;
//    for (;;) {
//        std::cout << "Enter the member's email for whom you want to find matches: ";
//        std::getline(std::cin, email);
//        if (email.empty())
//            return false;
//        pp = mdb.GetMemberByEmail(email);
//        if (pp != nullptr)
//            break;
//        std::cout << "That email is not in the member database." << std::endl;
//    }
//
//      // Show member's attribute-value pairs
//    std::cout << "The member has the following attributes:" << std::endl;
//    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
//        AttValPair av;
//        pp->GetAttVal(k, av);
//        std::cout << av.attribute << " --> " << av.value << std::endl;
//    }
//
//      // Prompt user for threshold
//    int threshold;
//    std::cout << "How many shared attributes must matches have? ";
//    std::cin >> threshold;
//    std::cin.ignore(10000, '\n'); 
//
//      // Print matches and the number of matching translated attributes
//    MatchMaker mm(mdb, at);
//    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
//    if (emails.empty())
//        std::cout << "No member was a good enough match." << std::endl;
//    else {
//        std::cout << "The following members were good matches:" << std::endl;;
//        for (const auto& emailCount : emails) {
//            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
//            std::cout << pp->GetName() << " at " << emailCount.email << " with "
//                      << emailCount.count << " matches!" << std::endl;
//        }
//    }
//    std::cout << std::endl;
//    return true;
//}

int main()
{
	//TESTING RadixTree
	RadixTree<std::string> rt;
	rt.insert("Georgia", "Atlanta");
	rt.insert("California", "San Diego");
	rt.insert("California", "Los Angeles");
	std::cout << *rt.search("California") << std::endl;

	RadixTree<AttValPair> rt2;
	rt2.insert("howdy", AttValPair("trait", "racist"));
	rt2.insert("hello", AttValPair("trait", "basic"));
	rt2.insert("hello", AttValPair("trait", "boring"));
	AttValPair* av = rt2.search("hello");
	std::cout << av->attribute << " => " << av->value << std::endl;

	std::cout << "========================" << std::endl;

	//TESTING PersonProfile
	PersonProfile pp1("Billy", "bbob@gmail.com");
	std::cout << pp1.GetName() << ", " << pp1.GetEmail() << std::endl;
	pp1.AddAttValPair(AttValPair("hobby", "gambling"));
	pp1.AddAttValPair(AttValPair("hobby", "gambling"));
	pp1.AddAttValPair(AttValPair("trait", "fabulous"));
	pp1.AddAttValPair(AttValPair("hobby", "running"));
	for (int i = 0; i != pp1.GetNumAttValPairs(); i++) {
		AttValPair av;
		pp1.GetAttVal(i, av);
		std::cout << av.attribute << " => " << av.value << std::endl;
	}

	std::cout << "========================" << std::endl;

	/*PersonProfile pp2("Joe", "jbru@yahoo.com");
	pp2.AddAttValPair(AttValPair("job", "dealer"));
	PersonProfile pp3("Sam", "ssmith@gmail.com");
	pp3.AddAttValPair(AttValPair("hobby", "pigeon_racing"));
	RadixTree<PersonProfile*> rt3;
	rt3.insert(pp1.GetEmail(), new PersonProfile(pp1));
	rt3.insert(pp2.GetEmail(), new PersonProfile(pp2));
	rt3.insert(pp2.GetEmail(), new PersonProfile(pp1));
	rt3.insert(pp3.GetEmail(), new PersonProfile(pp3));
	std::cout << (**(rt3.search(pp2.GetEmail()))).GetName() << std::endl;
	std::cout << "========================" << std::endl;*/
	//Lesson here is to not have a RadixTree of a type without a copy constructor, ValueType is a pointer type

	//TESTING MemberDatabase
	MemberDatabase md;
	if (md.LoadDatabase("members.txt")) std::cout << "MemberDatabase Load Success" << std::endl;
	else std::cout << "MemberDatabase Load Fail" << std::endl;
	const PersonProfile* ppMD = md.GetMemberByEmail("ELand@live.com");
	std::cout << ppMD->GetName() << ", " << ppMD->GetEmail() << std::endl;
	/*std::vector<std::string> matchesPPMD = md.FindMatchingMembers(AttValPair("job", "architect"));
	for (auto it = matchesPPMD.begin(); it != matchesPPMD.end(); it++) {
		const PersonProfile* ppTemp = md.GetMemberByEmail(*it);
		std::cout << ppTemp->GetName() << ", " << ppTemp->GetEmail() << std::endl;
	}*/

	std::cout << "========================" << std::endl;

	//Testing AttributeTranslator
	AttributeTranslator at;
	if (at.Load("translator.txt")) std::cout << "AttributeTranslator Load Success" << std::endl;
	else std::cout << "AttributeTranslator Load Fail" << std::endl;
	std::vector<AttValPair> compatibleAttVals = at.FindCompatibleAttValPairs(AttValPair("job", "engineer"));
	for (auto it = compatibleAttVals.begin(); it != compatibleAttVals.end(); it++) {
		std::cout << it->attribute << " => " << it->value << std::endl;
	}

	std::cout << "========================" << std::endl;
}
