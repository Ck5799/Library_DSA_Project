#include <cmath>                                                      // abs(), pow()
#include <compare>                                                    // weak_ordering
#include <iomanip>                                                    // quoted()
#include <iostream>
#include <string>
#include <type_traits>                                                // is_floating_point_v, common_type_t
#include <utility>                                                    // move()

#include "Book.hpp"



/*******************************************************************************
**  Implementation of non-member private types, objects, and functions
*******************************************************************************/
namespace    // unnamed, anonymous namespace
{
    // Avoid direct equality comparisons on floating point numbers. Two values are equal if they are "close enough", which is
    // represented by Epsilon.  Usually, this is a pretty small number, but since we are dealing with money (only two, maybe three
    // decimal places) we can be a bit more tolerant.  Two floating point values are considered equal if they are within EPSILON of
    // each other.
    template< typename T, typename U >

    constexpr bool floating_point_is_equal(T const lhs, U const rhs, double const EPSILON = 1e-4) noexcept
    {

        return (abs(lhs - rhs) < EPSILON);
    }
}    // unnamed, anonymous namespace







/*******************************************************************************
**  Constructors, assignments, and destructor
*******************************************************************************/

// Default and Conversion Constructor
Book::Book(std::string title, std::string author, std::string isbn, double price)
{
    _title = title,
        _author = author,
        _isbn = isbn,
        _price = price;
}




// Copy constructor
Book::Book(Book const& other)
{
    _title = (other._title),
        _author = (other._author),
        _isbn = (other._isbn),
        _price = (other._price);

}





// Move constructor
Book::Book(Book&& other) noexcept
{
    _title = (std::move(other._title)),
        _author = (std::move(other._author)),
        _isbn = (std::move(other._isbn)),
        _price = (std::move(other._price));


}




// Copy Assignment Operator
Book& Book::operator=(Book const& rhs)&
{
    if (this != &rhs) {
        _isbn = rhs._isbn;
        _title = rhs._title;
        _author = rhs._author;
        _price = rhs._price;
    }
    return *this;

}





// Move Assignment Operator
Book& Book::operator = (Book&& rhs) & noexcept
{
    if (this != &rhs) {
        _isbn = (std::move(rhs._isbn));
        _title = (std::move(rhs._title));
        _author = (std::move(rhs._author));
        _price = (std::move(rhs._price));

    }
    return *this;

}




// Destructor
Book::~Book() noexcept
{

}






/*******************************************************************************
**  Accessors
*******************************************************************************/

// isbn() const
std::string const& Book::isbn() const&
{
    ///////////////////////// TO-DO (8) //////////////////////////////
    return _isbn;
    /////////////////////// END-TO-DO (8) ////////////////////////////
}




// title() const
std::string const& Book::title() const&
{
    ///////////////////////// TO-DO (9) //////////////////////////////
    return _title;
    /////////////////////// END-TO-DO (9) ////////////////////////////
}




// author() const
std::string const& Book::author() const&
{
    ///////////////////////// TO-DO (10) //////////////////////////////
    return _author;
    /////////////////////// END-TO-DO (10) ////////////////////////////
}



// price() const
double Book::price() const&
{
    ///////////////////////// TO-DO (11) //////////////////////////////
    return _price;
    /////////////////////// END-TO-DO (11) ////////////////////////////
}




// isbn()
std::string Book::isbn()&&
{
    ///////////////////////// TO-DO (12) //////////////////////////////
    return std::move(_isbn);
    /////////////////////// END-TO-DO (12) ////////////////////////////
}




// title()
std::string Book::title()&&
{
    ///////////////////////// TO-DO (13) //////////////////////////////
    return std::move(_title);
    /////////////////////// END-TO-DO (13) ////////////////////////////
}




// author()
std::string Book::author()&&
{
    ///////////////////////// TO-DO (14) //////////////////////////////
    return std::move(_author);
    /////////////////////// END-TO-DO (14) ////////////////////////////
}








/*******************************************************************************
**  Modifiers
*******************************************************************************/

// isbn()
Book& Book::isbn(std::string newIsbn)&
{
    ///////////////////////// TO-DO (15) //////////////////////////////
    _isbn = std::move(newIsbn);
    return *this;

    /////////////////////// END-TO-DO (15) ////////////////////////////
}




// title()
Book& Book::title(std::string newTitle)&
{
    ///////////////////////// TO-DO (16) //////////////////////////////
    _title = std::move(newTitle);
    return *this;
    /////////////////////// END-TO-DO (16) ////////////////////////////
}




// author()
Book& Book::author(std::string newAuthor)&
{
    ///////////////////////// TO-DO (17) //////////////////////////////
    _author = std::move(newAuthor);
    return *this;
    /////////////////////// END-TO-DO (17) ////////////////////////////
}




// price()
Book& Book::price(double newPrice)&
{
    ///////////////////////// TO-DO (18) //////////////////////////////
    _price = std::move(newPrice);
    return *this;
    /////////////////////// END-TO-DO (18) ////////////////////////////
}








/*******************************************************************************
**  Relational Operators
*******************************************************************************/

// operator<=>
std::weak_ordering Book::operator<=>(const Book& rhs) const noexcept
{
    // Design decision:  A very simple and convenient defaulted 3-way comparison operator
    //                         auto operator<=>( const Book & ) const = default;
    //                   in the class definition (header file) would get very close to what is needed and would allow both the <=> and
    //                   the == operators defined here to be skipped.  The physical ordering of the attributes in the class definition
    //                   would have to be changed (easy enough in this case) but the default directly compares floating point types
    //                   (price) for equality, and that should be avoided, in general. For example, if x and y are of type double,
    //                   then x < y is okay but x == y is not.  So these (operator<=> and operator==) explicit definitions are
    //                   provided.
    //
    //                   Also, many ordering (sorting) algorithms, like those used in std::map and std::set, require at least a weak
    //                   ordering of elements. operator<=> provides only a partial ordering when comparing floating point numbers.
    //
    // Weak order:       Objects that compare equal but are not substitutable (identical).  For example, since _price can be within
    //                   EPSILON, Book("Title", "Author", "ISBN", 9.99999) and Book("Title", "Author", "ISBN", 10.00001) are equal but
    //                   they are not identical.  If you ignore case when comparing strings, as another example, Book("Title") and
    //                   Book("title") are equal but they are not identical.
    //
    // See std::weak_ordering    at https://en.cppreference.com/w/cpp/utility/compare/weak_ordering and
    //     std::partial_ordering at https://en.cppreference.com/w/cpp/utility/compare/partial_ordering
    //     The Three-Way Comparison Operator at  http://modernescpp.com/index.php/c-20-the-three-way-comparison-operator
    //     Spaceship (Three way comparison) Operator Demystified https://youtu.be/S9ShnAFmiWM 
    //
    //
    // Books are equal if all attributes are equal (or within Epsilon for floating point numbers, like price). Books are ordered
    // (sorted) by ISBN, author, title, then price.

    ///////////////////////// TO-DO (19) //////////////////////////////

    if (auto result = _isbn <=> rhs._isbn; result != 0) return result;
    if (auto result = _author <=> rhs._author; result != 0) return result;
    if (auto result = _title <=> rhs._title; result != 0) return result;


    if (floating_point_is_equal(_price, rhs._price))return std::weak_ordering::equivalent;
    if (_price < rhs._price) return std::weak_ordering::less;

    else return std::weak_ordering::greater;
    /////////////////////// END-TO-DO (19) ////////////////////////////
}




// operator==
bool Book::operator==(const Book& rhs) const noexcept
{
    // All attributes must be equal for the two books to be equal to the other.  This can be done in any order, so put the quickest
    // and then the most likely to be different first.

    ///////////////////////// TO-DO (20) //////////////////////////////
    return floating_point_is_equal(_price, rhs._price)
        && _isbn == rhs._isbn
        && _title == rhs._title
        && _author == rhs._author;
    /////////////////////// END-TO-DO (20) ////////////////////////////
}








/*******************************************************************************
**  Insertion and Extraction Operators
*******************************************************************************/

// operator>>
std::istream& operator>>(std::istream& stream, Book& book)
{
    ///////////////////////// TO-DO (21) //////////////////////////////
    Book input;
    char a;
    if (stream >> std::quoted(input._isbn) >> a >> std::quoted(input._title) >> a >> std::quoted(input._author) >> a >> (input._price)) {
        book = std::move(input);
        return stream;
    }

    else
    {
        stream.setstate(std::ios::failbit);
        return stream;
    }



    /////////////////////// END-TO-DO (21) ////////////////////////////
}




// operator<<
std::ostream& operator<<(std::ostream& stream, const Book& book)
{
    ///////////////////////// TO-DO (22) //////////////////////////////
      /// This function should be symmetrical with operator>> above.  Read what your write, and write what you read

    return stream << std::quoted(book._isbn) << ", " << std::quoted(book._title) << ", " << std::quoted(book._author) << ", " << book._price;

    /////////////////////// END-TO-DO (22) ////////////////////////////
}