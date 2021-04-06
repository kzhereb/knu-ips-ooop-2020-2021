/*
 * lab_k29_2021_03_30_composite.cpp
 *
 *  Created on: Mar 30, 2021
 *      Author: KZ
 */


#include "../doctest.h"

#include <string>
#include <memory>
#include <vector>
#include <stdexcept>
#include <ostream>
#include <sstream>


class FileSystemItem {
protected:
	std::string _name;
public:
	FileSystemItem(std::string name): _name{name} {}
	std::string name() { return _name; }
	virtual int size() = 0;

	virtual void add_child(std::shared_ptr<FileSystemItem> child) {
		throw std::logic_error("Can't add children to this object");
	}

	virtual std::size_t children_count() {
		return 0;
	}
};

class File: public FileSystemItem {
private:
	int _size;
public:
	File(std::string name, int size): FileSystemItem(name), _size{size} {}
	int size() override {
		return _size;
	}
};

class Directory: public FileSystemItem {
private:
	std::vector<std::shared_ptr<FileSystemItem>> children;
public:
	Directory(std::string name): FileSystemItem(name) {}

	int size() override {
		int result = 0;
		for(std::shared_ptr<FileSystemItem> child: children) {
			result += child->size();
		}
		return result;
	}

	void add_child(std::shared_ptr<FileSystemItem> child) override {
		children.push_back(child);
	}

	std::size_t children_count() override {
		return children.size();
	}
};

TEST_CASE("working with filesystem (composite)") {
	auto root_dir = std::make_shared<Directory>("root");
	root_dir->add_child(std::make_shared<File>("config.json", 1000));
	root_dir->add_child(std::make_shared<File>("data.bin", 55000));

	auto child_dir = std::make_shared<Directory>("child");
	child_dir->add_child(std::make_shared<File>("readme.txt", 123));
	root_dir->add_child(child_dir);

	CHECK(child_dir->size() == 123);
	CHECK(root_dir->size() == 56123);
}


class LoggingFileSystemItem: public FileSystemItem {
private:
	std::shared_ptr<FileSystemItem> decorated_item;
	std::ostream& log_stream;

public:
	LoggingFileSystemItem(std::shared_ptr<FileSystemItem> decorated_item, std::ostream& log_stream) :
		FileSystemItem{decorated_item->name()}, decorated_item{decorated_item}, log_stream{log_stream} {}

		int size() override {
			log_stream<<"Getting size for "<<decorated_item->name()<<std::endl;
			int result = decorated_item->size();
			log_stream<<"Size for "<<decorated_item->name()<<" is " <<result<<std::endl;
			return result;

		}

		void add_child(std::shared_ptr<FileSystemItem> child) override {
			log_stream<<"Trying to add child "<<child->name()<<" to item "<<decorated_item->name()
					<<" with children_count = "<<decorated_item->children_count()<<std::endl;
			decorated_item->add_child(child);
			log_stream<<"Child added successfully, new children_count = "<<decorated_item->children_count()<<std::endl;
		}

		std::size_t children_count() override {
			log_stream<<"Getting children_count for "<<decorated_item->name()<<std::endl;
			std::size_t result = decorated_item->children_count();
			log_stream<<"children_count for "<<decorated_item->name()<<" is " <<result<<std::endl;
			return result;
		}

};

TEST_CASE("using decorator to log API calls") {
	std::stringstream log;
	auto root_dir_real = std::make_shared<Directory>("root");
	auto root_dir = std::make_shared<LoggingFileSystemItem>(root_dir_real, log);

	root_dir->add_child(std::make_shared<File>("config.json", 1000));
	root_dir->add_child(std::make_shared<File>("data.bin", 55000));

	auto child_dir = std::make_shared<Directory>("child");
	child_dir->add_child(std::make_shared<File>("readme.txt", 123));
	root_dir->add_child(child_dir);



	CHECK(child_dir->size() == 123);
	CHECK(root_dir->size() == 56123);

	CHECK(log.str()==std::string(
					"Trying to add child config.json to item root with children_count = 0\n"
					"Child added successfully, new children_count = 1\n"
					"Trying to add child data.bin to item root with children_count = 1\n"
					"Child added successfully, new children_count = 2\n"
					"Trying to add child child to item root with children_count = 2\n"
					"Child added successfully, new children_count = 3\n"
					"Getting size for root\n"
					"Size for root is 56123\n"));
}

