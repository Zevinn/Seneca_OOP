// Name: MinWoo Kim
// Seneca Student ID: 156417172
// Seneca email: kim3@myseneca.ca
// Date of completion: 2019.09.10
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#include <string>

#pragma once
using namespace std;
namespace sdds {
	class Text {
		static int counter;
		string* text;
	public:
		Text();
		Text(const char*);
		Text(const Text&);
		Text(Text&&);
		Text& operator=(const Text&);
		Text& operator=(Text&&);
		~Text();
		size_t size() const;};
}
