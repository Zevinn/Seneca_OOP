// Workshop 5 - Functions and Error Handling
// 2019/10 - Cornel

// Name: MinWoo Kim
// Seneca Student ID: 156417172
// Seneca email: kim3@myseneca.ca
// Date of completion: 2019.10.12
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#include <exception>

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Collection.h"
#include "Collection.h"
#include "Book.h"
#include "Book.h"
#include "Movie.h"
#include "Movie.h"
#include "SpellChecker.h"
#include "SpellChecker.h"

using namespace sdds;

// The observer function for adding books to the collection:
//   should be called every time a new book is added to the collection
void bookAddedObserver(const Collection<Book>& theCollection,
	const Book& theBook)
{
	std::cout << "Book \"" << theBook.title() << "\" added!\n";
}

// The observer function for adding movies to the collection:
//   should be called every time a new movie is added to the collection
void movieAddedObserver(const Collection<Movie>& theCollection,
	const Movie& theMovie)
{
	std::cout << "Movie \"" << theMovie.title()
		<< "\" added to collection \"" << theCollection.name()
		<< "\" (" << theCollection.size() << " items).\n";
}

// ws books.txt movies.txt file_missing.txt file_words.txt
int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	// get the book
	sdds::Collection<sdds::Book> library("Bestsellers");
	{
		// TODO: load the first 4 books from the file "argv[1]".
		//       - read one line at a time, and pass it to the Book constructor
		//       - store each book read into the collection "library" (use the += operator)
		//       - lines that start with "#" are considered comments and should be ignored
		std::ifstream file(argv[1]);
		sdds::Book **bookP = nullptr;
		size_t cnt = 0;
		std::string tempBook;
		size_t i = 0;
		do {
			std::getline(file, tempBook);
			if (file) {
				if (tempBook[0] != '#') ++cnt;
			}
		} while (file);

		bookP = new sdds::Book*[cnt];
		

		file.clear();
		file.seekg(std::ios::beg); // I don't know what they are, just assume that this would reset reading status of the file.

		do {
			std::getline(file, tempBook);
			if (file) {
				if (tempBook[0] != '#') {
					bookP[i] = new sdds::Book(tempBook);
					library += tempBook;
					i++;
				}
			}

		} while (i < 4);


		library.setObserver(bookAddedObserver);

		// TODO: add the rest of the books from the file.
		do {
			std::getline(file, tempBook);
			bookP[i] = new sdds::Book(tempBook);
			library += tempBook;
			if (file) {
				if (tempBook[0] != '#') i++;
			}
		} while (i < cnt);

		file.close();
	}

	double usdToCadRate = 1.3;
	double gbpToCadRate = 1.5;

	// TODO: (from in-lab) create a lambda expression that fixes the price of a book accoding to the rules
	//       - the expression should receive a single parameter of type "Book&"
	auto fix = [&](Book& src) {
		//       - if the book was published in US, multiply the price with "usdToCadRate"
		//            and save the new price in the book object
		if (src.country() == "US") {
			src.price() = src.price() * usdToCadRate;
		}
		//       - if the book was published in UK between 1990 and 1999 (inclussive),
		//            multiply the price with "gbpToCadRate" and save the new price in the book object
		if (src.country() == "UK" && (src.year() >= 1990 && src.year() <= 1999)) {
			src.price() = src.price() * gbpToCadRate;
		}

	};

	std::cout << "-----------------------------------------\n";
	std::cout << "The library content\n";
	std::cout << "-----------------------------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n\n";

	// TODO (from in-lab): iterate over the library and update the price of each book
	//         using the lambda defined above.
	for (int i = 0; i < 7; i++) {
		fix(library[i]);
	}

	std::cout << "-----------------------------------------\n";
	std::cout << "The library content (updated prices)\n";
	std::cout << "-----------------------------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n\n";

	Collection<Movie> theCollection("Action Movies");

	// Process the file
	Movie movies[5];
	{
		// TODO: load 5 movies from the file "argv[2]".
		//       - read one line at a time, and pass it to the Movie constructor
		//       - store each movie read into the array "movies"
		//       - lines that start with "#" are considered comments and should be ignored
		std::ifstream file2(argv[2]);
		sdds::Movie **movieP = nullptr;
		std::string tempmovie;

		movieP = new sdds::Movie*[5];
		int i = 0;
		do {
			std::getline(file2, tempmovie);
			movieP[i] = new sdds::Movie(tempmovie);
			movies[i] = tempmovie;
			if (file2) {
				if (tempmovie[0] != '#') {
					i++;
				}
			}
		} while (i < 5);

		file2.close();

		std::cout << "-----------------------------------------\n";
		std::cout << "Testing addition and callback function\n";
		std::cout << "-----------------------------------------\n";
		// Add a few movies to collection; no observer is set
		((theCollection += movies[0]) += movies[1]) += movies[2];
		theCollection += movies[1];
		// add more movies; now we get a callback from the collection
		theCollection.setObserver(movieAddedObserver);
		theCollection += movies[3];
		theCollection += movies[3];
		theCollection += movies[4];
		std::cout << "-----------------------------------------\n\n";

		std::cout << "-----------------------------------------\n";
		std::cout << "Testing exceptions and operator[]\n";
		std::cout << "-----------------------------------------\n";

		// TODO: The following loop can generate generate an exception
		//         write code to handle the exception
		//       If an exception occurs print a message in the following format
		//EXCEPTION: ERROR_MESSAGE<endl>
		//         where ERROR_MESSAGE is extracted from the exception object.
		try {
			for (auto i = 0u; i < 10; ++i)
				std::cout << theCollection[i];
		}
		catch (std::exception& err) {
			std::cout << "EXCEPTION: " << err.what() << std::endl;
		}

		std::cout << "-----------------------------------------\n\n";


		std::cout << "-----------------------------------------\n";
		std::cout << "Testing the functor\n";
		std::cout << "-----------------------------------------\n";
		for (auto i = 3u; i <= 4u; ++i)
		{
			// TODO: The following statement can generate generate an exception
			//         write code to handle the exception
			//       If an exception occurs print a message in the following format
			//EXCEPTION: ERROR_MESSAGE<endl>
			//         where ERROR_MESSAGE is extracted from the exception object.
			try {
				SpellChecker sp(argv[i]);
				for (auto j = 0u; j < theCollection.size(); ++j)
					theCollection[j].fixSpelling(sp);
				for (auto j = 0u; j < library.size(); ++j)
					library[j].fixSpelling(sp);
			}
			catch (std::exception& e) {
				std::cout << "EXCEPTION: " << e.what() << std::endl;
			}

		}
		std::cout << "--------------- Movies ------------------\n";
		std::cout << theCollection;
		std::cout << "--------------- Books -------------------\n";
		std::cout << library;
		std::cout << "-----------------------------------------\n\n";


		std::cout << "-----------------------------------------\n";
		std::cout << "Testing operator[] (the other overload)\n";
		std::cout << "-----------------------------------------\n";
		const Movie* aMovie = theCollection["Terminator 2"];
		if (aMovie == nullptr)
			std::cout << "Movie Terminator 2 not in collection.\n";
		aMovie = theCollection["Dark Phoenix"];
		if (aMovie != nullptr)
			std::cout << "In collection:\n" << *aMovie;
		std::cout << "-----------------------------------------\n\n";

		return 0;
	}
}
