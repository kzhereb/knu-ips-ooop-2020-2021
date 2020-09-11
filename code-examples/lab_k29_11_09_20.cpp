#include <cstring>
#include <algorithm>
#include <iostream>

namespace lab_k29_11_09_20 {

class string
{
    char* data;

public:

	string() {
		std::cout<<"default ctor"<<std::endl;
	}

    string(const char* p)
    {
    	std::cout<<"ctor"<<std::endl;
        size_t size = std::strlen(p) + 1;
        data = new char[size];
        std::memcpy(data, p, size);
    }

    ~string()
    {
    	std::cout<<"dtor"<<std::endl;
        delete[] data;
    }

    string(const string& that)
    {
    	std::cout<<"copy"<<std::endl;
        size_t size = std::strlen(that.data) + 1;
        data = new char[size];
        std::memcpy(data, that.data, size);
    }

    string(string&& that)   // string&& is an rvalue reference to a string
    {
    	std::cout<<"move"<<std::endl;
        data = that.data;
        that.data = nullptr;
    }

    string& operator=(const string& that) {
    	std::cout<<"assign"<<std::endl;
    	delete [] data;
    	size_t size = std::strlen(that.data) + 1;
        data = new char[size];
        std::memcpy(data, that.data, size);
    	return *this;
    }

    string operator+(const string& second) {
    	char* buf = new char[std::strlen(this->data) +
    						std::strlen(second.data) + 1];
    	std::memcpy(buf, this->data, std::strlen(this->data));
    	return std::strcat(buf,second.data);
    }



    void print() {
    	std::cout<<data<<std::endl;
    }
};


int main() {
	string my_string {"hello world"};
	string copy = my_string;
	copy = my_string;
	copy.print();

	string hello {"hello"};
	//string world {"world"};
	string hw = hello + "world";
	hw.print();
	//std::cout<<my_string<<std::endl;
	return 0;
}

}
