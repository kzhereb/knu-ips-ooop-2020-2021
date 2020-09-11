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
    	std::cout<<"ctor "<<p<<std::endl;
        size_t size = std::strlen(p) + 1;
        data = new char[size];
        std::memcpy(data, p, size);
    }

    ~string()
    {
    	if (this->data) {
			std::cout<<"dtor "<<this->data<<std::endl;
			delete[] data;
    	} else {
    		std::cout<<"dtor for empty data"<<std::endl;
    	}
    }

    string(const string& that)
    {
    	std::cout<<"copy "<< that.data<<std::endl;
        size_t size = std::strlen(that.data) + 1;
        data = new char[size];
        std::memcpy(data, that.data, size);
    }

    string(string&& that)   // string&& is an rvalue reference to a string
    {
    	std::cout<<"move "<<that.data<<std::endl;
        data = that.data;
        that.data = nullptr;
        //std::cout<<"moved"<<std::endl;
    }

    string& operator=(const string& that) {
    	std::cout<<"assign "<<that.data<<std::endl;
    	delete [] data;
    	size_t size = std::strlen(that.data) + 1;
        data = new char[size];
        std::memcpy(data, that.data, size);
    	return *this;
    }

    string operator+(const string& second) {
    	std::cout<<"plus("<<this->data<<","<<second.data<<")"<<std::endl;
    	char* buf = new char[std::strlen(this->data) +
    						std::strlen(second.data) + 1];
    	std::memcpy(buf, this->data, std::strlen(this->data));
    	return std::strcat(buf,second.data);
    }

    void print() {
    	std::cout<<data<<std::endl;
    }

    friend string twice( string& value);
    friend string twice( string&& value);
};

string helloworld() {
	return "hello world";
}

// string twice(string& value)  // works, but requires copy constructor in some cases

string twice(string& value) {
	std::cout<<"twice& "<<value.data<<std::endl;
	return value + value;
}

string twice(string&& value) {
	std::cout<<"twice&& "<<value.data<<std::endl;
	return value + value;
}



int main() {
	std::cout<<"constructing and copying"<<std::endl;
	string my_string {"hello world"};
	string copy = my_string;
	copy = my_string;
	copy.print();

	std::cout<<"concat"<<std::endl;
	string hello {"hello"};
	//string world {"world"};
	string hw = hello + "world";
	std::cout<<"hw constructed"<<std::endl;
	hw.print();

	std::cout<<"function"<<std::endl;
	helloworld().print();
	(helloworld()+"!").print();

	std::cout<<"constructing from temporary"<<std::endl;
	string hw2{helloworld()};
	hw2.print();

	std::cout<<"calling function and passing string"<<std::endl;
	twice(hello).print();
	twice("world").print();
	twice(hello+" world ").print();

	return 0;
}

}
