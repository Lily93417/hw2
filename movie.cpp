#include "movie.h"
#include "util.h"
#include <sstream>

using namespace std;

Movie::Movie(const std::string name, double price, int qty,
             const std::string genre, const std::string rating)
    : Product("movie", name, price, qty),
      genre_(genre),
      rating_(rating)
{
}

set<string> Movie::keywords() const
{
    set<string> keywords;

    set<string> nameWords = parseStringToWords(name_);

    keywords.insert(nameWords.begin(), nameWords.end());

    keywords.insert(convToLower(genre_));

    return keywords;
}

string Movie::displayString() const
{
    stringstream ss;

    ss << name_ << endl;
    ss << "Genre: " << genre_ << " Rating: " << rating_ << endl;
    ss << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Movie::dump(ostream& os) const
{
    Product::dump(os);
    os << genre_ << endl;
    os << rating_ << endl;
}